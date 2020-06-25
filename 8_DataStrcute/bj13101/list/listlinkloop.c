#include "listlinkloop.h"
#include <stdlib.h>
#include <stdio.h>

listlinkloop *listcreate(void)
{
	listlinkloop *l = (listlinkloop *)malloc(sizeof(listlinkloop));

	l->next = l;

	return l;
}

void listinserttail(listlinkloop *l, listdata data)
{
	listlinkloop *temp1 = (listlinkloop *)malloc(sizeof(listlinkloop)), *temp2 = l;

	temp1->data = data;
	temp1->next = l;

	while(temp2->next != l)
	{
		temp2 = temp2->next;
	}

	temp2->next = temp1;
}

listlinkloop *listcuthead(listlinkloop *l)
{
	listlinkloop *temp = l;

	while(temp->next != l)
	{
		temp = temp->next;
	}

	temp->next = l->next;

	free(l);

	return temp->next;
}

void listprintf(listlinkloop *l)
{
	listlinkloop *temp = l;

	printf("%d ", temp->data);
	while(temp->next != l)
	{
		printf("%d ", temp->next->data);
		temp = temp->next;
	}
	printf("\n");
}
