#ifndef _ISAPI_STREAMINGADAPTER_H_
#define _ISAPI_STREAMINGADAPTER_H_

#include "isapi_adapter.h"
#include "sys_net.h"
#include "sys_netapi.h"
#include "rtmpsrv.h"

#define ISAPI_STREAM_MAXCH 128

typedef enum
{
    ISAPI_STREAM_OK = 0,
    ISAPI_STREAM_FAIL,
    ISAPI_STREAM_EMPTY,
    ISAPI_STREAM_NOIPC,
    ISAPI_STREAM_OTHER
}ISAPI_STREAM_STATUS;

typedef struct
{
    char   streamid[64];
    int    status;
    sint16 channel;
    sint16 type;
}STREAMING_STATUS_INFO;

typedef struct
{
    STREAMING_STATUS_INFO stream_info[ISAPI_STREAM_MAXCH];
}WEB_HEARTBEAT_INFO;

typedef struct
{
    char   streamid[64];
    char   option[32];
    sint32 speed;
}STREAMING_PB_CONTROL, *PSTREAMING_PB_CONTROL;

typedef struct
{
    sint32 year;
    sint32 month;
    sint32 day;
    sint32 hour;
    sint32 minute;
    sint32 second;
}STREAMING_PB_TIME, *PSTREAMING_PB_TIME;

int streaming_get_picture(int channel, char *picdata, int maxsize);

#endif
