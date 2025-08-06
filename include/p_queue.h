#ifndef __PQ_H__
#define __PQ_H__

#include <stddef.h>		/* size_t */

typedef struct pq pq_t;

/* 
*   @desc:          Create Priority Queue.
*   @params: 		@compare_func: Compare function that the priority is sorted by.
*   @return value:  Pointer to the allocated Priority Queue
*   @error: 		NULL if allocation fails or @compare_func is not valid.
*   @time complex: 	O(malloc) for both AC/WC
*   @space complex: O(malloc) for both AC/WC
*/
pq_t* PQCreate(int (*compare_func)(const void*, const void*));

/* 
*   @desc: 	        Frees Priority Queue. Must be created using @PQCreate.		
*   @params: 	    @pq: Pointer to a valid Priority queue.
*   @return value: 	None
*   @error: 		Undefined behavior if @pq is not valid
*   @time complex: 	O(n) for both AC/WC
*   @space complex: O(1) for both AC/WC
*/
void PQDestroy(pq_t* pq);

/* 
*   @desc: 	        Inserts an item to @p_queue with @data.		
*   @params: 	    @pq: Pointer to a valid Priority queue.
*				    @data: Pointer to an element to be added into @pq.
*   @return value: 	status result - 0 if success, 1 failure.
*   @error: 		In the event insertion fails(due to allocation) will return
* 				    non zero value. Undefined Behavior if @p_queue is not valid.
*   @time complex: 	O(n) for both AC/WC
*   @space complex: O(1) for both AC/WC
*/
int PQEnqueue(pq_t* pq, void* data);

/*
*   @desc:		   Removes the first element from @p_queue.
*   @params: 	   @pq: Pointer to a valid Priority queue.
*   @return value: None.
*   @error: 	   Undefined Behavior if @p_queue is invalid or empty.
*   @time complex: 	O(n) for both AC/WC.
*   @space complex: O(1) for both AC/WC.
*/
void* PQDequeue(pq_t* pq);

/* 
*   @desc: 		    Returns the first element of @p_queue.
*   @params: 	    @pq: Pointer to a valid Priority queue.
*   @return value:  The data of the first element.
*   @error: 	    Undefined behavior if @p_queue is invalid or empty.
*   @time complex: 	O(n) for both AC/WC.
*   @space complex: O(1) for both AC/WC.
*/
void* PQPeek(const pq_t* pq);

/* 
*   @desc: 		    Checks if @queue is empty.
*   @params:        @pq: Pointer to a valid Priority queue.
*   @return value:  1 if the queue is empty 0 otherwise.
*   @error: 	    Undefined behavior if queue is invalid.
*   @time complex: 	O(n) for both AC/WC.
*   @space complex: O(1) for both AC/WC.
*/
int PQIsEmpty(const pq_t* pq);

/* 
*   @desc: 	        Returns the number of elements in the priority queue.
*   @params: 		@pq: Pointer to a valid Priority queue.
*   @return value: 	Number of elements in the queue.
*   @error: 		Undefined behavior if @p_queue is invalid.
*   @time complex: 	O(n) for both AC/WC.
*   @space complex: O(1) for both AC/WC.
*/
size_t PQSize(const pq_t* pq);

/* 
*   @desc: 	        Clears the priority queue to be empty.
*   @params: 		@pq: Pointer to a valid Priority queue.
*   @return value: 	Number of elements in the queue.
*   @error: 		Undefined behavior if @p_queue is invalid.
*   @time complex: 	O(n) for both AC/WC.
*   @space complex: O(1) for both AC/WC.
*/
void PQClear(pq_t* pq);
/*
*   @desc:          Removes the first element in the priority that matches @param 
*                   according to @is_match.
*   @params:        @pq: Pointer to a valid Priority queue.
*                   @is_match: Returns 1 if @param and @data is matching and 0 otherwise.
*                   @param: User defined data to match.
*/
void* PQErase(pq_t* pq, int (*is_match)(const void* data, const void* param), const void* param);

#endif  /* __PQ_H__ */
