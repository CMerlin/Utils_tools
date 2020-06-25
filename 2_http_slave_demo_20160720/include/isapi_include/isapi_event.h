#ifndef _ISAPI_EVENT_H_
#define _ISAPI_EVENT_H_

#include "xml_util.h"
#include "isapi_util.h"
#include "isapi_event_adapter.h"

bool ISEventTriggersHnd(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);

bool ISEventCapabilitiesHnd(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);

bool ISEventSchedulessHnd(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);

bool ISEventManualHnd(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);

int GenXmlEventCapabilities(char * xml_buf, int size);

int GenXmlEventTrigger(char * xml_buf, int size, EVENT_TRIGGER_S * event_info);

int GenXmlEventSchedules(char * xml_buf, int size, EVENT_TRIGGER_S *eventtrigger);

int ParseXmlEventTrigger(char * xml_buf, int size, EVENT_TRIGGER_S * event_info);


#endif
