#ifndef _ISAPI_EVENTADAPTER_H_
#define _ISAPI_EVENTADAPTER_H_

#include "isapi_adapter.h"
#include "sys_net.h"
#include "sys_netapi.h"

typedef enum
{
    EVENT_DISK_FULL = 0,//硬盘满
    EVENT_DISK_ERR,//硬盘错误
    EVENT_NET_DISCONNENT,//网络断开
    EVENT_IP_COLLISION,//IP冲突
    EVENT_ILLACCESS,//非法访问
    EVENT_BADVIDEO,//视频信号异常
    EVENT_VIDEOMISMATCH,//视频制式不匹配
    EVENT_RECORD_FAILURE,//录像或抓图异常
    EVENT_VIDEO_LOSS  //视频丢失
}TRIGGER_TYPE_E;

typedef struct
{
    int enable;//开关
    int beep; //蜂鸣器
    int fullscreen;//全屏
    int email;//邮件上传
    int almpush;//报警上传
    int sensor_out;
    int temp_limit;//报警温度(温度报警有效)
    int outputDelay;//报警输出延时时间
    int almoutaudio;//输出音频
    int ptzEnable;//联动预置点开关
    uint32 presetenable[MAX_CH];//联动跳预置点
    int link_record[MAX_CH];
    int link_snap[MAX_CH];//截图联动
}TRIGGER_INFO_S, *PTRIGGER_INFO_S;

typedef struct
{
    char event_type[32];//事件类型
    TRIGGER_INFO_S triggerinfo;
    SCHEDULEINFO_S scheduleinfo;
} EVENT_TRIGGER_S, *PEVENT_TRIGGER_S;

typedef struct
{
    int status[32];
    int alarm_out_no;
} EVENT_MANUAL_S, *PEVENT_MANUAL_S;

int event_get_trigger_info (EVENT_TRIGGER_S * event_info);
int event_set_trigger_info (EVENT_TRIGGER_S * event_info, WEB_CMD_INFO_S *webinfo);
int event_get_schedule_info (EVENT_TRIGGER_S * event_info);
int event_set_schedule_info (EVENT_TRIGGER_S * event_info, WEB_CMD_INFO_S *webinfo);
int event_get_manual_info(PEVENT_MANUAL_S info);
int event_set_manual_info(PEVENT_MANUAL_S info);

#endif

