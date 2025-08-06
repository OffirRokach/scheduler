#include <assert.h>	/*assert*/
#include <stdlib.h> /*malloc,free*/

#include "sorted_list.h"

struct sorted_list
{
	dl_list_t* list;
	int (*compare_data_func)(const void*, const void*);
};

sorted_list_t* CreateSortedList(int (*compare_func)(const void* ,const void*))
{
	sorted_list_t* sorted_list;
	
	assert(compare_func);
	
	sorted_list = (sorted_list_t*)malloc(sizeof(sorted_list_t));
	
	if (NULL == sorted_list)
	{
		return NULL;
	}
	
	sorted_list->list = DLListCreate();
	
	if(NULL == sorted_list->list)
	{
		free(sorted_list);
		return NULL;
	}
	
	sorted_list-> compare_data_func = compare_func;
	
	return sorted_list;
}

void SortedListDestroy(sorted_list_t* sorted_list)
{
	assert(sorted_list);
	DLListDestroy(sorted_list->list);
	free(sorted_list);
}

sorted_list_iter_t SortedListBegin(sorted_list_t* sorted_list)
{
	sorted_list_iter_t begin;
	assert(sorted_list);
	begin.internal_iter = DLListBegin(sorted_list->list);
	#ifndef NDEBUG
    	begin.list = sorted_list;
	#endif
	return begin;
}

sorted_list_iter_t SortedListEnd(sorted_list_t* sorted_list)
{
	sorted_list_iter_t end;
	assert(sorted_list);
	end.internal_iter = DLListEnd(sorted_list->list);
	#ifndef NDEBUG
    	end.list = sorted_list;
	#endif
	return end;
}

sorted_list_iter_t SortedListNext(sorted_list_iter_t iter)
{	
	iter.internal_iter = DLListNext(iter.internal_iter);
	return iter;
}

sorted_list_iter_t SortedListPrev(sorted_list_iter_t iter)
{
	iter.internal_iter = DLListPrev(iter.internal_iter);
	return iter; 
}

int SortedListIsEmpty(const sorted_list_t* sorted_list)
{
	assert(sorted_list);
	
	return DLListIsEmpty(sorted_list->list);
}

int SortedListIsSameIter(sorted_list_iter_t one, sorted_list_iter_t other)
{
	return one.internal_iter == other.internal_iter;
}

const void* SortedListGetValue(sorted_list_iter_t iter)
{
	return DLListGetValue(iter.internal_iter);
}

sorted_list_iter_t SortedListInsert(sorted_list_t* sorted_list, void* data)
{
	sorted_list_iter_t from;
	sorted_list_iter_t to;
	
	assert(sorted_list);
	assert(data);
	
	from = SortedListBegin(sorted_list);
	to = SortedListEnd(sorted_list);
	
	for(; !SortedListIsSameIter(from ,to); from = SortedListNext(from))
	{
		if (0 <= sorted_list->compare_data_func(SortedListGetValue(from),data))
		{
			break;
		}
	}
	
	from.internal_iter = DLListInsertBefore(sorted_list->list,
	from.internal_iter, data);
		
	return from;
}
	
sorted_list_iter_t SortedListRemove(sorted_list_iter_t where)
{
	DLListRemoveElement(where.internal_iter);
	return where; 
}

void* SortedListPopFront(sorted_list_t* sorted_list)
{
	assert(sorted_list);
	return DLListPopFront(sorted_list->list);
}

void* SortedListPopBack(sorted_list_t* sorted_list)
{
	assert(sorted_list);
	return DLListPopBack(sorted_list->list);
}

size_t SortedListSize(const sorted_list_t* sorted_list)
{
	assert(sorted_list);
	return DLListSize(sorted_list->list);
}

void SortedListMerge(sorted_list_t* list_dst, sorted_list_t* list_src)
{		
	sorted_list_iter_t from;
	sorted_list_iter_t to;
	sorted_list_iter_t where;
	
	assert(list_dst);
	assert(list_src);
	assert(list_src != list_dst);
	assert(list_dst->compare_data_func == list_src->compare_data_func);
	
	where = SortedListBegin(list_dst);
	
	while (!SortedListIsEmpty(list_src))
	{
		from = SortedListBegin(list_src);
		to = from;
		
		while (!SortedListIsSameIter(where, SortedListEnd(list_dst)) && 
		list_dst->compare_data_func(SortedListGetValue(where),
		SortedListGetValue(from)) < 0)
		{
			where = SortedListNext(where);
		}
		
		if (SortedListIsSameIter(where, SortedListEnd(list_dst)))
		{
			   to = SortedListEnd(list_src);
		}
		
		else
		{		       
			while (!SortedListIsSameIter(to, SortedListEnd(list_src)) && 
			list_dst->compare_data_func(SortedListGetValue(where),
			 SortedListGetValue(to)) >= 0)
			{
				to = SortedListNext(to);
			}	
   		}
   		
   		DLListSplice(from.internal_iter,
			to.internal_iter, SortedListPrev(where).internal_iter);		
	}
}

int SortedListForEach(sorted_list_iter_t from, sorted_list_iter_t to, 
int (*action_func)(void* data, void* param), void* param)
{
	assert(from.list == to.list);
	assert(action_func);
	
	return DLListForEach(from.internal_iter, to.internal_iter, 
	action_func, param);	
}

sorted_list_iter_t SortedListFind(sorted_list_t* list, sorted_list_iter_t from,
 sorted_list_iter_t to, const void* param)
{
	assert(list);
	assert(from.list == to.list);
	assert(from.list == list);
	
	for(; !SortedListIsSameIter(from ,to); from = SortedListNext(from))	
	{
		if (0 == list->compare_data_func(SortedListGetValue(from), param))
		{
			break;
		}
	}
	return from;
}

sorted_list_iter_t SortedListFindIf(sorted_list_iter_t from,
 sorted_list_iter_t to, int (*is_match)(const void* data, const void* param), 
 const void* param)
{
	assert(from.list == to.list);
	assert(is_match);
	
	from.internal_iter =  DLListFind(from.internal_iter, to.internal_iter, 
	is_match ,param);
	return from;
}

