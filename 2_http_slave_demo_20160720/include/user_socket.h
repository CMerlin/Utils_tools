/****************************************************************
 * Copyright(C), 2016, Hanbang Tech.Co.,Ltd
 * File Name:slave_http
 * Author:merlin
 * Version:v1
 * Data:20160613
 * Description:TCP和UDP通信相关接口的定义
 * History:
 * *************************************************************/
#ifndef _USER_SOCKET_H_
#define _USER_SOCKET_H_

#include "common.h"

extern int createSocket(const int family, const int type, const int protocol);
extern int bindSocket(const int fd, const int family, char *addr); 
extern int listenSocket(const int fd, const int max);
extern int acceptSocket(const int fd, const int family, char *addr, const int port); //TCP  UDP
extern int connectSocket(int *fd, const int family, char *ip, const int port); //TCP UDP

#endif
