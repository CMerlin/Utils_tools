#ifndef _XML_PARSE_CONTENTMGMT_H_
#define _XML_PARSE_CONTENTMGMT_H_
#include "common.h"
#include "xml_common.h"

extern int ParseXmlInputProxyChannleName(char * xml_buf, CONTENT_IPC_OSDINFO_S *osdinfo);
extern int ParseXmlInputProxyOsdInfo(char * xml_buf, CONTENT_IPC_OSDINFO_S *osdinfo);
extern int ParseXmlChDeviceAdd_at(char * xml_buf, INPUTPROXY_S * input);
extern int ParseXmlStreamingChannelCapabilities(char *xml_buf, CONTENT_VENC_PARAM_S *channelparam);
extern int ParseXmlImageProxyparam(char * xml_buf, int size, CONTENT_IMAGE_PARAM_S *image_param);
extern int ParseXmlStorageInfo(char * xml_buf, DEVICE_DISK_ATTR_S * dev_attr);
extern int ParseXmlIOProxyInput(char * xml_buf, CONTENT_ALMIN_CONF_S *almin_conf);
extern int ParseXmlRecordTracks(char * xml_buf, RECORD_TRACKSLIST_S *trackslist);
extern int ParseXmlSearchRecord(char * xml_buf, SearchRec_S * search_rec);
extern int ParseXmlSearchLog(char * xml_buf, SearchLog_S * search_log);
extern int ParseXmlChPtzCtrl(char * xml_buf, char *ptzcmd, PTZ_DEVICE_CTRL *ptz_ctrl);
extern int ParseXmlInputProxyChannelStatusList(char * xml_buf, INPUTPROXY_S * input);
#endif
