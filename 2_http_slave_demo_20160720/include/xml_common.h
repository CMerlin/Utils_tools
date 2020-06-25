#ifndef _XML_INFO_H_
#define _XML_INFO_H_

#include "common.h"

/*宏定义*/
#define PT_SUCCESS          1
#define PT_FAILED           0

#define PTZ_CMD_START       32
#define MAX_PTNUM           64          //16//现支持的平台数
#define MAX_REG             8
#define MAX_MASK            4

#define MAX_OSD_NUM         6           //最多6行OSD
#define MAX_MASK            4           //最多4个屏蔽区域
#define MAX_MOTION          4           //最多4个移动侦测区域
#define MAX_DEV_DISK        (16)
#define MAX_DEV_USB         (12)
#define MAX_DEV_ESATA       (12)
#define MAX_DEV_CDDVD       (12)
#define PT_MAX_POE_NUM      (32)

#define MAX_PRESET          128
#define PT_MAX_STRING_EXT      64
#define MAX_STRING          32
#define MAX_DNS             4
#define MAX_AM              64
#define MAX_AMOUT           64
#define MAX_CH              64
#define MAX_PERIOD          4           //最多时间段
#define PT_MAX_ACCOUNT      16          //最多用户数
#define PT_MAX_PTZ          100
#define PT_MAX_BK           16          //最大备份数
#define PT_GRP_ACCOUNT      16
#define PT_MAX_MATRIX       64
#define PT_MAX_SMTP_HOST    128
#define PT_MAX_SMTP_ADDR    256
#define PT_MAX_LINE         256
#define PT_MAX_RESNUM       16          //最大清晰度个数     0-QCIF, 1-QVGA, 2-CIF, 3-DCIF, 4-HD1, 5-VGA, 6-FD1, 7-SD, 8-HD, 
#define MAX_AM_COUNT        16
#define MAX_VER_LEN         (64)
#define MAX_PAT			        15          //UPNP最大转换端口个数
#define PT_MAX_YDTDOMAIN    (128)       // 一点通域名地址长度 
#define PT_CLIENT_DL_ADDR   (128)       // 手机客户端下载地址长度 
#define MAX_IP_DEV_NUM 6
#define MAX_DNS_NUM      2
#define MAX_IPADDR_STR_LEN 128
#define MAX_DOMAINNAME_STR_LEN 256


#define NETMGR_MAX_DEVNUM       4 

#define PT_MAX_ADDR_STR        (128)
#define PT_GRAPH_REC_CH_NUM    (8)
#define PT_MAX_COMP_NUM        (36)     //最大模块数
#define PT_MAX_USER		  	   (16)		// 最大用户数
#define PT_MAX_REC_CH_NUM      (32)
#define PT_REC_DATA_GRAPH_PAGE_NUM (8)
#define PT_MAX_PB_NAME            (2)
#define PT_MAX_RAID_DEV_NUM     (10)
#define PT_MAX_DEV_NUM          (16)
#define PT_MAX_DEV_PATH         (32)
#define PT_GRAPH_DATA_MASK_NUM  (360)

#define PT_MAX_PSK_LEN          (65)
#define PT_MAX_WIFIAP_NUM       (10)
#define PT_MAX_SSID_LEN         (33)
#define PT_MAX_DISPLAY_TYPE_NUM   (4)

#define PT_MAX_INTEL_BLOCK_NUM   (50) //智能搜索最大支持区块 (n) * 8,当前为22 * 18 = 396

#define MAX_FILENAME_LENTH (256)
#define MAX_LOGO_NUM (10)           //主机当前最大logo种类

#define IPC_SEARCH_MAX_NUM      256     /* 支持最大搜索设备数 */
#define PT_MAX_NVD              16      /* 支持管理NVR/DVR最大设备数 */
#define PT_MAX_ALLOT_NVD        4       /* 每个ipc最多被几个NVR连接 */

#define YDT_MOBILE_ADDR_HB      "http://www.hbydt.cn/emobile.html"       /* 汉邦logo，设置非中文语言下的手机客户端下载地址 */
#define YDT_MOBILE_ADD_HB_ZW    "http://www.hbydt.cn/mobile.html"        /* 汉邦logo，设置中文语言下的手机客户端下载地址 */
#define YDT_MOBILE_ADDR_ENG     "http://www.ivview.com/emobile.html"     /* 中性中英文logo，设置英文语言下的手机客户端下载地址 */
#define YDT_MOBILE_ADDR_SDVR_ZW "http://www.ivview.com/mobile.html"      /* 中性中英文logo，设置中文语言下的手机客户端下载地址 */

#define PTUMIN(a, b)      ((a)<(b)?(a):(b))
#define PTIMAX(a, b)      ((a)>(b)?(a):(b))
#define PTCLIP(x, a, b)   ((x)<(a)?(a):((x)>(b)?(b):(x)))
#define PTICLIPI(x, b)    PTCLIP(x, 0, b)
#define PTIZERO(a, b)     ((a)?(b):0)       //a为0则0，否则为b
#define PTINONZERO(a, b)  ((a)?0:(b))       //a不为0则0，为0则为b
#define PTIABS(x)         ((x)<0?-(x):(x))  //取x 绝对值
#define PTPACKBYTES(a, b)  (((a<<8)&0xff00)|((b)&0x00ff))
#define PTPACK16LSB(a, b) (((a<<16)&0xffff0000)|((b)&0x0000ffff))
#define PTMUX(x, a, b)    ((x)?(a):(b))     //x不为0则为a,为0则为b
#define PTUBYTESEL(x,b)   (((x)>>((b)<<3))&0xff)
#define PTZERO_VAL {0,0,0,0,0,0,0,0}
#define PTPLANAR_ZERO_VAL {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}

#define ISAPI_STREAM_MAXCH 128
#define PT_MAX_LIST 16
#define MAX_DEVINFO_STR_LEN 32
#define MAX_IP_ADDR_LEN     64
#define MAX_STREAMID 2
#define MAX_INPUTIO 4
#define MAX_OUTPUTIO 4
#define MAX_INTPUTPROXYCH 32

#define MAX_STRLEN_128 128
#define MAX_STRLEN_32 32
#define WEEK_DAYNUM  7
#define DAY_SEGNUM 6
#define WEB_LOG_PAGE_SIZE 500
#define ADAPTER_MAX_LIST 16
#define ISAPI_CMD_MAX_LEN   128

typedef enum
{
    ISAPI_DDNS_HANBANG = 0,
    ISAPI_DDNS_ORAY,
    ISAPI_DDNS_DYNDNS,
    ISAPI_DDNS_NO_IP,
    ISAPI_DDNS_MEIBU,
    ISAPI_DDNS_FREEDNS
} DDNS_SERVER_E;

typedef enum
{
    PT_AUTOMODE,        //自适应
    PT_HALFMODE_10M,    //10M半双工
    PT_FULLMODE_10M,    //10M全双工
    PT_HALFMODE_100M,   //100M半双工
    PT_FULLMODE_100M ,  //100M全双工
    PT_FULLMODE_1000M   //1000M全双工
} PT_NETMODE_E;

typedef enum
{
    PT_OSD_SYSTIME = 0,
    PT_OSD_CHNAME = 1,
    PT_OSD_CHTIME = 2,
} PT_OSD_E;

typedef enum
{
    PT_OSD_TIME = 0,
    PT_OSD_CHANNEL = 1,
} PT_OSD_OLD_E;

typedef enum addressingFormatType
{
    ipaddress = 1,
    hostname = 2
} addrtype_e;

typedef enum proxyProtocol
{
     HBGK = 0,
    ONVIF = 1,
    MAX_PROTO
} protocol_e;

typedef enum
{
    CONTENT_RTSP = 0,
} CONTENT_TRANSPORT_E;

typedef enum
{
    CONTENT_H264 = 0,
} CONTENT_VIDEO_CODECTYPE_E;

typedef enum
{
    CONTENT_PROGRESSIVE = 0,//progressive
} CONTENT_VIDEO_SCANTYPE_E;

typedef enum
{
    CONTENT_VBR = 0,
    CONTENT_CBR = 1,
} CONTENT_VIDEO_QUALITYTYPE_E;

typedef enum
{
    CONTENT_JPEG = 0,
} CONTENT_SNAP_IMAGETYPE_E;

typedef enum
{
    CONTENT__AUSTREAM_DISABLE,    //视频流
    CONTENT__AUSTREAM_ENABLE,     //复合流
} CONTENT_AUSTREAMADD_E;

typedef enum
{
    DEVTYPE_NULL,           /* Null device */
    DEVTYPE_IDE,            /* IDE hard or SATA hard disk */
    DEVTYPE_RAM,            /* RAM disk */
    DEVTYPE_FLASH,          /* Flash memory */
    DEVTYPE_SD,             /* SD Card */
    DEVTYPE_USB,            /* USB host device */
    DEVTYPE_CDDVD,          /* CDDVD Rom */
    DEVTYPE_ESATA,          /* ESATA device */
    DEVTYPE_NETWORK,        /* network device */
    DEVTYPE_MAX
} DEVTYPE_E;

typedef enum connMode
{
    manual = 1,
    plugplay = 2
} conmode_e;

typedef enum
{
    PT_LINKSTATUS_DISABLE,  //不联动
    PT_LINKSTATUS_ENABLE,   //联动
} PT_LINKSTATUS_E;

typedef enum
{
    PT_LOWER = 0, //最低
    PT_LOW,     //低
    PT_NORMAL,  //正常
    PT_HIGH,    //高
    PT_HIGHER,  //最高
} PT_SENSITIVITY_E;

typedef enum
{
    PT_BLOCK_DISABLE,   //坐标设置移动侦测区域
    PT_BLOCK_ENABLE,    //块设置移动侦测区域
} PT_BLOCKENABLE_E;

typedef enum
{
    PT_ALMTYPE_CLOSE,   //常闭
    PT_ALMTYPE_OPEN,    //常开
} PT_ALMTYPE_E;

typedef enum
{
    WEB_PTZ_CMD_STOP,
    WEB_PTZ_CMD_UP,            // 上
    WEB_PTZ_CMD_DOWN,          // 下
    WEB_PTZ_CMD_LEFT,          // 左
    WEB_PTZ_CMD_RIGHT,         // 右
    WEB_PTZ_CMD_FOCUS_INC,     /* 聚焦+ */
    WEB_PTZ_CMD_FOCUS_DEC,     /* 聚焦- */
    WEB_PTZ_CMD_IRIS_INC,      /* 光圈+ */
    WEB_PTZ_CMD_IRIS_DEC,      /* 光圈- */
    WEB_PTZ_CMD_ZOOM_DEC,      /* 缩放+ */
    WEB_PTZ_CMD_ZOOM_INC,      /* 缩放- */
    WEB_PTZ_CMD_F1,            // 辅助
    WEB_PTZ_CMD_F1_1,
    WEB_PTZ_CMD_F2,            // 辅助
    WEB_PTZ_CMD_F2_1,
    WEB_PTZ_CMD_AUTO,          // 自动
    WEB_PTZ_CMD_AUTO_1,
    WEB_PTZ_CMD_PRESET_SET,    // 预置
    WEB_PTZ_CMD_PRESET_GET,    // 调用
    WEB_PTZ_CMD_SETUP,
    WEB_PTZ_CMD_ENTER,
    WEB_PTZ_CMD_PAGEUP,
    WEB_PTZ_CMD_PAGEDOWN,
    WEB_PTZ_CMD_BRUSH,         // 雨刷
    WEB_PTZ_CMD_LEFT_UP,       //24左上
    WEB_PTZ_CMD_LEFT_DOWN,     //25左下
    WEB_PTZ_CMD_RIGHT_UP,      //26右上
    WEB_PTZ_CMD_RIGHT_DOWN,    //27右下
    WEB_PTZ_CMD_PRESET_CLR,    //28预置点清除
    WEB_PTZ_CMD_SET_PATTERN_START, //29轨迹巡航--设置开始
    WEB_PTZ_CMD_SET_PATTERN_END,   //30轨迹巡航--设置结束
    WEB_PTZ_CMD_SET_PATTERN_RUN,   //31轨迹巡航--运行

} ADDTYPE_E;

typedef enum
{
    RECORD_WEEK_MON,        //星期一
    RECORD_WEEK_TUES,       //星期二
    RECORD_WEEK_WED,        //星期三
    RECORD_WEEK_THUR,       //星期四
    RECORD_WEEK_FRI,        //星期五
    RECORD_WEEK_SAT,        //星期六    
    RECORD_WEEK_SUN        //星期日
} RECORD_WEEK_E;

typedef enum
{
    RECORD_CMR = 0,
    RECORD_MOTION,
    RECORD_ALARM,
    RECORD_EDR,
    RECORD_ALARMANDMOTION
}RECORD_MODE_E;

typedef enum
{
    PT_AUTO_DISABLE,    //不自动连接
    PT_AUTO_ENABLE,     //自动连接
} PT_AUTOENABLE_E;

typedef enum
{
    PT_SUCCESS_FAIL,    //失败
    PT_SUCCESS_SUCC,    //成功
} PT_SUCCESS_E;

typedef enum
{
    PT_CONNECT_NO,      //断开
    PT_CONNECT_YES,     //连接
    PT_NOOPERATE        //无动作
} PT_CONNECT_E;

/*结构体定义*/
typedef struct
{
    uint16 left; //起始点横坐标
    uint16 top; //起始点纵坐标
    uint16 width; //宽度
    uint16 height; //高度
} ADAPTER_AREA_S;

typedef enum
{
    SINGLE  = 0,
    DUAL    = 1
} LIPVER_E;

typedef enum
{
    half = 0,
    full = 1
} DUPLEX_E;

typedef enum
{
	ISAPI_STATUSCODE_OK = 1,
	ISAPI_STATUSCODE_DEVBUSY = 2,
    ISAPI_STATUSCODE_DEVERROR = 3,
    ISAPI_STATUSCODE_INVALID_OPERATION = 4,
    ISAPI_STATUSCODE_INVALID_XMLFORMAT = 5,
    ISAPI_STATUSCODE_INVALID_XMLCONTENT = 6,
    ISAPI_STATUSCODE_REBOOTREQUIRED = 7,

}ISAPI_STATUSCODE_E;

typedef enum
{
    ISAPI_SUBSTATUSCODE_OK = 1,
    
    ISAPI_SUBSTATUSCODE_NOTSUPPORT = 10,
    ISAPI_SUBSTATUSCODE_INVALID_OPERATION,
    ISAPI_SUBSTATUSCODE_LOWPRIVILEGE,

    ISAPI_SUBSTATUSCODE_BAD_PARAM = 20,

    ISAPI_SUBSTATUSCODE_REBOOTREQUIRE = 30,
    
    ISAPI_SUBSTATUSCODE_ERROR_IP = 40,
    ISAPI_SUBSTATUSCODE_ERROR_MAC,
    ISAPI_SUBSTATUSCODE_ERROR_PWD,
    ISAPI_SUBSTATUSCODE_ERROR_USER,
    ISAPI_SUBSTATUSCODE_ERROR_OTHER,
}ISAPI_SUBSTATUSCODE_E;

enum
{
    ISAPI_USER_RIGHT_PREVIEW = 0,                 //实时预览权限C
    ISAPI_USER_RIGHT_REC_MANUAL,              //手动录像C
    ISAPI_USER_RIGHT_REC_PB,                  //录像查询回放C
    ISAPI_USER_RIGHT_BACKUP,                  //备份管理C
    ISAPI_USER_RIGHT_REC_SET_REC_PARAM,       //录像参数C
    ISAPI_USER_RIGHT_PTZ,                     //云台权限C
    ISAPI_USER_RIGHT_SNAPSHOT,                //截图C
    ISAPI_USER_RIGHT_SET_CH_SET,              //通道设置C
    ISAPI_USER_RIGHT_REC_SET_REC_PLAN,        //定时录像C
    ISAPI_USER_RIGHT_ALM_SET_MOTION,          //移动报警C
    ISAPI_USER_RIGHT_ALM_SET_ALM,             //报警设置C

    ISAPI_USER_RIGHT_NVR_MGR,                 //组网管理          11
    ISAPI_USER_RIGHT_CH_MGR,                 //通道管理

    ISAPI_USER_RIGHT_SET_MAN_GENERAL,         //常规设置
    ISAPI_USER_RIGHT_SET_MAN_UART,            //串口设置
    ISAPI_USER_RIGHT_HDD_MAN,                 //磁盘管理
    ISAPI_USER_RIGHT_SET_MAN_NET,             //网络设置
    ISAPI_USET_RIGHT_INFO_VIEW,               //信息查看权限
    ISAPI_USER_RIGHT_SYS_MAN_UPGRADE,         //升级权限
    ISAPI_USER_RIGHT_SYS_MAN_FAST_SET,        //快速设置
    ISAPI_USER_RIGHT_SYS_MAN_DEFAULT,         //恢复出厂设置权限
    ISAPI_USER_RIGHT_IMPORT,                  //导入导出          21
    ISAPI_USER_RIGHT_SHUTDOWN,                //系统关机

    ISAPI_USER_RIGHT_REC_SET_REC_CARD,        //卡号录像设置C
    ISAPI_USER_RIGHT_MAX,
};


enum
{
    ISAPI_USER_REMOTE_RIGHT_PREVIEW  = 0,          //实时预览权限C
    ISAPI_USER_REMOTE_PARAM_SET,              //参数设置权限C
    ISAPI_USER_REMOTE_PB,                     //回放权限C
    ISAPI_USER_REMOTE_BACKUP,                 //备份权限C
    ISAPI_USER_REMOTE_LOG,                    //日志查看权限
    ISAPI_USER_REMOTE_VOICE_CHAT,             //对讲
    ISAPI_USER_REMOTE_UPGRADE,                //升级
    ISAPI_USER_REMOTE_RIGHT_MAX,
};

enum
{
   ISAPI_STAT_NULL = 0,
   ISAPI_STAT_CMD_START,
   ISAPI_STAT_CMD_END,
   ISAPI_STAT_CMD_ERROR,
};

enum {
    ISAPI_UPNP_DISCONNECT,    // 已断开连接
    ISAPI_UPNP_SEARCHING,     // 正在搜索    
    ISAPI_UPNP_SCAN_SUCC,     // 扫描成功
    ISAPI_UPNP_SCAN_FAIL,     // 扫描失败
    ISAPI_UPNP_PORT_CONFLICT, // 端口冲突
}ISAPI_UPNP_STAT_E;

/*结构体的定义*/
typedef struct
{
    sint32 en_title;     // 1-显示OSD名0-不显示
    uint8 title[PT_MAX_STRING_EXT];// OSD名
    ADAPTER_AREA_S pos_title;    //OSD名的坐标信息
}CONTENT_IPC_OSDATTRI_S, *PCONTENT_IPC_OSDATTRI_S;

typedef struct
{
    sint32  channel;
    uint16  osdnum;          //osd数目
    uint16  osdattrib;      //OSD属性0-不透明 1 -透明
    uint16  format_date;         //日期格式 如果有日期OSD则该参数有用,PT_DATEFORMAT_E
    uint16  format_time;         //时间显示格式 如果有日期OSD则该参数有用,PT_TIMEFORMAT_E
    uint16   en_week;          //是否显示星期 如果有日期OSD则该参数有用
    uint16   refresh_osd;        /* 是否刷新osd 0-默认刷新  1-不刷新*/
    CONTENT_IPC_OSDATTRI_S osd[MAX_OSD_NUM];
}CONTENT_IPC_OSDINFO_S, *PCONTENT_IPC_OSDINFO_S;

typedef struct
{
    char almout_name[MAX_STRING];
    int defaultState;
    int outputState;
    int pulseDuration;
}SYSTEM_IO_OUTPUT_S, *PSYSTEM_IO_OUTPUT_S;

typedef struct
{
    SYSTEM_IO_OUTPUT_S  io_output[MAX_AMOUT];
}SYSTEM_IO_OUTPUTLIST_S, *PSYSTEM_IO_OUTPUTLIST_S;

typedef struct
{
    char   almin_name[MAX_STRING];
    sint32 enabled;
    sint32 triggering;    
}SYSTEM_IO_INPUT_S, *PSYSTEM_IO_INPUT_S;

typedef struct
{
    SYSTEM_IO_INPUT_S  io_input[MAX_AM];
}SYSTEM_IO_INPUTLIST_S, *PSYSTEM_IO_INPUTLIST_S;

typedef struct
{
    char dev_name[MAX_DEVINFO_STR_LEN];     /* 设备名称 */
    char dev_no[MAX_DEVINFO_STR_LEN];       /* 设备序列号 */
    char dev_id[MAX_DEVINFO_STR_LEN];       /* 设备号 */
    char dev_type[MAX_DEVINFO_STR_LEN];     /* 设备型号 */
    char main_ver[MAX_DEVINFO_STR_LEN];     /* 主控版本 */
    char main_date[MAX_DEVINFO_STR_LEN];
    char venc_ver[MAX_DEVINFO_STR_LEN];     /* 编码版本 */
    char venc_date[MAX_DEVINFO_STR_LEN];
	uint32 telecontrol_id;                  /* 串口控制号 */
    uint32 ch_num;                          /* 通道个数 */
    uint32 disk_num;                        /* 硬盘个数 */
    uint32 sensor_in;                       /* 报警输入个数 */
    uint32 sensor_out;                      /* 报警输出个数 */
    uint32 ipc_pap;                         /* IPC即插即用使能 */
}SYSTEM_DEVICE_INFO_S, *PSYSTEM_DEVICE_INFO_S;

typedef struct
{
    uint32 sec : 6;     /* 秒: 0~63 */
    uint32 min : 6;     /* 分: 0~63 */
    uint32 hour : 5;    /* 时: 0~23 */
    uint32 day : 5;     /* 日: 1~31 */
    uint32 month : 4;   /* 月: 1~12 */
    uint32 year : 6;    /* 年: 0~63 */
}SYSTEM_TIME_S, *PSYSTEM_TIME_S;

typedef struct
{
    SYSTEM_TIME_S    dev_time;        /* 主机时间 */
}SYSTEM_TIME_CFG_S, *PSYSTEM_TIME_CFG_S;

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

typedef struct
{
    char rout_ip[20];            //路由器ip
    char wan_ip[20];             //wan端口地址
} NETWORK_UPNP_SEARCH;

//UPNP设置
typedef struct
{
    uint32  upnp_en;                     // UPNP 使能
    uint16  pat_count;                   //转换端口个数
    uint16  status;                    //路由器个数
    NETWORK_PAT_UPNP_S  pat_info[MAX_PAT];   //转换端口信息
    NETWORK_UPNP_SEARCH rout_info; //所连接的路由器的信息
} NETWORK_UPNP_S, *PNETWORK_UPNP_S;

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

typedef struct
{
    char userName[MAX_STRING];
    char pwd[MAX_STRING];
    int  status;
    int  autologin;
} NETWORK_PPPOE_S, *PNETWORK_PPPOE_S;

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

typedef struct
{
    int id;
    IPADDR_S ip;
    DISCOVERY_S discovery;
    LINK_S link;
}NETWORK_DEVICE_INFO_S, *PNETWORK_DEVICE_INFO_S;

/* 系统时间定义 */
typedef struct
{
    uint32 sec : 6;     /* 秒: 0~63 */
    uint32 min : 6;     /* 分: 0~63 */
    uint32 hour : 5;    /* 时: 0~23 */
    uint32 day : 5;     /* 日: 1~31 */
    uint32 month : 4;   /* 月: 1~12 */
    uint32 year : 6;    /* 年: 0~63 */
} SYSTIME, *PSYSTIME;

typedef struct
{
    char   streamid[64];
    int    status;
    sint16 channel;
    sint16 type;
}STREAMING_STATUS_INFO;

typedef struct
{
    STREAMING_STATUS_INFO stream_info[ISAPI_STREAM_MAXCH];
}WEB_HEARTBEAT_INFO;

typedef struct
{
    char   streamid[64];
    char   option[32];
    sint32 speed;
}STREAMING_PB_CONTROL, *PSTREAMING_PB_CONTROL;

typedef struct SecurityUser
{
    char user_name[MAX_STRING];
    char user_pwd[MAX_STRING];
    uint64    local_authority[32];
    uint64    remote_authority[16];
    uint32    bind_ipaddr;                  // 远程绑定IP
    uint8     bind_macaddr[8];        // 远程绑定MAC
    sint32    user_pwdflag;  //是否修改密码
} SECURITY_USER_S, *PSECURITY_USER_S;

typedef struct
{
    sint32 httpport;
    sint32 listenport;
    sint32 rtspport;
    sint32 rtmpport;
    sint32 upgradeport;
}SECURITY_PORTINFO_S, *PSECURITY_PORTINFO_S;

typedef struct
{
    int status[32];
    int alarm_out_no;
} EVENT_MANUAL_S, *PEVENT_MANUAL_S;

typedef struct timeSpan
{
    SYSTIME start;
    SYSTIME end;
} timeSpan_S, *ptimeSpan_S;

typedef struct
{
    timeSpan_S tmperiod[DAY_SEGNUM];    
}TIMEPERIOD_S, *PTIMEPERIOD_S;

typedef struct
{
    TIMEPERIOD_S timeperiodinfo[WEEK_DAYNUM];
}SCHEDULEINFO_S, *PSCHEDULEINFO_S;

typedef struct
{
    int enable;//开关
    int beep; //蜂鸣器
    int fullscreen;//全屏
    int email;//邮件上传
    int almpush;//报警上传
    int sensor_out;
    int temp_limit;//报警温度(温度报警有效)
    int outputDelay;//报警输出延时时间
    int almoutaudio;//输出音频
    int ptzEnable;//联动预置点开关
    uint32 presetenable[MAX_CH];//联动跳预置点
    int link_record[MAX_CH];
    int link_snap[MAX_CH];//截图联动
}TRIGGER_INFO_S, *PTRIGGER_INFO_S;

typedef struct
{
    char event_type[32];//事件类型
    TRIGGER_INFO_S triggerinfo;
    SCHEDULEINFO_S scheduleinfo;
} EVENT_TRIGGER_S, *PEVENT_TRIGGER_S;

typedef struct
{
    uint32  channel;    // 通道号
    uint32  command;    // 云台控制命令 为0x00010028则停止
    uint32  index;      // 预制点号(受球机有效值范围影响)[0, 255]
    uint32  speed;      // 控制速度 [0, 255] ，0的速度是最慢的
} PTZ_DEVICE_CTRL;

typedef struct
{
    SYSTIME time;  // 记录日志时间
    char pri_type;     // 主类型
    char sec_type;     // 次类型
    char param;        // 操作类型
    char channel;      // 通道号
    int host;        // 0-主机 其他 –远程IP如0xc0a80006
    char user[17];     // 用户名
    char hard_driver;  // 硬盘号
    char sensor_in;    // 报警输入
    char sensor_out;   // 报警输出
    char reserve[32];  // 保留
} WEB_LOGINFO_S, *PWEB_LOGINFO_S;

typedef struct SearchLog
{
    char sid[128];
    char mid[128];
    SYSTIME start_time;
    SYSTIME end_time;
    int  pri_type;   
    int  sec_type;
    int startindex;//查询起始位置
    int max_ret;       
    int result_ret;
    int real_totalnum;//实际满足查询条件的总数量
    WEB_LOGINFO_S log_data[WEB_LOG_PAGE_SIZE];
} SearchLog_S, *pSearchLog_S;

typedef struct SearchRec
{
    char sid[64];
    int track_id;
    timeSpan_S time_span;
    int startindex;//查询起始位置
    int max_ret;//查询最大条数
    int real_totalnum;//实际满足查询条件的总数量
    int seg_num;//当前传输数量
    int success;
    char seg_buf[280000]; //MAX_ADAPTER_REC_SEG * sizeof(PT_RECFILE_SEGINFO_S) = 32000
} SearchRec_S, *pSearchRec_S;

typedef struct
{
    int starth;  //开始小时
    int startm;  //开始分钟
    int endh;    //结束小时
    int endm;    //结束分钟
}RECORD_TMPERIOD_S, *PRECORD_TMPERIOD_S;

typedef struct
{
    RECORD_MODE_E recordmode;
    RECORD_TMPERIOD_S tmperiod;    
}RECORD_SCHEDULEINFO_S, *PRECORD_SCHEDULEINFO_S;

typedef struct
{
    RECORD_SCHEDULEINFO_S scheduleinfo[DAY_SEGNUM];//8段时间设置
}RECORD_TRACKSINFO_S, *PRECORD_TRACKSINFO_S;

typedef struct 
{
    int resolution_w;
    int resolution_h;
    int framerate;
    int bitrate;
    int track_enable;//录像计划是否启用
    int SaveAudio;//是否记录音频
    int Duration;//录像过期时间
    int LoopEnable;//是否循环录像
    int RedundancyRecord;//是否冗余录像
    int PreRecordTimeSeconds;//预录时间
    int PostRecordTimeSeconds;//延迟录像时间
    RECORD_TRACKSINFO_S trackinfo[WEEK_DAYNUM];//一个星期7天
}RECORD_TRACKSCHANNEL_S, *PRECORD_TRACKSCHANNEL_S;

typedef struct
{
    int online_num;
    int cur_channel;//按位表示，通道复制设置使用
    RECORD_TRACKSCHANNEL_S tracklist[MAX_CH];
}RECORD_TRACKSLIST_S, *PRECORD_TRACKSLIST_S;

typedef struct
{
    sint32 almin_no;
    uint8  almin_name[MAX_STRING];  //探头名
    PT_ALMTYPE_E almtype;           //探头类型 0-常闭 1-常开
}CONTENT_ALMIN_CONF_S, *PCONTENT_ALMIN_CONF_S;


typedef struct
{
    sint16  hdd_attri;      // 磁盘属性0:读写；1 只读 ；2 冗余
    sint8   hdd_group;      // 盘组号
    sint8   hdd_devno;      // 当为ESATA盘时，存ESATA设备号
    DEVTYPE_E  dev_type;
    sint16  hdd_type;      // 磁盘属性0: 数据区 1 备份区 ；2 冗余
    sint16 recv;
} DEVICE_DISK_ATTR_S, *PDEVICE_DISK_ATTR_S;

typedef struct
{
    int channel;
    int bright;      /* 亮度0-255 */
    int contrast;    /* 对比度0-255 */
    int saturation;  /* 饱和度0-255 */
    int hue;         /* 色度0-255 */
    int sharp;       /* 锐度 0或1 */
    int nr_enable;   /* 视频去噪使能 0-关闭 1-开启 */
    int nr_level;    /* 视频去噪级别(0-5) */
    int image_lossdetection; /*视频丢失检测*/
}CONTENT_IMAGE_PARAM_S, *PCONTENT_IMAGE_PARAM_S;

typedef struct 
{
    sint16 width;
    sint16 height;
}ADAPTER_RES_S;

typedef struct 
{
    uint32 count;//当前列表条数
    ADAPTER_RES_S list[ADAPTER_MAX_LIST];
} CONTENT_RESLIST_S; //列表限定结构体

typedef struct 
{
    sint32 max_value;
    sint32 min_value;
} ADAPTER_RANGE_S; //范围限定结构体

typedef struct
{
    CONTENT_RESLIST_S resoution;  /*分辨率*/
    ADAPTER_RANGE_S frame_rate;      /*帧率范围*/
    ADAPTER_RANGE_S bit_rate;        /*码路段*/
    ADAPTER_RANGE_S quality;   /*图像质量*/
} CONTENT_VENC_RANGE_S, *PCONTENT_VENC_RANGE_S;

typedef struct
{
    CONTENT_AUSTREAMADD_E byStreamType;  //视频流类型
    ADAPTER_RES_S byResolution;   //视频分辨率
    CONTENT_VIDEO_QUALITYTYPE_E byBitrateType; //码率类型
    int byPicQuality;     //图像质量
    int dwVideoBitrate;          //视频码率 实际码率
    int dwVideoFrameRate;        //帧率 PAL 2-30 N 2-30
    int quant;                   //量化因子 1-31
}CONTENT_VENC_CONFIG_S, *PCONTENT_VENC_CONFIG_S;

typedef struct
{
    int channel;
    int streamtype;
    CONTENT_VENC_CONFIG_S venc_config;
    CONTENT_VENC_RANGE_S venc_range;    
}CONTENT_VENC_PARAM_S, *PCONTENT_VENC_PARAM_S;

typedef struct sourceinputportdescriptor
{
    protocol_e proto;
    addrtype_e atype;
    char ipaddr[MAX_STRLEN_128];
    int mport;
    int sport;
    char uname[MAX_STRLEN_32];
    char upw[MAX_STRLEN_32];
    conmode_e cmode;
} inputport_s;

typedef struct InputProxyChannel
{
    int id;
    int online_status;
    int poechannel;//POE通道标志0-普通IPC 1-POE通道IPC
    char name[PT_MAX_STRING_EXT];
    inputport_s desc;
} inputproxych_s, *pinputproxych_s;

typedef struct InputProxyChannelList
{
    inputproxych_s ich[MAX_INTPUTPROXYCH];

} INPUTPROXY_S, *pinputproxy_s;

#if 0
typedef struct
{
    //uint32 flag; /* 用于合法性检测 */
    //uint32 healthy; /* 句柄健康状况,0-正常,其他-故障 */
    //sint32 running; /* 线程运行标记 */
    sint32	sysnetapi_handle;			//主控接口句柄
    WebsHash is_t;
    WebsHash system_t;
    WebsHash contentmgmt_t;
    WebsHash network_t;
    WebsHash media_t;
    WebsHash ptz_t;
    WebsHash event_t;
    WebsHash security_t;
    WebsHash streaming_t;
    WebsHash notification_t;
    notifycallback notifyfunc;  /* 消息回调通知函数 */
    pthread_mutex_t mutex;      /* 线程互斥 */
    pthread_t tid;              /* 线程ID号 */
    pid_t pid;                  /* 线程PID */
    sint32 update_process;
    sint32 upgradestart;
    sint32 backupstatus;
    char   backupid[64]; 
    sint32 backup_process;
    sint32 maxchannel;
    uint32 sensorin_no;         // 报警输入数
    uint32 sensorout_no;        //报警输出数
    sint32 upnpstatus;
    sint32 webstat;
    char   webcmd[ISAPI_CMD_MAX_LEN];
} ISAPI_FD_S, *PISAPI_FD_S;
ISAPI_FD_S isapi_fd = {0};
#endif

/*NTP服务相关的信息*/
typedef struct
{
    char    ntp_host[MAX_IP_ADDR_LEN];   /* NTP服务器域名 */
    uint32  ntp_port;               /* NTP服务器端口 */
    uint32  autontp_enable;                     /* NTP校时使能 */// 开启ntp服务,0- 不启用 ,1-表示自动 ，2-表示手动
    uint32  server_index;         // 服务器索引号
    uint32  ajust_period;               /* NTP校时周期() */
    uint32  sync_unit;                   /* 周期单位，0-分钟 1-小时 2-天 3-星期 4-月*/
    sint32  time_zone;            /* 时区 */
}SYSTEM_NTP_CFG_S, *PSYSTEM_NTP_CFG_S;

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

/*Web通用的状态回复*/
typedef struct _common_response
{
	char requestURL[256];
	int statusCode;
	char statusString[32];
	char subStatusCode[32];
} COMMON_RESPONSE_S, *PCOMMON_RESPONSE_S;
#endif
