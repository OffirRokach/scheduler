#include <stdio.h> /*printf*/
#include <stdio.h> /*printf*/
#include <time.h> /*get time*/

#include "task.h"
#include "testing_macros.h" /*TEST(name, real, expected)*/

int action_func(void* params)
{
	if(params == NULL)
	{
		return 0; /*should repeat*/
	}
	
	else 
	{
		return -1; /*shouldn't repeat*/
	}
}

void TestTask()
{
	task_t* task1 = TaskCreate(action_func, NULL, 60);
	task_t* task2 = TaskCreate(action_func, NULL, 90);
	size_t sched_task1 = TaskGetScheduledTime(task1);
	size_t sched_task2 = TaskGetScheduledTime(task2);
	
	TEST("Tasks are equal", TaskIsEqual(task1,task2), 0);
	TEST("Tasks are equal", TaskIsEqual(task1,task1), 1);
	
	TEST("Test time to run",TaskGetScheduledTime(task1), (size_t)time(NULL)+60);
	TEST("Test time to run",TaskGetScheduledTime(task2), (size_t)time(NULL)+90);
	
	/*TEST("Test Get Interval", TaskGetInterval(task1), (size_t)60);
	TEST("Test Get Interval", TaskGetInterval(task2), (size_t)90);*/
	
	TaskRun(task1);
	
	TEST("Test new time to run", sched_task1 != TaskGetScheduledTime(task1), 1);
	
	TaskRun(task2);
	
	
	TEST("Test new time to run",sched_task2 != TaskGetScheduledTime(task2), 1);
	
	
	
	TaskDestroy(task1);
	TaskDestroy(task2);
}

int main()
{
	TestTask();
	PASS;
	return 0;
}
