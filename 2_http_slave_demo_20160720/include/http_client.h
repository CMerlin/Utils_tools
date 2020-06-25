/****************************************************************
 * Copyright(C), 2016, Hanbang Tech.Co.,Ltd
 * File Name:slave_http
 * Author:merlin
 * Version:v1
 * Data:20160613
 * Description:HTTP客户端的实现
 * History:
 * *************************************************************/

#ifndef _HTTP_CLIENT_H_
#define _HTTP_CLIENT_H_

#include "common.h"
#include "user_socket.h"
#include "xml_common.h"

/*收发的数据帧的特点描述*/
typedef enum
{
	PACKET_ATTR_MIN_E,
	PACKET_ATTR_HEADANDTAIL_E, //有头有尾
	PACKET_ATTR_HEAD_E, //有头无尾
	PACKET_ATTR_LEN_E, //固定长度
	PACKET_ATTR_SPECIAL_E, //特殊字符串
	PACKET_ATTR_TAIL_E, //只有尾巴
	PACKET_ATTR_MAX_E,
} PACKET_ATTR_E;

/*HTTP方法*/
typedef enum
{
	HTTP_GET, //get
	HTTP_PUT, //put
	HTTP_POST, //post
} HTTP_METHODS_E;

/*数据包的属性信息*/
typedef struct _package_attr
{
	char head[32]; // 数据帧的头
	char tail[32]; //数据帧的尾
	char special[32]; //数据帧中的某些特殊字符串
	int len; //数据帧的长度
	int attr; //数据帧的特性 PACKET_ATTR_E  1-有头有尾 2-有头无尾 3-固定长度[无头无尾] 4-特殊字符串
} PACKET_ATTR_S, *PPACKET_ATTR_S;

/*HTTP属性设置相关的信息*/
typedef enum
{
	KEEP_ALIVE, //长连接
	CLOSE, //短连接
} CONNECTION_E;

/*设备的本地网络信息*/
typedef struct _local_network_attr
{
	char ip[64]; //IP
	char gateway[64]; //网关
	char mask[64]; //子网源码
	char dns1[64]; //首选DND
	char dns2[64]; //备用DNS
	char hwaddr[64]; //MAC地址
} SLOCAL_NETWORK_ATTR, *P_SLOCAL_NETWORK_ATTR;

/*HTTP请求包的头相关设置项*/
typedef struct _http_attr
{
	char name[64]; //用户名
	char password[64]; //密码
	char ip[64]; //http Web服务器端的地址，格式是192.168.xx.xx
	sint32 port; //建立连接后的端口号
	CONNECTION_E connection; //http客户端和服务器端的连接方式,可用的值见 CONNECTION_E
} HTTP_ATTR_S, *PHTTP_ATTR_S; 

/*用于连接的网络信息*/
typedef struct _network_attr_S
{
	int fd; //文件描述符
	int connect; //连接状态
	CONNECTION_E type; //连接方式
	time_t btime; //建立连接开始的时间
	char ip[64]; //IP地址
	int port; //端口号	
	int complete; //发送和是否完成了接受
} NETWORK_ATTR_S, *PNETWORK_ATTR_S;

/*设置或获取http相关的属性*/
extern sint32 isapi_set_http_attr(HTTP_ATTR_S *attr);
extern sint32 isapi_get_http_attr(HTTP_ATTR_S *attr);
/*设置或获取当前HTTP的通信状态*/
extern sint32 isapi_get_connect_status(NETWORK_ATTR_S *attr);
extern sint32 isapi_set_connect_status(NETWORK_ATTR_S *attr);
/*http通信相关的接口*/
extern sint32 retry_connect_server_block(NETWORK_ATTR_S *server);
extern sint32 read_write_process(NETWORK_ATTR_S *server, const void* src, void *dest, sint32 dest_size);
extern sint32 checkHttpData(const void *buffer);
extern sint32 send_receive_data(const void *tx_buffer, void *rx_buffer, const sint32 rx_len);
extern sint32 get_http_package(const void *url, const void *http_body, void *buffer, const int size);
extern sint32 create_http_package(HTTP_METHODS_E methods,  const void *url, const void *xml, void *buffer, const int buffer_len);
extern sint32 put_http_head(const void *url, void *buffer, const int size, const int body_len);
//extern int getXmlData(const void *src, uint8 *dest, int dest_size, uint8 *node_name);
//extern int getXmlDataFromHttp(const void *src, uint8 *dest, int dest_size);
extern sint32 http_package(HTTP_METHODS_E methods,  const void *url, const void *tx_data, void *rx_data, const int data_len);

#endif
