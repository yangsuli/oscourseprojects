#ifndef __hash_h__
#define __hash_h__

#include "list.h"
#include "lock_type.h"

typedef struct __hash_t {
	int num_buckets;
	list_t **table;
	LOCK_TYPE *locks; //one lock per bucket
} hash_t;

void Hash_Init(hash_t *h, int numbuckets);
void Hash_Insert(hash_t *h, void *element, unsigned int key);
void Hash_Remove(hash_t *h, unsigned int key);
void* Hash_Lookup(hash_t *h, unsigned int key);

#endif // __hash_h__

