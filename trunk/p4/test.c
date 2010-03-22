#include <stdio.h>
#include "lock_type.h"
#include "counter.h"
#include "list.h"
#include "hash.h"
#include <assert.h>


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
	int *d = List_Lookup(slist,1);
	printf("%d\n",*d);
	List_Destroy(slist);
	free(a);
	
	hash_t *h = malloc(sizeof(hash_t));
	assert(h!=NULL);
	Hash_Init(h,5);
	int *b = malloc(sizeof(int));
	*b = 199;
	Hash_Insert(h,b,137);
	int *f = Hash_Lookup(h,137);
	printf("%d\n",*f);
	Hash_Remove(h,137);
	int *e = Hash_Lookup(h,137);
	printf("%d\n",e);


	Hash_Destroy(h);

	return 0;
}
