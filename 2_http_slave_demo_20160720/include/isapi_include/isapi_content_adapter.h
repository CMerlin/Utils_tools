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

#ifndef _ISAPI_CONTENTADAPTER_H_
#define _ISAPI_CONTENTADAPTER_H_

#include "isapi_adapter.h"
#include "sys_net.h"
#include "sys_netapi.h"
#include "config_usr.h"
#include "config.h"


//#define MAX_DEV_DISK        (12)
#define  ISAPI_MAX_HD  32

typedef enum proxyProtocol
{
     HBGK = 0,
    ONVIF = 1,
    MAX_PROTO
} protocol_e;


#if 0
char protocol_c[][16] =
{
    "HBGK",
    "ONVIF",
    "HUATU"
};
#endif

typedef enum connMode
{
    manual = 1,
    plugplay = 2
} conmode_e;

#if 0
char conmode_c[][16] =
{
    "manual",
    "plugplay"
};
#endif


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

typedef struct streamingProxyChannelIdList
{
    int spch_id[MAX_STREAMID];

} sproxyid_s, *psproxyid_s;


typedef struct inputProxyPortIdList
{
    int ipch_id[MAX_INPUTIO];

} iproxyid_s, *piproxyid_s;


typedef struct outputProxyPortIdList
{
    int opch_id[MAX_INPUTIO];

} oproxyid_s, *poproxyid_s;

typedef struct relatedIOProxy
{
    iproxyid_s iplist;
    oproxyid_s oplist;
} relatedio_s, *prelatedio_s;

typedef struct InputProxyChannelStatus
{
    int id;
    inputport_s desc;
    int online;
    sproxyid_s sid;
    relatedio_s rio;
} instatusch_s, *pinstatusch_s;


typedef struct InputProxyChannelStatusList
{
    instatusch_s ics_list[MAX_INTPUTPROXYCH];

} inproxystat_s, *pinproxystat_s;

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

typedef struct 
{
    uint32 count;//当前列表条数
    ADAPTER_RES_S list[ADAPTER_MAX_LIST];
} CONTENT_RESLIST_S; //列表限定结构体

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
    uint32 bright;      /* 亮度0-100 */
    uint32 contrast;    /* 对比度0-100 */
    uint32 saturation;  /* 饱和度0-100 */
    uint32 hue;         /* 色度0-100 */
    uint32 sharp;       /* 锐度 0-100 */
} CONTENT_IMAGE_SYSCOLOR_S, *PCONTENT_IMAGE_SYSCOLOR_S;

typedef struct
{
    int channel;
    CONTENT_IMAGE_SYSCOLOR_S scene[PT_SCENE_WEAK_LIGHT+1];
}CONTENT_IMAGE_SCENE_PARAM_S, *PCONTENT_IMAGE_SCENE_PARAM_S;

typedef struct
{
    int channel;
    int enable;
    int samplingInterval;
    int startTriggerTime;
    int endTriggerTime;
    int regionType;
    int rowGranularity;
    int columnGranularity;
    int sensitivityLevel;
    uint32  block[18];
}CONTENT_VIDEO_MOTIONDETECTION_S, *PCONTENT_VIDEO_MOTIONDETECTION_S;

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

typedef enum
{
    DEVSTAT_NORMAL   = 0x00, // 设备工作正常状态
    DEVSTAT_STANDBY  = 0x01, // 设备处于待命状态(用PT_DEVSTAT_NORMAL可立即唤醒硬盘)
    DEVSTAT_SLEEP    = 0x02, // 设备处于睡眠状态(用PT_DEVSTAT_NORMAL并不能立即唤醒硬盘,只有真正读写硬盘时才去唤醒)----暂时未使用这个方式
    DEVSTAT_ERROR    = 0x03, // 设备处于错误状态
    DEVSTAT_NOFORMAT = 0x04, // 设备未格式化
} DEVSTATUS_E;

typedef enum
{
    CONTENT_DISK_INFORMAT = 0,//磁盘正在被格式化
    CONTENT_DISK_FORMATEND,   //格式化结束
    CONTENT_FARMAT_ERR ,      //格式化错误

    CONTENT_DISK_NOEXIST,     //要格式化的磁盘不存在
    CONTENT_DISK_LOST,        //格式化中途错误
    CONTENT_DISK_BUSY,        //磁盘正在被使用
} CONTENT_FORMATTYPE_E;

typedef struct
{
    uint16 dev_num;         //格式化的磁盘号
    uint16 dev_type;        //格式化的磁盘类型 DEVTYPE_E
    sint16 percentstate;    //当前进度只在format_state为CONTENT_DISK_INFORMAT时有效
    uint16 format_state;    //格式化状态 CONTENT_FORMATTYPE_E
} CONTENT_FORMATSTATE_S, *PCONTENT_FORMATSTATE_S;

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
    uint16 dev_num;                 //设备挂载通道号(和物理插槽有关联)
    DEVICE_DISK_ATTR_S dev_attr;    //设备属性（默认硬盘）
    DEVSTATUS_E dev_status;         //设备状态
    uint32 active;                  //设备工作状态（休眠或者活动）
    uint64 device_capabilty;        //设备容量(字节) 平台根据各自需要进行相应转换
    uint32  mfs_fs_active;          //设备文件系统是否格式化，0-未格式化，1-已格式化，2-预分配
    uint64 mfs_free;                //当前可用容量(字节)平台根据各自需要进行相应转换
} DEVICEINFO_S, *PDEVICEINFO_S;

typedef struct
{
    int disk_num;   /*当前设备挂载硬盘数*/
    DEVICEINFO_S disk_info[ISAPI_MAX_HD];
} CONTENT_DISKINFO_S, *PCONTENT_DISKINFO_S;

typedef struct
{
    sint32 support;
    sint32 port;
}CONTENT_IPC_PROTOCOL_S;


/* 搜索列表数据结构体 */
typedef struct
{
    uint16   cur_index;
    uint16   item_num;
    CONTENT_IPC_PROTOCOL_S  item_list[MAX_PROTO]; /*设备协议支持-protocol_e*/
} CONTENT_IP_SUPPORT_PROT_S;

typedef struct
{
    char       ip_addr[MAX_IPADDR_STR_LEN];    /* ip addr*/
    uint16      dev_type;                       // 设备类型: GUI_IPC_TYPE_E
    uint8      stat;                           // 状态: 0-未添加,1-已添加,2-添加失败,3-正在添加
    uint8      online_stat;                    // 联机状态: 0-未联机  1-联机
    //uint32      port;                           // 端口号
    char        mac_addr[32];           // MAC 地址
    char        manufacturer[32];       // 厂商
    CONTENT_IP_SUPPORT_PROT_S protl;                //设备支持的协议
    char username[32];
    char password[32];
} CONTENT_IPC_SEARCH_INFO_S;

typedef struct
{
    uint16  num;                       // 搜索到的设备数
    CONTENT_IPC_SEARCH_INFO_S    dev_info[IPC_SEARCH_MAX_NUM]; // IPC信息
} CONTENT_IPC_SEARCH_S;

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
    sint32 almin_no;
    uint8  almin_name[MAX_STRING];  //探头名
    PT_ALMTYPE_E almtype;           //探头类型 0-常闭 1-常开
}CONTENT_ALMIN_CONF_S, *PCONTENT_ALMIN_CONF_S;

int content_get_ipc_info(int ch, INPUTPROXY_S * input);
int content_oper_ipc_add(INPUTPROXY_S * input, WEB_CMD_INFO_S *webinfo);
int content_oper_ipc_delete(int ch, INPUTPROXY_S * input, WEB_CMD_INFO_S *webinfo);
int content_oper_ipc_edit(int ch, INPUTPROXY_S * input, WEB_CMD_INFO_S *webinfo);
int content_get_storage_info(CONTENT_DISKINFO_S * disk_param);
int content_format_storage_progress(CONTENT_FORMATSTATE_S * format_status);
int content_format_storage_disk(sint32 hddtype, sint32 disk_id);
int content_set_storage_attri(sint32 disk_id, DEVICE_DISK_ATTR_S * dev_attr, WEB_CMD_INFO_S *webinfo);
int content_search_ipc(CONTENT_IPC_SEARCH_S * serch_info);
int content_get_channel_param(CONTENT_VENC_PARAM_S * venc_param);
int content_set_channel_param(CONTENT_VENC_PARAM_S * venc_param, WEB_CMD_INFO_S *webinfo);
int content_get_image_param(CONTENT_IMAGE_PARAM_S *image_param);
int content_set_image_param(CONTENT_IMAGE_PARAM_S *image_param, WEB_CMD_INFO_S *webinfo);
int content_get_scene_param(CONTENT_IMAGE_SCENE_PARAM_S *scene_param);
int content_get_video_motiondetection(CONTENT_VIDEO_MOTIONDETECTION_S *motiondetection);
int content_set_video_motiondetection(CONTENT_VIDEO_MOTIONDETECTION_S *motiondetection, WEB_CMD_INFO_S *webinfo);
int content_get_channel_osdinfo(CONTENT_IPC_OSDINFO_S *osdinfo);
int content_set_channel_osdinfo(CONTENT_IPC_OSDINFO_S *osdinfo, WEB_CMD_INFO_S *webinfo);


#endif
