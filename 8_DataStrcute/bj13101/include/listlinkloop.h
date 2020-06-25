#ifndef _LISTLINKLOOP_H
#define _LISTLINKLOOP_H

typedef int listdata;

typedef struct list
{
	listdata data;
	struct list *next;
}listlinkloop;

extern listlinkloop *listcreate(void);
extern void listinserttail(listlinkloop *l, listdata data);
extern void listprintf(listlinkloop *l);
extern listlinkloop *listcuthead(listlinkloop *l);

#endif
