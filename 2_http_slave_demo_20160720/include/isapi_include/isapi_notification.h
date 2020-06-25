#ifndef _ISAPI_NOTIFICATION_H_
#define _ISAPI_NOTIFICATION_H_

#include "xml_util.h"
#include "isapi_util.h"
#include "isapi_notification_adapter.h"

bool ISHndNotification(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);

#endif

