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

#ifndef _ISAPI_UTIL_H_
#define _ISAPI_UTIL_H_

#include "common.h"
#include "goahead.h"
#include "isapi_local.h"

#define XML_BUF_SIZE_1K    1 * 1024
#define XML_BUF_SIZE_4K    4 * 1024
#define XML_BUF_SIZE_1M 1024 * 1024

typedef void (*WebsISAPI)(Webs * wp);
typedef void (*ISAPIProc)(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int num);

sint32 uint_ip_to_string(char *str_ip, sint32 str_size, uint32 int_ip);
uint32 string_ip_to_uint(char * str_ip);
char *base64_encode(const char* data, int data_len); 
char *base64_decode(const char* data, int data_len); 
 
int ISDecodeCmd(char * buf, char isapi_cmd[][ISAPI_CMD_MAX_LEN]);
int ISParseCmd(Webs * wp, WebsHash table, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num, int flag);
int ParseTimeSpan(char * tm_buf, SYSTIME * tm);

#endif
