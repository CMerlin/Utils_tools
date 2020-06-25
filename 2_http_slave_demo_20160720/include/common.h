/****************************************************************
 * Copyright(C), 2016, Hanbang Tech.Co.,Ltd
 * File Name:common.h
 * Author:merlin
 * Version:v1
 * Data:20160613
 * Description:一些共用结构体的定义
 * History:
 * *************************************************************/

#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <time.h>
#include <termios.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/un.h>
#include <sys/poll.h>
#include <stdarg.h>
#include <stddef.h>
#include <sys/sem.h>
#include <pthread.h>
#include <sys/time.h>
#include <mxml.h>
#include <stdbool.h>

/* 数据类型定义 */
typedef signed char         sint8;
typedef signed short        sint16;
typedef signed int          sint32;
typedef signed long         slng32;
typedef signed long long    sint64;
typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned int        uint32;
typedef unsigned long       ulng32;
typedef unsigned long long  uint64;

/* 模块ID定义 */
typedef enum
{
    COMP_COMMON         = 0, 
    COMP_VIDEOIN        = 1, 
    COMP_VIDEOOUT       = 2, 
    COMP_VIDEOENC       = 3, 
    COMP_VIDEODEC       = 4, 
    COMP_AUDIOIN        = 5, 
    COMP_AUDIOOUT       = 6, 
    COMP_AUDIOENC       = 7, 
    COMP_AUDIODEC       = 8, 
    COMP_RECORD         = 9, 
    COMP_PLAYBACK       = 10, 
    COMP_STATMACH       = 11, 
    COMP_NETMS          = 12, 
    COMP_NETVOD         = 13, 
    COMP_NETUPGRADE     = 14, 
    COMP_NETCMD         = 15, 
    COMP_WEBSERV        = 16, 
    COMP_SERIAL         = 17, 
    COMP_PTZ            = 18, 
    COMP_GUI            = 19, 
    COMP_FIFO           = 20, 
    COMP_EVENT          = 21, 
    COMP_MFS            = 22, 
    COMP_MSHEAD         = 23, 
    COMP_OSD            = 24, 
    COMP_VIDEOVPP       = 25, 
    COMP_LINK           = 26, 
    COMP_TIMER          = 27, 
    COMP_RTC            = 28, 
    COMP_ALARM          = 29,   /* 报警模块 */
    COMP_MSG            = 30,   /* 消息队列 */
    COMP_SEM            = 31,   /* 进程间信号灯 */
    COMP_SHM            = 32,   /* 进程间共享内存 */
    COMP_NTP            = 33, 
    COMP_DDNS           = 34, 
    COMP_PPPOE          = 35, 
    COMP_SYS            = 36, 
    COMP_NETWORK        = 37, 
    COMP_TRANSUART      = 38, 
    COMP_DAEMON         = 39, 
    COMP_PROCFIFO       = 40, 
    COMP_EXTCMD         = 41, 
    COMP_SERIALKEYPAD   = 42, 
    COMP_RAID           = 43, 
    COMP_CMS            = 44,   /* 集中管理平台 */
    COMP_HVO            = 45,   /* 高清视频输出 */
    COMP_NETAPI         = 46,   /* 网络接口模块 */
    COMP_SSMTP          = 47,   /* SSMTP模块 */
    COMP_VIDEOAD        = 48,   /* 视频AD模块 */
    COMP_PCIV           = 49,   /* 主从片间通讯PCIV模块 */
    COMP_CDRAPP         = 50,   /* 刻录模块 */
    COMP_PCIVMSG        = 51,   /* PCIV模块 */
    COMP_VIDEOCFG       = 52,   /* 视频基础模块的配置模块 */
    COMP_ATMI           = 53,   /* ATM智能模块 */
    COMP_SOFTRAID       = 54, 
    COMP_VIDEOVOSD      = 55,   /* 视频基础模块的OSD模块 */
    COMP_FTPUPGRADE     = 56,   /* FTP升级模块 */
    COMP_FONT           = 57, 
    COMP_LIST           = 58, 
    COMP_DEBUGS         = 59, 
    COMP_SMART          = 60, 
    COMP_MFSCOMM        = 61, 
    COMP_MFSFAT32       = 62, 
    COMP_MFSDEV         = 63, 
    COMP_MFSFS          = 64, 
    COMP_MFSLOG         = 65,
    COMP_MFSSTORE       = 66, 
    COMP_MFSCTRL        = 67, 
    COMP_MFSQUERY       = 68, 
    COMP_MFSPLAYBACK    = 69, 
    COMP_MFSBACKUP      = 70, 
    COMP_VIDEOVPSS      = 71,
    COMP_VIDEOVDA       = 72,
    COMP_HBSDK          = 73,
    COMP_CONFIG         = 74,
    COMP_DEVLIB         = 75,   /* 外围设备抽象层模块 */
    COMP_TOAVI          = 76, 
    COMP_MEMMANAGE      = 77,   /* 内存管理模块 */
    COMP_GUITRANS       = 78,   /* GUI转换层 */
    COMP_NETCOMM        = 79,   /* 网络基础模块 */
    COMP_CYASSL         = 80,   /* 邮件上传加密模块 */
    COMP_HUAKE          = 81,   /* 华科平台 */
    COMP_TOMP4          = 82,   /* MP4转换模块 */
    COMP_BLOWFISH       = 83,   /* BLOWFISH加解密模块 */
    COMP_RC4            = 84,   /* RC4加解密模块 */
    COMP_MD5            = 85,   /* MD5加密模块 */
    COMP_BASE64         = 86,   /* BASE64加解密模块 */
    COMP_MFSBTREE       = 87,   /* MFS_BTREE模块 */
    COMP_PROCCOMM       = 88,   /* PROC_COMM模块 */
    COMP_MFSLINK        = 89,   /* MFS_LINK模块 */
    COMP_MFSFCLK        = 90,   /* MFS_FCLK模块 */
    COMP_MFSFILE        = 91,   /* MFS_FILE模块 */
    COMP_MFSNFS         = 92,   /* MFS_NFS模块 */
    COMP_UPNP           = 93,   /* UPNP模块 */
    COMP_TEST           = 94,   /* 测试模块 */
    COMP_IPDEV          = 95,   /* IPDEV模块 */
    COMP_RTSP           = 96,   /* RTSP模块 */
    COMP_PNP            = 97,   /* IPC即插即用 */
    COMP_FTPAPI         = 98,   /* FTP应用接口模块 */
    COMP_DHCP           = 99,   /* DHCP服务器 */
    COMP_POE            = 100,  /* POE模块 */
    COMP_MFSMKFS        = 101,  /* MFS_MKFS模块 */
    COMP_FLASHLOG       = 102,  /* 写FLASHLOG模块 */
    COMP_VPN            = 103,  /* VPN模块 */
    COMP_SSTRING        = 104,  /* SSTRING模块 */
    COMP_THREADPOOL     = 105,  /* THREADPOOL模块 */
    COMP_MPOOL          = 106,  /* 内存池MPOOL模块 */
    COMP_DIAGNOSIS      = 107,  /* 网络诊断模块 */
    COMP_RTMP           = 108,  /* RTMP模块 */
    COMP_ISAPI          = 109,  /* ISAPI模块 */
    COMP_AUDIOCFG       = 110,  /* 音频基础模块的配置模块 */
    COMP_RTSPSRV        = 111,  /* RTSP SERVER模块*/
    COMP_SDKAUDIOPRO    = 112,  /* 音频处理模块,主要处理报警,对讲音频 */
    COMP_POECTRL        = 113,  /* POE功率控制模块 */
    COMP_NDCMP          = 114,  /* 设备组网管理模块 */
    COMP_SSOCKET        = 115,  /* 网络套接字基础模块 */
    COMP_NDCMPSRV       = 116,  /* 设备组网管理服务器模块 */
    COMP_DANALE         = 117,  /* 大拿穿透服务 */
    COMP_MAX
} COMPID, *PCOMPID;

/*日志系统用到的打印级别*/
typedef enum
{
	RELEASE,
	ERROR,
	TRACE,
	DEBUG,
} PRINT_LEVEL_E;

/*错误码：函数执行错误的原因*/
typedef enum
{
	SUCCEED, //执行成功
	ERROR_INFO_MIN = -100,
	NULL_VALUE, //传入的参数为null
	CREATE_SOCKET, //创建套接字失败
	CONNECT_FAILED, //创建连接失败
	CREATE_PACKAGE, //创建数据包失败
	SEND_ERROR, //发送数据失败
	RECEIVE_ERROR, //接收数据失败
	XML_WRONG, //http响应帧中没有xml数据
	CREATE_XML, //组装xml文件失败
	HTTP_WRONG, //不正确的http数据帧
	HTTP_EXTEND, //不上上层应用所需要的HTTP数据包
	HTTP_CREATE, //创建http请求包失败
	MEMORY_FAILURE, //获取内存失败
}ERROR_INFO_E;

/*临时结构体*/
typedef struct _interim_data
{
	int id;
	int ip;
	int data;
} ITERIM_DATA_S, *PITERIM_DATA_S;

/*虚拟参数*/
typedef struct _isapi_null
{
	sint32 dummy;
} ISAPI_NULL_S;


/*日志系统相关的函数*/
extern int init_print_level();
extern int trace(const int plevel, const char *format, ...);
/*字符串处理函数*/
extern char* lstrtok_r(char *s, const char *delim, char **save_ptr);
extern int web2master_log_querytype_switch(char * query_xml, int * pri_type, int * sec_type);
#endif
