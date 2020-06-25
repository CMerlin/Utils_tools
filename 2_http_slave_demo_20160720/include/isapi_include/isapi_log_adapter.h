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

#ifndef _ISAPI_LOGADAPTER_H_
#define _ISAPI_LOGADAPTER_H_

#include "isapi_adapter.h"
#include "sys_net.h"
#include "sys_netapi.h"
#include "log.h"


#define WEB_LOG_PAGE_SIZE 500

typedef struct
{
    SYSTIME time;  // 记录日志时间
    char pri_type;     // 主类型
    char sec_type;     // 次类型
    char param;        // 操作类型
    char channel;      // 通道号
    int host;        // 0-主机 其他 –远程IP如0xc0a80006
    char user[17];     // 用户名
    char hard_driver;  // 硬盘号
    char sensor_in;    // 报警输入
    char sensor_out;   // 报警输出
    char reserve[32];  // 保留
} WEB_LOGINFO_S, *PWEB_LOGINFO_S;


typedef struct SearchLog
{
    char sid[128];
    char mid[128];
    SYSTIME start_time;
    SYSTIME end_time;
    int  pri_type;   
    int  sec_type;
    int startindex;//查询起始位置
    int max_ret;       
    int result_ret;
    int real_totalnum;//实际满足查询条件的总数量
    WEB_LOGINFO_S log_data[WEB_LOG_PAGE_SIZE];
} SearchLog_S, *pSearchLog_S;

typedef struct
{
    char weblogstr[32];
    int  hostlogindex;
}LOG_TYPE_TRANS, *PLOG_TYPE_TRANS;

int GetISSearchLog(SearchLog_S * search_log);
int master_get_paratype(int index, SearchLog_S * search_log, char *paradata);
int master2web_log_opertype_switch(int index, SearchLog_S * search_log);
int web2master_log_querytype_switch(char * query_xml, int * pri_type, int * sec_type);

#endif
