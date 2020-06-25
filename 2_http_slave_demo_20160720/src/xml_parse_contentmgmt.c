/****************************************************************
 * FileName:xml_parse_contentmgmt.c
 * Author:merlin
 * Version:v1
 * Time:20160613
 * Description:create and parse xml package
 * *************************************************************/
#include "common.h"
#include "xml_base.h"
#include "xml_parse_contentmgmt.h"
#include "xml_parse_system.h"

static char SvideoQualityControlType[][16] =
{
    "VBR",
    "CBR"
};

int ParseXmlInputProxyChannleName(char * xml_buf, CONTENT_IPC_OSDINFO_S *osdinfo)
{
    mxml_node_t *root = NULL;
    mxml_node_t * ChannleName = NULL;

    root = mxmlLoadString(NULL, xml_buf, NULL);
    if (NULL == root)
    {
        //TRACE_ERR("mxmlLoadString error\n");
        return -1;
    }

    ChannleName = xml_parse_Get_Group(root, "ChannleName", NULL, NULL); //HHHHHHHHHHHHHHH
    {
        //xml_parse_GetString(ChannleName, "name", osdinfo->osd[PT_OSD_CHANNEL].title); //MWARNING
        xml_parse_GetString(ChannleName, "name", (char*)(osdinfo->osd[PT_OSD_CHANNEL].title));
    }

    if (root != NULL)
    {
        mxmlRelease(root); 
    }

    return 0;
}

int ParseXmlInputProxyOsdInfo(char * xml_buf, CONTENT_IPC_OSDINFO_S *osdinfo)
{
    char strbuf[64] = {0};
    mxml_node_t *root = NULL;
    mxml_node_t * OSDData = NULL, *channelNameOverlay = NULL, *channelnameposition = NULL;

    root = mxmlLoadString(NULL, xml_buf, NULL);
    if (NULL == root)
    {
        //TRACE_ERR("mxmlLoadString error\n");
        return -1;
    }

    OSDData = xml_parse_Get_Group(root, "OSDData", NULL, NULL);
    {
        channelNameOverlay = xml_parse_Get_Group(OSDData, "channelNameOverlay", NULL, NULL); 
        {
            xml_parse_GetString(channelNameOverlay, "displaychannelname", strbuf);
            osdinfo->osd[PT_OSD_CHANNEL].en_title = (!strcmp("true", strbuf))?1:0;
            channelnameposition = xml_parse_Get_Group(channelNameOverlay, "channelnameposition", NULL, NULL); 
            {
                //xml_parse_Get_Integer(channelnameposition, "positionX", &(osdinfo->osd[PT_OSD_CHANNEL].pos_title.left));
                //xml_parse_Get_Integer(channelnameposition, "positionY", &(osdinfo->osd[PT_OSD_CHANNEL].pos_title.top)); //MWARNING
                xml_parse_Get_Integer(channelnameposition, "positionX", (int*)&(osdinfo->osd[PT_OSD_CHANNEL].pos_title.left));
                xml_parse_Get_Integer(channelnameposition, "positionY", (int*)&(osdinfo->osd[PT_OSD_CHANNEL].pos_title.top));
            }
        }
    }

    if (root != NULL)
    {
        mxmlRelease(root); 
    }

    return 0;
}

/*
 * change：完全从写
 * */
int ParseXmlInputProxyChannelStatusList(char * xml_buf, INPUTPROXY_S * response)
{
	int index = 0;
	char data[64] = {0};
	mxml_node_t *root = NULL;
	mxml_node_t * statusList = NULL, *current = NULL, *node3 = NULL;

	root = mxmlLoadString(NULL, xml_buf, NULL); //根节点
	if (NULL == root)
	{
		return -1;
	}

	statusList = xml_parse_Get_Group(root, "InputProxyChannelStatusList", NULL, NULL); //一级节点
	if(statusList == NULL)
	{
		mxmlRelease(root); 
		return -1;
	}

	for(current = mxmlFindElement(statusList, statusList, "InputProxyChannelStatus", NULL, NULL, MXML_DESCEND); 
			current != NULL; 
			current = mxmlFindElement(current, statusList, "InputProxyChannelStatus", NULL, NULL, MXML_DESCEND))

	{
		index++;
		if(index >= MAX_INTPUTPROXYCH)
		{
			break;
		}

		xml_parse_Get_Integer(current, "id", (int*)&(response->ich[index-1].id));  //ID
		node3 = xml_parse_Get_Group(current, "sourceInputPortDescriptor", NULL, NULL); //二级节点
		if(node3 == NULL)
		{
			continue;
		}

		xml_parse_GetString(node3, "proxyProtocol", data);
		if(0 == strncmp(data, "HB", strlen(data)))
		{
			response->ich[index-1].desc.proto = HBGK; //HBGK协议
		}
		else
		{
			response->ich[index-1].desc.proto = ONVIF; //ONVIF协议
		}
		memset(data, 0, strlen(data));
		xml_parse_GetString(node3, "ipAddress", response->ich[index-1].desc.ipaddr); //IP地址
		xml_parse_Get_Integer(node3, "managePortNo", &(response->ich[index-1].desc.mport));
		xml_parse_Get_Integer(node3, "srcInputPort", &(response->ich[index-1].desc.sport));
		xml_parse_GetString(node3, "userName", response->ich[index-1].desc.uname); //用户名
		xml_parse_GetString(node3, "password", response->ich[index-1].desc.upw); //用户密码
		xml_parse_GetString(node3, "POEChannel", data); //是否使用POE通道
		if(0 == strncmp(data, "true", strlen(data)))
		{
			response->ich[index-1].poechannel = 1; //使用POE通道
		}
		else
		{
			response->ich[index-1].poechannel = 0; //不使用POE通道
		}
		/*streamingProxyChannelIdList 此节点内数据未进行解析*/
		/*relatedIOProxy 此节点内数据未进行解析*/
	}

	if (root != NULL)
	{
		mxmlRelease(root); 
	}

	return 0;
}

int ParseXmlStreamingChannelCapabilities(char *xml_buf, CONTENT_VENC_PARAM_S *channelparam)
{
    char nodebuf[256] = {0};
    mxml_node_t *root = NULL;
    mxml_node_t *StreamingChannel = NULL;
    mxml_node_t *Audio = NULL, *Video = NULL;

    root = mxmlLoadString(NULL, xml_buf, NULL);
    if (NULL == root)
    {
        //TRACE_ERR("mxmlLoadString error\n");
        return -1;
    }
    {
        StreamingChannel = xml_parse_Get_Group(root, "StreamingChannel", NULL, NULL);
        
        Video = xml_parse_Get_Group(StreamingChannel, "Video", NULL, NULL);
        {
            //xml_parse_Get_Integer(Video, "videoResolutionWidth", &(channelparam->venc_config.byResolution.width)); //MWARNING
            //xml_parse_Get_Integer(Video, "videoResolutionHeight", &(channelparam->venc_config.byResolution.height)); //MWARNING
            xml_parse_Get_Integer(Video, "videoResolutionWidth", (int*)&(channelparam->venc_config.byResolution.width));
            xml_parse_Get_Integer(Video, "videoResolutionHeight", (int*)&(channelparam->venc_config.byResolution.height));
            xml_parse_GetString(Video, "videoQualityControlType", nodebuf);
            if (!strcmp(nodebuf, SvideoQualityControlType[CONTENT_CBR]))
            {
                channelparam->venc_config.byBitrateType = CONTENT_CBR;
                xml_parse_Get_Integer(Video, "constantBitRate", &(channelparam->venc_config.dwVideoBitrate));
            }
            else
            {
                channelparam->venc_config.byBitrateType = CONTENT_VBR;
                xml_parse_Get_Integer(Video, "vbrUpperCap", &(channelparam->venc_config.dwVideoBitrate));
            }

            xml_parse_Get_Integer(Video, "fixedQuality", &(channelparam->venc_config.byPicQuality));
            channelparam->venc_config.byPicQuality = channelparam->venc_config.byPicQuality;
            xml_parse_Get_Integer(Video, "maxFrameRate", &(channelparam->venc_config.dwVideoFrameRate));
            channelparam->venc_config.dwVideoFrameRate = channelparam->venc_config.dwVideoFrameRate/100;
                      
        }
        Audio = xml_parse_Get_Group(StreamingChannel, "Audio", NULL, NULL);
        {
            memset(nodebuf, 0, 256);
            xml_parse_GetString(Audio, "enabled", nodebuf);
            if (!strcmp(nodebuf, "true"))
            {
                channelparam->venc_config.byStreamType = CONTENT__AUSTREAM_ENABLE;
            }
            else
            {
                channelparam->venc_config.byStreamType = CONTENT__AUSTREAM_DISABLE;
            }
        }
    }

    if (root != NULL)
    {
        mxmlRelease(root); 
    }

    return 0;
}

int ParseXmlImageProxyparam(char * xml_buf, int size, CONTENT_IMAGE_PARAM_S *image_param)
{
    char strbuf[256] = {0};
    mxml_node_t *root = NULL;
    mxml_node_t *ImageChannel = NULL, *NoiseReduce = NULL, *GeneralMode = NULL, *Color = NULL;

    root = mxmlLoadString(NULL, xml_buf, NULL);
    if (NULL == root)
    {
        //TRACE_ERR("mxmlLoadString error\n");
        return -1;
    }

    ImageChannel = xml_parse_Get_Group(root, "ImageChannel", NULL, NULL);
    {
        NoiseReduce = xml_parse_Get_Group(ImageChannel, "NoiseReduce", NULL, NULL);
        {
            GeneralMode = xml_parse_Get_Group(NoiseReduce, "GeneralMode", NULL, NULL);
            xml_parse_Get_Integer(GeneralMode, "generalLevel", &(image_param->nr_level));
        }
        Color = xml_parse_Get_Group(ImageChannel, "Color", NULL, NULL);
        {
            xml_parse_Get_Integer(Color, "brightnessLevel", &(image_param->bright));
            xml_parse_Get_Integer(Color, "contrastLevel", &(image_param->contrast));
            xml_parse_Get_Integer(Color, "saturationLevel", &(image_param->saturation));
            xml_parse_Get_Integer(Color, "hueLevel", &(image_param->hue));
            xml_parse_Get_Integer(Color, "sharpnessLevel", &(image_param->sharp));
        }
        xml_parse_GetString(ImageChannel, "enableImageLossDetection", strbuf);
        image_param->image_lossdetection = (!strcmp("true", strbuf))?1:0;
    }

    if (root != NULL)
    {
        mxmlRelease(root); 
    }

    return 0;
}

int ParseXmlStorageInfo(char * xml_buf, DEVICE_DISK_ATTR_S * dev_attr)
{
    char hdd_attri[8] = {0}, hdd_type[16] = {0};
    //mxml_node_t *root = NULL, *storageNode = NULL, *hddListNode = NULL, *hddNode = NULL;
    mxml_node_t *root = NULL, *hddNode = NULL;

    //TRACE_DBG("xml_buf = \n%s\n", xml_buf);
    root = mxmlLoadString(NULL, xml_buf, NULL);
    if (NULL == root)
    {
        //TRACE_ERR("mxmlLoadString error\n");
    }
    else
    {
        hddNode = xml_parse_Get_Group(root, "hdd", NULL, NULL);
        if (NULL != hddNode)
        {
            //xml_parse_GetString(hddNode, "id", proto);
            //xml_parse_GetString(hddNode, "hddName", addr_type);
            //xml_parse_GetString(hddNode, "hddPath", input->ich[0].desc.ipaddr);
            //xml_parse_Get_Integer(hddNode, "hddType", &input->ich[0].desc.mport);
            //xml_parse_Get_Integer(hddNode, "status", &input->ich[0].desc.sport);
            //xml_parse_GetString(hddNode, "capacity", input->ich[0].desc.uname);
            //xml_parse_GetString(hddNode, "freeSpace", input->ich[0].desc.uname);
            xml_parse_GetString(hddNode, "hddName", hdd_type);
            xml_parse_GetString(hddNode, "property", hdd_attri);
        }

    }

    if(0 == strcmp(hdd_attri, "RW"))
    {
        dev_attr->hdd_attri = 0;
    }
    else
    {
        dev_attr->hdd_attri = 1;
    }

    if(0 == strcmp(hdd_type, "SATA"))
    {
        dev_attr->dev_type = DEVTYPE_IDE;
    }
    else if(0 == strcmp(hdd_type, "ESATA"))
    {
        dev_attr->dev_type = DEVTYPE_ESATA;
    }
    else if(0 == strcmp(hdd_type, "USB"))
    {
        dev_attr->dev_type = DEVTYPE_USB;
    }
    else if(0 == strcmp(hdd_type, "DVD"))
    {
        dev_attr->dev_type = DEVTYPE_CDDVD;
    }
    else
    {
        dev_attr->dev_type = DEVTYPE_IDE;
    }
    
    if (root != NULL)
    {
        mxmlRelease(root); 
    }
    
    return 0;
}

int ParseXmlIOProxyInput(char * xml_buf, CONTENT_ALMIN_CONF_S *almin_conf)
{
    char strbuf[32] = {0};
    mxml_node_t *root = NULL;
    mxml_node_t * IOProxyInput = NULL;

    root = mxmlLoadString(NULL, xml_buf, NULL);
    if (NULL == root)
    {
        //TRACE_ERR("mxmlLoadString error\n");
        return -1;
    }

    IOProxyInput = xml_parse_Get_Group(root, "IOProxyInput", NULL, NULL);
    {
        //xml_parse_GetString(IOProxyInput, "alarmInName", almin_conf->almin_name); //MWARNING
        xml_parse_GetString(IOProxyInput, "alarmInName", (char*)almin_conf->almin_name);
        xml_parse_GetString(IOProxyInput, "alarmType", strbuf);
        if (!strcmp(strbuf, "close"))
        {
            almin_conf->almtype = PT_ALMTYPE_CLOSE;
        }
        else
        {
            almin_conf->almtype = PT_ALMTYPE_OPEN;
        }
    }

    if (root != NULL)
    {
        mxmlRelease(root); 
    }

    return 0;
}

int ParseXmlSearchRecord(char * xml_buf, SearchRec_S * search_rec)
{
    mxml_node_t * root = NULL;
    mxml_node_t * CMSearchDescriptionNode = NULL, *timeSpanListNode = NULL, *timeSpanNode = NULL;
    mxml_node_t * trackListNode = NULL;
    char tm_buf[32];


    //printf("[ParseXmlSearchRecord]xml_buf = \n%s\n", xml_buf);

    root = mxmlLoadString(NULL, xml_buf, MXML_NO_CALLBACK);
    if (NULL == root)
    {
        printf("mxmlLoadString error\n");
        return -1;
    }

    CMSearchDescriptionNode = xml_parse_Get_Group(root, "CMSearchDescription", NULL, NULL);
    if (NULL != CMSearchDescriptionNode)
    {
        xml_parse_GetString(root, "searchID", search_rec->sid);
        //printf("search_rec->sid = %s\n", search_rec->sid);

        trackListNode = xml_parse_Get_Group(CMSearchDescriptionNode, "trackList", NULL, NULL);
        if (NULL != trackListNode)
        {
            xml_parse_Get_Integer(trackListNode, "trackID", &search_rec->track_id);
            //printf("search_rec->track_id = %d\n", search_rec->track_id);
        }
        else
        {
            if (NULL != root)
            {
                mxmlRelease(root); 
            }
            return -1;
        }

        timeSpanListNode = xml_parse_Get_Group(CMSearchDescriptionNode, "timeSpanList", NULL, NULL);
        if (NULL != timeSpanListNode)
        {
            timeSpanNode = xml_parse_Get_Group(timeSpanListNode, "timeSpan", NULL, NULL);
            if (NULL != timeSpanNode)
            {
                xml_parse_GetString(timeSpanNode, "startTime", tm_buf);
                ParseTimeSpan(tm_buf, &search_rec->time_span.start);
                printf("startTime = %d-%d-%d\n",search_rec->time_span.start.year, search_rec->time_span.start.month, 
                search_rec->time_span.start.day);

                xml_parse_GetString(timeSpanNode, "endTime", tm_buf);
                ParseTimeSpan(tm_buf, &search_rec->time_span.end);
                printf("endTime = %d-%d-%d\n",search_rec->time_span.end.year, search_rec->time_span.end.month, 
                search_rec->time_span.end.day);
            }
            else
            {
                if (NULL != root)
                {
                    mxmlRelease(root); 
                }
                return -1;
            }
        }
        else
        {
            if (NULL != root)
            {
                mxmlRelease(root); 
            }
            return -1;
        }

        xml_parse_Get_Integer(CMSearchDescriptionNode, "maxResults", &search_rec->max_ret);
        xml_parse_Get_Integer(CMSearchDescriptionNode, "searchResultPostion", &search_rec->startindex);
        //printf("search_rec->max_ret = %d\n", search_rec->max_ret);
    }

    if (NULL != root)
    {
        mxmlRelease(root); 
    }

    return 0;
}

int ParseXmlSearchLog(char * xml_buf, SearchLog_S * search_log)
{
    mxml_node_t * root = NULL;
    mxml_node_t * CMSearchDescriptionNode = NULL, *timeSpanListNode = NULL, *timeSpanNode = NULL;
    char tm_buf[32];

    memset(search_log, 0, sizeof(SearchLog_S));
    
    root = mxmlLoadString(NULL, xml_buf, MXML_NO_CALLBACK);
    if (NULL == root)
    {
        printf("mxmlLoadString error\n");
    }

    CMSearchDescriptionNode = xml_parse_Get_Group(root, "CMSearchDescription", NULL, NULL);
    if (NULL != CMSearchDescriptionNode)
    {
        xml_parse_GetString(root, "searchID", search_log->sid);
        //printf("search_log->sid = %s\n", search_log->sid);
        xml_parse_GetString(root, "metaId", search_log->mid);
        //printf("search_log->mid = %s\n", search_log->mid);
        timeSpanListNode = xml_parse_Get_Group(CMSearchDescriptionNode, "timeSpanList", NULL, NULL);
        if (NULL != timeSpanListNode)
        {
            timeSpanNode = xml_parse_Get_Group(timeSpanListNode, "timeSpan", NULL, NULL);
            if (NULL != timeSpanNode)
            {
                xml_parse_GetString(timeSpanNode, "startTime", tm_buf);
                ParseTimeSpan(tm_buf, &search_log->start_time);
                //printf("startTime = %d-%d-%d\n", search_log->start_time.year, search_log->start_time.month, search_log->start_time.day);

                xml_parse_GetString(timeSpanNode, "endTime", tm_buf);
                ParseTimeSpan(tm_buf, &search_log->end_time);
                //printf("endTime = %d-%d-%d\n", search_log->end_time.year, search_log->end_time.month, search_log->end_time.day);
            }
        }
        xml_parse_Get_Integer(CMSearchDescriptionNode, "maxResults", &search_log->max_ret);
        xml_parse_Get_Integer(CMSearchDescriptionNode, "searchResultPostion", &search_log->startindex);
        //printf("search_log->max_ret = %d startindex=%d\n", search_log->max_ret, search_log->startindex);
    }

    web2master_log_querytype_switch(search_log->mid, (int *)&search_log->pri_type, (int *)&search_log->sec_type);
    //printf("[web2master_log_querytype_switch]pri_type:%d, sec_type:%d \n", search_log->pri_type, search_log->sec_type);
    //search_log->pri_type = -1;
    //search_log->sec_type = 1;
    
    if (NULL != root)
    {
        mxmlRelease(root); 
    }
    
    return 0;
}


int ParseXmlChPtzCtrl(char * xml_buf, char *ptzcmd, PTZ_DEVICE_CTRL *ptz_ctrl)
{
    int ptzpan = 0, ptztilt = 0, autopan = 0, zoom = 0, focus = 0;
    int iris = 0;
    mxml_node_t * root = NULL;
    mxml_node_t * ptzdata = NULL;

    root = mxmlLoadString(NULL, xml_buf, NULL);
    if (NULL == root)
    {
        printf("mxmlLoadString error\n");
    }
    
    if (!strcmp(ptzcmd, "continuous"))
    {
        ptzdata = xml_parse_Get_Group(root, "PTZData", NULL, NULL);
        {
            xml_parse_Get_Integer(ptzdata, "pan", &ptzpan);
            xml_parse_Get_Integer(ptzdata, "tilt", &ptztilt);
            
            if((ptzpan > 0) && (!ptztilt))
            {
                ptz_ctrl->command = WEB_PTZ_CMD_RIGHT;
                ptz_ctrl->speed = ptzpan;
            }
            else if((ptzpan < 0) && (!ptztilt))
            {
                ptz_ctrl->command = WEB_PTZ_CMD_LEFT;
                ptz_ctrl->speed = -ptzpan;
            }
            else if((ptztilt < 0) && (!ptzpan))
            {
                ptz_ctrl->command = WEB_PTZ_CMD_DOWN;
                ptz_ctrl->speed = -ptztilt;
            }
            else if((ptztilt > 0) && (!ptzpan))
            {
                ptz_ctrl->command = WEB_PTZ_CMD_UP;
                ptz_ctrl->speed = ptztilt;
            }
            else if((ptzpan < 0) && (ptztilt < 0))
            {
                ptz_ctrl->command = WEB_PTZ_CMD_LEFT_DOWN;
                ptz_ctrl->speed = -ptzpan;
            }
            else if((ptzpan < 0) && (ptztilt > 0))
            {
                ptz_ctrl->command = WEB_PTZ_CMD_LEFT_UP;
                ptz_ctrl->speed = ptztilt;
            }
            else if((ptzpan > 0) && (ptztilt > 0))
            {
                ptz_ctrl->command = WEB_PTZ_CMD_RIGHT_UP;
                ptz_ctrl->speed = ptzpan;
            }
            else if((ptzpan > 0) && (ptztilt < 0))
            {
                ptz_ctrl->command = WEB_PTZ_CMD_RIGHT_DOWN;
                ptz_ctrl->speed = ptzpan;
            }
            else
            {
                ptz_ctrl->command = WEB_PTZ_CMD_STOP;
                //ptz_ctrl->speed = 0;
            }
        }
    }
    else if (!strcmp(ptzcmd, "autoPan"))
    {
        ptzdata = xml_parse_Get_Group(root, "autoPanData", NULL, NULL);
        xml_parse_Get_Integer(ptzdata, "autoPan", &autopan);
        if (0 == autopan)
        {
            ptz_ctrl->command = WEB_PTZ_CMD_STOP;
        }
        else
        {
            ptz_ctrl->command = WEB_PTZ_CMD_AUTO;
        }
        ptz_ctrl->speed = autopan;
    }
    else if (!strcmp(ptzcmd, "zoom"))
    {
        ptzdata = xml_parse_Get_Group(root, "ZoomData", NULL, NULL);
        xml_parse_Get_Integer(ptzdata, "zoom", &zoom);
        if (0 == zoom)
        {
            ptz_ctrl->command = WEB_PTZ_CMD_STOP;
        }
        else
        {
            ptz_ctrl->command = (zoom>0)?(WEB_PTZ_CMD_ZOOM_INC):(WEB_PTZ_CMD_ZOOM_DEC);
        }
        ptz_ctrl->speed = (zoom>0)?(zoom):(-zoom);
    }
    else if (!strcmp(ptzcmd, "focus"))
    {
        ptzdata = xml_parse_Get_Group(root, "FocusData", NULL, NULL);
        xml_parse_Get_Integer(ptzdata, "focus", &focus);
        if (0 == focus)
        {
            ptz_ctrl->command = WEB_PTZ_CMD_STOP;
        }
        else
        {
            ptz_ctrl->command = (focus>0)?(WEB_PTZ_CMD_FOCUS_INC):(WEB_PTZ_CMD_FOCUS_DEC);
        }
        ptz_ctrl->speed = (focus>0)?(focus):(-focus);
    }
    else if (!strcmp(ptzcmd, "iris"))
    {
        ptzdata = xml_parse_Get_Group(root, "IrisData", NULL, NULL);
        xml_parse_Get_Integer(ptzdata, "iris", &iris);
        if (0 == iris)
        {
            ptz_ctrl->command = WEB_PTZ_CMD_STOP;
        }
        else
        {
            ptz_ctrl->command = (iris>0)?(WEB_PTZ_CMD_IRIS_INC):(WEB_PTZ_CMD_IRIS_DEC);
        }
        ptz_ctrl->speed = (iris>0)?(iris):(-iris);
    }
    else if (!strcmp(ptzcmd, "wiper"))
    {
        ptz_ctrl->command = WEB_PTZ_CMD_BRUSH;
    }
    else if (!strcmp(ptzcmd, "light"))
    {
        ptz_ctrl->command = WEB_PTZ_CMD_F1;
    }
    else
    {
        if (NULL != root)
        {
            mxmlRelease(root); 
        }
        return -1;
    }

    if (NULL != root)
    {
        mxmlRelease(root); 
    }
    
    return 0;
}


