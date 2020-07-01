/******************************************************************************************
* Brif:
*
*******************************************************************************************/

//#include <stdio.h>
//#include <string.h>
#include "stl_tools.h"

#if 1 /*************************************************************************/
int STLTest::setIntVal(int val){
	_ival = val;
	return 0;
}

int STLTest::setStrVal(string str){
	_strval = str;
	return 0;
}

int STLTest::showVal(){
	//printf("[%s][%d]:ival=%d\n", __func__, __LINE__, _ival);
	std::cout<<"["<<__func__<<"]"<<"["<<__LINE__<<"]:"<<"ival="<<_ival<<" strval="<<_strval<<std::endl;
	return 0;
}
STLTest::STLTest(int ival, string strval){
	printf("[%s][%d]:\n", __func__, __LINE__);
	_ival = ival;
	_strval = strval;
}
#endif /*************************************************************************/


