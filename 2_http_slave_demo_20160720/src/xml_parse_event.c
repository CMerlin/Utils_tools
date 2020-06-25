/****************************************************************
 * FileName:xml_parse_event.c
 * Author:merlin
 * Version:v1
 * Time:20160613
 * Description:create and parse xml package
 * *************************************************************/
#include "common.h"
#include "xml_base.h"
#include "xml_parse_event.h"

int ParseXmlEventSchedules(char * xml_buf, int size, EVENT_TRIGGER_S *eventtrigger)
{
    int i = 0, dayindex = 0, segindex[WEEK_DAYNUM] = {0}, index = 0;
    char strbuf[32] = {0};
    int startth = 0, starttm = 0, endth = 0, endtm = 0;
    mxml_node_t *root = NULL;
    mxml_node_t *Schedule = NULL, *TimeBlockList = NULL, *TimeBlock = NULL, *TimeRange = NULL;

    root = mxmlLoadString(NULL, xml_buf, NULL);
    if (NULL == root)
    {
        printf("mxmlLoadString error\n");
        return -1;
    }
    else
    {
        Schedule = xml_parse_Get_Group(root, "Schedule", NULL, NULL);
        if (NULL != Schedule)
        {
            TimeBlockList = xml_parse_Get_Group(Schedule, "TimeBlockList", NULL, NULL);

            memset(segindex, 0, WEEK_DAYNUM*sizeof(int));  
            for (i = 0; i < (WEEK_DAYNUM*DAY_SEGNUM); i++)
            {
                TimeBlock = mxmlFindElementIns((0 == i)?TimeBlockList:TimeBlock, TimeBlockList, "TimeBlock", NULL, NULL, MXML_DESCEND);
                if (TimeBlock != NULL)
                {
                    xml_parse_Get_Integer(TimeBlock, "dayOfWeek", &dayindex);
                    dayindex = dayindex - 1;
                    index = segindex[dayindex];
                    segindex[dayindex]++;

                    TimeRange = xml_parse_Get_Group(TimeBlock, "TimeRange", NULL, NULL);
                    xml_parse_GetString(TimeRange, "beginTime", strbuf);
                    sscanf(strbuf, "%2d:%2d:00", &startth, &starttm);
                    xml_parse_GetString(TimeRange, "endTime", strbuf);
                    sscanf(strbuf, "%2d:%2d:00", &endth, &endtm);
                    if (24 == endth)
                    {
                        endth = 23;
                        endtm = 59;
                    }
                    eventtrigger->scheduleinfo.timeperiodinfo[dayindex].tmperiod[index].start.hour = startth;
                    eventtrigger->scheduleinfo.timeperiodinfo[dayindex].tmperiod[index].start.min = starttm;
                    eventtrigger->scheduleinfo.timeperiodinfo[dayindex].tmperiod[index].end.hour = endth;
                    eventtrigger->scheduleinfo.timeperiodinfo[dayindex].tmperiod[index].end.min = endtm;

                    //printf("ParseXmlEventSchedules dayindex:%d index:%d start:%2d:%2d end:%2d:%2d\n", dayindex, index,
                    //startth, starttm, endth, endtm);
                }
                else
                {
                    break;
                }
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
    }

    if (NULL != root)
    {
        mxmlRelease(root); 
    }
    return 0;
}

int ParseXmlEventManual(char * xml_buf, int size, PEVENT_MANUAL_S info)
{
    mxml_node_t *root = NULL;
    mxml_node_t * ManualList = NULL;
    int id = 0;
    char trigger[32] = {0};

    root = mxmlLoadString(mxmlNewXML("1.0"), xml_buf, NULL);
    if (NULL == root)
    {
        printf("mxmlLoadString error\n");
        return -1;
    }

    ManualList = xml_parse_Get_Group(root, "ManualList", NULL, NULL);
    if (ManualList != NULL)
    {
        mxml_node_t *manual;
        for (manual = mxmlFindElement(ManualList, ManualList, "Manual", NULL, NULL, MXML_DESCEND);
            manual != NULL;
            manual = mxmlFindElement(manual, ManualList, "Manual", NULL, NULL, MXML_DESCEND))
        {
            xml_parse_Get_Integer(manual, "id", &id);
            xml_parse_GetString(manual, "trigger", trigger);
            printf("ParseXmlEventManual id=%d, trigger=%s\n", id, trigger);
            if (id < 1 || id > 32)
            {   
                printf("ParseXmlEventManual Invalid id=%d\n", id);
                return -1;
            }

            if (!strcmp("true", trigger))
            {
                info->status[id-1] = 1;
            }
            else
            {
                info->status[id-1] = 0;
            }
        }
        if (NULL != root)
        {
            mxmlRelease(root); 
        }
        return 0;
    }

    if (NULL != root)
    {
        mxmlRelease(root); 
    }
    return -1;
}

int ParseXmlEventManualIdx(char * xml_buf, int size, PEVENT_MANUAL_S info, int index)
{
    mxml_node_t *root = NULL;
    mxml_node_t * Manual = NULL;
    int id = 0;
    char trigger[32] = {0};

    if (index <= 0 || index > 32)
    {
        return -1;
    }

    root = mxmlLoadString(mxmlNewXML("1.0"), xml_buf, NULL);
    if (NULL == root)
    {
        printf("mxmlLoadString error\n");
        return -1;
    }

    Manual = xml_parse_Get_Group(root, "Manual", NULL, NULL);
    if (NULL != Manual)
    {
        xml_parse_Get_Integer(Manual, "id", &id);
        xml_parse_GetString(Manual, "trigger", trigger);
        printf("ParseXmlEventManual id=%d, trigger=%s\n", id, trigger);
        //if (id < 1 || id > 32)
        if (id != index)
        {   
            printf("ParseXmlEventManualIdx Invalid id=%d\n", id);
            return -1;
        }

        if (!strcmp("true", trigger))
        {
            info->status[id-1] = 1;
        }
        else
        {
            info->status[id-1] = 0;
        }
        if (NULL != root)
        {
            mxmlRelease(root); 
        }
        return 0;
    }

    if (NULL != root)
    {
        mxmlRelease(root); 
    }
    return -1;
}

