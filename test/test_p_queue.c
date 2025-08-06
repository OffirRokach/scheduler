#include <stdio.h> /*printf*/
#include <string.h> /*strcmp*/

#include "p_queue.h"
#include "testing_macros.h"


typedef struct contact
{
	char last_name[20];
	char first_name[20];
	char phone_number[20];
} contact_t;

static contact_t entries[8] =
{
    { "Levy", "Ben", "1874058321" },
    { "Levy", "Rachel", "1874058321" },
    { "Cohen", "Avi", "7839465876" },
    { "Gabay", "Shir", "6297519006" },
    { "Yoseph", "Daniel", "5239876201"},
    { "Peretz", "Eyal", "9631038546" },
    {"Floom","Noa", "2365786014"},
    {"Brown","Sapir", "2365786014"}   
};

static int compare_func(const void* data1, const void* data2)
{
	const contact_t* contact1 = (const contact_t*)data1;
	const contact_t* contact2 = (const contact_t*)data2;
	
	if(0 == strcmp(contact1->last_name, contact2->last_name))
	{
		return strcmp(contact1->first_name, contact2->first_name);
	}
	else
	{
		return strcmp(contact1->last_name, contact2->last_name);
	}
}

static int is_match(const void* data, const void* param)
{
	const contact_t* contact = (const contact_t*)data;
	const char* last_name = (const char*)param;
	
	return (0 == (strcmp(contact->last_name,last_name)));	
}

void TestPriorityQueue()
{
	pq_t* pq1 = PQCreate(compare_func);
	pq_t* pq2 = PQCreate(compare_func);
	
	TEST("Test IsEmpty",PQIsEmpty(pq2),1);
	TEST("Test IsEmpty",PQIsEmpty(pq1),1);
	
	PQEnqueue(pq1, &entries[0]);
	PQEnqueue(pq1, &entries[1]);
	PQEnqueue(pq1, &entries[2]);
	PQEnqueue(pq1, &entries[3]);
	PQEnqueue(pq1, &entries[4]);
	PQEnqueue(pq1, &entries[5]);
	
	TEST("Test Enqueue",PQPeek(pq1), &entries[2]);
		
	PQEnqueue(pq2, &entries[6]);
	PQEnqueue(pq2, &entries[7]);
	
	TEST("Test Enqueue", PQPeek(pq2) , &entries[7]);
	
	PQDequeue(pq1);
	PQDequeue(pq1);
	
	TEST("Test Enqueue",PQPeek(pq1), &entries[0]);
	
	PQDequeue(pq2);
	
	TEST("Test Enqueue",PQPeek(pq2), &entries[6]);
	
	
	TEST("Test PQ Size",PQSize(pq1),4);
	TEST("Test PQ Size",PQSize(pq2),1);
			
	PQErase(pq2, is_match, "Floom");
	
	TEST("Test IsEmpty",PQIsEmpty(pq2),1);
	
	PQClear(pq1);
	
	TEST("Test IsEmpty",PQIsEmpty(pq1),1);
		
	PQDestroy(pq1);
	PQDestroy(pq2);
	
}

int main(void)
{
	TestPriorityQueue();
	PASS;
	return 0;
}

