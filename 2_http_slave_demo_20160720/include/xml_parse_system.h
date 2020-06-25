#ifndef _XML_PARSE_SYSTEM_H_
#define _XML_PARSE_SYSTEM_H_

#include "common.h"
#include "xml_common.h"
#include "xml_base.h"

/*xml数据帧的解析函数*/
extern int ParseXmlNetworkInterfaces(char * xml_buf, NETWORK_DEVICE_INFO_S * net_param);
extern int ParseXmlPPPoE(char * xml_buf, NETWORK_PPPOE_S * pppoe_param);
extern int ParseXmlDDNS(char * xml_buf, NETWORK_DDNS_S * ddns_param);
extern int ParseXmlUPnP(char * xml_buf, NETWORK_UPNP_S * upnp_param);
extern int ParseXmlUPnPPort_Add(char * xml_buf, NETWORK_PAT_UPNP_S * upnp_part);
extern int ParseXmlUPnPPort_Edit(char * xml_buf, NETWORK_PAT_UPNP_S * upnp_part);
extern int ParseXmlSystemTime(char * xml_buf, SYSTEM_TIME_CFG_S * time_cfg);
extern int ParseXmlDeviceInfo(char * xml_buf, SYSTEM_DEVICE_INFO_S * dev_info);
extern int ParseXmlSystemIoInput(char * xml_buf, SYSTEM_IO_INPUTLIST_S *inputlist, int almin_num);
extern int ParseXmlSystemIoOutput(char * xml_buf, SYSTEM_IO_OUTPUTLIST_S *outputlist, int almout_num);
extern int ParseXmlMailing(char * xml_buf, NETWORK_SMTP_S * smtp_param);
extern int ParseXmlCommonResponse(char * xml_buf, COMMON_RESPONSE_S *response);
extern int ParseXmlSystemNtpServer(char * xml_buf, SYSTEM_NTP_CFG_S * ntp_cfg);
extern int ParseXmlCommonResponse(char * xml_buf, COMMON_RESPONSE_S *response);
extern int ParseXmlUPnPPortList(char * xml_buf, NETWORK_UPNP_S * response);

/*xml数据帧的封装函数*/
extern int GenXmlDDNS(char * xml_buf, int size, NETWORK_DDNS_S * ddns_param);
extern int GenXmlUPnP(char * xml_buf, int size, NETWORK_UPNP_S * upnp_param);
extern int GenXmlMailing(char * xml_buf, int size, NETWORK_SMTP_S * smtp_param);
extern int GenXmlNetworkInterfacesChannel(char * xml_buf, int size, NETWORK_DEVICE_INFO_S * net_param, int iscapabilities);
extern int GenXmlDeviceInfo(char * xml_buf, SYSTEM_DEVICE_INFO_S dev_info);
extern int GenXmlSystemNtpServer(char * xml_buf, int size, SYSTEM_NTP_CFG_S * ntp_cfg);
#endif
