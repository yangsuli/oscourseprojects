#include "list.h"
#include "lock_type.h"
#include <assert.h>

void List_Init(list_t *l){//initialize the list with a header node
	l -> head = (struct list_item *)malloc(sizeof(struct list_item));
	assert(l -> head != NULL);
	l -> head -> element = NULL;
	l -> head -> next = NULL;
	LOCK_INIT(&l->list_lock,NULL);
}

void List_Destroy(list_t *l){
	free(l -> head);
	LOCK_DESTROY(&l->list_lock);
}

void List_Insert(list_t *l, void *element, unsigned int key){
	struct list_item *new_item = (struct list_item *)malloc(sizeof(struct list_item));
	assert(new_item != NULL);
	new_item -> element = element;
	new_item -> key = key;
	LOCK(&l->list_lock);
	new_item -> next = l -> head -> next;
	l -> head -> next = new_item;
	UNLOCK(&l->list_lock);
}

void List_Remove(list_t *l, unsigned int key){
	LOCK(&l->list_lock);
	struct list_item * prev;
	struct list_item * temp;

	for(prev = l -> head; prev -> next != NULL; prev = prev -> next){
		if( prev -> next -> key == key){
			break;
		}
	}

	if( prev -> next != NULL ){// found the item in list
		temp = prev -> next;
		prev -> next = prev -> next -> next;
		free(temp);
	}

	UNLOCK(&l->list_lock);
}

void * List_Lookup(list_t *l, unsigned int key){

	LOCK(&l->list_lock);
	struct list_item * prev;
	void * found;

	for(prev = l -> head; prev -> next != NULL; prev = prev -> next){
		if( prev -> next -> key == key){
			break;
		}
	}

	if( prev -> next != NULL ){// found the item in list
		found = prev -> next -> element;
	}else{
		found = NULL;
	}

	UNLOCK(&l->list_lock);

	return found;
}







