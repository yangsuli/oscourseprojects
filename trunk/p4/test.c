#include <stdio.h>
#include "lock_type.h"
#include "counter.h"


int main(){
	counter_t c;
	Counter_Init(&c,0);
	Counter_Increment(&c);
	printf("%d\n",Counter_GetValue(&c));
	return 0;
}
