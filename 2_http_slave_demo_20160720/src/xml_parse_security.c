/****************************************************************
 * FileName:xml_parse_security.c
 * Author:merlin
 * Version:v1
 * Time:20160613
 * Description:create and parse xml package
 * *************************************************************/
#define XML_BUF_SIZE_4K    4 * 1024

#include "common.h"
#include "xml_base.h"
#include "xml_parse_security.h"

int GenXmlAdminAccesses(char * xml_buf, SECURITY_PORTINFO_S *portinfo)
{
    mxml_node_t * root = NULL;
    mxml_node_t * AdminAccessProtocolListNode = NULL;
    mxml_node_t * AdminAccessProtocolNode = NULL;

    root = mxmlNewXML("1.0");
    AdminAccessProtocolListNode = add_element(root, "AdminAccessProtocolList", 1);
    {
        AdminAccessProtocolNode = add_element(AdminAccessProtocolListNode, "AdminAccessProtocol", 0);
        {
            add_node_num(AdminAccessProtocolNode, "id", 1);
            add_node_str(AdminAccessProtocolNode, "protocol", "HTTP");
            add_node_num(AdminAccessProtocolNode, "portNo", portinfo->httpport);
        }
        AdminAccessProtocolNode = add_element(AdminAccessProtocolListNode, "AdminAccessProtocol", 0);
        {
            add_node_num(AdminAccessProtocolNode, "id", 2);
            add_node_str(AdminAccessProtocolNode, "protocol", "LISTEN");
            add_node_num(AdminAccessProtocolNode, "portNo", portinfo->listenport);
        }
        AdminAccessProtocolNode = add_element(AdminAccessProtocolListNode, "AdminAccessProtocol", 0);
        {
            add_node_num(AdminAccessProtocolNode, "id", 3);
            add_node_str(AdminAccessProtocolNode, "protocol", "UPGRADE");
            add_node_num(AdminAccessProtocolNode, "portNo", portinfo->upgradeport);
        }
        AdminAccessProtocolNode = add_element(AdminAccessProtocolListNode, "AdminAccessProtocol", 0);
        {
            add_node_num(AdminAccessProtocolNode, "id", 4);
            add_node_str(AdminAccessProtocolNode, "protocol", "RTSP");
            add_node_num(AdminAccessProtocolNode, "portNo", portinfo->rtspport);
        }
        AdminAccessProtocolNode = add_element(AdminAccessProtocolListNode, "AdminAccessProtocol", 0);
        {
            add_node_num(AdminAccessProtocolNode, "id", 5);
            add_node_str(AdminAccessProtocolNode, "protocol", "RTMP");
            add_node_num(AdminAccessProtocolNode, "portNo", portinfo->rtmpport);
        }
    }
    mxmlSaveString(root, xml_buf, XML_BUF_SIZE_4K, 0);
    mxmlRelease(root);
    return 0;
}


int ParseXmlAdminAccesses(char * xml_buf, SECURITY_PORTINFO_S *portinfo)
{    
    char protocol_name[16] = {0};
    int i = 0, port = 0;
    mxml_node_t * root = NULL;
    mxml_node_t * AdminAccessProtocolListNode = NULL;
    mxml_node_t * AdminAccessProtocolNode = NULL;
    //int http_id = 0, rtsp_id = 0, https_id = 0, sdk_id = 0;
    //int rtsp_port = 0, https_port = 0, sdk_port = 0;
    //char http_prot[16] = {0}, rtsp_en[16] = {0}, rtsp_prot[16] = {0}, https_prot[16] = {0},sdk_prot[16] = {0};

    root = mxmlLoadString(NULL, xml_buf, NULL);
    if (NULL == root)
    {
        printf("mxmlLoadString error\n");
    }

    AdminAccessProtocolListNode = xml_parse_Get_Group(root, "AdminAccessProtocolList", NULL, NULL);
    if (NULL != AdminAccessProtocolListNode)
    {
        for (i = 0; i < 8; i++)
        {
            AdminAccessProtocolNode= mxmlFindElementIns((0 == i)?AdminAccessProtocolListNode:AdminAccessProtocolNode, AdminAccessProtocolListNode, 
                                    "AdminAccessProtocol", NULL, NULL, MXML_DESCEND);
            if(AdminAccessProtocolNode != NULL)
            {
                xml_parse_GetString(AdminAccessProtocolNode, "protocol", protocol_name);
                xml_parse_Get_Integer(AdminAccessProtocolNode, "portNo", &port);

                if (!strcmp(protocol_name, "HTTP"))
                {
                    portinfo->httpport = port;
                }
                else if (!strcmp(protocol_name, "LISTEN"))
                {
                    portinfo->listenport = port;
                }
                else if (!strcmp(protocol_name, "RTMP"))
                {
                    portinfo->rtmpport = port;
                }
                else 
                {
                    continue;
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
		printf("AdminAccessProtocolListNode is NULL! \n");
	}

	if (NULL != root)
	{
		mxmlRelease(root); 
	}

	return 0;
}

int ParseXmlSecurityUsers(char * xml_buf, SECURITY_USER_S * user, int type)//type:0-put,1-post
{
    mxml_node_t * root = NULL;
    mxml_node_t * UserNode = NULL;
    mxml_node_t * bondIpListNode = NULL, *attributeNode = NULL;
    mxml_node_t * bondIpNode = NULL;
    int user_id = 0, bond_id = 0;
    char pwdbuf[32] = {0};
    char ip_addr[128] = {0}, ip_v6[128] = {0}, userlev[16] = {0}, inhert[16] = {0};

    root = mxmlLoadString(NULL, xml_buf, NULL);
    if (NULL == root)
    {
        printf("mxmlLoadString error\n");
    }

    UserNode = xml_parse_Get_Group(root, "User", NULL, NULL);
    if (NULL != UserNode)
    {
        xml_parse_Get_Integer(UserNode, "id", &user_id);
        xml_parse_GetString(UserNode, "userName", user->user_name);
        if(xml_parse_GetString(UserNode, "password", user->user_pwd))
        {
            user->user_pwdflag = 1;
        }
        if(xml_parse_GetString(UserNode, "pwdempty", pwdbuf))
        {
            if (!strcmp(pwdbuf, "true"))
            {
                user->user_pwdflag = 1;
                strcpy(user->user_pwd, "");
            }
        }        
        
        //printf("ParseXmlSecurityUsers pwd:%s  user_pwdflag:%d\n", user->user_pwd, user->user_pwdflag);
        bondIpListNode = xml_parse_Get_Group(UserNode, "bondIpList", NULL, NULL);
        {
            bondIpNode = xml_parse_Get_Group(bondIpListNode, "bondIp", NULL, NULL);
            {
                xml_parse_Get_Integer(bondIpNode, "id", &bond_id);
                xml_parse_GetString(bondIpNode, "ipAddress", ip_addr);
                xml_parse_GetString(bondIpNode, "ipv6Address", ip_v6);
            }
        }
        xml_parse_GetString(bondIpNode, "userLevel", userlev);
        attributeNode = xml_parse_Get_Group(UserNode, "attribute", NULL, NULL); //MWARNING
		if(attributeNode != NULL)
        {
            xml_parse_GetString(bondIpNode, "inherent", inhert);
        }
    }

    if (NULL != root)
    {
        mxmlRelease(root); 
    }

    return 0;
    
}

