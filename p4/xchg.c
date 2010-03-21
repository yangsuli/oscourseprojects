#include <stdlib.h>
#include <stdio.h>

static inline uint
xchg(volatile unsigned int *addr, unsigned int newval)
{
    uint result;
    asm volatile("lock; xchgl %0, %1" : "+m" (*addr), "=a" (result) : "1" (newval) : "cc");
    return result;
}

int main(){
	unsigned int a = 0;
	unsigned int b = 1;
	printf("%d\n",xchg(&a,b));
	printf("a=%d\n",a);
	return 0;
}
