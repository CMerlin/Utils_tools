#include "listseq.h"
#include <stdlib.h>
#include <stdio.h>

listseq *listcreate(void)
{
	listseq *l = (listseq *)malloc(sizeof(listseq));

	l->n = 0;

	return l;
}

void listinsert(listseq *l, listdata data)
{
	l->data[l->n++] = data;
}

void listdelete(listseq *l, listdata data)
{
	int i, j = 0;

	for(i=0; i<l->n; i++)
	{
		if(l->data[i].age != data.age)
		{
			l->data[j++] = l->data[i];
		}
	}

	l->n = j; 
}

void listprintf(listseq *l)
{
	int i;

	printf("name\tage\n");
	for(i=0; i<l->n; i++)
	{
		printf("%s\t%d\n", l->data[i].name, l->data[i].age);
	}
}

int listempty(listseq *l)
{
	return l->n == 0;
}

int listfull(listseq *l)
{
	return l->n == N;
}
