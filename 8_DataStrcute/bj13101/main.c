#include "listlinkloop.h"
#include <string.h>

#if 0
int main(void)
{
	listseq *l = listcreate();
	listdata s;
	int i = 1;

	strcpy(s.name, "niu");

	while(listfull(l) == 0)
	{
		s.age = i++;
		listinsert(l, s);
	}

	s.age = 6;
	listdelete(l, s);

	listprintf(l);

	return 0;
}
#endif

#if 0
int main(void)
{
	listlink *l = listcreate();
	listdata s;

	strcpy(s.name, "niu");
	s.age = 20;
	listinserthead(l, s);

	strcpy(s.name, "liu");
	s.age = 25;
	listinserthead(l, s);

	strcpy(s.name, "zhang");
	s.age = 30;
	listinserttail(l, s);

	s.age = 30;
	listdelete(l, s);

	listprintf(l);

	return 0;
}
#endif

#if 1
int main(void)
{
	listlinkloop *l = listcreate();
	int i;

	for(i=1; i<=8; i++)
	{
		listinserttail(l, i);
	}

	l = listcuthead(l);

	listprintf(l);

	return 0;
}
#endif
