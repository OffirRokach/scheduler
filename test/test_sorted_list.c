#include <stdio.h> /*printf*/
#include <string.h> /*strcmp*/

#include "sorted_list.h"
#include "testing_macros.h"
/*TEST(name, real, expected)*/

typedef struct contact
{
	char last_name[20];
	char first_name[20];
	char phone_number[20];
} contact_t;

static contact_t entries[7] =
{
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

/* static int print_func(void* data, void* param)
{
	contact_t* contact = (contact_t*)data;
	(void)param;
	
	fprintf(stdout, "Last Name: %s, First Name: %s, Phone Number: %s\n",contact->last_name, contact->first_name, contact->phone_number);
	
	return 0;
}
 */
void TestSortedList()
{
	sorted_list_t* sorted_list1 = CreateSortedList(compare_func);
	sorted_list_t* sorted_list2 = CreateSortedList(compare_func);
	contact_t contact;
	const void* real;
	
	SortedListInsert(sorted_list1, &entries[0]);
	SortedListInsert(sorted_list1, &entries[1]);
	SortedListInsert(sorted_list1, &entries[2]);
	SortedListInsert(sorted_list1, &entries[3]);
	SortedListInsert(sorted_list1, &entries[4]);
	
	TEST("Sorted list Insertion", SortedListGetValue(SortedListBegin(sorted_list1)), &entries[1]);
	TEST("Sorted list Insertion", SortedListGetValue(SortedListPrev(SortedListEnd(sorted_list1))), &entries[3]);
	
	
	SortedListInsert(sorted_list2, &entries[5]);
	SortedListInsert(sorted_list2, &entries[6]);
	
	TEST("Sorted list Insertion", SortedListGetValue(SortedListBegin(sorted_list2)), &entries[6]);
	TEST("Sorted list Insertion", SortedListGetValue(SortedListPrev(SortedListEnd(sorted_list2))), &entries[5]);
	
	TEST("Sorted list Insertion", SortedListGetValue(SortedListPrev(SortedListEnd(sorted_list2))), &entries[5]);
	
	/*SortedListForEach(SortedListBegin(sorted_list1), SortedListEnd(sorted_list1), print_func, (void*)NULL);
	fprintf(stdout, "\n");
	
	SortedListForEach(SortedListBegin(sorted_list2), SortedListEnd(sorted_list2), print_func, (void*)NULL);
	fprintf(stdout, "\n");*/
	
	strcpy(contact.last_name, "Cohen");
	
	real = SortedListGetValue(SortedListFind(sorted_list1, SortedListBegin(sorted_list1), SortedListEnd(sorted_list1), &contact));
	
	TEST("List Find",real, &entries[1]);
	
	SortedListMerge(sorted_list1, sorted_list2);
	
	TEST("Sorted list Insertion", SortedListGetValue(SortedListBegin(sorted_list1)), &entries[6]);
	
	/*SortedListForEach(SortedListBegin(sorted_list1), SortedListEnd(sorted_list1), print_func, (void*)NULL);
	fprintf(stdout, "\n");*/
		
	SortedListDestroy(sorted_list1);
	SortedListDestroy(sorted_list2);
	
}

int main()
{
	TestSortedList();
	PASS;
	return 0;
}
