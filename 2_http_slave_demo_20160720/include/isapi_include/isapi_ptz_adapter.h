#ifndef _ISAPI_PTZ_ADAPTER_H_
#define _ISAPI_PTZ_ADAPTER_H_

#include "isapi_adapter.h"
#include "config_usr.h"
#include "config.h"
#include "sys_net.h"
#include "sys_netapi.h"


typedef enum
{
    WEB_PTZ_CMD_STOP,
    WEB_PTZ_CMD_UP,            // 上
    WEB_PTZ_CMD_DOWN,          // 下
    WEB_PTZ_CMD_LEFT,          // 左
    WEB_PTZ_CMD_RIGHT,         // 右
    WEB_PTZ_CMD_FOCUS_INC,     /* 聚焦+ */
    WEB_PTZ_CMD_FOCUS_DEC,     /* 聚焦- */
    WEB_PTZ_CMD_IRIS_INC,      /* 光圈+ */
    WEB_PTZ_CMD_IRIS_DEC,      /* 光圈- */
    WEB_PTZ_CMD_ZOOM_DEC,      /* 缩放+ */
    WEB_PTZ_CMD_ZOOM_INC,      /* 缩放- */
    WEB_PTZ_CMD_F1,            // 辅助
    WEB_PTZ_CMD_F1_1,
    WEB_PTZ_CMD_F2,            // 辅助
    WEB_PTZ_CMD_F2_1,
    WEB_PTZ_CMD_AUTO,          // 自动
    WEB_PTZ_CMD_AUTO_1,
    WEB_PTZ_CMD_PRESET_SET,    // 预置
    WEB_PTZ_CMD_PRESET_GET,    // 调用
    WEB_PTZ_CMD_SETUP,
    WEB_PTZ_CMD_ENTER,
    WEB_PTZ_CMD_PAGEUP,
    WEB_PTZ_CMD_PAGEDOWN,
    WEB_PTZ_CMD_BRUSH,         // 雨刷
    WEB_PTZ_CMD_LEFT_UP,       //24左上
    WEB_PTZ_CMD_LEFT_DOWN,     //25左下
    WEB_PTZ_CMD_RIGHT_UP,      //26右上
    WEB_PTZ_CMD_RIGHT_DOWN,    //27右下
    WEB_PTZ_CMD_PRESET_CLR,    //28预置点清除
    WEB_PTZ_CMD_SET_PATTERN_START, //29轨迹巡航--设置开始
    WEB_PTZ_CMD_SET_PATTERN_END,   //30轨迹巡航--设置结束
    WEB_PTZ_CMD_SET_PATTERN_RUN,   //31轨迹巡航--运行

} ADDTYPE_E;



typedef struct
{
    uint32  channel;    // 通道号
    uint32  command;    // 云台控制命令 为0x00010028则停止
    uint32  index;      // 预制点号(受球机有效值范围影响)[0, 255]
    uint32  speed;      // 控制速度 [0, 255] ，0的速度是最慢的
} PTZ_DEVICE_CTRL;


int web_ptz_ctrl (PTZ_DEVICE_CTRL* ptz_ctrl);

#endif

