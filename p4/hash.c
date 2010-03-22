#include "hash.h"
#include "lock_type.h"
#include <assert.h>

#define HASH(key,n_buckets) (key%n_buckets)

void Hash_Init(hash_t *h, int numbuckets){
	int i;
	h -> num_buckets = numbuckets;
	h -> table = (list_t **)malloc(sizeof(list_t *) * numbuckets);
	assert(h -> table != NULL);
	for(i = 0; i < numbuckets; i++){
		h -> table[i] = (list_t *)malloc(sizeof(list_t));
		assert( h -> table[i] != NULL);
		List_Init(h -> table[i]);
	}
}

void Hash_Insert(hash_t *h, void *element, unsigned int key){
	//int idx = key % h -> num_buckets;
	int idx = HASH(key,h->num_buckets);
	List_Insert(h -> table[idx], element, key);
}

void* Hash_Lookup(hash_t *h, unsigned int key){
	int idx = HASH(key,h->num_buckets);
	return List_Lookup(h->table[idx],key);
}

void Hash_Remove(hash_t *h, unsigned int key){
	int idx = HASH(key,h->num_buckets);
	List_Remove(h->table[idx],key);
}

void Hash_Destroy(hash_t *h){
	int i;
	for(i = 0; i < h -> num_buckets; i++){
		List_Destroy( h -> table[i]);
		free( h -> table[i] );
	}
	free(h->table);
}
