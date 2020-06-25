/*
 * FileName:
 * Author:         luny  Version: 1.0  Date: 2014-5-6
 * Description:
 * Version:
 * Function List:
 *                 1.
 * History:
 *     <author>   <time>    <version >   <desc>
 */

#ifndef _ISAPI_ISAPIADAPTER_H_
#define _ISAPI_ISAPIADAPTER_H_

#include <string.h>

#include "common.h"
#include "isapi.h"
#include "sys_net.h"

#define MAX_STREAMID 2
#define MAX_INPUTIO 4
#define MAX_OUTPUTIO 4
#define MAX_INTPUTPROXYCH 32

#define MAX_STRLEN_128 128
#define MAX_STRLEN_32 32
#define WEEK_DAYNUM  7
#define DAY_SEGNUM 6


typedef enum addressingFormatType
{
    ipaddress = 1,
    hostname = 2
} addrtype_e;

#if 0
char addrtype_c[][16] =
{
    "ipaddress",
    "hostname"
};
#endif

typedef struct 
{
    sint32 max_value;
    sint32 min_value;
} ADAPTER_RANGE_S; //范围限定结构体

typedef struct 
{
    sint16 width;
    sint16 height;
}ADAPTER_RES_S;

typedef struct
{
    uint16 left; //起始点横坐标
    uint16 top; //起始点纵坐标
    uint16 width; //宽度
    uint16 height; //高度
} ADAPTER_AREA_S;


#define ADAPTER_MAX_LIST 16

typedef struct timeSpan
{
    SYSTIME start;
    SYSTIME end;
} timeSpan_S, *ptimeSpan_S;

typedef struct
{
    timeSpan_S tmperiod[DAY_SEGNUM];    
}TIMEPERIOD_S, *PTIMEPERIOD_S;

typedef struct
{
    TIMEPERIOD_S timeperiodinfo[WEEK_DAYNUM];
}SCHEDULEINFO_S, *PSCHEDULEINFO_S;

typedef struct
{
    char user_name[MAX_STRING];
    int remoteip;
}WEB_CMD_INFO_S, *PWEB_CMD_INFO_S;

sint32 isapi_adapter_init(notifycallback notifyfunc);
PNETAPICALLBACK isapi_netapi_callback(sint32 cmd, sint32 channel, sint32 * param, sint32 param_size, sint32 flag);
int isapi_cmd_check_permission(char *username, sint32 cmd, sint32 channel);
int isapi_log_write(WEB_CMD_INFO_S * webinfo, sint32 channel, sint8 pri_type, sint8 sec_type, sint8 param_type);
int hostschedule_trans_webschedule(PT_TMSCHEDULE_S *hostschedule, SCHEDULEINFO_S *webschedule);
int webschedule_trans_hostschedule(SCHEDULEINFO_S *webschedule, PT_TMSCHEDULE_S *hostschedule);


#endif

