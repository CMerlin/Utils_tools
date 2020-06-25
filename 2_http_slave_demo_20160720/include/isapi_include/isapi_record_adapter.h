/*
 * FileName:
 * Author: luny  Version: 1.0  Date: 2014-5-6
 * Description:
 * Version:
 * Function List:
 *                 1.
 * History:
 *     <author>   <time>    <version >   <desc>
 */


#ifndef _ISAPI_RECORDADAPTER_H_
#define _ISAPI_RECORDADAPTER_H_

#include "isapi_adapter.h"
#include "sys_net.h"
#include "sys_netapi.h"

#define MAX_ADAPTER_REC_SEG 1000


typedef struct trackDailyParam
{
    int year;
    int month;
    int days[32];
} trackDailyParam_S, *ptrackDailyParam_S;

typedef struct SearchRec
{
    char sid[64];
    int track_id;
    timeSpan_S time_span;
    int startindex;//查询起始位置
    int max_ret;//查询最大条数
    int real_totalnum;//实际满足查询条件的总数量
    int seg_num;//当前传输数量
    int success;
    char seg_buf[280000]; //MAX_ADAPTER_REC_SEG * sizeof(PT_RECFILE_SEGINFO_S) = 32000
} SearchRec_S, *pSearchRec_S;

typedef struct SearchRecRet
{
    char sid[36];
    int track_id;
    timeSpan_S time_span;
    int max_ret;
} SearchRecRet_S, *pSearchRecRet_S;

typedef struct
{
    int starth;  //开始小时
    int startm;  //开始分钟
    int endh;    //结束小时
    int endm;    //结束分钟
}RECORD_TMPERIOD_S, *PRECORD_TMPERIOD_S;

typedef enum
{
    RECORD_CMR = 0,
    RECORD_MOTION,
    RECORD_ALARM,
    RECORD_EDR,
    RECORD_ALARMANDMOTION
}RECORD_MODE_E;

typedef enum
{
    RECORD_WEEK_MON,        //星期一
    RECORD_WEEK_TUES,       //星期二
    RECORD_WEEK_WED,        //星期三
    RECORD_WEEK_THUR,       //星期四
    RECORD_WEEK_FRI,        //星期五
    RECORD_WEEK_SAT,        //星期六    
    RECORD_WEEK_SUN        //星期日
} RECORD_WEEK_E;


typedef struct
{
    RECORD_MODE_E recordmode;
    RECORD_TMPERIOD_S tmperiod;    
}RECORD_SCHEDULEINFO_S, *PRECORD_SCHEDULEINFO_S;

typedef struct
{
    RECORD_SCHEDULEINFO_S scheduleinfo[DAY_SEGNUM];//8段时间设置
}RECORD_TRACKSINFO_S, *PRECORD_TRACKSINFO_S;

typedef struct 
{
    int resolution_w;
    int resolution_h;
    int framerate;
    int bitrate;
    int track_enable;//录像计划是否启用
    int SaveAudio;//是否记录音频
    int Duration;//录像过期时间
    int LoopEnable;//是否循环录像
    int RedundancyRecord;//是否冗余录像
    int PreRecordTimeSeconds;//预录时间
    int PostRecordTimeSeconds;//延迟录像时间
    RECORD_TRACKSINFO_S trackinfo[WEEK_DAYNUM];//一个星期7天
}RECORD_TRACKSCHANNEL_S, *PRECORD_TRACKSCHANNEL_S;

typedef struct
{
    int online_num;
    int cur_channel;//按位表示，通道复制设置使用
    RECORD_TRACKSCHANNEL_S tracklist[MAX_CH];
}RECORD_TRACKSLIST_S, *PRECORD_TRACKSLIST_S;

typedef struct
{
    int id;   //通道号
    int enable;    //使能
}MANUAL_RECORD_TRACKSCHANNEL_S, *PMANUAL_RECORD_TRACKSCHANNEL_S;

typedef struct
{
    MANUAL_RECORD_TRACKSCHANNEL_S tracklist[MAX_CH];
}MANUAL_RECORD_TRACKSLIST_S, *PMANUAL_RECORD_TRACKSLIST_S;
typedef enum
{
    ISAPI_REC_TYPE_UNKNOW = 0,
    ISAPI_REC_TYPE_MANUAL = 1,      //手动录像
    ISAPI_REC_TYPE_SCHEDULE = 2,    //定时录像
    ISAPI_REC_TYPE_MOTION = 4,      //移动录像
    ISAPI_REC_TYPE_ALARM = 8,       //报警录像
    ISAPI_REC_TYPE_CARD = 9,        //卡号录像
    ISAPI_PIC_TYPE_MANUAL = 0x11,   //图片-手动录像
    ISAPI_PIC_TYPE_SCHEDULE = 0x12, //图片-定时录像
    ISAPI_PIC_TYPE_MOTION = 0x14,   //图片-移动录像
    ISAPI_PIC_TYPE_ALARM = 0x18,    //图片-报警录像
    ISAPI_PIC_TYPE_ALLPIC = 0x1f,   //图片-所有
    ISAPI_REC_TYPE_ALL = 0xff       //所有
} ISAPI_RECTYPE_E;


typedef struct
{
    int channel;
    PT_RECFILESEG_S  recfileseg_info; 
}RECORD_BACKUPINFO_S, *PRECORD_BACKUPINFO_S;

typedef struct
{
    PT_RECSEGINFO_S seginfo;
}RECORD_SEGINFO_S, *PRECORD_SEGINFO_S;

typedef struct
{
    uint32 readsize;
    RECORD_SEGINFO_S recseginfo;
    PT_BACKUPREAD_S  backup_read;
}RECORD_BACKUPREAD_S, *PRECORD_BACKUPREAD_S;

int GetIStrackDailyParam(int channel, trackDailyParam_S * daily);
int GetISSearchRecord(SearchRec_S * search_rec);

#endif
