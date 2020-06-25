/****************************************************************
 * FileName:slave_http
 * Author:merlin
 * Version:v1
 * Time:20160613
 * Description:这是一个HTTP协议的客户端程序
 * *************************************************************/

#include "common.h"

/******************************************************************************
 * Description：创建套接字
 * Input family：协议族
 * Input type：协议类型
 * Input protocol：
 * Return：创建好的文件描述符
 * *****************************************************************************/
int createSocket(const int family, const int type, const int protocol)
{
	int fd = socket(family, type, protocol);
	if(fd < 0)
	{
		close(fd);
		trace(ERROR, "[%s]:socket=%s LINE:%d\n", __func__, strerror(errno), __LINE__);
		return fd;
	}
	return fd;
}

/******************************************************************************
 * Description：绑定套接字
 * Input fd：需要绑定的文件
 * Input family：协议类型
 * Input addr：地址
 * Return：fd 
 * *****************************************************************************/
int bindSocket(const int fd, const int family, char *addr) 
{
	int len = 0;
	struct sockaddr_un un;

	unlink(addr);      
	memset(&un, 0, sizeof(un));   
	un.sun_family = family;   
	strcpy(un.sun_path, addr);   
	
	len = offsetof(struct sockaddr_un, sun_path) + strlen(addr);   
	if (bind(fd, (struct sockaddr *)&un, len) < 0)  
	{
		perror("bind");
		return -1;
	}   
	return fd;
}

/******************************************************************************
 * Description：监听套接字
 * Input fd：
 * Input max：listen最多可监听的文件数
 * Return：监听的文件
 * *****************************************************************************/
int listenSocket(const int fd, const int max)
{
	if(listen(fd, max) < 0)
	{
		perror("listen");
		return -1;
	}
	return fd;
}

/******************************************************************************
 * Description：接受连接请求
 * Input：
 * Input：
 * Output：
 * Return：已将接收的文件描述符
 * *****************************************************************************/
int acceptSocket(const int fd, const int family, char *addr, const int port) //TCP  UDP
{
	socklen_t len = 0;
	int cfd = 0;
	struct sockaddr_in un;

	un.sin_family = family;
	//un.sin_addr.sin_addr.s_addr = addr;
	//un.sin_addr.sin_addr.s_addr = INADDR_ANY;
	un.sin_port = htons(port);

	len = sizeof(struct sockaddr_in);
	cfd = accept(fd, (struct sockaddr *)&un, &len);
	if(cfd < 0)
	{
		perror("accept");
		return -1;
	}
	return cfd;
}

/******************************************************************************
 * Description：申请和服务器端建立连接
 * Input：
 * Output：
 * Return：
 * *****************************************************************************/
int connectSocket(int *fd, const int family, char *ip, const int port) //TCP UDP
{
	struct sockaddr_in addr;

	addr.sin_family = family;
	//un.sin_addr.sin_addr.s_addr = addr;
	//inet_pton(AF_INET, ip, addr.sin_addr.sin_addr.s_addr);
	inet_pton(AF_INET, ip, &(addr.sin_addr));
	addr.sin_port = htons(port);

	//if(connect(*fd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) < 0)
	if(0 > connect(*fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)))
	{
		//perror("connect");
		close(*fd);
		trace(ERROR, "[%s]:connect=%s LINE:%d\n", __func__, strerror(errno),__LINE__);
		return -1;
	}
	return 0;
}

