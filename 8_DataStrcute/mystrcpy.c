#include <stdio.h>
#include <string.h>

char *mystrcpy(char* strDest, const char* strSrc)
{
	if((strDest==NULL) || (strSrc==NULL))
		return NULL;

	int i = 0;
	char *address = strDest;
	for(i = 0; strSrc[i] != '\0'; i++)
	{
		strDest[i] = strSrc[i];
	}
	strDest[i] = '\0';

	return address;
}

int main(int argc, const char *argv[])
{
	char str1[32] = {"Hello"}, str2[32] = {0}, *pResult = NULL;

	pResult = mystrcpy(str2, str1);
	printf("pResult:%s str1:%s str2:%s\n", pResult, str1, str2);
	
	return 0;
}
