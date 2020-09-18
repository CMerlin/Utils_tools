#ifndef _RTC_QUEUE_H_
#define _RTC_QUEUE_H_

#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>


#if 1 /*[B][call c func]:***********************************************/
#ifdef __cplusplus
extern "C" {
#endif

#define __LINUX_DEV__ 1
#ifdef __LINUX_DEV__
#include <stdio.h>
//#define LOGINFO(format, ...) printf(format "\n", ##__VA_ARGS__)
#define TRACEV(format, ...) printf(format, ##__VA_ARGS__)
#define LOGINFO(format, ...) printf(format, ##__VA_ARGS__)
#define TRACEI(format, ...) printf(format, ##__VA_ARGS__)
#define TRACEW(format, ...) printf(format, ##__VA_ARGS__)
#define LOGERR(format, ...) printf(format, ##__VA_ARGS__)
#else /* LOG FILE */
#define LOGERR(format, ...) printf(format, ##__VA_ARGS__)
#endif /*__LINUX_DEV__*/

#define RTC_QUEUE 1
#define RTC_QUEUE_H 1

#if RTC_QUEUE_H /* RTC_QUEUE_H ****************************************************************/
enum e_media_type{
	EAV_AUDIO,
	EAV_VIDEO,
	EAV_UNKNOW
};
	
typedef struct _av_pkg{
	int type; /*e_media_type*/
	unsigned char *data;
	int data_len;
	unsigned long long pts; /* from 1970 us */
	/* vide attr */
	int width;
	int height;
	short key;
	/*audio attr*/
}S_AV_PKG;

typedef S_AV_PKG QDataType;

//typedef int QDataType;
typedef struct QNode
{
	struct QNode* _pNext;
	QDataType _data;
}QNode;
 
typedef struct Queue
{
	QNode* _front;
	QNode* _back;
}Queue;

typedef struct _video_pkg{
	int type;
	unsigned char *data;
	int data_len;
	unsigned long long pts; /* from 1970 us */
	int width;
	int height;
}S_VIDEO_PKG;

#endif /* RTC_QUEUE_H ****************************************************************/

void QueueInit(Queue* q);//队列初始化
void QueuePush(Queue* q, QDataType data);//入队
void QueuePop(Queue* q);//出队
QDataType QueueFront(Queue* q);//获取队头元素
QDataType QueueBack(Queue* q);//获取队尾元素
int QueueSize(Queue* q);//队列中有效元素的个数
int QueueEmpty(Queue* q);//队列是否为空
void QueueDestory(Queue* q);//销毁队列
//uint64_t get_sys_time_ms();
//int sip_pjsua_init();
int test_func_queue();

#ifdef __cplusplus
}
#endif
#endif /*[E][call c func]:***********************************************/


#endif /* _RTC_QUEUE_H_ */
