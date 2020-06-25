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

#ifndef _ISAPI_NETWORKADAPTER_H_
#define _ISAPI_NETWORKADAPTER_H_

#include "isapi_adapter.h"
#include "sys_net.h"
#include "sys_netapi.h"
#include "config_usr.h"
#include "config.h"

typedef enum
{
    SINGLE  = 0,
    DUAL    = 1
} LIPVER_E;

typedef struct
{
    LIPVER_E ipver;
    int dhcp_enable;     //dhcp使能
    int ipaddr;
    int netmask;
    int gateway;
    int dns1;
    int dns2;
    int ipv6[4];
    int ipv6_mask[4];
} IPADDR_S, *PIPADDR_S;

typedef struct
{
    int upnp;
    int zeroconf;
} DISCOVERY_S, *PDISCOVERY_S;

typedef enum
{
    half = 0,
    full = 1
} DUPLEX_E;

typedef struct
{
    int iterm_num;   //支持项总数
    int list_iterm[PT_MAX_LIST];      //列表数 ,// 0-自适应, 1-10M半双工，2-10全双工，3-100M半双工， 4-100M全双工，5-1000M全双工
} PHY_MODE_LIST_S, *PPHY_MODE_LIST_S;


typedef struct
{
    PHY_MODE_LIST_S phy_mode; // 0-自适应, 1-10M半双工，2-10全双工，3-100M半双工， 4-100M全双工，5-1G全双工
    char mac[16];
    int  nego;
    int speed;
    DUPLEX_E duplex;
    int mtu;
    int mtu_min;
    int mtu_max;
} LINK_S, *PLINK_S;

typedef struct
{
    int id;
    IPADDR_S ip;
    DISCOVERY_S discovery;
    LINK_S link;
}NETWORK_DEVICE_INFO_S, *PNETWORK_DEVICE_INFO_S;

typedef struct
{
    NETWORK_DEVICE_INFO_S neti_list[2];
} NETWORK_DEVICE_INFOLIST_S, *PNETWORK_DEVICE_INFOLIST_S;

/********************************************************/

typedef struct
{
    char userName[MAX_STRING];
    char pwd[MAX_STRING];
    int  status;
    int  autologin;
} NETWORK_PPPOE_S, *PNETWORK_PPPOE_S;

typedef struct
{
    NETWORK_PPPOE_S pppoe_list[1];
} NETWORK_PPPOE_LIST_S, *PNETWORK_PPPOE_LIST_S;

/*DDNSList*******************************************************/
#if 0
typedef enum
{
    HANBANG = 0,
    ORAY,
    DYNDNS,
    NO_IP,
    MEIBU,
    FREEDNS
} PROVIDER_E;

typedef struct
{
    addrtype_e addr_type;
    char hname[32];
} DSERVER_ADDR_S, *PDSERVER_ADDR_S;

typedef struct
{
    int id;
    int enable;
    PROVIDER_E provider;
    DSERVER_ADDR_S serv_addr;
    int port;
    char domainame[32];
    char usr[32];
} NETWORK_DDNS_S, *PNETWORK_DDNS_S;

typedef struct
{
    NETWORK_DDNS_S ddns_list[1];
} NETWORK_DDNS_LIST_S, *PNETWORK_DDNS_LIST_S;
#else
typedef enum
{
    ISAPI_DDNS_HANBANG = 0,
    ISAPI_DDNS_ORAY,
    ISAPI_DDNS_DYNDNS,
    ISAPI_DDNS_NO_IP,
    ISAPI_DDNS_MEIBU,
    ISAPI_DDNS_FREEDNS
} DDNS_SERVER_E;

typedef struct
{
    sint32  index;                      //ddns索引
    uint8   server[MAX_STRING];         // 当前服务器地址
    uint8   user[MAX_STRING];           // 用户名
    uint8   pwd[MAX_STRING];            // 密码
    uint32  ip_addr;                    // 服务器返回的IP地址    
    uint8   dn[MAX_DNS * MAX_STRING];   // 解析的地址 可支持返回最多4个DNS域名
    PT_AUTOENABLE_E auto_connect;       // 是否为自动连接
    PT_SUCCESS_E    status;             // 是否解析成功
    PT_CONNECT_E    command;            // 连接动作
    uint8   set_dn[PT_MAX_LINE];        // 设置域名(有些域名服务器需要设定域名，或者多个域名时指定一个时用)
    uint32  gui_get_flag;               //值为1，表示直接将从状态机获取的多个解析地址放在dn_set里，传给GUI    
    uint8   hb_defuser[MAX_STRING];           // 用户名
    uint16  domain_default_flag;        // 域名默认非默认标志位，0为默认，1为非默认
    uint16	iterm_num;
    uint8   list_iterm[12][MAX_STRING]; //支持服务器的个数以及服务器列表，当前服务器索引
}NETWORK_DDNS_S, *PNETWORK_DDNS_S;
#endif

/*mailingList*******************************************************/

typedef struct
{
    int id;
    char   host[PT_MAX_SMTP_HOST];     // 发送邮件的SMTP服务器，例如：126信箱的是smtp.126.com
    int    port;                        // 服务器端口，发送邮件(SMTP)端口：默认值25
    char   user[MAX_STRING];            // 邮件用户名
    char   pwd[MAX_STRING];             // 邮件用户密码
    char   send_addr[PT_MAX_SMTP_HOST];  // FROM：邮件地址
    char   recv_addr[PT_MAX_SMTP_ADDR];  // TO：邮件地址，最多8个邮箱地址
    int    send_period;                 // 上传周期,单位(分钟,最大值120)
    int    snap_enable;              // 是否抓拍上传
    int    ssl_enable;              // ssl加密使能，0-关闭 1-开启
    int    starttls_enable;         // 0-关闭 1-开启
} NETWORK_SMTP_S, *PNETWORK_SMTP_S;

typedef struct
{
    NETWORK_SMTP_S mail_list[1];
} NETWORK_SMTPLIST_S, *PNETWORK_SMTPLIST_S;

/*UPnP*******************************************************/

typedef enum internalPort
{
    http = 1,
    admin = 2,
    rtsp = 3,
    https = 4

} interp_e;

#if 0
char interp_c[][16] =
{
    "http",
    "admin",
    "rtsp",
    "https"
};
#endif

typedef enum nipVersion
{
    v4 = 1,
    v6 = 2
} nipver_e;

typedef struct
{
    char rout_ip[20];            //路由器ip
    char wan_ip[20];             //wan端口地址
} NETWORK_UPNP_SEARCH;

//端口地址信息
typedef struct
{
    char rout_ip[20];                   //路由器ip
    char server_name[MAX_STRING];       //转换端口名称
    uint16 protocol;        //协议
    uint16 dvr_port;        //DVR端口
    uint16 rount_port;      //路由器端口
    sint16  status;         //状态
    uint32 pat_en;          //标志该项是否被选中:1:选中；0:未选中
} NETWORK_PAT_UPNP_S;

//UPNP设置
typedef struct
{
    uint32  upnp_en;                     // UPNP 使能
    uint16  pat_count;                   //转换端口个数
    uint16  status;                    //路由器个数
    NETWORK_PAT_UPNP_S  pat_info[MAX_PAT];   //转换端口信息
    NETWORK_UPNP_SEARCH rout_info; //所连接的路由器的信息
} NETWORK_UPNP_S, *PNETWORK_UPNP_S;


int network_get_device_info(NETWORK_DEVICE_INFO_S * net_param);
int network_set_device_info(NETWORK_DEVICE_INFO_S * net_param, WEB_CMD_INFO_S *webinfo);
int network_get_pppoe_info(NETWORK_PPPOE_S * pppoe_param);
int network_set_pppoe_info(NETWORK_PPPOE_S * pppoe_param, WEB_CMD_INFO_S *webinfo);
int network_get_smtp_info(NETWORK_SMTP_S * smtp_param);
int network_set_smtp_info(NETWORK_SMTP_S * smtp_param, WEB_CMD_INFO_S *webinfo);
int network_email_test(NETWORK_SMTP_S * smtp_param);
int network_get_ddns_info(NETWORK_DDNS_S * ddns_param);
int network_set_ddns_info(NETWORK_DDNS_S * ddns_param, WEB_CMD_INFO_S *webinfo);
int network_get_upnp_info(NETWORK_UPNP_S * upnp_param);
int network_set_upnp_info(NETWORK_UPNP_S * upnp_param, WEB_CMD_INFO_S *webinfo);

#endif
