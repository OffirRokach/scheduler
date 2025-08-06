#include <stddef.h> /*size_t*/
#include <time.h>  /*get time*/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/

#include "task.h" /*task funcs*/


struct task
{
    ilrd_uid_t uid;
    int (*action_func)(void* remaining_reps);
    void* remaining_reps;
    size_t interval_in_sec;
    size_t time_to_run; 
};

task_t* TaskCreate(int(*action_func)(void* remaining_reps), void* remaining_reps,
					size_t interval_in_sec)
{
	task_t* task = (task_t*)malloc(sizeof(task_t));
	
	if(NULL == task)
	{
		return NULL;
	}
	
	task->uid = UIDCreate();
	
	
	if(UIDIsSame(task->uid ,bad_uid))
	{
		free(task);
		return NULL;
	}
	
	task->action_func = action_func;
	task->remaining_reps = remaining_reps;
	task->interval_in_sec = interval_in_sec;
	task->time_to_run = (size_t)time(NULL) + interval_in_sec;
	
	return task;
}

void TaskDestroy(task_t* task)
{
	assert(task);
	free(task);
}

int TaskRun(task_t* task)
{
	assert(task);
	task->time_to_run = time(NULL) + task->interval_in_sec;
	return task->action_func(task->remaining_reps);
}

ilrd_uid_t TaskGetUID(const task_t* task)
{
	assert(task);
	return task->uid;
}

size_t TaskGetInterval(const task_t* task)
{
	assert(task);
	return task->interval_in_sec;
}

void SetTimeToRun(task_t* task, size_t time_to_run)
{
	assert(task);
	task->time_to_run = time_to_run;
}

int TaskIsEqual(const task_t* task1, const task_t* task2)
{
	assert(task1);
	assert(task2);
	return UIDIsSame(task1->uid , task2->uid);
}

size_t TaskGetScheduledTime(const task_t* task)
{
	assert(task);
	return task->time_to_run;
}



