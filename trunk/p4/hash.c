#include "hash.h"
#include "lock_type.h"
#include <assert.h>

void Hash_Init(hash_t *h, int numbuckets){
	hast_h h;
	h -> num_buckets = numbuckets;
	h -> table = (list_t **)malloc(sizeof(list_t *) * num_buckets);
	assert(h -> table != NULL);
	for(int i = 0; i < num_buckets; i++){
		h -> table[i] = (list_t *)malloc(sizeof(list_t));
	}
	h -> locks = (LOCK_TYPE *)malloc(sizeof(LOCK_TYPE) * num_buckets);

