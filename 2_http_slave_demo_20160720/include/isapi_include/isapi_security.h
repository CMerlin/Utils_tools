/*
 * FileName:
 * Author:         luny  Version: 1.0  Date: 2014-5-5
 * Description:
 * Version:
 * Function List:
 *                 1.
 * History:
 *     <author>   <time>    <version >   <desc>
 */

#ifndef _ISAPI_SECURITY_H_
#define _ISAPI_SECURITY_H_

#include "xml_util.h"
#include "isapi_util.h"
#include "isapi_security_adapter.h"

void ISOpenSecurity();
int ISDefineSecurity(char * name, void * fn);
void ISCloseSecurity();
bool ISHndSecurity(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);
bool ISHndSecurityUsercheck(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);
bool ISHndSecurityAdminAccesses(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);
bool ISHndSecurityUsers(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);
bool ISHndSecurityPermission(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);
bool ISHndChannelPermission(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);
int GenXmlChannelPermission(char * xml_buf, int size, char *option, int permission);
int GenXmlUserCheck(char * xml_buf, int params);
int GenXmlAdminAccesses(char * xml_buf, SECURITY_PORTINFO_S *portinfo);
int GenXmlSecurityUsers(char * xml_buf, SECURITY_USER_LIST_S * user_list);
int GenXmlUserPermission(char * xml_buf, int size, int id, SECURITY_USER_S *user_permission);
int ParseXmlAdminAccesses(char * xml_buf, SECURITY_PORTINFO_S *portinfo);
int ParseXmlSecurityUsers(char * xml_buf, SECURITY_USER_S * user, int type);//type:0-put,1-post
int ParseXmlUserPermission(char * xml_buf, SECURITY_USER_S *user_permission);

#endif
