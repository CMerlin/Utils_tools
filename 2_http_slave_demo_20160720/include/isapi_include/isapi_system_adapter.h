#ifndef _ISAPI_SYSTEM_ADAPTER_H_
#define _ISAPI_SYSTEM_ADAPTER_H_

#include "isapi_adapter.h"
#include "config_usr.h"
#include "config.h"
#include "sys_net.h"
#include "sys_netapi.h"

#define UPGRADE_TEMP_FILE	"/tmp/upgrade.bin"

#define MAX_DEVINFO_STR_LEN 32
#define MAX_IP_ADDR_LEN     64

typedef struct
{
    char dev_name[MAX_DEVINFO_STR_LEN];     /* 设备名称 */
    char dev_no[MAX_DEVINFO_STR_LEN];       /* 设备序列号 */
    char dev_id[MAX_DEVINFO_STR_LEN];       /* 设备号 */
    char dev_type[MAX_DEVINFO_STR_LEN];     /* 设备型号 */
    char main_ver[MAX_DEVINFO_STR_LEN];     /* 主控版本 */
    char main_date[MAX_DEVINFO_STR_LEN];
    char venc_ver[MAX_DEVINFO_STR_LEN];     /* 编码版本 */
    char venc_date[MAX_DEVINFO_STR_LEN];
	uint32 telecontrol_id;                  /* 串口控制号 */
    uint32 ch_num;                          /* 通道个数 */
    uint32 disk_num;                        /* 硬盘个数 */
    uint32 sensor_in;                       /* 报警输入个数 */
    uint32 sensor_out;                      /* 报警输出个数 */
    uint32 ipc_pap;                         /* IPC即插即用使能 */
}SYSTEM_DEVICE_INFO_S, *PSYSTEM_DEVICE_INFO_S;

typedef struct
{
    uint32 sec : 6;     /* 秒: 0~63 */
    uint32 min : 6;     /* 分: 0~63 */
    uint32 hour : 5;    /* 时: 0~23 */
    uint32 day : 5;     /* 日: 1~31 */
    uint32 month : 4;   /* 月: 1~12 */
    uint32 year : 6;    /* 年: 0~63 */
}SYSTEM_TIME_S, *PSYSTEM_TIME_S;

#if 0
typedef struct
{
    uint16  autontp_enable;                     /* NTP校时使能 */// 开启ntp服务,0- 不启用 ,1-表示自动 ，2-表示手动
    //uint16  ntp_mt;                     /* 手动校时使能 */
    uint16 server_index;         // 服务器索引号
    char    ntp_host[MAX_IP_ADDR_LEN];   /* NTP服务器域名 */
    uint32  ntp_port;               /* NTP服务器端口 */
    uint16  ajust_period;               /* NTP校时周期() */
    uint16 sync_unit;                   /* 周期单位，0-分钟 1-小时 2-天 3-星期 4-月*/
    SYSTEM_TIME_S dev_time;        /* 主机时间 */
    SYSTEM_TIME_S set_time;        /* 设置时间 */
    uint16 syn_systime;             /* 与本地时间同步使能 */
    uint16 reserve;                 /* 保留位 */
}SYSTEM_NTP_CFG_S;

typedef struct
{
    SYSTEM_NTP_CFG_S   ntp_set;            /* ntp设置 */
    sint32           time_zone;            /* 时区 */
}SYSTEM_TIME_CFG_S, *PSYSTEM_TIME_CFG_S;
#else
typedef struct
{
    char    ntp_host[MAX_IP_ADDR_LEN];   /* NTP服务器域名 */
    uint32  ntp_port;               /* NTP服务器端口 */
    uint32  autontp_enable;                     /* NTP校时使能 */// 开启ntp服务,0- 不启用 ,1-表示自动 ，2-表示手动
    uint32  server_index;         // 服务器索引号
    uint32  ajust_period;               /* NTP校时周期() */
    uint32  sync_unit;                   /* 周期单位，0-分钟 1-小时 2-天 3-星期 4-月*/
    sint32  time_zone;            /* 时区 */
}SYSTEM_NTP_CFG_S, *PSYSTEM_NTP_CFG_S;

typedef struct
{
    SYSTEM_TIME_S    dev_time;        /* 主机时间 */
}SYSTEM_TIME_CFG_S, *PSYSTEM_TIME_CFG_S;
#endif

typedef struct
{
    char   almin_name[MAX_STRING];
    sint32 enabled;
    sint32 triggering;    
}SYSTEM_IO_INPUT_S, *PSYSTEM_IO_INPUT_S;

typedef struct
{
    SYSTEM_IO_INPUT_S  io_input[MAX_AM];
}SYSTEM_IO_INPUTLIST_S, *PSYSTEM_IO_INPUTLIST_S;

typedef struct
{
    char almout_name[MAX_STRING];
    int defaultState;
    int outputState;
    int pulseDuration;
}SYSTEM_IO_OUTPUT_S, *PSYSTEM_IO_OUTPUT_S;

typedef struct
{
    SYSTEM_IO_OUTPUT_S  io_output[MAX_AMOUT];
}SYSTEM_IO_OUTPUTLIST_S, *PSYSTEM_IO_OUTPUTLIST_S;

typedef struct
{
    char   isRegular[32];
    sint32 splitSum;
    sint32 type;
}SYSTEM_ZERO_SPLIT_S, *PSYSTEM_ZERO_SPLIT_S;

typedef struct
{
    sint32              zeropb_support; //是否支持零通道回放 0:不支持 1:支持
    sint32              talk_support;	//是否支持对讲 0 --不支持	1--支持 
    SYSTEM_ZERO_SPLIT_S zero_split;  //零通道画面格式 SYSTEM_ZERO_SPLIT_E
}SYSTEM_DEVICE_SUPPORT_S, *PSYSTEM_DEVICE_SUPPORT_S;

sint32 system_set_device_reboot(int param);

sint32 system_set_device_reset(sint32 flag, WEB_CMD_INFO_S *webinfo);

sint32 system_get_device_info(SYSTEM_DEVICE_INFO_S * dev_info);

sint32 system_set_device_info(SYSTEM_DEVICE_INFO_S * dev_info, WEB_CMD_INFO_S *webinfo);

sint32 system_get_device_capabilities(SYSTEM_DEVICE_SUPPORT_S *device_support);

sint32 system_get_device_time(SYSTEM_TIME_CFG_S * time_cfg);

sint32 system_set_device_time(SYSTEM_TIME_CFG_S * time_cfg, WEB_CMD_INFO_S *webinfo);

sint32 system_set_io_inputs(int almin_num, SYSTEM_IO_INPUTLIST_S *inputlist, WEB_CMD_INFO_S *webinfo);

sint32 system_set_io_outputs(int almout_num, SYSTEM_IO_OUTPUTLIST_S *io_outputlist, WEB_CMD_INFO_S *webinfo);

#endif

