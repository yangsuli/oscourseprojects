#include "mem.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

struct malloc_chunk{
	size_t prev_size;  /*size of previous chunk, if free*/
	size_t head; /*size and inuse bit*/
	struct malloc_chunk *fd;
	struct malloc_chunk *bk;
};

#define PREV_USE_BIT 0x01
#define NEXT_USE_BIT 0x02
#define ADDR_MASK 0x03
#define prev_in_use(head) (head & PREV_USE_BIT)
#define next_in_use(head) (head & NEXT_USE_BIT)
#define set_next_use(head) (head = head | PREV_USE_BIT)
#define set_prev_use(head) (head = head | NEXT_USE_BIT)
#define clr_next_use(head) (head = head & (~PREV_USE_BIT))
#define clr_prev_use(head) (head = head & (~NEXT_USE_BIT))
#define get_size(head) (head & (~ADDR_MASK))
#define get_use(head) (head & ADDR_MASK)

#define FREE_PATTERN 0xDEADBEEF
#define PAD_PATTERN 0xABCDDCBA
#define PAD_SIZE 64
#define ALIGN_SIZE 4
#define MAGIC_POINTER 0x0000001

#define unlink(P,BK,FD) {\
	BK = P -> bk;\
	FD = P -> fd;\
	FD -> bk = BK;\
	BK -> fd = FD;\
}

#define insert(P) {\
	P -> bk = top;\
	P -> fd = top -> fd;\
	top -> fd = P;\
	P -> fd -> bk = P;\
}

/*
#define unlink(P) {\
P -> bk -> fd = P -> fd; \
P -> fd -> bk = P -> bk; \
}
 */

int m_error;
int m_debug;
struct malloc_chunk * top; //head of our free list
struct malloc_chunk * tail;
size_t heap_size;

struct malloc_chunk *p;
struct malloc_chunk *q; //p and q are just some temp variables to do unlink

int check_written_pattern(struct malloc_chunk *ptr);

int Mem_Init(int sizeOfRegion, int debug) {
	static int times = 0;
	//check arguments, round up if necessary
	if(sizeOfRegion <= 0){
		m_error = E_BAD_ARGS;
		return -1;
	}else if(debug != 0 && debug != 1){
		m_error = E_BAD_ARGS;
		return -1;
	}else{
		int page_size = getpagesize();
		sizeOfRegion = (sizeOfRegion%page_size == 0) ? sizeOfRegion : (sizeOfRegion/page_size + 1) * page_size;
	}

	if(times > 0){
		return -1;
	}

	m_debug = debug;
	heap_size = sizeOfRegion;

	// open the /dev/zero device
	int fd = open("/dev/zero", O_RDWR);

	if (fd == -1){
		/*	fprintf(stderr,"open /dev/zero error!\n"); */
		return -1;
	}
	// sizeOfRegion (in bytes) needs to be evenly divisible by the page size
	void *ptr = mmap(NULL, sizeOfRegion, 
			PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (ptr == MAP_FAILED) {
		return -1;
	}

	//set up the memory we got
	top = (struct malloc_chunk *)ptr;
	tail = (struct malloc_chunk *)((char *)top + heap_size - sizeof(struct malloc_chunk));
	tail -> fd = top;
	top -> bk = tail;
	//size of the top and tail chunks would always be 0, and it's always free, to simplify our free list
	top -> fd = (struct malloc_chunk *)((char*) top + sizeof(struct malloc_chunk));
	tail -> bk = top -> fd;
	top -> prev_size = 0;
	top -> head = 0;
	tail -> prev_size = top -> fd -> head = sizeOfRegion - 3 * sizeof(struct malloc_chunk);
	top -> fd -> fd = tail;
	top -> fd -> bk = top;
	top -> fd -> prev_size = 0;


	if(m_debug != 0){//debug mode
		//fill all free memory with a well-know patter
		int i = 2 * sizeof(struct malloc_chunk);
		for (; i < 2 * sizeof(struct malloc_chunk) + PAD_SIZE; i += sizeof(PAD_PATTERN)){
			*(unsigned int *)((char *)top + i) = PAD_PATTERN;
		}

		for (; i < sizeOfRegion - sizeof(struct malloc_chunk) - PAD_SIZE; i += sizeof(FREE_PATTERN)){ 
			*(unsigned int *)((char *)top + i) = FREE_PATTERN;
		}

		for (; i < sizeOfRegion - sizeof(struct malloc_chunk); i += sizeof(PAD_PATTERN)){
			*(unsigned int *)((char *)top + i) = PAD_PATTERN;
		}
	}

	// close the device (don't worry, mapping should be unaffected)
	close(fd);
	times++;
	return 0;
}

void write_free_pattern(struct malloc_chunk *ptr){

	int i =  sizeof(struct malloc_chunk);
	for (; i < sizeof(struct malloc_chunk) + PAD_SIZE; i += sizeof(PAD_PATTERN)){
		*(unsigned int *)((char *)ptr + i) = PAD_PATTERN;
	}

	for (; i < sizeof(struct malloc_chunk) + get_size(ptr -> head) - PAD_SIZE; i += sizeof(FREE_PATTERN)){ 
		*(unsigned int *)((char *)ptr + i) = FREE_PATTERN;
	}

	for (; i < sizeof(struct malloc_chunk) + get_size(ptr -> head); i += sizeof(PAD_PATTERN)){
		*(unsigned int *)((char *)ptr + i) = PAD_PATTERN;
	}
}

int check_free_pattern(struct malloc_chunk *ptr){
	//for chunk doesn't have that much space to store debug info
	if ( get_size(ptr -> head) < 2 * PAD_SIZE){
		return 0;
	}

	int i = 0;
	for(; i < PAD_SIZE; i+= sizeof(PAD_PATTERN)){
		if(*(unsigned int *)((char *)ptr + sizeof(struct malloc_chunk) + i) != PAD_PATTERN){
			return -1;
		}
	}

	for(; i < get_size(ptr -> head) - PAD_SIZE; i+=sizeof(FREE_PATTERN)){
		if(*(unsigned int *)((char *)ptr + sizeof(struct malloc_chunk) + i) != FREE_PATTERN){
			return -1;
		}
	}

	for(; i < get_size(ptr -> head); i += sizeof(PAD_PATTERN)){
		if(*(unsigned int *)((char *)ptr + sizeof(struct malloc_chunk) + i) != PAD_PATTERN){
			return -1;
		}
	}

	return 0;
}


void *Mem_Alloc(int size) 
{
	if(size <= 0){
		return NULL;
	}

	int real_size;
	if(m_debug == 0){
		real_size = size;
	}else{
		real_size = size + 2 * PAD_SIZE;
	}
	int aligned_size;

	aligned_size = (real_size%ALIGN_SIZE == 0 )? real_size : (real_size/ALIGN_SIZE + 1)*ALIGN_SIZE;

	//search Best Fit in free list
	struct malloc_chunk * bf = top;
	struct malloc_chunk * curr = top -> fd;
	while (curr != top){
		if(m_debug != 0){//debug mode
			if(check_free_pattern(curr) == -1){
				m_error = E_CORRUPT_FREESPACE;
				return NULL;
			}
		}
		if( bf == top){
			if(get_size(curr -> head) >= aligned_size){
				bf = curr;
			}
		}else{
			if(get_size(curr -> head) >= aligned_size && get_size(curr -> head) < get_size(bf -> head) ){
				bf = curr;
			}	
		}
		curr = curr -> fd;
	}

	if(bf == top){ //no enough contiguous memory
		m_error = E_NO_SPACE;
		return NULL;
	}

	struct malloc_chunk * prev;
	struct malloc_chunk * next;
	prev = (struct malloc_chunk *)((char *)bf - (bf -> prev_size) - sizeof(struct malloc_chunk));
	next = (struct malloc_chunk *)((char *)bf + sizeof(struct malloc_chunk) + get_size(bf -> head));
	if((get_size(bf -> head) - aligned_size) <= sizeof(struct malloc_chunk)){
		unlink(bf,p,q);
		set_next_use(prev -> head);
		set_prev_use(next -> head);
		if(m_debug != 0){
			bf -> fd = (struct malloc_chunk *)MAGIC_POINTER;
			return (void *)((char *)(bf + 1) + PAD_SIZE);
		}
		return (void *)(bf + 1);
	}else{
		unlink(bf,p,q);
		struct malloc_chunk *remainder = (struct malloc_chunk *)((char *)bf + sizeof(struct malloc_chunk) + aligned_size);
		remainder -> head = get_size(bf -> head) - aligned_size - sizeof(struct malloc_chunk);
		set_prev_use(remainder -> head);
		next_in_use(bf -> head) ? set_next_use(remainder -> head):0;
		clr_next_use(bf -> head);
		clr_prev_use(next -> head);
		remainder -> prev_size = aligned_size;
		next -> prev_size = get_size(remainder -> head);
		insert(remainder);
		bf -> head = aligned_size | get_use (bf -> head);
		if(m_debug != 0){
			if(get_size(remainder -> head) >= 2*PAD_SIZE){
				int i = 0;
				for(; i<PAD_SIZE; i+=sizeof(PAD_PATTERN)){
					*(unsigned *)((char *)remainder + sizeof(struct malloc_chunk) + i) = PAD_PATTERN;
				}
			}
			int j = 0;
			for(; j<PAD_SIZE; j+=sizeof(PAD_PATTERN)){
				*(unsigned *)((char *)bf + sizeof(struct malloc_chunk) + get_size(bf -> head) - PAD_SIZE + j) = PAD_PATTERN;
			}
			bf -> fd = (struct malloc_chunk *)MAGIC_POINTER;
			return (void *)((char *)(bf + 1) + PAD_SIZE);
		}
		return (void *)(bf+1);
	}

	//should not get here
	return NULL;
}

int Mem_Free(void *ptr) {
	if( ptr == NULL){
		return 0;
	}

	struct malloc_chunk * m_ptr;
	if(m_debug == 0){
		m_ptr = (struct malloc_chunk *)((char *)ptr - sizeof(struct malloc_chunk));
	}else{
		m_ptr = (struct malloc_chunk *)((char *)ptr - sizeof(struct malloc_chunk) - PAD_SIZE);
	}

	if(m_debug != 0){//check whether padding has been overwritten
		if(m_ptr -> fd != (struct malloc_chunk *)MAGIC_POINTER){
			m_error = E_BAD_POINTER;
			return -1;
		}
		if(check_written_pattern(m_ptr) == -1){
			m_error = E_PADDING_OVERWRITTEN;
			return -1;
		}
	}


	struct malloc_chunk * prev = (struct malloc_chunk *)((char *)m_ptr - m_ptr -> prev_size - sizeof(struct malloc_chunk));
	struct malloc_chunk * next = (struct malloc_chunk *)((char *)m_ptr + get_size(m_ptr->head) + sizeof(struct malloc_chunk));

	if ( next_in_use( m_ptr -> head) == 0 && next != tail){
		unlink(next,p,q);
		m_ptr -> head += (get_size(next -> head) + sizeof(struct malloc_chunk));           
		if(next_in_use(next -> head) == 0){
			clr_next_use(m_ptr -> head);
		}else{
			set_next_use(m_ptr -> head);
		}
	}else{
		clr_prev_use(next -> head);
	}

	if ( prev_in_use( m_ptr -> head) == 0 && prev != top){
		prev -> head += (get_size(m_ptr -> head) + sizeof(struct malloc_chunk));
		if(next_in_use(m_ptr -> head) == 0){
			clr_next_use( prev -> head);
		}else{ 
			set_next_use (prev -> head);
		}
		unlink(prev,p,q);
		m_ptr = prev;
	}else{
		clr_next_use( prev -> head);
	}

	insert(m_ptr);
	if( m_debug != 0){
	write_free_pattern(m_ptr);
	}

	//return -1;
	return 0;
}

void Mem_Dump(){
	int i = 0;
	for(; i < heap_size; i += sizeof(FREE_PATTERN)){
		fprintf(stdout,"%08x",*(unsigned int *)((char*)top + i));
	}
}
/*
int main(){
	fprintf(stdout,"%d %d\n",sizeof(FREE_PATTERN),sizeof(double));
	Mem_Init(3,1);
	fprintf(stdout,"%p %d %d %p %p\n",top,top->prev_size,top->head,top->fd,top->bk);
	double * p = Mem_Alloc(7);
	* p = 0;
	Mem_Dump();
	Mem_Free(p);
	fprintf(stdout, "yangsuli\n");
	Mem_Dump();

	return 0;
}
*/
int check_written_pattern(struct malloc_chunk *ptr){

	int i = 0;
	for(; i < PAD_SIZE; i+= sizeof(PAD_PATTERN)){
		if(*(unsigned int *)((char *)ptr + sizeof(struct malloc_chunk) + i) != PAD_PATTERN){
			return -1;
		}
	}

	for(; i < get_size(ptr -> head) - PAD_SIZE; i+=sizeof(FREE_PATTERN)){
	}

	for(; i < get_size(ptr -> head); i += sizeof(PAD_PATTERN)){
		if(*(unsigned int *)((char *)ptr + sizeof(struct malloc_chunk) + i) != PAD_PATTERN){
			return -1;
		}
	}

	return 0;
}

