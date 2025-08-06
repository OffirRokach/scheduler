#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/

#include "dl_list.h"

#define UNUSED(x) ((void)x) 

struct dll_node_t
{
	struct dll_node_t* next;
	struct dll_node_t* prev;
	void* data;
};

struct dl_list
{
	struct dll_node_t head;
	struct dll_node_t tail;
};



dl_list_t* DLListCreate(void)
{
	dl_list_t* dl_list = (dl_list_t*)malloc(sizeof(dl_list_t));
	
	if(NULL == dl_list)
	{
		return NULL;
	}
	
	dl_list->head.next = &dl_list->tail;
	dl_list->head.prev = NULL;
	dl_list->head.data = NULL;
		
	dl_list->tail.next = NULL;
	dl_list->tail.prev = &dl_list->head;
	dl_list->tail.data = NULL;
	
	return dl_list;	
}

void DLListDestroy(dl_list_t* dl_list)
{	
	while(!DLListIsEmpty(dl_list))
	{
		DLListPopFront(dl_list);
	}
	
	free(dl_list);
}

int DLListIsEmpty(const dl_list_t* dl_list)
{
	assert(dl_list);
	return ((dl_list->head.next == &dl_list->tail) && (dl_list->tail.prev == &dl_list->head));
}

int DLListIsSameIter(dll_iter_t one, dll_iter_t other)
{
	return one->next == other->next && one->data == other->data;
}

dll_iter_t DLListBegin(const dl_list_t* dl_list)
{
	assert(dl_list);
	return dl_list->head.next;
}

dll_iter_t DLListEnd(const dl_list_t* dl_list)
{
	assert(dl_list);
	return DLListNext(dl_list->tail.prev); 
}

dll_iter_t DLListNext(dll_iter_t iter)
{
	assert(iter);
	return iter->next;
}

dll_iter_t DLListPrev(dll_iter_t iter)
{
	assert(iter);
	return iter->prev;
}

dll_iter_t DLListInsertBefore(dl_list_t* dl_list, dll_iter_t iter, const void* element)
{
	dll_iter_t new_node = NULL;
	
	assert(dl_list);
	
	new_node = (dll_iter_t)malloc(sizeof(struct dll_node_t));
		
	if (NULL == new_node)
	{
		return DLListEnd(dl_list);
	}
	
	new_node->prev = iter->prev;
	new_node->next = iter;
	new_node->data = (void*)element;
	
	iter->prev->next = new_node;
	iter->prev = new_node;
	
	return new_node;
}

dll_iter_t DLListPushFront(dl_list_t* dl_list, const void* element)
{	
	assert(dl_list);
		
	return DLListInsertBefore(dl_list, DLListBegin(dl_list), element);
}

dll_iter_t DLListPushBack(dl_list_t* dl_list, const void* element)
{
	assert(dl_list);
	
	return DLListInsertBefore(dl_list,  DLListEnd(dl_list) , element);
}

dll_iter_t DLListRemoveElement(dll_iter_t iter)
{
	dll_iter_t new_iter = iter->next;
	
	iter->prev->next = new_iter;
	new_iter->prev = iter->prev;
	
	free(iter);
	
	return new_iter;
}

void* DLListPopFront(dl_list_t* dl_list)
{
	dll_iter_t first_node_iter = NULL;
	void* element = NULL;
	
	assert(dl_list);
	
	first_node_iter = DLListBegin(dl_list);
	element = first_node_iter-> data;
	
	DLListRemoveElement(first_node_iter);
	
	return element;
	
}

void* DLListPopBack(dl_list_t* dl_list)
{
	dll_iter_t last_node_iter = NULL;
	void* element = NULL;
		
	assert(dl_list);
		
	last_node_iter = DLListPrev(DLListEnd(dl_list));
	element = last_node_iter->data;
		
	DLListRemoveElement(last_node_iter);
	
	return element;
}

void* DLListGetValue(dll_iter_t iter)
{
	return iter->data;
}

void DLListSetValue(dll_iter_t iter, const void* value)
{
	iter->data = (void*)value;
}

int DLListForEach(dll_iter_t from, dll_iter_t to, int (*action_func)(void* data, void* param), void* param)
{
	for(;!DLListIsSameIter(from, to); from = DLListNext(from))
		{
			if (1 == (*action_func)(from->data, param))
			{
				return 1;
			}
		}
		return 0;
}

dll_iter_t DLListFind(dll_iter_t from, dll_iter_t to, int (*is_match)(const void* data, const void* param) ,const void* param)
{
	for(; !DLListIsSameIter(from, to); from = DLListNext(from))
	{
		if(1 == (*is_match)(from->data, param))
		{
			break;
		}
	}
	return from;
}

static int CountFunc(void* data, void* param)
{
	UNUSED(data);
	++(*(size_t*)param);
	return 0;
}


size_t DLListSize(const dl_list_t* dl_list)
{
	size_t count = 0;
	
	DLListForEach(DLListBegin(dl_list), DLListEnd(dl_list), CountFunc , &count);
	
	return count;
}

int DLListMultiFind(dll_iter_t from, dll_iter_t to,
int (*is_match)(const void* data, const void* param), const void* param,
dl_list_t* out_dl_list)
{
	for(; !DLListIsSameIter(from, to); from = DLListNext(from))
	{
		if(1 == (*is_match)(from->data, param))
		{
			DLListPushBack(out_dl_list, param);
		}
	}
	return 0;	
}

dll_iter_t DLListSplice(dll_iter_t from_src, dll_iter_t to_src, dll_iter_t where)
{
	dll_iter_t node_before_from = from_src->prev;
	dll_iter_t node_before_to = DLListPrev(to_src);
	
	node_before_from->next = to_src;
	to_src->prev = node_before_from;
	
	node_before_to->next = where->next;
	where->next->prev = node_before_to;
	
	where->next = from_src;
	from_src->prev = where;
	
	return DLListNext(where);
}

