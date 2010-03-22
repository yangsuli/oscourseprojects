#ifndef __list_h__
#define __list_h__

#include "lock_type.h"

struct list_item {
	void * element;
	unsigned int key;
	struct list_item * next;
};

typedef struct __list_t {
	struct list_item * head;
	LOCK_TYPE list_lock;
} list_t;


void List_Init(list_t *l);
void List_Insert(list_t *l, void *element, unsigned int key);
void List_Remove(list_t *l, unsigned int key);
void* List_Lookup(list_t *l, unsigned int key);
void List_Destroy(list_t *l);

#endif // __list_h__

