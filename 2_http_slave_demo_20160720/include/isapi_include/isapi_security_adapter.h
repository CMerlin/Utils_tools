/*
 * FileName:
 * Author: luny  Version: 1.0  Date: 2014-5-6
 * Description:
 * Version:
 * Function List:
 *                 1.
 * History:
 *     <author>   <time>    <version >   <desc>
 */


#ifndef _ISAPI_SECURITYADAPTER_H_
#define _ISAPI_SECURITYADAPTER_H_

#include "isapi_adapter.h"
#include "sys_net.h"
#include "sys_netapi.h"

typedef struct SecurityUser
{
    char user_name[MAX_STRING];
    char user_pwd[MAX_STRING];
    uint64    local_authority[32];
    uint64    remote_authority[16];
    uint32    bind_ipaddr;                  // 远程绑定IP
    uint8     bind_macaddr[8];        // 远程绑定MAC
    sint32    user_pwdflag;  //是否修改密码
} SECURITY_USER_S, *PSECURITY_USER_S;

typedef struct
{
    uint8 count;
    SECURITY_USER_S        accounts[PT_MAX_ACCOUNT];
} SECURITY_USER_LIST_S, *PSECURITY_USER_LIST_S;

typedef struct
{
    sint32 httpport;
    sint32 listenport;
    sint32 rtspport;
    sint32 rtmpport;
    sint32 upgradeport;
}SECURITY_PORTINFO_S, *PSECURITY_PORTINFO_S;

int security_get_usr_info(SECURITY_USER_LIST_S * user_list);
int security_get_usr_permission(int id, SECURITY_USER_S *user_permission);
int security_set_usr_permission(int id, SECURITY_USER_S *user_permission, WEB_CMD_INFO_S *webinfo);
int security_delete_user(int id, WEB_CMD_INFO_S *webinfo);
int security_add_user (SECURITY_USER_S* user, WEB_CMD_INFO_S *webinfo);
int security_edit_user (SECURITY_USER_S* user, WEB_CMD_INFO_S *webinfo);
int security_get_admin_accesses(SECURITY_PORTINFO_S *portinfo);
int security_set_admin_accesses(SECURITY_PORTINFO_S *portinfo, WEB_CMD_INFO_S *webinfo);
//int security_check_user(uint32 remote_ip, SECURITY_USER_S * user);
int security_cmd_check_login(int remote_ip, SECURITY_USER_S user_account);

#endif

