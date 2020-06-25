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

#ifndef _ISAPI_H_
#define _ISAPI_H_

#include "common.h"

#define ROUTE_ISAPI       "/ISAPI"

/******************************************************************************
* 函数功能: 打开ISAPI模块
* 输入参数: pnp_info: pnp配置信息，包括主网口和POE配置
*           notifyfunc: 消息通知回调函数
* 输出参数: 无
* 返回值  : >=0-成功,<0-错误
*****************************************************************************/
//sint32 isapi_open(char *local_ip, char *documents, notifycallback notifyfunc);
sint32 isapi_open(notifycallback notifyfunc);

#if 0
/******************************************************************************
* 函数介绍: 启动ISAPI模块,主网口的DHCP服务器,POE的即插即用支持
* 输入参数: handle: 模块句柄
*           start_dhcp:是否启动内置DHCP服务器,根据pnp_checkdhcpserver情况来决定
*                       1启用,0不启用
*           start_poe:是否启动poe服务,默认启用,传1即可
*           priority: 线程优先级1~99
* 输出参数: 无
* 返回值  : 0-成功,<0-错误代码
*****************************************************************************/
sint32 isapi_start(sint32 handle, sint32 priority);

/******************************************************************************
* 函数介绍:停止ISAPI模块
* 输入参数:handle: 模块句柄
* 输出参数:无
* 返回值  :0-成功,<0-错误代码
*****************************************************************************/
sint32 isapi_stop(sint32 handle);

/******************************************************************************
* 函数介绍:关闭ISAPI模块,释放系统资源
* 输入参数:handle: 模块句柄
* 输出参数:无
* 返回值  :0-成功,<0-错误代码
*****************************************************************************/
sint32 isapi_close(sint32 handle);
#endif

#endif
