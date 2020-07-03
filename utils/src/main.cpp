/********************************************************************************************
* Brief：
********************************************************************************************/
#include "com_utils.h"
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

int get_local_mac(char *mac, int len_limit){
    struct ifreq mifreq;
    int sock = 0;
	if ((sock = socket (AF_INET, SOCK_STREAM, 0)) < 0){
        printf("[AIR][Er][%s][%d]:info=%s\n", __func__, __LINE__, strerror(errno));
        return -1;
    }
    strcpy (mifreq.ifr_name, "eth0");
    if (ioctl (sock, SIOCGIFHWADDR, &mifreq) < 0){
        printf("[AIR][Er][%s][%d]:info=%s\n", __func__, __LINE__, strerror(errno));
        return -1;
    }
	snprintf (mac, len_limit, "%X:%X:%X:%X:%X:%X", (unsigned char) mifreq.ifr_hwaddr.sa_data[0], 
	(unsigned char) mifreq.ifr_hwaddr.sa_data[1], (unsigned char) mifreq.ifr_hwaddr.sa_data[2], (unsigned char)
	mifreq.ifr_hwaddr.sa_data[3], (unsigned char) mifreq.ifr_hwaddr.sa_data[4], (unsigned char)mifreq.ifr_hwaddr.sa_data[5]);
	printf("[AIR][%s][%d]:mac=%s\n", __func__, __LINE__, mac);
	return 0;
}

int main(int argc, const char *argv[])
{
	char mac_addr[32] = {0};
	get_local_mac(mac_addr, sizeof(mac_addr));
	//test_STLTest();
	//test_myString();
	return 0;
}


