#include "stl_tools.h"
#include "print.h"

int test_STLTest(){
	STLTest mstl;
	mstl.setIntVal(32);
	mstl.showVal();

	string str = "hello";
	STLTest mstl1(10, str);
	mstl1.showVal();
	return 0;
}

int main(int argc, const char *argv[])
{
	test_STLTest();	
	return 0;
}


