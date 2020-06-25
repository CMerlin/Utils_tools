#ifndef _ISAPI_NOTIFICATIONADAPTER_H_
#define _ISAPI_NOTIFICATIONADAPTER_H_

#include "isapi_adapter.h"
#include "sys_net.h"
#include "sys_netapi.h"

#define ISAPI_NTF_MAXCH     128
#define ISAPI_NTF_MAXAM     64

typedef struct {
    sint8 video_lost;
    sint8 vcover_detect;
    sint8 motion_detect;
    sint8 poeconfict_detect;
} NTF_VIDEO_STATUS_INFO;

typedef struct {
    sint8 temp_error;
    sint8 disk_err;
    sint8 disk_full_alm;
    sint8 net_down;
    uint8 sensor_detect[ISAPI_NTF_MAXAM];
    uint32 sensor_no;
    NTF_VIDEO_STATUS_INFO video_status[ISAPI_NTF_MAXCH];
    uint32 video_no;
} NTF_STATUS_INFO, *PNTF_STATUS_INFO;

int notification_get_status(PNTF_STATUS_INFO info);

#endif

