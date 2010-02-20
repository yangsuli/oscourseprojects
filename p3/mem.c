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

#define FD_USE_BIT 0x01
#define BK_USE_BIT 0x02
#define TOP_BIT 0x04
#define ADDR_MASK 0x07
#define is_top(head) (head & TOP_BIT)
#define set_top(head) head = head | TOP_BIT;
#define fd_in_use(head) (head & FD_USE_BIT)
#define bk_in_use(head) (head & BK_USE_BIT)
#define set_fd_use(head) head = head | FD_USE_BIT;
#define set_bk_use(head) head = head | BK_USE_BIT;
#define clr_fd_use(head) head = head & (~FD_USE_BIT);
#define clr_bk_use(head) head = head & (~BK_USE_BIT);
#define get_size(head) (head & (~ADDR_MASK))

#define FREE_PATTERN 0xDEADBEEF
#define PAD_PATTERN 0xABCDDCBA
#define ALIGN_SIZE 4

#define unlink(P,BK,FD) {\
	BK = P -> bk;\
	FD = P -> fd;\
	FD -> bk = BK;\
	BK -> fd = FD;\
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
size_t heap_size;

struct malloc_chunk *p;
struct malloc_chunk *q;

int Mem_Init(int sizeOfRegion, int debug) {
	static int times = 0;
	//check arguments, round up if necessary
	if(sizeOfRegion <= 0){
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
	set_top(top -> head);  //size of the top chunk would always be 0, and it's always free, to simplify our free list
	top -> bk = top -> fd = (struct malloc_chunk *)((char*) top + sizeof(struct malloc_chunk));
	top -> prev_size = top -> fd -> head = sizeOfRegion - 2 * sizeof(struct malloc_chunk);
	top -> fd -> fd = top -> fd -> bk = top;
	top -> fd -> prev_size = 0;

	if(m_debug != 0){//debug mode
		//fill all free memory with a well-know patter
		int i = 2 * sizeof(struct malloc_chunk);
		for (; i < sizeOfRegion; i += sizeof(FREE_PATTERN)){
				*(unsigned int *)((char *)top + i) = FREE_PATTERN;
		}
	}

	// close the device (don't worry, mapping should be unaffected)
	close(fd);
	times++;
	return 0;
}

void *Mem_Alloc(int size) 
{
	int aligned_size;

	if(size <= 0){
		return NULL;
	}else{
		aligned_size = size%ALIGN_SIZE == 0 ? size : (size/ALIGN_SIZE + 1)*ALIGN_SIZE;
	}

	//search Best Fit in free list
	return NULL;
}

	int 
Mem_Free(void *ptr) 
{
	return -1;
}

void Mem_Dump(){
	int i = 0;
	for(; i < heap_size; i += sizeof(FREE_PATTERN)){
		fprintf(stdout,"%08x",*(unsigned int *)((char*)top + i));
	}
}

int main(){
	fprintf(stdout,"%d %d\n",sizeof(FREE_PATTERN),sizeof(struct malloc_chunk));
	Mem_Init(3,1);
	unlink(top->fd,p,q);
	fprintf(stdout,"%p %d %d %p %p\n",top,top->prev_size,top->head,top->fd,top->bk);
	Mem_Dump();
	
	return 0;
}
