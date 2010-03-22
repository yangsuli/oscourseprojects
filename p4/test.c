#include <stdio.h>
#include "lock_type.h"
#include "counter.h"
#include "list.h"


int main(){
	counter_t c;
	Counter_Init(&c,0);
	Counter_Increment(&c);
	printf("%d\n",Counter_GetValue(&c));

	list_t *slist;
	slist=malloc(sizeof(slist));
	List_Init(slist);

	int *a = malloc(sizeof(int));
	*a=3002;
	List_Insert(slist,a,1);
	List_Insert(slist,a,2);
	//printf("%d\n",*((int*)List_Lookup(slist,1)));
	int *b = List_Lookup(slist,1);
	printf("%d\n",*b);
	List_Destroy(slist);

	free(a);

	return 0;
}
