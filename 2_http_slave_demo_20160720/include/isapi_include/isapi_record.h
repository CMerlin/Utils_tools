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

#ifndef _ISAPI_RECORD_H_
#define _ISAPI_RECORD_H_

#include "xml_util.h"
#include "isapi_util.h"
#include "isapi_record_adapter.h"

int GenXmlRecordDaily(char * xml_buf, trackDailyParam_S * daily);
int GenXmlSearchRecord(Webs * wp, char * xml_buf, SearchRec_S * search_rec);
int ParseXmlRecordDaily(char * xml_buf, trackDailyParam_S * daily);
int ParseXmlSearchRecord(char * xml_buf, SearchRec_S * search_rec);
bool ISHndRecord(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);
bool ISHndSearch(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);

#endif
