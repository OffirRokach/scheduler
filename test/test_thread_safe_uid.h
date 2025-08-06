#include <pthread.h>
#include "../include/uid.h" 
#include "testing_macros.h"

#define NUM_OF_THREADS (10)
#define NUM_OF_UIDS (100)

pthread_t threads[NUM_OF_THREADS] = {0};
uid_t uids[NUM_OF_UIDS] = {0};

void* ThreadCreateWorkLoad(void* arg)
{
	long index = *(long*)arg;
	long work_divided = NUM_OF_UIDS / NUM_OF_THREADS;
	long start = index * work_divided;
	long end = start + work_divided;
	long i = 0;

	for(i = start; i < end; ++i)
	{
		uids[i] = UIDCreate();
	}
	return NULL;
}

void MainTest()
{
	size_t i = 0;
	long thread_indexes[NUM_OF_THREADS] = {0};

	for(i = 0; i< NUM_OF_THREADS; ++i) 
	{
		thread_indexes[i] = i;
		pthread_create(&threads[i], NULL , ThreadCreateWorkLoad, thread_indexes + i);
	}

	for(i = 0; i< NUM_OF_THREADS; ++i) 
	{
		pthread_join(threads[i], NULL);
	}
	
	for(i = 0; i <= NUM_OF_UIDS - 1; ++i) 
	{
    	TEST("UID IsSame", UIDIsSame(uids[i],uids[i+1]), 0);
		TEST("UID IsSame", UIDIsSame(uids[i],uids[i]), 1);
	}

	for(i = 0; i< NUM_OF_UIDS; ++i) 
	{
		TEST("UID counter", uids[i].counter < 100, 1);
	}

}

int main()
{
	MainTest();
	PASS;
	return 0;
}
