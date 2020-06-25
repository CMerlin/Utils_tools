#include "listlink.h"
#include <stdlib.h>
#include <stdio.h>

listlink *listcreate(void)
{
	listlink *l = (listlink *)malloc(sizeof(listlink));

	l->next = NULL;

	return l;
}

void listinserthead(listlink *l, listdata data)
{
	listlink *temp = (listlink *)malloc(sizeof(listlink));

	temp->data = data;
	temp->next = l->next;

	l->next = temp;
}

void listinserttail(listlink *l, listdata data)
{
	listlink *temp1 = (listlink *)malloc(sizeof(listlink)), *temp2 = l;

	temp1->data = data;
	temp1->next = NULL;

	while(temp2->next != NULL)
	{
		temp2 = temp2->next;
	}

	temp2->next = temp1;
}

void listdelete(listlink *l, listdata data)
{
	listlink *temp1 = l, *temp2;

	while(temp1->next != NULL)
	{
		if(temp1->next->data.age == data.age)
		{
			temp2 = temp1->next;
			temp1->next = temp2->next;
			free(temp2);
			break;
		}
		temp1 = temp1->next;
	}
}

void listprintf(listlink *l)
{
	listlink *temp = l;

	printf("name\tage\n");
	while(temp->next != NULL)
	{
		printf("%s\t%d\n", temp->next->data.name, temp->next->data.age);
		temp = temp->next;
	}
}
