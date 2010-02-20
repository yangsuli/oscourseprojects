#include "mem.h"
#include <stdio.h>

struct malloc_chunk{
	size_t prev_chunk;  /*size of previous chunk, if free*/
	size_t head; /*size and inuse bit*/
	struct malloc_chunk *fd;
	struct malloc_chunk *bk;
};

#define FD_USE_BIT 0x01
#define BK_USE_BIT 0x02
#define ADDR_MASK 0x07
#define fd_in_use(head) (head & FD_USE_BIT)
#define bk_in_use(head) (head & BK_USE_BIT)
#define set_fd_use(head) head = head | FD_USE_BIT;
#define set_bk_use(head) head = head | BK_USE_BIT;
#define clr_fd_use(head) head = head & (~FD_USE_BIT);
#define clr_bk_use(head) head = head & (~BK_USE_BIT);
#define get_size(head) (head & (~ADDR_MASK))


int main(){
	fprintf(stdout,"%d\n",sizeof(struct malloc_chunk));
	int a = 0x01;
	fprintf(stdout,"%d\n",fd_in_use(a));
	fprintf(stdout,"%d\n",bk_in_use(a));
	set_bk_use(a);
	clr_fd_use(a);
	fprintf(stdout,"%d\n",a);
	fprintf(stdout,"%d\n",get_size(a));
	return 0;
}
