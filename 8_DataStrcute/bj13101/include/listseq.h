#ifndef _LISTSEQ_H
#define _LISTSEQ_H

#define N 6

typedef struct
{
	char name[64];
	int age;
}student;

typedef student listdata;

typedef struct
{
	listdata data[N];
	int n;
}listseq;

extern listseq *listcreate(void);
extern void listinsert(listseq *l, listdata data);
extern void listprintf(listseq *l);
extern int listempty(listseq *l);
extern int listfull(listseq *l);
extern void listdelete(listseq *l, listdata data);

#endif
