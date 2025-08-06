#ifndef __SORTED_LIST_H__
#define __SORTED_LIST_H__

#include <stddef.h> /* size_t */

#include "dl_list.h"

typedef struct sorted_list sorted_list_t;
typedef struct
{
    dll_iter_t internal_iter;
    #ifndef NDEBUG
        sorted_list_t* list;
    #endif
} sorted_list_iter_t;


/* 
*   @desc:          Allocates a new sorted list which is sorted by @compare_func. Must be destroyed with @SortedListDestroy.
*   @params: 		@compare_func: Compare function that the list is sorted by.
*   @return value: 	Pointer to the allocated list.
*   @error: 		NULL if allocation fails.
*                   Undefined behavior if @CompareFunc is invalid.
*   @time complex: 	O(malloc) for both AC/WC
*   @space complex: O(malloc) for both AC/WC
*/
sorted_list_t* CreateSortedList(int (*compare_func)(const void* ,const void*));


/* 
*   @desc: 	        Frees sorted list. Must be created using @CreateSortedList.		
*   @params: 	    @sorted_list : Sorted list to free
*   @return value: 	None
*   @error: 		Undefined behavior if @sorted_list is not valid
*   @time complex: 	O(n) for both AC/WC
*   @space complex: O(1) for both AC/WC
*/
void SortedListDestroy(sorted_list_t* sorted_list);

	
/* 
*   @desc: 		    Inserts @data at the appropiate location in the list regarding the list's compare_func.
*   @params: 		@sorted_list: pre-allocated sorted list.
*			        @data: the data to insert.
*   @return value: 	Returns the newly added iterator.
*   @error: 		Returns invalid iterator if allocation failed.
*			        Undefined behavior if @sorted_list is invalid.
*   @time complex: 	O(n) + O(malloc) for both AC/WC
*   @space complex: O(1) for both AC/WC
*/
sorted_list_iter_t SortedListInsert(sorted_list_t* sorted_list, void* data);


/* 
*   @desc: 			Removes the element pointed to by @where.
*   @params: 		@where: Iterator pointing to the element to remove.
*   @return value: 	Iterator to the next element.
*   @error: 		Undefined behavior if @where is invalid.
*   @time complex: 	O(1) for both AC/WC
*   @space complex: O(1) for both AC/WC
*/
sorted_list_iter_t SortedListRemove(sorted_list_iter_t where);


/* 
*   @desc: 	        Removes the first element from @sorted_list and returns the element	
*   @params: 	    @sorted_list pre-allocated sorted list that the element will be remove from
*   @return value: 	Returns the popped data.
*   @error: 		Undefined behavior if @sorted_list is invalid or empty
*   @time complex: 	O(1) for both AC/WC
*   @space complex: O(1) for both AC/WC
*/
void* SortedListPopFront(sorted_list_t* sorted_list);


/* 
*   @desc: 		    Removes the last element from @sorted_list and returns the element.
*   @params: 	    @sorted_list: pre-allocated sorted list to remove element from.
*   @return value: 	Returns the popped data.
*   @error: 		Undefined behavior if @sorted_list is invalid or empty.
*   @time complex: 	O(1) for both AC/WC
*   @space complex: O(1) for both AC/WC
*/
void* SortedListPopBack(sorted_list_t* sorted_list);


/* 
*   @desc: 	        Returns the count of elements in @sorted_list		
*   @params: 		@sorted_list: pre-allocated sorted list
*   @return value: 	Number of elements
*   @error: 		Undefined behavior if @sorted_list is invalid
*   @time complex: 	O(n) for both AC/WC
*   @space complex: O(1) for both AC/WC
*/
size_t SortedListSize(const sorted_list_t* sorted_list);


/* 
*   @desc: 	        Checks if the list is empty		
*   @params:        @sorted_list sorted list to check if empty		
*   @return value: 	one if the list is empty, and zero if the list contains any elements.
*   @error: 		Undefined behavior if @sorted_list is invalid.
*   @time complex: 	O(1) for both AC/WC
*   @space complex: O(1) for both AC/WC
*/
int SortedListIsEmpty(const sorted_list_t* sorted_list);


/* 
*   @desc: 		    Checks if @one and @other refers to the same element.
*   @params: 		@one: valid iterator.
*			        @other: valid iterator.
*   @return value: 	Returns 1 if the iterators are the same and 0 otherwise.
*   @error: 		None.
*   @time complex: 	O(1) for both AC/WC
*   @space complex: O(1) for both AC/WC
*/
int SortedListIsSameIter(sorted_list_iter_t one, sorted_list_iter_t other);


/* 
*   @desc: 			Get the value @iter points to.
*   @params: 		@iter: Iterator that points to the element.
*   @return value: 	Returns the data of the element.
*   @error: 		Undefined behavior if @iter is invalid.
*   @time complex: 	O(1) for both AC/WC
*   @space complex: O(1) for both AC/WC
*/
const void* SortedListGetValue(sorted_list_iter_t iter);


/* 
*   @desc:      	Return an iterator for the first valid element in the list		
*   @params: 		@sorted_list: pre-allocated sorted list
*   @return value: 	Return the first valid iterator in the list or invalid iterator if @sorted_list is empty
*   @error: 		Undefined behavior if @sorted_list is invalid 
*   @time complex: 	O(1) for both AC/WC
*   @space complex: O(1) for both AC/WC
*/
sorted_list_iter_t SortedListBegin(sorted_list_t* sorted_list); 


/* 
*   @desc: 		    Returns iterator to the invalid iterator after the last element in @sorted_list.
*   @params: 		@sorted_list: pre-allocated sorted list to get iterator from.
*   @return value: 	Returns the invalid iterator after the last element.
*   @error: 		Undefined behavior if @sorted_list is invalid.
*   @time complex: 	O(1) for both AC/WC
*   @space complex: O(1) for both AC/WC
*/
sorted_list_iter_t SortedListEnd(sorted_list_t* sorted_list); 


/* 
*   @desc: 			Returns the next element iterator after @iter.
*   @params: 		@iter: Valid iterator.
*   @return value: 	Returns iterator to the next element, can be invalid iterator.
*   @error: 		Undefined behavior if @iter is not valid
*   @time complex: 	O(1) for both AC/WC
*   @space complex: O(1) for both AC/WC
*/
sorted_list_iter_t SortedListNext(sorted_list_iter_t iter);


/* 
*   @desc: 	        Returns the previous element iterator before @iter.	
*   @params: 		@iter: Valid iterator.
*   @return value: 	Returns the previous iterator 
*   @error: 		Undefined behavior if @iter is invalid or iter is begin of list
*   @time complex: 	O(1) for both AC/WC
*   @space complex: O(1) for both AC/WC
*/
sorted_list_iter_t SortedListPrev(sorted_list_iter_t iter);


/* 
*   @desc:          Searches an element satisfying @list.compare_func with @param in range from @from (inclusive) to @to(exclusive).
*   @params:        @from: valid iterator to start searching from.
*                   @to: iterator to the end of the search range, must be reachable from @from in a forward manner.
*		            @param: a parameter to match to.
*   @return value: 	Iterator to the found element or @to if none of the elements match.
*   @error: 		Undefined behavior if @from is invalid or @to is before @from or
                    @from and @to are not iterators of the same list.
*   @time complex: 	O(n) * O(@list.compare_func) for both AC/WC
*   @space complex: O(@list.compare_func) for both AC/WC
*/
sorted_list_iter_t SortedListFind(sorted_list_t* list, sorted_list_iter_t from, sorted_list_iter_t to, const void* param);


/* 
*   @desc: 			Searches the first element in range from @from(inclusive) to @to(exclusive) that @is_match returns true with @param.
*   @params: 		@from: Iterator to the First element to start search from
                    @to: Iterator to end the search at.
                    @is_match: Returns 1 if @param and @data is matching and 0 otherwise.
                    @param: User defined data to match.
*   @return value: 	Iterator to the found element or @to if none of the elements match.
*   @error: 		Undefined behavior if @to is before @from or @from is invalid iterator or 
                    @from and @to are not iterators of the same list or @is_match is not valid.
*   @time complex: 	O(n) * O(@is_match) for both AC/WC
*   @space complex: O(@is_match) for both AC/WC
*/
sorted_list_iter_t SortedListFindIf(sorted_list_iter_t from, sorted_list_iter_t to, int (*is_match)(const void* data, const void* param) ,const void* param);


/* 
*   @desc: 		    Performs the @action_func with the @param on the elements in range from @from (inclusive) to @to (exclusive).
*   @params:        @from: Valid iterator to start from.
                    @to: Iterator to end the actions at.
                    @action_func: The user defined function to perform for each element.
                    @param: The parameter that the function would use.
*   @return value: 	Return 0 if the function performed successfully otherwise return the @action_func return value
*   @error: 		Undefined behavior if @from is invalid or @to is before @from or if @action_func is not valid or
                    @from and @to are not iterators of the same list or @action_func is not valid or
                    if the @action_func changes the element data.
*   @time complex: 	O(n* @action_func) for both AC/WC
*   @space complex: O(@action_func) for both AC/WC
*/
int SortedListForEach(sorted_list_iter_t from, sorted_list_iter_t to, int (*action_func)(void* data, void* param), void* param);


/* 
*   @desc: 	        Merges sorted list @list_src into sorted list @list_dst.
*   @params: 		@list_dst: pre-allocated sorted list to merge with @list_src.
*                   @list_src: pre-allocated sorted list to be merged into @list_dst.
*   @return value: 	None.
*   @error: 		Undefined if @list_dst or @list_src are invalid, or the same list or compare_func are different between 
*   @time complex: 	O(n + m) for both AC/WC
*   @space complex: O(1) for both AC/WC
*/
void SortedListMerge(sorted_list_t* list_dst, sorted_list_t* list_src);

#endif  /* End of header guard */ 
