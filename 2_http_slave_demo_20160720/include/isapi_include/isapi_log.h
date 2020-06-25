/*
 * FileName:
 * Author:         luny  Version: 1.0  Date: 2014-5-6
 * Description:
 * Version:
 * Function List:
 *                 1.
 * History:
 *     <author>   <time>    <version >   <desc>
 */

#ifndef _ISAPI_LOG_H_
#define _ISAPI_LOG_H_

#include "log.h"
#include "xml_util.h"
#include "isapi_util.h"
#include "isapi_log_adapter.h"

int GenXmlSearchLog(char * xml_buf, SearchLog_S * search_log);
int ParseXmlSearchLog(char * xml_buf, SearchLog_S * search_log);
bool ISHndSearchLog(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);

#endif
