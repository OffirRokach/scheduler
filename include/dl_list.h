#ifndef __DL_LIST_H__
#define __DL_LIST_H__
#include <stddef.h> /* size_t */
typedef struct dl_list dl_list_t;
typedef struct dll_node_t* dll_iter_t;
/* 
*   @desc: 			Allocates doubly linked list. Must be freed using @DLListDestroy.
*   @params: 		None
*   @return value: 	Returns a pointer to the allocated doubly list.
*   @error: 		Returns null if allocation failed
*   @time complex: 	O(1)
*   @space complex: O(1)
*/
dl_list_t* DLListCreate(void);
/* 
*   @desc: 			Frees doubly linked list. Must be created using @DLListCreate.
*   @params: 		@dl_list: the list to free 
*   @return value: 	None
*   @error: 		Undefined behavior if dl_list is not valid
*   @time complex: 	O(n)
*   @space complex: O(1)
*/
void DLListDestroy(dl_list_t* dl_list);
/* 
*   @desc: 			Inserts @element before the element pointed by @iter into @dl_list
*   @params: 		@dl_list: preallocated doubly linked list
*					@iter: iterator before who to insert
*					@element: the element to insert
*   @return value: 	Returns the newly added iterator
*   @error: 		Returns invalid iterator if allocation failed.
*					Undefined behavior if @dl_list is not the same list as iter or @dl_list is invalid
*   @time complex: 	O(n)
*   @space complex: O(1)
*/
dll_iter_t DLListInsertBefore(dl_list_t* dl_list, dll_iter_t iter, const void* element);
/* 
*   @desc: 			Inserts @element to the beginning of the @dl_list
*   @params: 		@dl_list: preallocated doubly linked list
*					@element: the element to insert
*   @return value: 	Returns the newly added iterator
*   @error: 		Returns invalid iterator if allocation failed
*					Undefined behavior if @dl_list is invalid
*   @time complex: 	O(1)
*   @space complex: O(1)
*/
dll_iter_t DLListPushFront(dl_list_t* dl_list, const void* element);
/* 
*   @desc: 			Inserts @element to the end of the @dl_list
*   @params: 		@dl_list: preallocated doubly linked list
*					@element: the element to insert
*   @return value: 	Returns the newly added iterator
*   @error: 		Returns invalid iterator if allocation failed
*					Undefined behavior if @dl_list is invalid
*   @time complex: 	O(1)
*   @space complex: O(1)
*/
dll_iter_t DLListPushBack(dl_list_t* dl_list, const void* element);
/* 
*   @desc: 			Removes the element pointed by @iter from the list
*   @params: 		@iter: valid iterator pointing to the element wanted to be removed.
*   @return value: 	Returns iterator pointing to the next element after the removed element
*   @error: 		Undefined behavior if @iter is invalid iter.
*   @time complex: 	O(1)
*   @space complex: O(1)
*/
dll_iter_t DLListRemoveElement(dll_iter_t iter);
/* 
*   @desc: 			Removes the first element from @dl_list
*   @params: 		@dl_list: preallocated doubly linked list to remove element from.
*   @return value: 	Returns the data that was in the removed node
*   @error: 		Undefined behavior if @dl_list is invalid or empty.
*   @time complex: 	O(1)
*   @space complex: O(1)
*/
void* DLListPopFront(dl_list_t* dl_list);
/* 
*   @desc: 			Removes the last element from @dl_list
*   @params: 		@dl_list: preallocated doubly linked list to remove element from.
*   @return value: 	Returns the data that was in the removed node
*   @error: 		Undefined behavior if @dl_list is invalid or empty.
*   @time complex: 	O(1)
*   @space complex: O(1)
*/
void* DLListPopBack(dl_list_t* dl_list);
/* 
*   @desc: 			Returns the count of elements in @dl_list
*   @params: 		@dl_list: preallocated doubly linked list to count elements
*   @return value: 	Returns the count of elements
*   @error: 		Undefined behavior if @dl_list is invalid
*   @time complex: 	O(n)
*   @space complex: O(1)
*/
size_t DLListSize(const dl_list_t* dl_list);
/* 
*   @desc: 			Checks if @dl_list is empty
*   @params: 		@dl_list: preallocated doubly linked list to check if empty
*   @return value: 	Returns 1 if the list is empty and 0 otherwise
*   @error: 		Undefined behavior if @dl_list is invalid
*   @time complex: 	O(1)
*   @space complex: O(1)
*/
int DLListIsEmpty(const dl_list_t* dl_list);
/* 
*   @desc: 			Returns iterator to the first element in @dl_list
*   @params: 		@dl_list: preallocated doubly linked list to get iterator from
*   @return value: 	Returns a valid iterator to the first element
*   @error: 		Returns invalid iterator if the list is empty
*					Undefined behavior if @dl_list is invalid
*   @time complex: 	O(1)
*   @space complex: O(1)
*/
dll_iter_t DLListBegin(const dl_list_t* dl_list);
/* 
*   @desc: 			Returns iterator to the invalid iterator after the last element in @dl_list
*   @params: 		@dl_list: preallocated doubly linked list to get iterator from
*   @return value: 	Returns an invalid iterator to one past the last element
*   @error: 		Undefined behavior if @dl_list is invalid
*   @time complex: 	O(1)
*   @space complex: O(1)
*/
dll_iter_t DLListEnd(const dl_list_t* dl_list);
/* 
*   @desc: 			Advances @iter to the next element and returns the new iterator 
*   @params: 		@iter: iterator to advance
*   @return value: 	Returns an iterator to the next element
*   @error: 		Undefined behavior if @iter is invalid
*   @time complex: 	O(1)
*   @space complex: O(1)
*/
dll_iter_t DLListNext(dll_iter_t iter);
/* 
*   @desc: 			Advances @iter to the previous element and returns the new iterator 
*   @params: 		@iter: iterator to advance
*   @return value: 	Returns an iterator to the previous element
*   @error: 		Undefined behavior if @iter is invalid(unless it is one after the last element)
*   @time complex: 	O(1)
*   @space complex: O(1)
*/
dll_iter_t DLListPrev(dll_iter_t iter);
/* 
*   @desc: 			Checks if one and other point to the same element 
*   @params: 		@one: valid iterator
*					@other: valid iterator
*   @return value: 	Returns 1 if the iterators are the same and 0 otherwise
*   @error: 		None
*   @time complex: 	O(1)
*   @space complex: O(1)
*/
int DLListIsSameIter(dll_iter_t one, dll_iter_t other);
/* 
*   @desc: 			Returns the data of the element pointed by @iter
*   @params: 		@iter: valid iterator
*   @return value: 	Returns the data the element pointed by @iter is storing
*   @error: 		Undefined behavior if @iter is invalid
*   @time complex: 	O(1)
*   @space complex: O(1)
*/
void* DLListGetValue(dll_iter_t iter);
/* 
*   @desc: 			Sets the data of the element pointed by @iter
*   @params: 		@iter: valid iterator
*   @return value: 	None
*   @error: 		Undefined behavior if @iter is invalid
*   @time complex: 	O(1)
*   @space complex: O(1)
*/
void DLListSetValue(dll_iter_t iter, const void* value);
/* 
*   @desc: 			Searches an element satisfying @is_match function with @param in range from @from(inclusive) to @to(exclusive) returns the iterator to such element
*   @params: 		@from: valid iterator to start searching from
*					@to: iterator to the end the search at, must be reachable from @from in a forward manner
*					@is_match: match function that returns 1 if two elements match and 0 otherwise
*					@param: a parameter to match to.
*   @return value: 	Iterator to the found element or @to if none of the elements match
*   @error: 		Undefined behavior if @from is invalid or @to is before @from or if @is_match is not valid
*   @time complex: 	O(n) * O(@is_match)
*   @space complex: O(@is_match)
*/
dll_iter_t DLListFind(dll_iter_t from, dll_iter_t to, int (*is_match)(const void* data, const void* param) ,const void* param);
/* 
*   @desc: 			Searches for all elements satisfying @is_match function with @param in range from @from(inclusive) to @to(exclusive)
*					and copies their data to the @out_dl_list provided(inserts them to the end of the list).
*   @params: 		@from: valid iterator to start searching from
*					@to: iterator to the end the search at, must be reachable from @from in a forward manner
*					@is_match: match function that returns 1 if two elements match and 0 otherwise
*					@param: a parameter to match to.
*   @return value: 	Returns 0 if the function performed successfully
*   @error: 		Undefined behavior if @from is invalid or @to is before @from or if @is_match is not valid and @out_dl_list is invalid
*   @time complex: 	O(n) * O(@is_match)
*   @space complex: O(n) * O(@is_match)
*/
int DLListMultiFind(dll_iter_t from, dll_iter_t to, int (*is_match)(const void* data, const void* param) ,const void* param, dl_list_t* out_dl_list);
/* 
*   @desc: 			Activates @action_func with @param on each of the elements in range from @from(inclusive) to @to(exclusive)
*   @params: 		@from: valid iterator to start action on
*					@to: iterator to past the last element the action will be preformed on, must be reachable from @from in a forward manner
*					@action_func: a function that does user defined actions on elements data and returns 0 upon success
*					@param: a user defined additional parameter to pass into @action_func
*   @return value: 	Returns 0 if the function performed successfully otherwise returns the @action_func return value
*   @error: 		Undefined behavior if @from is invalid or @to is before @from or if @is_match is not valid and @out_dl_list is invalid
*   @time complex: 	O(n) * O(@action_func)
*   @space complex: O(@action_func)
*/
int DLListForEach(dll_iter_t from, dll_iter_t to, int (*action_func)(void* data, void* param), void* param);
/* 
*   @desc: 		   Cuts elements from @from(inclusive) to @to(exclusive) and pastes after @where
*   @params: 	   @from: valid iterator to start cutting from
*				   @to: iterator to stop cutting at (make sure @to is after @from)
*				   @where: After which element to paste the elements cut.
*   @return value: Iterator to an iterator which points to the first element pasted. 
*   @error: 	   Undefined Behavior if @from is invalid or @to is before @from or if @where is invalid or @where is inside the range of @from and @to.
*   @time-complexity: O(1)
*   @space-complexity: O(1)
*/
dll_iter_t DLListSplice(dll_iter_t from_src, dll_iter_t to_src, dll_iter_t where);

#endif  /* End of header guard */ 
