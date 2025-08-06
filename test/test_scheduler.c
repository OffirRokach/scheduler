#include <stdio.h> /*printf*/
#include <limits.h>

#include "thread_safe_uid.h"
#include "testing_macros.h"
#include "scheduler.h"


static uid_t* easy_task_checker;

static int EasyTask(void* param)
{
	uid_t* task = (uid_t*)param;
	TEST("Easy task", UIDIsSame(*task, *easy_task_checker), 1);
	++easy_task_checker;
	return -1;
}

static int StopRequest(void* param)
{
	SchedulerStop((scheduler_t*)param);
	return 0;
}

static void TestScheduler(void)
{
	scheduler_t* scheduler = SchedulerCreate();
	uid_t uids[5];
	size_t i = 0;
	int res = 0;
	status_t status;
	
	for (i = 0; i < 5; ++i)
	{
		uids[i] = SchedulerAdd(scheduler, EasyTask, uids + i, i);
	}
	
	TEST("Size", SchedulerSize(scheduler), 5);
	TEST("IsEmpty", SchedulerIsEmpty(scheduler), 0);
	res = SchedulerRemove(scheduler, *uids);
	TEST("Remove task", res, 0);
	res = SchedulerRemove(scheduler, *uids);
	TEST("Remove task", res != 0, 1);
	easy_task_checker = uids + 1;
	printf(GREEN "Please wait about 5 seconds\n");
	
	for (i = 0; i < 4; ++i)
	{
		status = SchedulerRun(scheduler);
		TEST("Status after run", status, SUCCESS);
	}
	
	*uids = SchedulerAdd(scheduler, StopRequest, scheduler, 0);
	
	TEST("Size", SchedulerSize(scheduler), 1);
	
	for (i = 0; i < 100; ++i)
	{
		SchedulerRun(scheduler);
	}
	
	SchedulerClear(scheduler);
	
	for (i = 0; i < 20; ++i)
	{
		*uids = SchedulerAdd(scheduler, EasyTask, uids, i);
	}
	
	SchedulerDestroy(scheduler);
}




int main(void)
{
	TestScheduler();
	PASS;
	return 0;
}

