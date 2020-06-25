/****************************************************************
 * FileName:xml_parse_system.c
 * Author:merlin
 * Version:v1
 * Time:20160613
 * Description:create and parse xml package
 * *************************************************************/
#include "common.h"
#include "xml_base.h"
#include "xml_parse_system.h"

#define XML_BUF_SIZE_4K    4 * 1024

/*************************************************************
* 函数介绍：无符号整形IP转字符串
* 输入参数：
        int_ip: 整形IP
        str_size: str_ip字符指针大小
* 输出参数：str_ip: IP字符串
* 返回值  ：<0: 错误, =0成功，
*************************************************************/
sint32 uint_ip_to_string(char * str_ip, sint32 str_size, uint32 int_ip)
{
    snprintf(str_ip, str_size, "%d.%d.%d.%d", int_ip >> 24, (int_ip >> 16) & 0xff, (int_ip >> 8) & 0xff, int_ip & 0xff);

    return 0;
}

/*************************************************************
* 函数介绍：字符串IP转无整形数
* 输入参数：
        str_ip: IP字符串
* 输出参数：s
* 返回值  ：<0: 错误, >=0: 无整形IP
*************************************************************/
uint32 string_ip_to_uint(char * str_ip)
{
    uint16 num;
    uint32 addr = 0;
    uint8 parts = 0;
    uint8 * ap;

    ap = (uint8 *)(&addr) + 3;
    while (parts < 4)
    {
        if (*str_ip < '0' || *str_ip > '9')
            break;
        for (num = 0; num <= 255;)
        {
            num = (num * 10) + (*str_ip - '0');
            if (*++str_ip < '0' || *str_ip > '9')
                break;
        }
        if (num > 255)
            break;
        parts++;
        *ap = (uint8) num;
        if (*str_ip != '.')
        {
            if (parts == 4)
                return addr;
            break;
        }
        ap--;
        str_ip++;
    }
    return 0;
}


int ParseTimeSpan(char * tm_buf, SYSTIME * tm)
{
    int year, month, day, hour, min, sec;

    //printf("tm_buf = %s\n", tm_buf);

    sscanf(tm_buf, "%d-%d-%dT%d:%d:%dZ", &year, &month, &day, &hour, &min, &sec);

    tm->year = year - 2000;
    tm->month = month;
    tm->day = day;
    tm->hour = hour;
    tm->min = min;
    tm->sec = sec;
    return 0;
}

/*
 * 函数功能描述：解析xml文件，将解析出来的信息存储到met_param中
 * 输入参数：需要进行解析的xml数据
 * 输出参数：解析好的xml数据
 * 函数返回值：0-成功
 * change:修改
 * */
int ParseXmlNetworkInterfaces(char * xml_buf, NETWORK_DEVICE_INFO_S * net_param)
{
    mxml_node_t * root = NULL;
    mxml_node_t * NetworkInterfaceNode = NULL;
    mxml_node_t * IPAddressNode = NULL, * DefaultGatewayNode = NULL, * PrimaryDNSNode = NULL, * SecondaryDNSNode = NULL;
    mxml_node_t * LinkNode = NULL;

	//printf("[%lu][%s]:xml_buf=%s LINE:%d\n", pthread_self(), __func__, xml_buf, __LINE__);
    char ip_ver[32] = {0}, addr_type[32] = {0}, ipaddr[128] = {0}, net_mask[128] = {0};
    char gate_addr[32] = {0}, dns1[128] = {0}, dns2[128] = {0};
    char mac_addr[32] = {0}, at_neg[8] = {0}, speed[8] = {0}, duplex[32] = {0}, mtu[8] = {0};

    root = mxmlLoadString(NULL, xml_buf, NULL);
    if (NULL == root)
    {
        printf("mxmlLoadString error\n");
    }

    NetworkInterfaceNode = xml_parse_Get_Group(root, "NetworkInterface", NULL, NULL);
    if (NULL != NetworkInterfaceNode)
    {
        //xml_parse_GetString(NetworkInterfaceNode, "id", sid);
        xml_parse_Get_Integer(NetworkInterfaceNode, "id", &(net_param->id));
        IPAddressNode = xml_parse_Get_Group(NetworkInterfaceNode, "IPAddress", NULL, NULL);
        if (NULL != IPAddressNode)
        {
            xml_parse_GetString(IPAddressNode, "ipVersion", ip_ver);
            xml_parse_GetString(IPAddressNode, "addressingType", addr_type);
            xml_parse_GetString(IPAddressNode, "ipAddress", ipaddr);
			xml_parse_GetString(IPAddressNode, "subnetMask", net_mask);
			//printf("[%lu][%s]:ipaddr=%s LINE:%d\n", pthread_self(), __func__, ipaddr, __LINE__);
			DefaultGatewayNode = xml_parse_Get_Group(IPAddressNode, "DefaultGateway", NULL, NULL);
            if (NULL != DefaultGatewayNode)
            {
                xml_parse_GetString(DefaultGatewayNode, "ipAddress", gate_addr);
                //printf("gate_addr:%s \n", gate_addr);
            }
            PrimaryDNSNode = xml_parse_Get_Group(IPAddressNode, "PrimaryDNS", NULL, NULL);
            if (NULL != PrimaryDNSNode)
            {
                xml_parse_GetString(PrimaryDNSNode, "ipAddress", dns1);
                //printf("dns1:%s \n", dns1);
            }
            SecondaryDNSNode = xml_parse_Get_Group(IPAddressNode, "SecondaryDNS", NULL, NULL);
            if (NULL != SecondaryDNSNode)
            {
                xml_parse_GetString(SecondaryDNSNode, "ipAddress", dns2);
                //printf("dns2:%s \n", dns2);
            }
        }
        else
        {
            printf("IPAddressNode is NULL! \n");
        }

        LinkNode = xml_parse_Get_Group(NetworkInterfaceNode, "Link", NULL, NULL);
        if (NULL != LinkNode)
        {
            xml_parse_GetString(LinkNode, "MACAddress", mac_addr);
            xml_parse_GetString(LinkNode, "autoNegotiation", at_neg);
            xml_parse_GetString(LinkNode, "speed", speed);
            xml_parse_GetString(LinkNode, "duplex", duplex);
            xml_parse_GetString(LinkNode, "MTU", mtu);
        }
        else
        {
            printf("LinkNode is NULL! \n");
        }
    }
    else
    {
        printf("NetworkInterfaceNode is NULL! \n");
    }

	memcpy(net_param->link.mac, mac_addr, strlen(mac_addr));
    net_param->link.speed = atoi(speed);
    net_param->link.duplex = (!strcmp(duplex,"half"))?half:full;
    net_param->ip.dhcp_enable = strcmp("static", addr_type)?1:0;
    net_param->ip.ipaddr = string_ip_to_uint(ipaddr);
    net_param->ip.netmask = string_ip_to_uint(net_mask);
    net_param->ip.dns1 = string_ip_to_uint(dns1);
    net_param->ip.dns2 = string_ip_to_uint(dns2);
    net_param->ip.gateway = string_ip_to_uint(gate_addr);
	//trace(TRACE, "[%s]:ip=%s gateway=%s dns1=%s dns2=%s mask=%s hwaddr=%s LINE:%d\n", __func__, ipaddr, gate_addr, dns1, dns2, net_mask, mac_addr, __LINE__);
    
	if (NULL != root)
    {
        mxmlRelease(root); 
    }

    return 0;
}

int ParseXmlPPPoE(char * xml_buf, NETWORK_PPPOE_S * pppoe_param)
{
    mxml_node_t * root = NULL;
    mxml_node_t * PPPoENode = NULL;
    char tmpbuf[16] = {0};

    root = mxmlLoadString(NULL, xml_buf, NULL);
    if (NULL == root)
    {
        printf("mxmlLoadString error\n");
    }

    PPPoENode = xml_parse_Get_Group(root, "PPPoE", NULL, NULL);
    if (NULL != PPPoENode)
    {
        xml_parse_GetString(PPPoENode, "user", pppoe_param->userName);
        xml_parse_GetString(PPPoENode, "password", pppoe_param->pwd);
        xml_parse_GetString(PPPoENode, "autoLogin", tmpbuf);
        if (!strcmp(tmpbuf, "true"))
        {
            pppoe_param->autologin = 1;
        }
        else
        {
            pppoe_param->autologin = 0;
        }
        xml_parse_GetString(PPPoENode, "status", tmpbuf);
        if (!strcmp(tmpbuf, "true"))
        {
            pppoe_param->status = 1;
        }
        else
        {
            pppoe_param->status = 0;
        }
    }
    else
    {
        printf("PPPoENode is NULL! \n");
    }

    if (NULL != root)
    {
        mxmlRelease(root); 
    }

    return 0;
}

int ParseXmlDDNS(char * xml_buf, NETWORK_DDNS_S * ddns_param)
{
    char nodebuf[32] = {0};
    mxml_node_t * root = NULL;
    mxml_node_t * DDNSNode = NULL;
    //mxml_node_t * serverAddressNode = NULL; //MWARNING

    //char enable[8] = {0}, provider[32] = {0}, addr_type[8] = {0}, hiddns[32] = {0};
    //char domain[32] = {0};

    root = mxmlLoadString(NULL, xml_buf, NULL);
    if (NULL == root)
    {
        printf("mxmlLoadString error\n");
    }

    DDNSNode = xml_parse_Get_Group(root, "DDNS", NULL, NULL);
    if (NULL != DDNSNode)
    {
        xml_parse_Get_Integer(DDNSNode, "id", &ddns_param->index);
        ddns_param->index--;
        xml_parse_GetString(DDNSNode, "server", (char *)ddns_param->server);
        xml_parse_GetString(DDNSNode, "defaultRegist", nodebuf);
        if (!strcmp(nodebuf, "true"))
        {
            ddns_param->domain_default_flag = 1;
        }
        else
        {
            ddns_param->domain_default_flag = 0;
        }
        xml_parse_GetString(DDNSNode, "domainName", (char*)ddns_param->set_dn); 
        xml_parse_GetString(DDNSNode, "user", (char*)ddns_param->user); 
        xml_parse_GetString(DDNSNode, "password",  (char*)ddns_param->pwd); 
        xml_parse_GetString(DDNSNode, "autoLogin", nodebuf);
        if (!strcmp(nodebuf, "true"))
        {
            ddns_param->auto_connect = 1;
        }
        else
        {
            ddns_param->auto_connect = 0;
        }
        xml_parse_GetString(DDNSNode, "login", nodebuf);
        if (!strcmp(nodebuf, "true"))
        {
            ddns_param->command = 1;
        }
        else
        {
            ddns_param->command = 0;
        }
    }
	//trace(TRACE, "[%s]:index=%d domain_default_flag=%d set_dn=%s user=%s pwd=%s auto_connect=%d command=%d LINE:%d\n",__func__, ddns_param->index, ddns_param->domain_default_flag, ddns_param->set_dn, ddns_param->user, ddns_param->pwd, ddns_param->auto_connect, ddns_param->command, __LINE__);

    if (NULL != root)
    {
        mxmlRelease(root); 
    }

    return 0;
}

int ParseXmlUPnP(char * xml_buf, NETWORK_UPNP_S * upnp_param)
{
    char upnp_en[16] = {0};
    mxml_node_t * root = NULL;
    mxml_node_t * UPnP = NULL;

    root = mxmlLoadString(NULL, xml_buf, NULL);
    if (NULL == root)
    {
        printf("mxmlLoadString error\n");
    }
    
    UPnP = xml_parse_Get_Group(root, "UPnP", NULL, NULL);
    if (NULL != UPnP)
    {
        xml_parse_GetString(UPnP, "enabled", upnp_en);
    }

    if(0 == strcmp(upnp_en, "true"))
    {
        upnp_param->upnp_en = 1;
    }
    else
    {
        upnp_param->upnp_en = 0;
    }

	trace(TRACE, "[%s]:upnp_en=%d LINE:%d\n", __func__,  upnp_param->upnp_en, __LINE__);
    if (NULL != root)
    {
        mxmlRelease(root); 
    }
    return 0;
}

int ParseXmlUPnPPort_Add(char * xml_buf, NETWORK_PAT_UPNP_S * upnp_part)
{
    char strbuf[32] = {0};
    mxml_node_t * root = NULL;
    mxml_node_t * UPnPPort = NULL, *port = NULL;

	trace(DEBUG, "[%s]: ******************LINE:%d\n", __func__, __LINE__);
    root = mxmlLoadString(NULL, xml_buf, NULL);
    if (NULL == root)
    {
        printf("mxmlLoadString error\n");
    }
    
	trace(DEBUG, "[%s]: ******************LINE:%d\n", __func__, __LINE__);
    UPnPPort = xml_parse_Get_Group(root, "UPnPPort", NULL, NULL);
    {
	trace(DEBUG, "[%s]: ******************LINE:%d\n", __func__, __LINE__);
        port = xml_parse_Get_Group(UPnPPort, "port", NULL, NULL);
        {
	trace(DEBUG, "[%s]: ******************LINE:%d\n", __func__, __LINE__);
            xml_parse_GetString(port, "name", upnp_part->server_name);
            xml_parse_GetString(port, "protocol", strbuf);
            if(0 == strcmp(strbuf, "TCP"))
            {
                upnp_part->protocol = 1;
            }
            else
            {
                upnp_part->protocol = 0;
            }
            xml_parse_Get_Integer(port, "DVRPort", (int *)&(upnp_part->dvr_port)); 
            xml_parse_Get_Integer(port, "routerPort", (int *)(&(upnp_part->rount_port))); 
	trace(DEBUG, "[%s]: ****************** DVRPort=%d LINE:%d\n", __func__, upnp_part->dvr_port, __LINE__);
        }
    }

	trace(DEBUG, "[%s]: ******************LINE:%d\n", __func__, __LINE__);
    if (NULL != root)
    {
        mxmlRelease(root); 
    }

    return 0;
}

int ParseXmlUPnPPort_Edit(char * xml_buf, NETWORK_PAT_UPNP_S * upnp_part)
{
    int id = 0;
    char strbuf[32] = {0};
    mxml_node_t * root = NULL;
    mxml_node_t * UPnPPort = NULL, *port = NULL;

    root = mxmlLoadString(NULL, xml_buf, NULL);
    if (NULL == root)
    {
        printf("mxmlLoadString error\n");
    }
    
    UPnPPort = xml_parse_Get_Group(root, "UPnPPort", NULL, NULL);
    {
        port = xml_parse_Get_Group(UPnPPort, "port", NULL, NULL);
        {
            xml_parse_Get_Integer(port, "id", &id);
            xml_parse_GetString(port, "name", upnp_part->server_name);
            xml_parse_GetString(port, "protocol", strbuf);
            if(0 == strcmp(strbuf, "TCP"))
            {
                upnp_part->protocol = 1;
            }
            else
            {
                upnp_part->protocol = 0;
            }
            xml_parse_Get_Integer(port, "DVRPort", (int *)&(upnp_part->dvr_port));
            xml_parse_Get_Integer(port, "routerPort",  (int *)&((upnp_part->rount_port)));
        }
    }

    if (NULL != root)
    {
        mxmlRelease(root); 
    }

    return id;
}

int ParseXmlSystemTime(char * xml_buf, SYSTEM_TIME_CFG_S * time_cfg)
{
	mxml_node_t *root = NULL;
	mxml_node_t *TimeNode = NULL;
	char localtime[32] = {0};
	sint32 year = 0, day = 0, month = 0, hour = 0, min = 0, second = 0;
	
    root = mxmlLoadString(NULL, xml_buf, NULL);
    if (NULL == root)
    {
        printf("mxmlLoadString error\n");
    }

    TimeNode = xml_parse_Get_Group(root, "Time", NULL, NULL);
    if (NULL != TimeNode)
    {
        //xml_parse_GetString(TimeNode, "timeZone", timezone);
        //printf("[ParseXmlSystemTime]timezone = %s\n", timezone);
        xml_parse_GetString(TimeNode, "localTime", localtime);
        //TRACE_DBG("localtime:%s\n", localtime);
        sscanf(localtime, "%d-%d-%dT%d:%d:%d", &year, &month, &day, &hour, &min, &second);
        //printf("year =%d month=%d day = %d hour= %d min = %d sec = %d\n", year, month, day, hour, min, second);
        time_cfg->dev_time.year = year - 2000;
        time_cfg->dev_time.month = month;
        time_cfg->dev_time.day = day;
        time_cfg->dev_time.hour = hour;
        time_cfg->dev_time.min = min;
        time_cfg->dev_time.sec = second;
		
	    //TRACE_DBG("time_zone:%d\n", time_cfg->time_zone);
    }
    else
    {
        printf("TimeNode is NULL! \n");
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

/*
 * 函数功能描述：
 * 输入参数：
 * 输出参数：
 * 输入参数：
 * 函数返回值：
 * */
char * xml_parse_GetOpaque(mxml_node_t * node, const char * name, char * str)
{
    mxml_node_t * element = NULL;

    if (str == NULL)
    {
        return NULL;
    }

    element = mxmlFindElementIns(node, node, name, NULL, NULL, MXML_DESCEND);
    if (element)
    {
        if (NULL == mxmlGetOpaque(element))
        {
            return NULL;
        }
        strcpy(str, mxmlGetOpaque(element));
        //printf("<%s>%s</%s>\n", name, str, name);

        return str;
    }
    return NULL;
}

#if 1
int ParseXmlMailing(char * xml_buf, NETWORK_SMTP_S * smtp_param)
{
    char strbuf[256], recvbuf[64];
    int id = 0, i = 0;
    mxml_node_t * root = NULL;
    mxml_node_t * mailinglist = NULL, *mailing = NULL;
    mxml_node_t * recvAddrList = NULL, *recvAddr = NULL;

    root = mxmlLoadString(NULL, xml_buf, NULL);
    if (NULL == root)
    {
        printf("mxmlLoadString error\n");
    }

    mailinglist = xml_parse_Get_Group(root, "mailinglist", NULL, NULL);
    mailing = xml_parse_Get_Group(mailinglist, "mailing", NULL, NULL);
    
    if (NULL != mailing)
    {
        xml_parse_Get_Integer(mailing, "id", &id);
        xml_parse_GetString(mailing, "host", smtp_param->host);
        xml_parse_Get_Integer(mailing, "port", &(smtp_param->port));
        xml_parse_GetString(mailing, "user", smtp_param->user);
        xml_parse_GetString(mailing, "password", smtp_param->pwd);
        xml_parse_GetString(mailing, "sendAddr", smtp_param->send_addr);
		//trace(TRACE, "[%s]:id=%d host=%s port=%d user=%s password=%s sendAddr=%s LINE:%d\n", __func__, id, smtp_param->host, smtp_param->port, smtp_param->user, smtp_param->pwd, smtp_param->send_addr , __LINE__);
        recvAddrList = xml_parse_Get_Group(mailing, "recvAddrList", NULL, NULL);
        {
            //while(recvAddr= mxmlFindElementIns((0 == i)?recvAddrList:recvAddr, recvAddrList, "recvAddr", NULL, NULL, MXML_DESCEND))
            while(NULL != (recvAddr= mxmlFindElementIns((0 == i)?recvAddrList:recvAddr, recvAddrList, "recvAddr", NULL, NULL, MXML_DESCEND)))
            {
                xml_parse_GetString(recvAddr, "email", recvbuf);
                if(0==i)
                {                   
                    strcpy(smtp_param->recv_addr, recvbuf);                    
                }
                else
                {   strcpy(strbuf, smtp_param->recv_addr);
                    sprintf(smtp_param->recv_addr, "%s;%s", strbuf, recvbuf);
                }
                i++;
                //printf("+++++++++++mail recv addrnum:%d\n", i);
            }
            //printf("+++++++++++mail recv addr:%s\n", smtp_param->recv_addr);
        }

        xml_parse_Get_Integer(mailing, "sendPeriod", &(smtp_param->send_period));
        xml_parse_GetString(mailing, "snapshotEnable", recvbuf);
        if(!strcmp("true", recvbuf))
        {
            smtp_param->snap_enable = 1;
        }
        xml_parse_GetString(mailing, "SSLEnable", recvbuf);
        if(!strcmp("true", recvbuf))
        {
            smtp_param->ssl_enable= 1;
        }
        xml_parse_GetString(mailing, "STARTEnable", recvbuf);
        if(!strcmp("true", recvbuf))
        {
            smtp_param->starttls_enable= 1;
        }
        
    }

    if (NULL != root)
    {
        mxmlRelease(root); 
    }

    return 0;
}

#endif

/*
 * change：修改
 * */
int ParseXmlDeviceInfo(char * xml_buf, SYSTEM_DEVICE_INFO_S * dev_info)
{
    mxml_node_t * root = NULL;
    mxml_node_t * DeviceInfoNode = NULL;
    char version_1[16] = {0}, version_2[16] = {0};
    char enc_ver_1[16] = {0}, enc_ver_2[16] = {0};
    int ch_num = 0, disk_num = 0, senin_num = 0, senout_num = 0, dev_id = 0;


    //root = mxmlLoadString(NULL, xml_buf, mxml_opaque_cb);
    root = mxmlLoadString(NULL, xml_buf, NULL);
    if (NULL == root)
    {
        printf("mxmlLoadString error\n");
    }

    DeviceInfoNode = xml_parse_Get_Group(root, "DeviceInfo", NULL, NULL);
    if (NULL != DeviceInfoNode)
    {
        /*xml_parse_GetString(DeviceInfoNode, "deviceName", dev_info->dev_name);*/
        xml_parse_GetOpaque(DeviceInfoNode, "deviceName", dev_info->dev_name);
        //xml_parse_GetString(DeviceInfoNode, "deviceID", dev_info->dev_id);
        xml_parse_Get_Integer(DeviceInfoNode, "deviceID", &dev_id);
		sprintf(dev_info->dev_id, "%d", dev_id);
        xml_parse_GetString(DeviceInfoNode, "model", dev_info->dev_type);
        xml_parse_GetString(DeviceInfoNode, "serialNumber", dev_info->dev_no);
        xml_parse_GetString(DeviceInfoNode, "firmwareVersion", version_1);
        xml_parse_GetString(DeviceInfoNode, "firmwareReleasedDate", version_2);
        xml_parse_GetString(DeviceInfoNode, "encoderVersion", enc_ver_1);
        xml_parse_GetString(DeviceInfoNode, "encoderReleasedDate", enc_ver_2);
        xml_parse_Get_Integer(DeviceInfoNode, "ChannelNum", &ch_num);
        xml_parse_Get_Integer(DeviceInfoNode, "DiskNum", &disk_num);
        xml_parse_Get_Integer(DeviceInfoNode, "AlarmInNum", &senin_num);
        xml_parse_Get_Integer(DeviceInfoNode, "AlarmOutNum", &senout_num);
    }

    if (NULL != root)
    {
        mxmlRelease(root); 
    }

    return 0;
}

int ParseXmlSystemIoInput(char * xml_buf, SYSTEM_IO_INPUTLIST_S *inputlist, int almin_num)
{
    char nodebuf[32] = {0};
    mxml_node_t * root = NULL;
    //mxml_node_t * *IOInputPort = NULL;
    mxml_node_t * IOInputPort = NULL;

    root = mxmlLoadString(NULL, xml_buf, NULL);
    if (NULL == root)
    {
        printf("mxmlLoadString error\n");
        return -1;
    }

    IOInputPort = xml_parse_Get_Group(root, "IOInputPort", NULL, NULL);
    if (NULL != IOInputPort)
    {
        xml_parse_GetString(IOInputPort, "enabled", nodebuf);
        inputlist->io_input[almin_num].enabled = (!strcmp(nodebuf, "true")) ? 1 : 0;

        xml_parse_GetString(IOInputPort, "triggering", nodebuf);
        inputlist->io_input[almin_num].triggering = (!strcmp(nodebuf, "high")) ? 1 : 0;

        xml_parse_GetString(IOInputPort, "name", inputlist->io_input[almin_num].almin_name); //MWARNING
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

int ParseXmlSystemIoOutput(char * xml_buf, SYSTEM_IO_OUTPUTLIST_S *outputlist, int almout_num)
{   
    mxml_node_t *root = NULL;
    //mxml_node_t **IOOutputPort = NULL, *PowerOnState = NULL;
    mxml_node_t *IOOutputPort = NULL, *PowerOnState = NULL;

    root = mxmlLoadString(NULL, xml_buf, NULL);
    if (NULL == root)
    {
        printf("mxmlLoadString error\n");
        return -1;
    }

    IOOutputPort = xml_parse_Get_Group(root, "IOOutputPort", NULL, NULL); //MWARNING
    if (NULL != IOOutputPort)
    {
        PowerOnState = xml_parse_Get_Group(IOOutputPort, "PowerOnState", NULL, NULL); //MWARNING
        {
            xml_parse_GetString(PowerOnState, "pulseDuration", (char*)&(outputlist->io_output[almout_num].pulseDuration)); //MWARNING
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

    if (NULL != root)
    {
        mxmlRelease(root); 
    }

    return 0;
}

/******************************************************************************
 * Description：
 * Input handler：模块句柄，暂时无效
 * Input request：封装http请求包需要用到的参数
 * Output response：解析响应包得到的信息
 * Return：0-成功 <0-错误代码
 * *****************************************************************************/
int ParseXmlCommonResponse(char * xml_buf, COMMON_RESPONSE_S *response)
{   
    mxml_node_t *root = NULL;

    root = mxmlLoadString(NULL, xml_buf, NULL);
    if (NULL == root)
    {
        printf("mxmlLoadString error\n");
        return -1;
	}
	xml_parse_GetString(root, "requestURL", response->requestURL);
	xml_parse_Get_Integer(root, "statusCode", &(response->statusCode));
	xml_parse_GetString(root, "statusString", response->statusString);
	xml_parse_GetString(root, "subStatusCode", response->subStatusCode);

    if (NULL != root)
    {
        mxmlRelease(root); 
    }

    return 0;
}

int ParseXmlSystemNtpServer(char * xml_buf, SYSTEM_NTP_CFG_S * ntp_cfg)
{
    mxml_node_t * root = NULL;
    mxml_node_t * NTPServerNode = NULL;
    char tmpbuf[32] = {0};
    char timezone[16] = {0};
	char  timezoneflag[8] = {0};
	char  timezonenum[8] = {0};
	char  period_unit[16] = {0};

    //printf("xml_buf = \n%s\n", xml_buf);

    root = mxmlLoadString(NULL, xml_buf, NULL);
    if (NULL == root)
    {
        printf("mxmlLoadString error\n");
    }

    NTPServerNode = xml_parse_Get_Group(root, "TimeNTP", NULL, NULL);
    if (NULL != NTPServerNode)
    {
        xml_parse_GetString(NTPServerNode, "enableDefault", tmpbuf);
        if (!strcmp(tmpbuf, "true"))
        {
            ntp_cfg->server_index = 0;
        }
        else
        {
            ntp_cfg->server_index = 1;
        }
        //printf("enableDefault:%s server_index:%d\n", tmpbuf, ntp_cfg->server_index);
        xml_parse_GetString(NTPServerNode, "server", ntp_cfg->ntp_host);
        //printf("ntp_host = %s\n", ntp_cfg->ntp_host);
        xml_parse_Get_Integer(NTPServerNode, "port", (int *)&ntp_cfg->ntp_port);
        //printf("portno = %d\n", ntp_cfg->ntp_port);
        xml_parse_Get_Integer(NTPServerNode, "autoEnable", (int *)&ntp_cfg->autontp_enable);
        xml_parse_Get_Integer(NTPServerNode, "syncPeriod", (int *)&ntp_cfg->ajust_period);
        //printf("interval = %d\n", ntp_cfg->ajust_period);
        xml_parse_GetString(NTPServerNode, "timeZone", timezone);
        sscanf(timezone, "GMT%[+-]%[^:]", timezoneflag, timezonenum);//省略分钟，只匹配时钟
        if (timezoneflag[0] == '+')
        {
            ntp_cfg->time_zone = atoi(timezonenum);	
        }
        else
        {
            ntp_cfg->time_zone =  -atoi(timezonenum);	
        }
        //printf("ParseXmlSystemNtpServer timezone:%s timezoneflag:%s timezonenum:%s time_zone:%d\n", timezone, timezoneflag, timezonenum, 
        //ntp_cfg->time_zone);
        
        xml_parse_GetString(NTPServerNode, "syncUnit", period_unit);
        if (!strcmp(period_unit, "hour"))
        {
            ntp_cfg->sync_unit = 1;
        }
        else if (!strcmp(period_unit, "day"))
        {
            ntp_cfg->sync_unit = 2;
        }
        else if (!strcmp(period_unit, "week"))
        {
            ntp_cfg->sync_unit = 3;
        }
        else 
        {
            ntp_cfg->sync_unit = 4;
        }
    }
    else
    {
        printf("NTPServerNode is NULL! \n");
    }

    if (NULL != root)
    {
        mxmlRelease(root); 
    }

    return 0;
}

/******************************************************************************
 * Description：解析UPnpPortListxml文件
 * Input xml_buf：需要进行解析的xml数据
 * Output response：解析xml数据帧，获取到的信息
 * Return：0-成功 <0-错误代码
 * *****************************************************************************/
int ParseXmlUPnPPortList(char * xml_buf, NETWORK_UPNP_S * response)
{
	int index = 0;
	char strbuf[64] = {0};
	mxml_node_t * root = NULL;
	mxml_node_t * UPnPPort = NULL, *port = NULL;

	root = mxmlLoadString(NULL, xml_buf, NULL);
	if (NULL == root)
	{
		printf("mxmlLoadString error\n");
		return -1;
	}

	if(NULL == strstr(xml_buf, "UPnPPortList")) //根节点名称
	{
		return -1;
	}

	index = 0;
	port = NULL;
	UPnPPort = xml_parse_Get_Group(root, "UPnPPortList", NULL, NULL);
	{
		for(port = mxmlFindElement(UPnPPort, UPnPPort, "port", NULL, NULL, MXML_DESCEND); 
				port != NULL; 
				port = mxmlFindElement(port, UPnPPort, "port", NULL, NULL, MXML_DESCEND))

		{
			if(index >= MAX_PAT)
			{
				break;
			}

			xml_parse_GetString(port, "name", (char*)(response->pat_info[index].server_name));
			memset(strbuf, 0, strlen(strbuf));
			xml_parse_GetString(port, "protocol", strbuf);
			if(0 == strncmp(strbuf, "TCP", strlen(strbuf)))
			{
				response->pat_info[index].protocol = 1;
			}
			else //UDP
			{
				response->pat_info[index].protocol = 0;
			}
			xml_parse_Get_Integer(port, "DVRPort", (int*)&(response->pat_info[index].dvr_port)); 
			xml_parse_Get_Integer(port, "routerPort", (int*)&(response->pat_info[index].rount_port)); 
			memset(strbuf, 0, strlen(strbuf));
			xml_parse_GetString(port, "status", strbuf);
			if(0 == strncmp(strbuf, "active", strlen(strbuf)))
			{
				response->pat_info[index].status = 1;
			}
			else //inactive
			{
				response->pat_info[index].status = 0;
			}
			xml_parse_Get_Integer(port, "id", &index); //id 子节点的id 
		}
		response->pat_count = index; //子节点的总数
	}

	if (NULL != root)
	{
		mxmlRelease(root); 
	}

	return 0;
}



/****************************************************
 * **************** DESCRIPTION:CREATE_XML
 * **************************************************/
/*
 * Description:change
 * */
int GenXmlUPnP(char * xml_buf, int size, NETWORK_UPNP_S * upnp_param)
{
    mxml_node_t * root = NULL;
    mxml_node_t * UPnP = NULL;

    root = mxmlNewXML("1.0");
	UPnP = mxmlNewElement(root, "UPnP");
	mxmlElementSetAttr(UPnP, "xmlns", "http://www.isapi.org/ver20/XMLSchema");
	mxmlElementSetAttr(UPnP, "version", "1.0");
	{
		add_node_str(UPnP, "enabled", (upnp_param->upnp_en) ? "true" : "false");

		if (upnp_param->status == ISAPI_UPNP_DISCONNECT)
		{
			add_node_str(UPnP, "status", "disconnect");
		}
		else if (upnp_param->status == ISAPI_UPNP_SEARCHING)
		{
			add_node_str(UPnP, "status", "searching");
		}
		else if (upnp_param->status == ISAPI_UPNP_SCAN_SUCC)
		{
			add_node_str(UPnP, "status", "scansucc");
		}
		else if (upnp_param->status == ISAPI_UPNP_SCAN_FAIL)
		{
			add_node_str(UPnP, "status", "scanfail");
		}
		else if (upnp_param->status == ISAPI_UPNP_PORT_CONFLICT)
		{
			add_node_str(UPnP, "status", "portconflict");
		}
        else
        {
            add_node_str(UPnP, "status", "disconnect");
        }

        add_node_str(UPnP, "LANAddress", upnp_param->rout_info.rout_ip);

        add_node_str(UPnP, "WANAddress", upnp_param->rout_info.wan_ip);
    }

    mxmlSaveString(root, xml_buf, size, 0);
    mxmlRelease(root);
    return 0;
}


/*
 * PUT DDNS 的xml数据段
 * change : 修改过
 * */
int GenXmlDDNS(char * xml_buf, int size, NETWORK_DDNS_S * ddns_param)
{
    //char ip_addr[128] = {0};
    mxml_node_t * root = NULL;
    mxml_node_t * DDNS = NULL;
    //mxml_node_t * loginStatus = NULL;

    root = mxmlNewXML("1.0");

    DDNS = add_element(root, "DDNS", 0);
    {
        add_node_num(DDNS, "id", (int)(ddns_param->index+1));
        add_node_str(DDNS, "server", (char*)ddns_param->server); 
        add_node_str(DDNS, "defaultRegist", ddns_param->domain_default_flag?"true":"false");
        add_node_str(DDNS, "domainName", (char*)ddns_param->set_dn); 
        add_node_str(DDNS, "user", (char *)ddns_param->user); 
        add_node_str(DDNS, "password", (char*)ddns_param->pwd); 
        add_node_str(DDNS, "autoLogin", ddns_param->auto_connect?"true":"false");
        add_node_str(DDNS, "login", (char*)"false"); 
    }

    mxmlSaveString(root, xml_buf, size, 0);
    mxmlRelease(root);
    return 0;
}


int GenXmlSystemNtpServer(char * xml_buf, int size, SYSTEM_NTP_CFG_S * ntp_cfg)
{
    mxml_node_t *root = NULL;
    //mxml_node_t **NTPServerNode = NULL;
    mxml_node_t *NTPServerNode = NULL;
    char timezone[16] = {0};
    char period_uint[4][16] = {{"hour"}, {"day"}, {"week"}, {"month"}};

    root = mxmlNewXML("1.0");
    NTPServerNode = add_element(root, "TimeNTP", 1);
    {
        //printf("GenXmlSystemNtpServer enableDefault:%d\n", ntp_cfg->server_index);
        add_node_str(NTPServerNode, "enableDefault", ntp_cfg->server_index?"false":"true");
        add_node_str(NTPServerNode, "server", ntp_cfg->ntp_host);
        add_node_num(NTPServerNode, "port", ntp_cfg->ntp_port);
        add_node_num(NTPServerNode, "autoEnable", ntp_cfg->autontp_enable);
        if (ntp_cfg->time_zone >= 0)
        {
            snprintf(timezone, 15, "GMT+%02d:00:00", ntp_cfg->time_zone);
        }
        else
        {
            snprintf(timezone, 15, "GMT-%02d:00:00", abs(ntp_cfg->time_zone));
        }
        add_node_str(NTPServerNode, "timeZone", timezone);
        add_node_num(NTPServerNode, "syncPeriod", ntp_cfg->ajust_period);
        add_node_str(NTPServerNode, "syncUnit", period_uint[ntp_cfg->sync_unit - 1]);
    }

    mxmlSaveString(root, xml_buf, size, 0);
    mxmlRelease(root);
    return 0;
}


int GenXmlDeviceInfo(char * xml_buf, SYSTEM_DEVICE_INFO_S dev_info)
{
    mxml_node_t * root = NULL;
    mxml_node_t * DeviceInfoNode = NULL;

    root = mxmlNewXML("1.0");
    DeviceInfoNode = add_element(root, "DeviceInfo", 1);
    {
        add_node_str(DeviceInfoNode, "deviceName", dev_info.dev_name);
        add_node_str(DeviceInfoNode, "deviceID", dev_info.dev_id);
        add_node_str(DeviceInfoNode, "model", dev_info.dev_type);
        add_node_str(DeviceInfoNode, "serialNumber", dev_info.dev_no);
        add_node_str(DeviceInfoNode, "firmwareVersion", dev_info.main_ver);
        add_node_str(DeviceInfoNode, "firmwareReleasedDate", dev_info.main_date);
        add_node_str(DeviceInfoNode, "encoderVersion", dev_info.venc_ver);
        add_node_str(DeviceInfoNode, "encoderReleasedDate", dev_info.venc_date);
		 add_node_str(DeviceInfoNode, "deviceType", "NVR");
        add_node_num(DeviceInfoNode, "ChannelNum", dev_info.ch_num);
        add_node_num(DeviceInfoNode, "DiskNum", dev_info.disk_num);
        add_node_num(DeviceInfoNode, "AlarmInNum", dev_info.sensor_in);
        add_node_num(DeviceInfoNode, "AlarmOutNum", dev_info.sensor_out);
        add_node_num(DeviceInfoNode, "telecontrolID", dev_info.telecontrol_id);
    }

    mxmlSaveString(root, xml_buf, XML_BUF_SIZE_4K, 0);
    mxmlRelease(root);
    return 0;
}

int GenXmlMailing(char * xml_buf, int size, NETWORK_SMTP_S * smtp_param)
{
    int i = 0;
    char *recvaddrbuf;
    mxml_node_t * root = NULL;
    mxml_node_t * mailingListNode = NULL, *mailingNode = NULL;
	//mxml_node_t *mailingNode = NULL;
    mxml_node_t * recvAddrList = NULL, *recvAddr = NULL;

    root = mxmlNewXML("1.0");

    //mailingListNode = add_element(root, "mailinglist", 1);
    mailingListNode = add_element(root, "mailinglist", 0);
    {
        //mailingNode = add_element(mailingListNode, "mailing", 1);
        mailingNode = add_element(mailingListNode, "mailing", 0);
        {
            add_node_num(mailingNode, "id", 1);
            add_node_str(mailingNode, "host", smtp_param->host);
            add_node_num(mailingNode, "port", smtp_param->port);
            add_node_str(mailingNode, "user", smtp_param->user);
            add_node_str(mailingNode, "password", smtp_param->pwd);
            add_node_str(mailingNode, "sendAddr", smtp_param->send_addr);
            recvAddrList = add_element(mailingNode, "recvAddrList", 0);
            {
                recvaddrbuf = strtok(smtp_param->recv_addr, ";");
                while(recvaddrbuf)
                {
                    i++;
                    recvAddr = add_element(recvAddrList, "recvAddr", 0);
                    add_node_num(recvAddr, "id", i);
                    add_node_str(recvAddr, "email", recvaddrbuf);
                    recvaddrbuf = strtok(NULL, ";");
                }                
            }
            add_node_num(mailingNode, "sendPeriod", smtp_param->send_period);
            add_node_str(mailingNode, "snapshotEnable", smtp_param->snap_enable?"true":"false");
            add_node_str(mailingNode, "SSLEnable", smtp_param->ssl_enable?"true":"false");
            add_node_str(mailingNode, "STARTEnable", smtp_param->starttls_enable?"true":"false");
        }
    }

    mxmlSaveString(root, xml_buf, size, 0);
    mxmlRelease(root);
    return 0;
}

/*
 * 函数功能描述：将本地的网路配置信息封装到xml文件中
 * 输出参数：已经封装好的数据
 * 输入参数：xml数据帧的最大长度
 * 输入参数：本地的网络配置信息
 * 输入参数：子命令
 * 函数返回值：
 * Change:修改
 * */
int GenXmlNetworkInterfacesChannel(char * xml_buf, int size, NETWORK_DEVICE_INFO_S * net_param, int iscapabilities)
{
    mxml_node_t * root = NULL;
    mxml_node_t * NetworkInterfaceNode = NULL;
    mxml_node_t * IPAddressNode = NULL, *LinkSpeed = NULL, *LinkDup = NULL;
    mxml_node_t * DefaultGatewayNode = NULL, *PrimaryDNSNode = NULL, *SecondaryDNSNode = NULL;
    mxml_node_t *LinkNode = NULL, *MTUNode = NULL;
    char ip_addr[128] = {0}, ip_mask[128] = {0}, ip_gateway[128] = {0};
    char dns1[128] = {0}, dns2[128] = {0};
    char mac[128] = {0};
    char autoNego[16] = "false";
    char nodebuf[256] = {0}, linspeeed_10_string[16] = {0}, linspeeed_100_string[16] = {0}, linspeeed_1000_string[16] = {0}, lindup_half_string[16] = {0}, lindup_full_string[16] = {0};
    int  i = 0;

    char lipver_c[][16] =
    {
        "single",
        "dual"
    };
    char link_dup[][16] = 
    {
        "half",
		"full"
	};

	root = mxmlNewXML("1.0");

	NetworkInterfaceNode = add_element(root, "NetworkInterface", 0);
	{
		add_node_str(NetworkInterfaceNode, "workMode", "active-backup"); //工作模式
		add_node_num(NetworkInterfaceNode, "id", net_param->id);

		IPAddressNode = add_element(NetworkInterfaceNode, "IPAddress", 0);
		{
			add_node_str(IPAddressNode, "ipVersion", lipver_c[net_param->ip.ipver]);
			add_node_str(IPAddressNode, "addressingType", net_param->ip.dhcp_enable?"dynamic":"static");

			uint_ip_to_string(ip_addr, 127, net_param->ip.ipaddr);
			add_node_str(IPAddressNode, "ipAddress", ip_addr);

			uint_ip_to_string(ip_mask, 127, net_param->ip.netmask);
			add_node_str(IPAddressNode, "subnetMask", ip_mask);
			DefaultGatewayNode = add_element(IPAddressNode, "DefaultGateway", 0); //网关
			{
				uint_ip_to_string(ip_gateway, 127, net_param->ip.gateway);
				add_node_str(DefaultGatewayNode, "ipAddress", ip_gateway);
			}

			PrimaryDNSNode = add_element(IPAddressNode, "PrimaryDNS", 0);
			{
				uint_ip_to_string(dns1, 127, net_param->ip.dns1);
				add_node_str(PrimaryDNSNode, "ipAddress", dns1);
			}
			SecondaryDNSNode = add_element(IPAddressNode, "SecondaryDNS", 0);
			{
				uint_ip_to_string(dns2, 127, net_param->ip.dns2);
				add_node_str(SecondaryDNSNode, "ipAddress", dns2);
			}
		}

		LinkNode = add_element(NetworkInterfaceNode, "Link", 0);
		{
			snprintf(mac, 127, "%02x:%02x:%02x:%02x:%02x:%02x",
					net_param->link.mac[0], net_param->link.mac[1], net_param->link.mac[2], net_param->link.mac[3], net_param->link.mac[4], net_param->link.mac[5]);
			add_node_str(LinkNode, "MACAddress", mac);
		
			if (!iscapabilities)
			{
				if (0 == net_param->link.speed)
				{
					add_node_str(LinkNode, "autoNegotiation", "true");
				}
				else
				{
					add_node_str(LinkNode, "autoNegotiation", "false");
				}
			}
			else
			{
				for(i=0;i<net_param->link.phy_mode.iterm_num;i++)
				{
					if (PT_AUTOMODE == net_param->link.phy_mode.list_iterm[i])
					{
						memset(autoNego, 0, sizeof(autoNego));
						strcpy(autoNego, "true");
					}
					else if (PT_HALFMODE_10M == net_param->link.phy_mode.list_iterm[i] || PT_FULLMODE_10M == net_param->link.phy_mode.list_iterm[i])
					{
						strcpy(linspeeed_10_string, "10");
					}
					else if (PT_HALFMODE_100M == net_param->link.phy_mode.list_iterm[i] || PT_FULLMODE_100M == net_param->link.phy_mode.list_iterm[i])
					{
						strcpy(linspeeed_100_string, "100");
					}
					else
					{
						strcpy(linspeeed_1000_string, "1000");
					}
				}

				if (0 != strlen(linspeeed_10_string))
				{
					if (0 != strlen(linspeeed_100_string) || 0 != strlen(linspeeed_100_string))
					{
						sprintf(nodebuf, "%s%s,", nodebuf, linspeeed_10_string);
					}
					else
					{
						sprintf(nodebuf, "%s%s", nodebuf, linspeeed_10_string);
					}
				}
				if (0 != strlen(linspeeed_100_string))
				{
					if (0 != strlen(linspeeed_1000_string))
					{
						sprintf(nodebuf, "%s%s,", nodebuf, linspeeed_100_string);
						sprintf(nodebuf, "%s%s", nodebuf, linspeeed_1000_string);
					}
					else
					{
						sprintf(nodebuf, "%s%s", nodebuf, linspeeed_100_string);
					}
				}

				add_node_str(LinkNode, "autoNegotiation", autoNego);
				add_node_attr(LinkSpeed, "opt", nodebuf);

				memset(nodebuf, 0, sizeof(nodebuf));
				for(i=0;i<net_param->link.phy_mode.iterm_num;i++)
				{
					if (PT_HALFMODE_10M == net_param->link.phy_mode.list_iterm[i] || PT_HALFMODE_100M == net_param->link.phy_mode.list_iterm[i] || PT_FULLMODE_1000M == net_param->link.phy_mode.list_iterm[i])
					{
						strcpy(lindup_half_string, "half");
					}
					else if (PT_FULLMODE_10M == net_param->link.phy_mode.list_iterm[i] || PT_FULLMODE_100M == net_param->link.phy_mode.list_iterm[i])
					{
						strcpy(lindup_full_string, "full");
					}
				}

				if (0 != strlen(lindup_half_string))
				{
					if (0 != strlen(lindup_full_string))
					{
						sprintf(nodebuf, "%s%s,", nodebuf, lindup_half_string);
						sprintf(nodebuf, "%s%s", nodebuf, lindup_full_string);
					}
					else
					{
						sprintf(nodebuf, "%s%s", nodebuf, lindup_half_string);
					}
				}
				add_node_attr(LinkDup, "opt", nodebuf);
			}
			LinkSpeed = add_node_num(LinkNode, "speed", net_param->link.speed);
			LinkDup = add_node_str(LinkNode, "duplex",link_dup[net_param->link.duplex]);

			MTUNode =  add_node_num(LinkNode, "MTU", 1500);
			if(MTUNode == NULL)
			{
				return -1;
			}
		}
	}

	mxmlSaveString(root, xml_buf, size, 0);
	mxmlRelease(root);

	return 0;
}



