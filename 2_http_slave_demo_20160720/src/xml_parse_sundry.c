/****************************************************************
 * FileName:xml_parse_sundry.c
 * Author:merlin
 * Version:v1
 * Time:20160613
 * Description:create and parse xml package
 * *************************************************************/
#include "common.h"
#include "xml_base.h"
#include "xml_parse_sundry.h"

int ParseXmlStreamingPbControl(char * xml_buf, STREAMING_PB_CONTROL * pb_control)
{
    mxml_node_t * root = NULL;
	mxml_node_t * playback = NULL;

	root = mxmlLoadString(NULL, xml_buf, NULL);
    if (NULL == root)
    {
        printf("mxmlLoadString error\n");
    }

    playback = xml_parse_Get_Group(root, "playback", NULL, NULL);
    if (NULL != playback)
    {
        xml_parse_GetString(playback, "streamId", pb_control->streamid);
        xml_parse_GetString(playback, "control", pb_control->option);
        xml_parse_Get_Integer(playback, "speed", &(pb_control->speed));      
    }
    else
    {
        printf("playback is NULL! \n");
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



int ParseXmlHeartBeatInfo(char * xml_buf, WEB_HEARTBEAT_INFO *heartbeat_info)
{
    int i = 0;
    char typebuf[16] = {0};
    mxml_node_t * root = NULL;
    mxml_node_t * heartbeat = NULL;
    mxml_node_t * RTMPStream = NULL;

    root = mxmlLoadString(NULL, xml_buf, NULL);
    if (NULL == root)
    {
        printf("mxmlLoadString error\n");
    }

    heartbeat = xml_parse_Get_Group(root, "heartbeat", NULL, NULL);

    if (NULL != heartbeat)
    {
        for (i = 0; i < ISAPI_STREAM_MAXCH; i++)
        {
            RTMPStream= mxmlFindElementIns((0 == i)?heartbeat:RTMPStream, heartbeat, "RTMPStream", NULL, NULL, MXML_DESCEND);

            if (NULL != RTMPStream)
            {
                xml_parse_GetString(RTMPStream, "streamId", heartbeat_info->stream_info[i].streamid);
                xml_parse_Get_Integer(RTMPStream, "channel", (int *)&(heartbeat_info->stream_info[i].channel)); //MWRNING
                xml_parse_GetString(RTMPStream, "type", typebuf);
                if (!strcmp(typebuf, "playback"))
                {
                    heartbeat_info->stream_info[i].type = 1;
                }
                else
                {
                    heartbeat_info->stream_info[i].type = 0;
                }
            }
            else
            {
                break;
            }
        }
    
    }
    else
    {
        printf("ParseXmlHeartBeatInfo is NULL! \n");
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

