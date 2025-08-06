#include <assert.h> /*assert*/
#include <stddef.h> /*size_t*/
#include <stdlib.h> /*malloc, free*/
#include <time.h>  /*size_t*/
#include <unistd.h> /*sleep*/

#include "task.h" /*task funcs*/
#include "scheduler.h" /*scheduler funcs*/
#include "p_queue.h" /*priority queue funcs*/

struct scheduler
{
    pq_t* p_queue;
	status_t status;
	status_t signal;
};


static int compare_func(const void* data1, const void* data2)
{
    const task_t* task1 = (const task_t*)data1;
    const task_t* task2 = (const task_t*)data2;
    

    return (int)((time_t)TaskGetScheduledTime(task1) - (time_t)TaskGetScheduledTime(task2));
}

static int is_match(const void* data, const void* param)
{
    const task_t* task_to_find = (const task_t*)data;
    uid_t* uid_identifier = (uid_t*)param;

    return UIDIsSame(TaskGetUID(task_to_find), *uid_identifier);
}

static void HandleTask(scheduler_t* scheduler);

scheduler_t* SchedulerCreate(void)
{
    scheduler_t* scheduler = (scheduler_t*)malloc(sizeof(scheduler_t));
    if (NULL == scheduler)
    {
        return NULL;
    }

    scheduler->p_queue = PQCreate(compare_func);
    if (NULL == scheduler->p_queue)
    {
        free(scheduler);
        return NULL;
    }

    scheduler->status = STOPPED;
	scheduler->signal = STOPPED;
	
    return scheduler;
}

uid_t SchedulerAdd(scheduler_t* scheduler,
						int (*action_func)(void* params),
						void* params, size_t interval_in_sec)
{
    task_t* task = NULL;
    int result;

    assert(scheduler);
    assert(action_func);

    task = TaskCreate(action_func, params, interval_in_sec);
    
    if(NULL == task)
    {
    	return bad_uid;
    }

    result = PQEnqueue(scheduler->p_queue, task);
    if (1 == result)
    {
        TaskDestroy(task);
        return bad_uid;
    }

    return TaskGetUID(task);
}

int SchedulerRemove(scheduler_t* scheduler, uid_t identifier)
{
    void* result = 	NULL;

    assert(scheduler);
    assert(!UIDIsSame(identifier, bad_uid));

    result = PQErase(scheduler->p_queue, is_match, &identifier);
    
    if (NULL != result)
    {
        TaskDestroy(result);
        return 0;
    }

    return 1;
}

static void HandleTask(scheduler_t* scheduler)
{
    task_t* task = NULL;

	assert(scheduler);

	task = PQDequeue(scheduler->p_queue);

    if(0 == TaskRun(task))
    {
        PQEnqueue(scheduler->p_queue, task); 
    }
    else
    {
        TaskDestroy(task);
    }
}

status_t HandleSignals(scheduler_t* scheduler)
{
	switch(scheduler->signal)
	{
		case DESTROYED: 
						scheduler->status = DESTROYED;
						SchedulerDestroy(scheduler);
						return DESTROYED;
						
		case STOPPED:	
						SchedulerStop(scheduler);
						scheduler->status = STOPPED;
						break;
						
		case ERROR:  
						scheduler->status = ERROR;
						break;
						
		default:  
						scheduler->status = SUCCESS;
						break;
	}
	
	return scheduler->status;
}

status_t SchedulerRun(scheduler_t* scheduler)
{
	task_t* next_task;
	size_t current_time;

	assert(scheduler);

	if(RUNNING == scheduler->status)
	{
		return RUNNING;
	}

	scheduler->signal = RUNNING;	
	scheduler->status = RUNNING;
	
	while (RUNNING == scheduler->signal && !SchedulerIsEmpty(scheduler))
	{
		next_task = (task_t*)PQPeek(scheduler->p_queue);
		current_time = (size_t)time(NULL);
        
		if (TaskGetScheduledTime(next_task) > current_time)
		{
			sleep(TaskGetScheduledTime(next_task) - current_time);
		}

		HandleTask(scheduler);
	}
	
	return HandleSignals(scheduler);
}


size_t SchedulerSize(const scheduler_t* scheduler)
{
	assert(scheduler);
	return PQSize(scheduler->p_queue);
}

int SchedulerIsEmpty(const scheduler_t* scheduler)
{
	assert(scheduler);
	return PQIsEmpty(scheduler->p_queue);
}

void SchedulerClear(scheduler_t* scheduler)
{
	task_t* task;
	assert(scheduler);

	while (!SchedulerIsEmpty(scheduler))
	{
		task = PQDequeue(scheduler->p_queue);
		TaskDestroy(task);
	}
}

void SchedulerStop(scheduler_t* scheduler)
{
	assert(NULL != scheduler);

	if(scheduler->signal != DESTROYED)
	{
		scheduler->signal = STOPPED;
	}
}

void SchedulerDestroy(scheduler_t* scheduler)
{
	assert(NULL != scheduler);
	
	if(RUNNING == scheduler->status)
	{
		scheduler->signal = DESTROYED;
		return;
	}
    
	SchedulerClear(scheduler);
	PQDestroy(scheduler->p_queue);
	free(scheduler);
}
