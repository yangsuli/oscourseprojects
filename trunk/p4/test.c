#include <stdio.h>
#include "lock_type.h"
#include "counter.h"
#include "list.h"
#include "hash.h"
#include <assert.h>
#include <sys/time.h>
#include <pthread.h>

#define MAX_LOOP 1E6
#define MAX_THREADS 20

double GetTime(){
	struct timeval t;
	int rc = gettimeofday(&t,NULL);
	assert(rc==0);
	return t.tv_sec + t.tv_usec/1e6; 
}

counter_t c;

void * counter_test(void *arg){
	int i;
	for(i = 0; i < MAX_LOOP; i++){
		Counter_Increment(&c);
	}

	return NULL;
}

int main(){
	int num_threads;
	int loop;
	pthread_t tid[MAX_THREADS];
	double t1, t2;
	int i, j;
	//compare counter performance
	for(num_threads = 1; num_threads <= MAX_THREADS; num_threads++){
		t1 = GetTime();
		Counter_Init(&c,0);
		for(i = 0; i < num_threads; i++){//create threads
			assert(pthread_create(&(tid[i]),NULL,counter_test,NULL) == 0);
		}
		for(j = 0; j < num_threads; j++){//join  threads
			//note that here we in turn join each thread. So if tid[2] finishes earlier than tid[1], it still has to wait until tid[1] finishes to be joined.
			assert(pthread_join(tid[j],NULL) == 0);
		}
		Counter_Destroy(&c);
		t2 = GetTime();
		printf("Counter test: %d threads, %f seconds consumed\n",num_threads,t2-t1);
	}
}

	
/*
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
}*/
