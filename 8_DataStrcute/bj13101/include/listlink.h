#ifndef _LISTLINK_H
#define _LISTLINK_H

typedef struct
{
	char name[64];
	int age;
}student;

typedef student listdata;

typedef struct list
{
	listdata data;
	struct list *next;
}listlink;

extern listlink *listcreate(void);
extern void listinserthead(listlink *l, listdata data);
extern void listinserttail(listlink *l, listdata data);
extern void listprintf(listlink *l);
extern void listdelete(listlink *l, listdata data);

#endif
