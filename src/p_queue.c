#include <assert.h> /*assert*/
#include <stdlib.h> /*maloc,free*/

#include "sorted_list.h" /*sorted list funcs*/
#include "p_queue.h"

struct pq 
{
	sorted_list_t* pq_list;
};

pq_t* PQCreate(int (*compare_func)(const void*, const void*))
{
	pq_t* pq = (pq_t*)malloc(sizeof(pq_t));
	
	if(NULL == pq)
	{
		return NULL;
	}
	
	pq->pq_list = CreateSortedList(compare_func);
	
	if(NULL == pq->pq_list)
	{
		free(pq);
		return NULL;
	}
		
	return pq;
}

void PQDestroy(pq_t* pq)
{
	assert(pq);
	SortedListDestroy(pq->pq_list);
	free(pq);
}

int PQEnqueue(pq_t* pq, void* data)
{
	
	sorted_list_iter_t iter;
	
	assert(pq);
	
	iter = SortedListInsert(pq->pq_list, data);
	
	return SortedListIsSameIter(SortedListEnd(pq->pq_list),iter);
}

void* PQDequeue(pq_t* pq)
{
	assert(pq);
	assert(!PQIsEmpty(pq));
	
	return SortedListPopFront(pq->pq_list); 
}

void* PQPeek(const pq_t* pq)
{
	assert(pq);
	assert(!PQIsEmpty(pq));
	
	return((void*)SortedListGetValue(SortedListBegin(pq->pq_list)));
}

int PQIsEmpty(const pq_t* pq)
{
	assert(pq);
	
	return SortedListIsEmpty(pq->pq_list);
}

size_t PQSize(const pq_t* pq)
{
	assert(pq);
	
	return SortedListSize(pq->pq_list);
}

void PQClear(pq_t* pq)
{
	assert(pq);
	
	while(!PQIsEmpty(pq))
	{
		PQDequeue(pq);
	}
}

void* PQErase(pq_t* pq, int (*is_match)(const void* data, const void* param), 
const void* param)
{
	sorted_list_iter_t iter;
	void* value;
	
	assert(pq);
	/* assert(!PQIsEmpty(pq)); */ 
	
	iter = SortedListFindIf(SortedListBegin(pq->pq_list),
							SortedListEnd(pq->pq_list), is_match, param);
	
	if(SortedListIsSameIter(SortedListEnd(pq->pq_list), iter))
	{
		return NULL;
	}
	
	value = (void*)SortedListGetValue(iter);
	
	SortedListRemove(iter);
	
	return value;		
}
