#include <stdio.h> /*printf*/
#include <stdio.h> /*printf*/

#include "dl_list.h"
#include "testing_macros.h" /*TEST(name, real, expected)*/

static int PrintFunc(void* data, void* param)
{
	(void)param;
	fprintf(stdout, "%lu\t", (unsigned long)data);
	
	return 0;
}

static int is_match(const void* data, const void* element)
{
	return data == element ? 1 : 0;
}

void TestDLL()
{	
	dl_list_t* dl_list = DLListCreate();
	dl_list_t* out_list = DLListCreate();
	int data1 = 1, data2 = 2, data3 = 3, data4 = 4;
	
	
	TEST("Test List Create", !!dl_list, 1);
	
	TEST("Test Empty List", DLListIsEmpty(dl_list), 1);
	
	TEST("Test Begin List of Empty List",DLListBegin(dl_list), DLListEnd(dl_list));
	
	TEST("Is Same Iteretor", DLListIsSameIter(DLListBegin(dl_list), DLListEnd(dl_list)), 1);
	
	DLListPushFront(dl_list, &data1);
	
	TEST("Test Get Element", DLListGetValue(DLListBegin(dl_list)),&data1);
	
	TEST("Is Same Iteretor", DLListIsSameIter(DLListBegin(dl_list), DLListEnd(dl_list)), 0);
	
	DLListPushFront(dl_list, &data2);
	
	TEST("Test Get Element", DLListGetValue(DLListBegin(dl_list)),&data2);
		
	DLListInsertBefore(dl_list, DLListNext(DLListBegin(dl_list)) , &data3);
	
	TEST("Is Same Iteretor", DLListIsSameIter(DLListNext(DLListBegin(dl_list)), DLListPrev(DLListPrev(DLListEnd(dl_list)))), 1);
	
	TEST("Test Get Element", DLListGetValue(DLListNext(DLListBegin(dl_list))),&data3);
	
	DLListSetValue(DLListBegin(dl_list), &data4);
	
	TEST("Test Get Element", DLListGetValue(DLListBegin(dl_list)),&data4);
	
	DLListForEach(DLListBegin(dl_list), DLListEnd(dl_list), PrintFunc, (void*)NULL); 
	
	fprintf(stdout, "\n");
	
	DLListPopBack(dl_list);
	
	DLListForEach(DLListBegin(dl_list), DLListEnd(dl_list), PrintFunc, (void*)NULL); 
	
	fprintf(stdout, "\n");
	
	TEST("Test Find - param in list",DLListFind( DLListBegin(dl_list), DLListEnd(dl_list), is_match,&data4), DLListBegin(dl_list));
	
	TEST("Test Find - param not in list",DLListFind( DLListBegin(dl_list), DLListEnd(dl_list), is_match, &data1), DLListEnd(dl_list));
	
	TEST("Test Find - param in list",DLListFind( DLListBegin(dl_list), DLListEnd(dl_list), is_match, &data3), DLListPrev(DLListEnd(dl_list)));
	
	TEST("Test List Size", DLListSize(dl_list), 2);
	
	TEST("Test Multifind Success",  DLListMultiFind(DLListBegin(dl_list), DLListEnd(dl_list), is_match, &data3 , out_list), 0);
	
	DLListForEach(DLListBegin(out_list), DLListEnd(out_list), PrintFunc, (void*)NULL); 
	
	fprintf(stdout, "\n");
	
	DLListPushBack(dl_list, &data2); 
	DLListPushBack(dl_list, &data2); 
	
	TEST("Test List Size", DLListSize(dl_list), 4);
	
	DLListForEach(DLListBegin(dl_list), DLListEnd(dl_list), PrintFunc, (void*)NULL); 
	fprintf(stdout, "\n");
	
	DLListSplice(DLListBegin(dl_list), DLListNext(DLListBegin(dl_list)), DLListPrev(DLListEnd(dl_list)));
	
	DLListForEach(DLListBegin(dl_list), DLListEnd(dl_list), PrintFunc, (void*)NULL); 
	fprintf(stdout, "\n");
	
	
	DLListSplice(DLListPrev(DLListEnd(dl_list)), DLListEnd(dl_list), DLListBegin(dl_list));
	DLListForEach(DLListBegin(dl_list), DLListEnd(dl_list), PrintFunc, (void*)NULL); 
	fprintf(stdout, "\n");
	
	DLListSplice(DLListPrev(DLListEnd(dl_list)), DLListEnd(dl_list), DLListPrev(DLListBegin(dl_list)));
	DLListForEach(DLListBegin(dl_list), DLListEnd(dl_list), PrintFunc, (void*)NULL); 
	fprintf(stdout, "\n");
	
	DLListDestroy(dl_list);
	DLListDestroy(out_list);
}


int main()
{
	TestDLL();
	PASS;
	return 0;
}

