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

#ifndef _ISAPI_NETWORK_H_
#define _ISAPI_NETWORK_H_

#include "xml_util.h"
#include "isapi_util.h"
#include "isapi_network_adapter.h"

void ISOpenNetwork();
int ISDefineNetwork(char * name, void * fn);
void ISCloseNetwork();
int GenXmlNetworkInterfaces(char * xml_buf, int size, NETWORK_DEVICE_INFO_S * net_param, int iscapabilities);
int GenXmlPPPoE(char * xml_buf, int size, NETWORK_PPPOE_S * pppoe_param);
int GenXmlDDNS(char * xml_buf, int size, NETWORK_DDNS_S * ddns_param);
int GenXmlMailing(char * xml_buf, int size, NETWORK_SMTP_S * smtp_param);
int GenXmlSNMP(char * xml_buf, int size, int params);
int GenXmlUPnP(char * xml_buf, int size, NETWORK_UPNP_S * upnp_param);
bool ISNetworkHnd(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);
bool ISNetworkInterfacesHnd(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);
bool ISNetworkPPPoEHnd(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);
bool ISNetworkMailHnd(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);
bool ISNetworkDDNSHnd(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);
bool ISNetworkUPnPHnd(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);
int ParseXmlNetworkInterfaces(char * xml_buf, NETWORK_DEVICE_INFO_S * net_param);
int ParseXmlPPPoE(char * xml_buf, NETWORK_PPPOE_S * pppoe_param);
int ParseXmlDDNS(char * xml_buf, NETWORK_DDNS_S * ddns_param);
int ParseXmlMailing(char * xml_buf, NETWORK_SMTP_S * smtp_param);
int ParseXmlSNMP(char * xml_buf, int params);
int ParseXmlUPnP(char * xml_buf, NETWORK_UPNP_S * upnp_param);

#endif
