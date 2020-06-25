#ifndef _ISAPI_STREAMING_H_
#define _ISAPI_STREAMING_H_

#include "xml_util.h"
#include "isapi_util.h"
#include "isapi_streaming_adapter.h"

bool ISHndStreaming(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);
bool ISHndHeartBeat(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);

#endif