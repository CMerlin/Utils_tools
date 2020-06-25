/****************************************************************
 * Copyright(C), 2016, Hanbang Tech.Co.,Ltd
 * File Name:isapi_api_client.h
 * Author:merlin
 * Version:v1
 * Data:20160613
 * Description:以下接口是提供给其他模块使用的
 * History:
 * *************************************************************/
#ifndef _ISAPI_API_CLIENT_H_
#define _ISAPI_API_CLIENT_H_

#include "common.h"
#include "http_client.h"
#include "xml_parse_system.h"
#include "xml_parse_security.h"
#include "xml_parse_contentmgmt.h"

/*GET相关测试接口*/
extern sint32 isapi_get_network_interfaces(sint32 handler, ISAPI_NULL_S *request, NETWORK_DEVICE_INFO_S *response);
extern sint32 isapi_get_network_mailing(sint32 handler, ISAPI_NULL_S *request, NETWORK_SMTP_S *response);
extern sint32 isapi_get_network_interfaces_capabilities(sint32 handler, ISAPI_NULL_S *request, NETWORK_DEVICE_INFO_S *response);
extern sint32 isapi_get_network_ddns_channel(sint32 handler, ISAPI_NULL_S *request, sint32 channel, NETWORK_DDNS_S *response);
extern sint32 isapi_get_deviceInfo(sint32 handler, ISAPI_NULL_S *request, SYSTEM_DEVICE_INFO_S *response);
extern sint32 isapi_get_deviceInfo_capabilities(sint32 handler, ISAPI_NULL_S *request, SYSTEM_DEVICE_INFO_S *response);
extern sint32 isapi_get_storage(sint32 handler, ISAPI_NULL_S *request, DEVICE_DISK_ATTR_S *response);
extern sint32 isapi_get_time_ntpservers(sint32 handler, ISAPI_NULL_S *request, SYSTEM_NTP_CFG_S *response);
extern sint32 isapi_get_time(sint32 handler, ISAPI_NULL_S *request, SYSTEM_TIME_CFG_S *response);
extern sint32 isapi_get_inputProxy_pnp(sint32 handler, ISAPI_NULL_S *request, COMMON_RESPONSE_S *response);
extern sint32 isapi_get_inputProxy_channels_status(sint32 handler, ISAPI_NULL_S *request, INPUTPROXY_S *response);
extern sint32 isapi_get_network_UPnP_ports_status(sint32 handler, ISAPI_NULL_S *request, NETWORK_UPNP_S *response);
extern sint32 isapi_get_network_UPnP(sint32 handler, ISAPI_NULL_S *request, NETWORK_UPNP_S *response);
extern sint32 isapi_get_network_ddns_capabilities(sint32 handler, ISAPI_NULL_S *request, NETWORK_DDNS_S *response);
extern sint32 isapi_get_adminAccesses(sint32 handler, ISAPI_NULL_S *request, SECURITY_PORTINFO_S *response);

/*PUT测试相关接口*/
extern sint32 isapi_put_network_mailing1(sint32 handler, NETWORK_SMTP_S *request, COMMON_RESPONSE_S *response);
extern sint32 isapi_put_network_mailing(sint32 handler, NETWORK_SMTP_S *request, COMMON_RESPONSE_S *response);
extern sint32 isapi_put_network_interfaces_channel(sint32 handler, NETWORK_DEVICE_INFO_S *request, sint32 channel, COMMON_RESPONSE_S *response);
extern sint32 isapi_put_deviceInfo(sint32 handler, SYSTEM_DEVICE_INFO_S *request, COMMON_RESPONSE_S *response);
extern sint32 isapi_put_time_ntpservers(sint32 handler, SYSTEM_NTP_CFG_S *request, COMMON_RESPONSE_S *response);
extern sint32 isapi_put_inputProxy_pnp(sint32 handler, ISAPI_NULL_S *request, COMMON_RESPONSE_S *response);
extern sint32 isapi_put_adminAccesses(sint32 handler, SECURITY_PORTINFO_S *request, COMMON_RESPONSE_S *response);
extern sint32 isapi_put_network_UPnP(sint32 handler, NETWORK_UPNP_S *request, COMMON_RESPONSE_S *response);
extern sint32 isapi_put_network_ddns(sint32 handler, NETWORK_DDNS_S *request, COMMON_RESPONSE_S *response);

#endif
