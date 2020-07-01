#ifndef _PRINT_H_
#define _PRINT_H_
#if 1
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <iostream>
#include <vector>
using namespace std;
//using std::vector;

#endif

#if 1 /*************************************************************************/
class STLTest
{
public:
	~ STLTest(){
		printf("[%s][%d]:\n", __func__, __LINE__);
	};
	
	STLTest(){
		printf("[%s][%d]:\n", __func__, __LINE__);
	};
	
	STLTest(int ival, string strval);

	int setIntVal(int val);
	int setStrVal(string str);	
	int showVal();

private:
	int _ival;
	string _strval;
};
#endif /*************************************************************************/


#endif
