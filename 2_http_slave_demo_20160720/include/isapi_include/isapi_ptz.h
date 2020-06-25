#ifndef _ISAPI_PTZ_H_
#define _ISAPI_PTZ_H_

#include "xml_util.h"
#include "isapi_util.h"
#include "isapi_ptz_adapter.h"

bool ISHndContentMgmtPTZCtrlProxy(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);

#endif
