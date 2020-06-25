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

#ifndef _ISAPI_CONTENTMGMT_H_
#define _ISAPI_CONTENTMGMT_H_

#include "xml_util.h"
#include "isapi_util.h"
#include "isapi_content_adapter.h"


void ISOpenContentmgmt();

int ISDefineContentmgmt(char * name, void * fn);

bool ISHndContentMgmt(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);

bool ISHndContentMgmtInputproxy(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);

bool ISHndContentMgmtSourceSupport(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);

bool ISHndContentMgmtStreamingproxy(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);

bool ISHndContentMgmtImageProxy(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);

bool ISHndContentMgmtStorage(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);

bool ISHndContentMgmtIOproxye(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);

bool ISHndZeroVideo(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);

int GenXmlInputProxy(char * xml_buf, INPUTPROXY_S * input);

int GenXmlInputProxySearch(char * xml_buf, CONTENT_IPC_SEARCH_S * serch_info);

int GenXmlInputProxyStatus(char * xml_buf, INPUTPROXY_S * input);

int GenXmlInputProxyChannel(char * xml_buf, int param);

int GenXmlInputProxyComplete(char * xml_buf, int params);

int GenXmlInputProxyPnp(char * xml_buf, int params);

int GenXmlSourceSupport(char * xml_buf, int param);

int GenXmlStreamingProxy(char * xml_buf, int params);

int GenXmlStreamingChannelCapabilities(char *xml_buf, CONTENT_VENC_PARAM_S *channelparam, int iscapabilities);

int GenXmlImageProxyparam(char * xml_buf, int size, CONTENT_IMAGE_PARAM_S *image_param);

int GenXmlStorage(char * xml_buf, CONTENT_DISKINFO_S * disk_param);

int GenXmlStorageFormatStatus(char * xml_buf, int params);

int GenXmlIOProxy(char * xml_buf, int params);

int GenXmlPTZCtrlProxy(char * xml_buf, int params);

int GenXmlZeroVideo(char * xml_buf, int params);

int ParseXmlChConfigOsd(char * xml_buf, int params);
int ParseXmlChConfigVideo(char * xml_buf, int params);
int ParseXmlChConfigPlan(char * xml_buf, int params);
int ParseXmlChConfigMotion(char * xml_buf, int params);
int ParseXmlChConfigLost(char * xml_buf, int params);
int ParseXmlChConfigHide(char * xml_buf, int params);
int ParseXmlChConfigCoverAlarm(char * xml_buf, int params);
int ParseXmlChConfigOverlap(char * xml_buf, int params);
int ParseXmlChDeviceAdd_at(char * xml_buf, INPUTPROXY_S * input);
int ParseXmlStorageInfo(char * xml_buf, DEVICE_DISK_ATTR_S * dev_attr);
int ParseXmlImageProxyparam(char * xml_buf, int size, CONTENT_IMAGE_PARAM_S *image_param);
int GenXmlInputProxyChannleName(char * xml_buf, int size, CONTENT_IPC_OSDINFO_S *osdinfo);
int GenXmlInputProxyOsdCapabilities(char * xml_buf, int size);
int GenXmlInputProxyOsdInfo(char * xml_buf, int size, CONTENT_IPC_OSDINFO_S *osdinfo);
int ParseXmlInputProxyChannleName(char * xml_buf, CONTENT_IPC_OSDINFO_S *osdinfo);
int ParseXmlInputProxyOsdInfo(char * xml_buf, CONTENT_IPC_OSDINFO_S *osdinfo);

#endif
