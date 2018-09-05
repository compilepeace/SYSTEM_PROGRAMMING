#include <stdio.h>
#include <stdlib.h>


struct list
{
	int value;
	struct list *next;
}; 


typedef struct list ListMember;


ListMember *CreateNode(int val, ListMember *NextAddr)
{
	ListMember *ptr = (ListMember *)malloc(sizeof(ListMember));
	
	ptr->value = val;
	ptr->next = NextAddr;

	return ptr;
}


void PrintList(ListMember *NodeAddr)
{	
	while( NodeAddr )
	{
		printf("[%p : %d] -> ", &NodeAddr, NodeAddr->value);
		NodeAddr = NodeAddr->next;
	}

	printf("\n");
}


void DestroyLink(ListMember *ptr)
{
	memset(ptr, 0, sizeof(ListMember));
	free(ptr);
}

int main()
{
	ListMember *ptr1 = CreateNode(10, NULL);
	ListMember *ptr2 = CreateNode(20, ptr1);
	ListMember *ptr3 = CreateNode(30, ptr2);
	ListMember *ptr4 = CreateNode(40, ptr3);

	ListMember *head = ptr4;

	PrintList(head);

	DestroyLink(ptr1);
	DestroyLink(ptr2);
	DestroyLink(ptr3);	
	DestroyLink(head);







return 0;
}
