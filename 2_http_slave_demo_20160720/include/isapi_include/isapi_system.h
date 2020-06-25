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

#ifndef _ISAPI_SYSTEM_H_
#define _ISAPI_SYSTEM_H_

#include "xml_util.h"
#include "isapi_util.h"
#include "isapi_system_adapter.h"
#include "isapi_content_adapter.h"

void ISOpenSystem();
void ISCloseSystem();
int ISDefineSystem(char * name, void * fn);
bool ISHndSystem(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);
bool ISHndSystemDeviceInfo(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);
bool ISHndSystemIO(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);
bool ISHndSystemVideo(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);
bool ISHndSystemTime(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);
bool ISHndSystemCapabilities(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);
bool ISHndSystemReboot(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);
bool ISHndSystemReset(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);
bool ISHndSystemUpdate(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);
bool ISHndSystemUpgradeStatus(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);
bool ISHndSystemTwoWayAudio(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);
bool IsHndZeroChannel(Webs * wp, char isapi_cmd[][ISAPI_CMD_MAX_LEN], int cmd_num);
int GenXmlDeviceInfo(char * xml_buf, SYSTEM_DEVICE_INFO_S dev_info);
int GenXmlSystemIoInput(char * xml_buf, int size, SYSTEM_IO_INPUTLIST_S *inputlist, char *ioid);
int GenXmlSystemIoOutput(char * xml_buf, int size, SYSTEM_IO_OUTPUTLIST_S *outputlist, char *ioid);
int GenXmlSystemVideo(char * xml_buf);
int GenXmlSystemTime(char * xml_buf, int size, SYSTEM_TIME_CFG_S * time_cfg);
int GenXmlSystemNtpServer(char * xml_buf, int size, SYSTEM_NTP_CFG_S * ntp_cfg);
int GenXmlSystemCapabilities(char * xml_buf, int size, SYSTEM_DEVICE_SUPPORT_S *device_support);
int GenXmlZeroChannelSplit(char * xml_buf, int size, SYSTEM_DEVICE_SUPPORT_S *device_support);
int GenXmlSystemTwoWayAudio(char * xml_buf, int param);
int ParseXmlSystemTime(char * xml_buf, SYSTEM_TIME_CFG_S * time_cfg);
int ParseXmlSystemNtpServer(char * xml_buf, SYSTEM_NTP_CFG_S * ntp_cfg);
int ParseXmlDeviceInfo(char * xml_buf, SYSTEM_DEVICE_INFO_S * dev_info);
int ParseXmlSystemIoInput(char * xml_buf, SYSTEM_IO_INPUTLIST_S *inputlist, int almin_num);
int ParseXmlSystemIoOutput(char * xml_buf, SYSTEM_IO_OUTPUTLIST_S *outputlist, int almout_num);

#endif

