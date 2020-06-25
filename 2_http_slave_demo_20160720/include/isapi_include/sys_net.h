#ifndef SYSNET_H_
#define SYSNET_H_

#include "common.h"

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

typedef int PT_MFSDEV_HANDLE;//设备操作句柄类型
/*********************************************************************************
* 函数介绍：云台控制函数
* 输入参数：handle: 控制句柄
            cmd: 控制命令
            puartconf: 串口参数
            speed: 云台速率
            addr:云台地址码
            param:控制参数，如预制点
* 输出参数：无
* 返回值  ：0---成功，<0---失败
**********************************************************************************/
typedef int (*ptptz_control)(int handle, int cmd, int puartconf, int speed, int addr, int param);

/*********************************************************************************
* 函数介绍：数据处理回调
* 输入参数：idx: 通道号
            data: 数据接收缓冲区
            size: 数据接收缓冲区大小
            flag: 0--主码流数据 1--子码流数据
               paramin---扩充指针暂不用
* 输出参数：无
* 返回值  ：无
* 注: 当fifo为0时，数据存储于data中，size表示数据长度
*     当fifo不为0时，数据存储于fifo中，data表示用户缓冲区地址，size表示缓冲区长度
*     当fifo,data都为空时，表示无数据需要处理，也即数据处理结束标记
**********************************************************************************/
typedef int (*PNETSETVSTREAM)(sint32 idx, sint8 * data, uint32 size, sint32 flag, void * paramin);

/*********************************************************************************
* 函数介绍：对讲音频数据处理回调
* 输入参数：pdata --- 音频数据指针
                                len --- 音频数据大小
                                paramin---扩充指针暂不用
* 输出参数：无
* 返回值  ：
    0 --- 成功，<0 --- 失败
**********************************************************************************/
typedef int (*PNETSETASTREAM)(sint8 * data, uint32 size, sint32 type, void * paramin);

/********************************************
函数介绍:  报警信息回调函数
输入参数:  ch--- 通道号或探头号(从0开始)
                         type---见结构体PT_ALARMTYPE_E
                         status---见结构体PT_ALARMSTATUS_E
                         paramin---扩充指针暂不用
输出参数:  无
返回值:    无
*********************************************/
typedef int (*PNETSETALARMINFO)(sint32 ch, sint32 type, sint32 status, void * paramin);

/********************************************
函数介绍:  录像回放回调函数
输入参数:  idx--- 通道号或探头号(从0开始)
                         data: 数据接收缓冲区
                         size: 数据接收缓冲区大小
                         paramin---扩充指针暂不用
输出参数:  无
返回值:    无
*********************************************/
typedef int (*PPLAYBACKSTREAM)(sint32 idx, sint8 * data, uint32 size, void * paramin);

/********************************************
函数介绍: 通知网络模块回调函数
输入参数:
                         wparam: 参数
                         lparam: 参数
输出参数:  无
返回值:    无
*********************************************/
typedef void (*PNETNOTIFYCALL)(int wparam, int lparam);

/*********************************************************************************
* 函数介绍：透明串口数据处理回调
* 输入参数：data --- 透明串口数据指针
                                size --- 透明串口数据大小
* 输出参数：无
* 返回值  ：
    0 --- 成功，<0 --- 失败
**********************************************************************************/
typedef int(*PNETSERIALSTREAM)(sint8 * data, uint32 size);
/*********************************************************************************
* 函数介绍：智能模块报警信息处理回调
* 输入参数：alarminfo --- 智能模块信息指针
                              size_alarminfo --- 智能模块信息大小
                              pic_data--图片缓冲地址，如果无图片，则为NULL
                              pic_size--图片数据大小
* 输出参数：无
* 返回值  ：
    0 --- 成功，<0 --- 失败
**********************************************************************************/
typedef int(*PATMIALARMINFONOTIFY)(sint8 * alarminfo, uint32 size_alarminfo, sint8 * pic_data, uint32 pic_size);

/************************************************
    *函数介绍:主码流音视频回调处理
    * 输入参数：idx: 通道号
                fifo: 数据缓存FIFO
                data: 数据接收缓冲区
                size: 数据接收缓冲区大小
    输出参数:无
    返回值:无
*************************************************/
datacallback sysnetapi_privideocallback(sint32 idx, sint32 fifo, sint8 * data, sint32 size);

/************************************************
*函数介绍:  子码流音视频回调处理
* 输入参数：idx: 通道号
            fifo: 数据缓存FIFO
            data: 数据接收缓冲区
            size: 数据接收缓冲区大小
输出参数:无
返回值:无
*************************************************/
datacallback sysnetapi_secvideocallback(sint32 idx, sint32 fifo, sint8 * data, sint32 size);

/************************************************
*函数介绍:  对讲回调处理
* 输入参数：idx: 通道号
            fifo: 数据缓存FIFO
            data: 数据接收缓冲区
            size: 数据接收缓冲区大小
输出参数:无
返回值:无
*************************************************/
datacallback sysnetapi_talkcallback(sint32 idx, sint32 fifo, sint8 * data, sint32 size);

/********************************************
函数介绍:  统一的消息/数据回调格式(推荐使用)
输入参数:
输出参数:  无
返回值:    无
*********************************************/
typedef int (*PNETAPICALLBACK)(sint32 cmd, sint32 ch, sint32 * param, sint32 param_size, int flag);

typedef sint32(*PNETDATACALLBACK)(sint32 channel, sint32 id, sint8 * data, uint32 size, void * user_data, sint32 data_size);

typedef enum
{
    SYSNETAPI_SENSOR = 0,       //探头报警
    SYSNETAPI_MOTION,           //移动侦测报警
    SYSNETAPI_VLOST,            //视频丢失报警
    SYSNETAPI_DISKFULL,         //磁盘满报警
    SYSNETAPI_DISKERR,          //磁盘错误报警
    SYSNETAPI_VMASK,            //视频遮挡报警  5
    SYSNETAPI_PTCONFIG_CHANGE,  //平台配置文件改变 ，平台模块收到该报警信息后需要重新获取平台配置文件与原有的配置文件对比
    SYSNETAPI_VIDEO_CONNECT,    //0-无连接 1-有连接
    SYSNETAPI_SENSOR_DETECT,    //0-无触发 1-有触发
    SYSNETAPI_MOTION_DETECT,    //0-无触发 1-有触发
    SYSNETAPI_ATMI_ALARM,       //智能模块报警
    SYSNETAPI_DISK_NO_FORMAT,   //硬盘未格式化
    SYSNETAPI_DEFENCE_STAT,     //通知布防/撤防状态
} PT_ALARMTYPE_E;

typedef enum
{
    ALARM_START = 0,    //报警开启
    ALARM_END,          //报警清除
} PT_ALARMSTATUS_E;

typedef enum
{
    SYSPT_CMD_GET_PTINFO,
    SYSPT_CMD_SET_PTINFO,
    SYSPT_CMD_TEST_FTPUPLOAD,
} SYSPT_CMD;

typedef enum
{
    PT_NOTIFY_UPDATE,
    PT_NOTIFY_UPGRADEPOS,
    PT_NOTIFY_VIDEOSYS,
    PT_NOTIFY_ALARMINOPEN, //延时布放
    PT_NOTIFY_ALARMINCLOSE, //撤防
} PT_SYSNETAPI_NOTIFY_E;

typedef enum
{
    PT_UPDATE_START,       //开始升级状态
    PT_UPDATE_SUCCESS,     //升级成功
} PT_UPDATE_STATUS_E;

typedef enum
{
    PT_UPDATE_ERROR_CHECKFILE = ERRNO(COMP_ERROR_START, COMP_HBSDK), //升级文件校验错误
    PT_UPDATE_ERROR_COVERFILE,      //升级文件替换错误
    PT_UPDATE_ERROR_PARAM,          //参数错误
    PT_UPDATE_ERROR_RWFILE,         //读写文件失败
    PT_UPDATE_ERROR_OPENFAIL,       //打开升级模块失败
    PT_UPDATE_ERROR_USB_NOTFIND,    //
    PT_UPDATE_ERROR_FTP_DOWNLOAD,
    PT_UPDATE_ERROR_FTP_UPGRADE,
    PT_UPDATE_ERROR_NET_DOWNLOAD,  //网络下载数据失败
    PT_UPDATE_ERROR_NET_UPGRADE,   //网络升级失败
} PT_UPDATE_ERR_STATUS_E;

#define PT_MAX_LIST 16
typedef struct
{
    sint32 max_value;
    sint32 min_value;
} PT_RANGE_S; //范围限定结构体

typedef struct
{
    uint32 count;//当前列表条数
    sint32 list[PT_MAX_LIST];
} PT_LIST_S; //列表限定结构体

// 云台类型
typedef enum
{
    PTZ_UNKNOWN = 0,
    PTZ_RV800,
    PTZ_TOTA120,
    PTZ_S1601,
    PTZ_CLT_168,
    PTZ_TD_500,
    PTZ_V1200,
    PTZ_ZION,
    PTZ_ANT,
    PTZ_CBC,
    PTZ_CS850A = 10,
    PTZ_CONCORD,
    PTZ_HD600,
    PTZ_SAMSUNG,
    PTZ_YAAN,
    PTZ_PIH,        //利凌
    PTZ_MG_CS160,
    PTZ_WISDOM,
    PTZ_PHILIPS,
    PTZ_NEOCAM,
    PTZ_ZHCD = 20,
    PTZ_DONGTIAN,
    PTZ_EMERSON,
    PTZ_TOTA160,
    PTZ_BANGTVD,
    PTZ_BANGTVP,
    PTZ_SANSHAND,
    PTZ_SANSHANP,
    PTZ_LILIN1,
    PTZ_LILIN2,
    PTZ_PDDR = 30,  //PLECOD东容
    PTZ_PPDR,       //PLECOP东容
    PTZ_TOYANI,
    PTZ_HY,
    PTZ_TEOP,
    PTZ_PELCOD1,
    PTZ_PELCOD2,
    PTZ_PELCOD3,
    PTZ_PELCOD4,
    PTZ_PELCOD5,
    PTZ_PELCOD7 = 40,
    PTZ_PELCOD_ZH,
    PTZ_PELCOD_5F,
    PTZ_PELCOD,
    PTZ_PELCO_D,
    PTZ_PELCOP1,
    PTZ_PELCOP2,
    PTZ_PELCOP3,
    PTZ_PELCOP5,
    PTZ_PELCOP6,
    PTZ_PELCOP7 = 50,
    PTZ_PELCO_P,
} PT_PROTOCOL_E;

typedef struct
{
    uint32 type;        //云台类型 详细见PT_PROTOCOL_E
    uint32 addr;        //云台地址码
    uint32 speed;       //云台速度
    uint32 uart_type;   //串口类别RS-485串口0, sdi-485 1
} PT_PTZPARAM_S, *PPT_PTZPARAM_S;

typedef enum
{
    PT_UART_RS485 = 0,
    PT_UART_RS232 = 1,
    PT_UART_SDI485 = 2,
    PT_UART_RS422 = 3,
} PT_UART_TYPE_E;

typedef enum
{
    PT_DEF_FB_NULL = 0,
    PT_DEF_FB0 = 1,
    PT_DEF_FB1 = 2,
    PT_DEF_FB2 = 3,
    PT_DEF_FB3 = 4,
    PT_DEF_FB4 = 5,
    PT_DEF_FB5 = 6,
} PT_DEF_FB_E;

typedef struct
{
    uint32 host_addr;   //地址
    uint32 baudrate; 	//串口波特率 (0-300,1-1200,2-2400,3-4800,4-9600,5-19200,6-38400,7-57600,8-115200)
    uint32 enable;      //是否使用-off,1-on
    uint32 func;        //0-no,1-ptz,2-keyboard,3-transparent uart
    uint32 databits;    //数据位(7,8)
    uint32 stopbits;    //停止位(1,2)
    uint32 parity;      //校验位(0-NONE,1-ODD,2-EVEN,3-SPACE)
    uint16 flow_control;//流控(0-无,1-Xon/Xoff,2-硬件)
    uint16 rc_lock;     //远程遥控器锁定使能
    uint16 uart_mode;   // 串口类型 0 -- 半双工 1 -- 全双工
    uint16 atm_protocol;//ATM协议，暂时不用
} PT_UARTPARAM_S, *PPT_UARTPARAM_S;

typedef enum
{
    SYSNETAPIPTZ_CMD_GETLIST = CMDNO(0, COMP_PTZ), // 获取协议列表,参数:指向PPTZ_LIST的指针,返回值表示协议个数
    SYSNETAPIPTZ_CMD_GETSPEED,      // 获取相应通道云台控制速度param(int *)
    SYSNETAPIPTZ_CMD_SETSPEED,      // 配置相应通道云台控制速度param(int)
    SYSNETAPIPTZ_CMD_GETADDR,       // 获取相应通道云台控制地址,param(int *)
    SYSNETAPIPTZ_CMD_SETADDR,       // 配置相应通道云台控制地址,param(int)
    SYSNETAPIPTZ_CMD_GETPROTOCOL,   // 获取相应通道云台协议类型,param(int *)
    SYSNETAPIPTZ_CMD_SETPROTOCOL,   // 配置相应通道云台协议类型,param(int)
    SYSNETAPIPTZ_CMD_GET_PATTERN,   // 获取相应通道云台协议是否支持轨迹巡航,param(int)

    SYSNETAPIPTZ_CMD_STOP = CMDNO(PTZ_CMD_START, COMP_PTZ),
    SYSNETAPIPTZ_CMD_UP,            // 上
    SYSNETAPIPTZ_CMD_DOWN,          // 下
    SYSNETAPIPTZ_CMD_LEFT,          // 左
    SYSNETAPIPTZ_CMD_RIGHT,         // 右
    SYSNETAPIPTZ_CMD_FOCUS_INC,     /* 聚焦+ */
    SYSNETAPIPTZ_CMD_FOCUS_DEC,     /* 聚焦- */
    SYSNETAPIPTZ_CMD_IRIS_INC,      /* 光圈+ */
    SYSNETAPIPTZ_CMD_IRIS_DEC,      /* 光圈- */
    SYSNETAPIPTZ_CMD_ZOOM_INC,      /* 缩放+ */
    SYSNETAPIPTZ_CMD_ZOOM_DEC,      /* 缩放- */
    SYSNETAPIPTZ_CMD_F1,            // 辅助
    SYSNETAPIPTZ_CMD_F1_1,
    SYSNETAPIPTZ_CMD_F2,            // 辅助
    SYSNETAPIPTZ_CMD_F2_1,
    SYSNETAPIPTZ_CMD_AUTO,          // 自动
    SYSNETAPIPTZ_CMD_AUTO_1,
    SYSNETAPIPTZ_CMD_PRESET_SET,    // 预置
    SYSNETAPIPTZ_CMD_PRESET_GET,    // 调用
    SYSNETAPIPTZ_CMD_SETUP,
    SYSNETAPIPTZ_CMD_ENTER,
    SYSNETAPIPTZ_CMD_PAGEUP,
    SYSNETAPIPTZ_CMD_PAGEDOWN,
    SYSNETAPIPTZ_CMD_BRUSH,         // 雨刷
    SYSNETAPIPTZ_CMD_LEFT_UP,       //24左上
    SYSNETAPIPTZ_CMD_LEFT_DOWN,     //25左下
    SYSNETAPIPTZ_CMD_RIGHT_UP,      //26右上
    SYSNETAPIPTZ_CMD_RIGHT_DOWN,    //27右下
    SYSNETAPIPTZ_CMD_PRESET_CLR,    //28预置点清除
    SYSNETAPIPTZ_CMD_SET_PATTERN_START, //29轨迹巡航--设置开始
    SYSNETAPIPTZ_CMD_SET_PATTERN_END,   //30轨迹巡航--设置结束
    SYSNETAPIPTZ_CMD_SET_PATTERN_RUN,   //31轨迹巡航--运行

} PT_PTZCMD_E;

typedef struct
{
    int cmd;            //云台控制命令详见PT_PTZCMD_E
    int param;          //设置参数
} PT_PTZCTRL_S, *PPT_PTZCTRL_S;

typedef enum
{
    PT_SCENE_CUSTOM = 0,
    PT_SCENE_STANDARD = 1,
    PT_SCENE_INDOOR = 2,
    PT_SCENE_OUTDOOR = 3,
    PT_SCENE_STONG_LIGHT = 4,
    PT_SCENE_WEAK_LIGHT = 5,
} PT_SYSCOLOR_SCENE_E;

/* 当值为0xFFFF 时表示该项不支持 */
typedef struct
{
    uint32 bright;      /* 亮度0-100 */
    uint32 contrast;    /* 对比度0-100 */
    uint32 saturation;  /* 饱和度0-100 */
    uint32 hue;         /* 色度0-100 */
    uint32 sharp;       /* 锐度 0-100 */
} PT_SYSCOLOR_S, *PPT_SYSCOLOR_S;

typedef struct
{
    uint16 year ;       //年 如2009
    uint16 month ;      //月 1-12
    uint8   day ;       //日 1-31
    sint8   hour ;      //小时 0-23
    sint8   minute ;    //分钟 0-59
    sint8   second ;    //秒 0-59
    sint32 msec;        //毫秒
} PT_TIME_S, *PPT_TIME_S;

typedef enum
{
    PT_WEEK_SUN,        //星期日
    PT_WEEK_MON,        //星期一
    PT_WEEK_TUES,       //星期二
    PT_WEEK_WED,        //星期三
    PT_WEEK_THUR,       //星期四
    PT_WEEK_FRI,        //星期五
    PT_WEEK_SAT,        //星期六
} PT_WEEK_E;

typedef struct
{
    PT_TIME_S time;
    PT_WEEK_E week;     //星期   获取时有用
} PT_SYSTIME_S, *PPT_SYSTIME_S;

typedef enum
{
    PT_TYPE_PRI = 0,        //主码流
    PT_TYPE_SEC = 1,        //子码流
} PT_STREAMTYPE_E;

typedef enum
{
    PT_DISABLE = 0,         //关闭
    PT_ENABLE = 1,          //开启
} PT_ENABLE_E;
typedef struct
{
    PT_STREAMTYPE_E  type;
    PT_ENABLE_E          enable;
} PT_ENCSTATUS_S, *PPT_ENCSTATUS_S;

typedef struct
{
    PT_STREAMTYPE_E  type;
    sint32 user_handle;
} PT_VIDEOTYPE_S;
typedef enum
{
    PT_AUTOMODE,        //自适应
    PT_HALFMODE_10M,    //10M半双工
    PT_FULLMODE_10M,    //10M全双工
    PT_HALFMODE_100M,   //100M半双工
    PT_FULLMODE_100M ,  //100M全双工
    PT_FULLMODE_1000M   //1000M全双工
} PT_NETMODE_E;
typedef struct
{
    uint32 enable;
    uint32 ip_addr;
    uint16 port[MAX_CH]; // 多播端口
} PT_MULTICAST_S, *PPT_MULTICAST_S;
typedef struct
{
    sint8 type[MAX_STRING]; //网卡类型 区别各个网卡
    uint32 ip ;             //dvr ip地址
    uint32 mask ;           //dvr子码掩码
    uint32 gateway ;        //网关
    uint32 dns[2];          //DNS
    uint8 mac_addr[8];      //物理地址
    PT_NETMODE_E phy_mode;  //网卡工作模式
    uint32 dhcp_enable;     //dhcp使能
    uint32 ip_reserve;      //备用ip地址
    uint32 mask_reserve;    //备用子码掩码
    uint32 gateway_reserve; //备用网关
    uint32 dns_reserve[2];  // 备用DNS
    sint32 dhcpflag;        //获取的时候有效:0-表示本ip是手动设置的ip, 1-表示本ip是自动获取的ip, 2-表示本ip是备用ip
    uint16 cmdport;             //主机命令端口
    uint16 httpport;            //主机http端口
    uint16 rtmpport;            //主机rtmp端口
    PT_MULTICAST_S  multicast;  //多播配置
} PT_IPCONFIG_S, *PPT_IPCONFIG_S;

/* 多网卡模式 */
typedef enum
{
    PT_ETH_BOND_BALANCE_RR = 0,       /* 负载均衡 */
    PT_ETH_BOND_ACTIVE_BACKUP = 1,    /* 主从复用 */
    PT_ETH_BOND_ADDR_SETTING = 2,     /* 多址设定 */
} PT_ETH_BOND_MODE_E;

typedef struct
{
    PT_LIST_S speed_mode;   /* 速率双工模式 */
    PT_LIST_S bond_mode;    /* 绑定模式 PT_ETH_BOND_MODE_E */
}PT_ETH_LIST_S;

typedef struct
{
    sint8 host_name[MAX_STRING];
    PT_IPCONFIG_S  ip_config;
    uint16 cmdport;             //主机命令端口---此参数已经无效，已经调整到　PT_IPCONFIG_S结构体体请知悉
    uint16 httpport;            //主机http端口---此参数已经无效，已经调整到　PT_IPCONFIG_S结构体体请知悉
    PT_MULTICAST_S  multicast;  //多播配置    ---此参数已经无效，已经调整到　PT_IPCONFIG_S结构体体请知悉
    PT_IPCONFIG_S  sec_ip_config;
    sint32 muti_work_mode;//双网卡工作模式          见PT_ETH_BOND_MODE_E                新增参数　双网卡模式下有效
    sint32 muti_def_route;//双网卡默认路由　0---主网卡路由eth0　 1---次网卡eth1路由  新增参数　双网卡模式下有效
    sint32 muti_pri_net_card;//双网卡默认主网卡　　0---主网卡　 1---次网卡  　　　　 新增参数　双网卡模式下有效
} PT_NETCONFIG_S, *PPT_NETCONFIG_S;
typedef struct
{
    char    ftp_server[PT_MAX_ADDR_STR];//ftp服务器地址
    char    ftp_usr[MAX_STRING];        //ftp用户名
    char    ftp_pwd[MAX_STRING];        //ftp密码
    char    ftp_path[PT_MAX_ADDR_STR];  //ftp文件路径
    sint32  ftp_port;                   //ftp端口号
    uint32  reserve;
} PT_FTPCONFIG_S, *PPT_FTPCONFIG_S;

typedef enum
{
    PT_AUTO_DISABLE,    //不自动连接
    PT_AUTO_ENABLE,     //自动连接
} PT_AUTOENABLE_E;

typedef enum
{
    PT_SAVEPWD_DISABLE, //不保存密码
    PT_SAVEPWD_ENABLE,  //保存密码
} PT_SAVEPWD_E;

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

typedef enum
{
    PT_WIRELESS_PPPOE, //PPPOE
    PT_WIRELESS_3G, //3g
} PT_WIRELESS_E;


typedef enum
{
    PT_NETSTD_TYPE_ETH0 = 0,        //有线拨号
    PT_NETSTD_TYPE_WCDMA ,          // 联通WCDMA
    PT_NETSTD_TYPE_CDMA2000_EVDO,   //电信CDMA2000-EVDO
    PT_NETSTD_TYPE_CDMA1x,          //电信CDMA1x
    PT_NETSTD_TYPE_TD_CDMA,         //移动TD-CDMA
    PT_NETSTD_TYPE_GPRS,
} PT_NETSTD_TYPE_E;

typedef struct
{
    uint8 user[MAX_STRING];         // 用户名
    uint8 pwd[MAX_STRING];          // 密码
    PT_AUTOENABLE_E auto_connect;   // 是否自动连接
    PT_SAVEPWD_E save_pwd;          //是否保存密码
    PT_SUCCESS_E status;            // 是否解析成功
    PT_CONNECT_E command;
    PT_IPCONFIG_S ip_config;
    PT_WIRELESS_E wireless_en;      //无线使能
    PT_NETSTD_TYPE_E   net_std;     //网络制式
    uint8   apn[MAX_STRING];		// APN
    uint8	dailnum[MAX_STRING];	// 拨号号码
} PT_PPPOECONFIG_S, *PPT_PPPOECONFIG_S;

typedef struct
{
    sint32  index;                      //ddns索引
    uint8   server[MAX_STRING];         // 当前服务器地址
    uint8   user[MAX_STRING];           // 用户名
    uint8   pwd[MAX_STRING];            // 密码
    uint8   dn[MAX_DNS * MAX_STRING];   // 解析的地址 可支持返回最多4个DNS域名
    uint32  ip_addr;                    // 服务器返回的IP地址
    PT_AUTOENABLE_E auto_connect;       // 是否为自动连接
    PT_SUCCESS_E    status;             // 是否解析成功
    PT_CONNECT_E    command;            // 连接动作
    uint8   dn_set[PT_MAX_LINE];        // 设置域名(有些域名服务器需要设定域名，或者多个域名时指定一个时用)
    uint32  gui_get_flag;               //值为1，表示直接将从状态机获取的多个解析地址放在dn_set里，传给GUI
    uint16  domain_default_flag;        // 域名默认非默认标志位，0为默认，1为非默认
    uint16	iterm_num;
    uint8   list_iterm[12][MAX_STRING]; //支持服务器的个数以及服务器列表，当前服务器索引
} PT_DDNSCONFIG_S, *PPT_DDNSCONFIG_S;

typedef enum
{
    PT_WEPTYPE_UNABLE,  //unable
    PT_WEPTYPE_64B,     //64bit
    PT_WEPTYPE_128B,    //128bit
    PT_WEPTYPE_152B,    //152bit
} PT_WEPTYPE_E, *PPT_WEPTYPE_E;

typedef struct
{
    char wlan_enable;           //0-未启用，1-已启用
    char ssid_connected;        //当wlan_enable==1时有效，0-没有连接上ap，1-表示已经连接上ap
    uint8 ssid[PT_MAX_SSID_LEN];//SSID号
    uint8 wirelessIP[16];       //无线ip
    uint32 wpa_set;             //wpa安全类型设置
    PT_WEPTYPE_E wep_type;
    uint8 psw[PT_MAX_PSK_LEN];
} PT_WIFICONFIG_S, *PPT_WIFICONFIG_S;

typedef struct
{
    char wlan_enable;//0-未启用，1-已启用
    char ssid_connected;//当wlan_enable==1时有效，0-没有连接上ap，1-表示已经连接上ap
    char ssid[PT_MAX_SSID_LEN];// 已经连上的ap的ssid，ssid最大长度是32，加上结束符共33个字节，
} PT_WLAN_CFG_S, *PPT_PWLAN_CFG_S;

typedef struct
{
    char savepsk;
    //获取时，==0，表示该ssid未保存过密码，ssid、psk、auth_type都无效，
    // 			     ==1，表示后面三个参数有效
    //设置时，==0，表示删除ssid 的配置项
    // 			    ==1，表示保存配置并连接,如果之前已配置则更新配置
    // 			    ==2，表示进行连接
    char psk_status;  // 0-表示密码未保存，1-表示密码已保存
    char ssid[PT_MAX_SSID_LEN];// ssid最大长度是32，加上结束符共33个字节，
    char psk[PT_MAX_PSK_LEN];// 密码最大长度是64，加上结束符共65个字节，
    uint32 auth_type;//0-开放式，即无密码,1-wep，2-wpa/wpa2-psk
} PT_WIFI_CFG_S, *PPT_PWIFI_CFG_S;

typedef struct
{
    int signallevel;        //信号强度
    uint32 auth_type;       //安全性:0-开放式，即无密码,1-wep，2-wpa/wpa2-psk
    char ssid[MAX_STRING];  // ssid最大长度是32，加上结束符共33个字节
    char connect_state;     //连接状态，SSID_CONNECT_STA_E
    char psk_state;         //密码状态，0-未设置，1-已保存
    char wps_state;         //WPS状态，0-不可用，1-可用
    int connection_speed;   //连接速度
    uint8 bssid[8];
} PT_WIFIAP_CFG, *PPT_WIFIAP_CFG;

typedef struct
{
    int ssid_num;           //搜索到的ap个数
    PT_WIFIAP_CFG aplist[PT_MAX_WIFIAP_NUM]; //搜索到的ap列表，最大10个
} PT_WIFIAP_LIST_S, *PPT_WIFIAP_LIST_S;

/*******************UPNP***************/
typedef struct
{
    char lanip[20];
    char wanip[20];
} PT_ROUTE_S, *PPT_ROUTE_S;

typedef struct
{

    char server_name[MAX_STRING];		//转换端口名称
    uint8  port_status;			//端口映射状态状态
    uint8  port_enable;	        //单条端口映射是否要添加到路由器上使能开关
    uint8   reserve[2];
    uint16 dvr_port;		//DVR端口
    uint16 rount_port;		//路由器端口
    uint32 protocol;		//协议
} PT_UPNP_PORT_S, *PPT_UPNP_PORT_S;

typedef struct
{
    uint16          upnp_en;
    uint16          pat_count;				 //转换端口个数
    uint32  iaddr;             /*DVR IP*/
    uint32  gatewayip;         /*DVR 当前网关IP*/
    PT_ROUTE_S routerip;		   /*网关路由器地址*/
    PT_UPNP_PORT_S pat_info[MAX_PAT];	     //转换端口信息
} PT_UPNP_CONN_S, *PPT_UPNP_CONN_S;

/********************************************/


typedef struct
{
    uint32 minver; //阶段版本号
    uint32 secver; //子版本号
    uint32 majver; //主版本号
    PT_TIME_S time;//时间
    COMPID comp_type;
} PT_VERSION_S, *PPT_VERSION_S;

typedef enum
{
    PT_AUSTREAM_DISABLE,    //视频流
    PT_AUSTREAM_ENABLE,     //复合流
} PT_AUSTREAMADD_E;

typedef enum
{
    PT_QCIF     = 0, //QCIF,176×144
    PT_QQ960H   = 1,
    PT_QVGA     = 2, //QVGA,240×320
    PT_Q960H    = 3,
    PT_CIF      = 4, //CIF, 352*288/360*288
    PT_DCIF     = 5, //DCIF,704*288
    PT_HD1      = 6, //HD1,704*288/720*288
    PT_VGA      = 7, //VGA,640X480
    PT_FD1      = 8, //FD1,705*576
    PT_SD       = 9, //SD,
    PT_HD       = 10, //HD
    PT_960H     = 11,//960*576
    PT_720P     = 12,//1280×720
    PT_1080P    = 13,//1920×1080
    PT_960P     = 14,   /* 1280*960 130w万网络摄像机编码常用分辨率4:3 */
    PT_1024P    = 15,   /* 1280*1024 */
    PT_768x432  = 16,   /* 768*432 */
    PT_640x368  = 17,   /* 640*368 */
    PT_320x192  = 18,   /* 320*192 */
    PT_1920x960  = 19,   /* 1920*960 */
    PT_720x576  = 20,   /* 720*576 */
    PT_NONE     = 0xFF, /*针对某些IPC不常见分辨率过滤处理*/
    PT_MAX_RES     // PT_MAX
} PT_RESOLUTION_E;


/*vga HDMI分辨率*/
typedef enum
{
    PT_VGA_MOD_800x600      = 0,
    PT_VGA_MOD_1024x768     = 1,
    PT_VGA_MOD_1280x1024    = 2,
    PT_VGA_MOD_1440x900     = 3,
    PT_VGA_MOD_1280x720P    = 4,
    PT_VGA_MOD_1920x1080I   = 5,
    PT_VGA_MOD_1920x1080P   = 6 ,
    PT_VGA_MOD_3840x2160    = 7,
} PT_VGA_MOD_E;

typedef enum
{
    PT_RATE_30K    = 0,
    PT_RATE_45K    = 45,
    PT_RATE_60K    = 60,
    PT_RATE_75K    = 75,
    PT_RATE_90K    = 90,
    PT_RATE_100K   = 100,
    PT_RATE_128K   = 128,
    PT_RATE_256K   = 256,
    PT_RATE_512K   = 512,
    PT_RATE_768K   = 768,
    PT_RATE_1M     = 1024,
    PT_RATE_1536K  = 1536,
    PT_RATE_2M     = 2048,
    PT_RATE_3M     = 3072,
    PT_RATE_4M     = 4096,
    PT_RATE_5M     = 5120,
    PT_RATE_6M     = 6144,
    PT_RATE_7M     = 7168,
    PT_RATE_8M     = 8192,
    PT_RATE_9M     = 9216,
    PT_RATE_10M    = 10240,
    PT_RATE_11M    = 11264,
    PT_RATE_12M    = 12288,
} PT_RATE_MOD_E;

/*高清视频源类型*/
typedef enum
{
    PT_VIDEO_FORMAT_NO = 0,
    PT_VIDEO_1080P60 = 1,   //数字输入源,1920*1080 60帧.
    PT_VIDEO_1080P50,
    PT_VIDEO_1080P30,
    PT_VIDEO_1080P25,
    PT_VIDEO_1080P24,
    PT_VIDEO_720P60,
    PT_VIDEO_720P50,
    PT_VIDEO_720P30,
    PT_VIDEO_720P25,
    PT_VIDEO_720P24,
    PT_VIDEO_PAL,
    PT_VIDEO_NTSC,
    PT_VIDEO_EXT = 13,
    PT_VIDEO_960H,          //模拟输入源,960*576
    PT_VIDEO_D1,            //720*576
    PT_VIDEO_NONE = 0xFF, /*针对某些IPC不常见分辨率过滤处理*/
    PT_VIDEO_MAX,
} PT_VIDEO_SRC_TYPE_E;

typedef enum
{
    PT_VIDEO_NOSIGNAL,
    PT_VIDEO_OK,
    PT_VIDEO_NOTSUPPORT,
    PT_NO_REFRESH,
} PT_VIDEO_STATUS;

typedef enum
{
    PT_MODE_SMART = 0,  /*智能模式*/
    PT_MODE_COMMON,     /*普通模式*/
    PT_MODE_HIK,        /*类海康模式*/
    PT_MODE_ZW,         /*类中维模式*/
    PT_MODE_YCX,        /*类研创新模式*/
} PT_IPC_MANAGE_MODE_E;


typedef struct
{
    sint16 width;
    sint16 height;
} PT_RES_S;

typedef struct
{
    PT_LIST_S vga_mod;              //主输出分辨率 (与通道无关) PT_VGA_MOD_E
    PT_LIST_S vga_sub_mod;          //sub输出分辨率 (与通道无关) PT_VGA_MOD_E
    /*INVALID*/
    PT_LIST_S resolution;           //本地视频分辨率 PT_RESOLUTION_E
    PT_LIST_S net_resolution;       //网络视频分辨率 PT_RESOLUTION_E
    PT_LIST_S snapshot_resolution;  //截图清晰度 PT_RESOLUTION_E
    /*INVALID*/
    PT_LIST_S phy_mode;             //网卡模式
} PT_COMMON_RANGE_S; //通用范围

#if 1 /*INVALID*/
typedef struct
{
    uint32 resolution;              //PT_RESOLUTION_E 传入参数

    PT_RANGE_S frame_rate;          //本地帧率
    PT_RANGE_S bit_rate;            //本地码率
    PT_LIST_S  bit_rate_list;       //本地码率列表 平台根据自己选择选择bit_rate和bit_rate_list其中一个

    PT_RANGE_S net_frame_rate;      //子码流帧率
    PT_RANGE_S net_bit_rate;        //子码流码率
    PT_LIST_S  net_bit_rate_list;   //子码流码率列表 平台根据自己选择选择net_bit_rate和net_bit_rate_list其中一个
} PT_ENCPARAM_RANGE_S; //与视频分辨率相关的编码参数的范围.
#endif

typedef struct
{
    int src_type;       //PT_VIDEO_SRC_TYPE_E
    int src_status;     //PT_VIDEO_STATUS
} PT_VIDEO_SRC_S;

typedef enum
{
    PT_BITRATE_CHANGE,   //变码率
    PT_BITRATE_NOCHANGE, //定码率
} PT_BITRATETYPE_E;

typedef enum
{
    PT_VQUALITY_BEST = 0, //最高
    PT_VQUALITY_BETTER, //较高
    PT_VQUALITY_GOOD,   //高
    PT_VQUALITY_NORMAL, //中
    PT_VQUALITY_BAD,    //低
    PT_VQUALITY_WORSE   //最低
} PT_VQUALITY_E;

typedef struct
{
    PT_AUSTREAMADD_E byStreamType;  //视频流类型
    PT_RES_S byResolution;          //视频分辨率
    PT_BITRATETYPE_E byBitrateType; //码率类型
    sint32 byPicQuality;            //图像质量
    uint32 dwVideoBitrate;          //视频码率 实际码率
    uint16 dwVideoFrameRate;        //帧率 PAL 2-30 N 2-30
    uint16 quant;                   //量化因子 1-31
    uint32 encode;                  //编码码流类型，h264\h265,PT_VIDEO_ENCODING_E
} PT_ENCCONFIG_S, *PPT_ENCCONFIG_S;

typedef enum
{
    SYENETAPI_REC_TYPE_UNKNOW = 0,
    SYENETAPI_REC_TYPE_MANUAL = 1,      //手动录像
    SYENETAPI_REC_TYPE_SCHEDULE = 2,    //定时录像
    SYENETAPI_REC_TYPE_MOTION = 4,      //移动录像
    SYENETAPI_REC_TYPE_ALARM = 8,       //报警录像
    SYENETAPI_REC_TYPE_CARD = 9,        //卡号录像
    SYENETAPI_PIC_TYPE_MANUAL = 0x11,   //图片-手动录像
    SYENETAPI_PIC_TYPE_SCHEDULE = 0x12, //图片-定时录像
    SYENETAPI_PIC_TYPE_MOTION = 0x14,   //图片-移动录像
    SYENETAPI_PIC_TYPE_ALARM = 0x18,    //图片-报警录像
    SYENETAPI_PIC_TYPE_ALLPIC = 0x1f,   //图片-所有
    SYENETAPI_PIC_TYPE_IP_INVALID =0xe0, //IP无效
    SYENETAPI_PIC_TYPE_STREAM_CLOSE =0xe1, //主子流关闭
    SYENETAPI_REC_TYPE_ALL = 0xff       //所有
} PT_RECTYPE_E;

typedef struct
{
    PT_STREAMTYPE_E streamtype; //要设置或者获取的码流类型
    PT_RECTYPE_E       rectype; //录像类型
    PT_ENCCONFIG_S enc;         //编码参数
} PT_STREAMENCPARAM_S, *PPT_STREAMENCPARAM_S;

typedef struct
{
    uint16 left; //起始点横坐标
    uint16 top; //起始点纵坐标
    uint16 width; //宽度
    uint16 height; //高度
} PT_AREA_S, *PPT_AREA_S;

typedef enum
{
    MASK_DISABLE = 0,   /* 禁用 */
    MASK_ALL,       /* 全屏蔽 */
    MASK_REAL,      /* 实时屏蔽 */
    MASK_RECORD,    /* 录像屏蔽 */
} PT_MASK_TYPE_E;

typedef struct
{
    PT_MASK_TYPE_E enable;  //视频区域屏蔽；
    sint32 num; 	//区域个数
    PT_AREA_S area[MAX_MASK];   /* 坐标以(10000*10000)的坐标系来传 */
} PT_MASKPARAM_S, *PPT_MASKPARAM_S;

typedef struct
{
    sint32 enable;              //视频特殊区域；0-禁用，1启用(特别关注区域是否显示)
    sint32 num;                 //区域个数
    PT_AREA_S area[MAX_MASK];
    sint32 type;                //特别关注区域类型
    sint32 value;               //特别关注区域值
} PT_SPECIALAREA_S, *PPT_SPECIALAREA_S;

typedef struct
{
    uint32 starth;  //开始小时
    uint32 startm;  //开始分钟
    uint32 endh;    //结束小时
    uint32 endm;    //结束分钟
} PT_TMPERIOD_S, *PPT_TMPERIOD_S;

typedef enum
{
    PT_STATUS_OFF,  //NO/OFF
    PT_STATUS_ON,   //YES/ON
} PT_STATUS_E;

typedef struct
{
    PT_STATUS_E bselect;                //0-no 1-yes
    PT_TMPERIOD_S period[MAX_PERIOD];   //布防时间
    uint32      seg_enable;             //缺省值为0，即获取和设置用period，当值为1时，用segment结构体。
    uint32      segment[3];             // 按位分割24小时，总共96位，每位的时间为15分钟
} PT_TMITEM_S, *PPT_TMITEM_S;

typedef struct
{
    uint32 bstatus : 1;         // 是否启用，0-禁用，1-启用
    uint32 force_enable : 1;    // 强制开关，0-关闭，1-打开；强制开关打开时，全天布防（时间段设置不起作用）
    uint32 reserve : 30;        // 保留位
    PT_TMITEM_S item[8];        // 0-7: everyday, monday...sunday
} PT_TMSCHEDULE_S, *PPT_TMSCHEDULE_S;

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

typedef struct
{
    PT_TMSCHEDULE_S schedule;   //布防时间设置
    uint16 almdelay;            //报警延时时间 缺省为0
    uint16 almoutsec;           //报警输出时间
    //PT_ENABLE_E forcestatus;  //强制报警输出状态
} PT_LINKOUTPARAM_S, *PPT_LINKOUTPARAM_S;

typedef struct
{
    uint16 recordtime;          //联动报警录像时间
    uint16 prerecordtime;       //预录时间
    //PT_TMSCHEDULE_S schedule; //布防时间设置
} PT_LINKRECPARAM_S, *PPT_LINKRECPARAM_S;

typedef struct
{
    uint32 stay_time;           //停留时间
    uint8 alm2preset[MAX_CH];   //联动跳预置点
    //PT_TMSCHEDULE_S schedule; //布防时间设置
} PT_LINKPRESETPARAM_S, *PPT_LINKPRESETPARAM_S;

typedef struct
{
    uint32 snaptimes;           //抓拍次数
    uint32 snaptimeval;         //抓拍间隔 以秒为单位
    //PT_TMSCHEDULE_S schedule; //布防时间设置
} PT_LINKSNAPPARAM_S, *PPT_LINKSNAPPARAM_S;

typedef struct
{
    uint32 almout[MAX_AMOUT];   //联动报警输出 关联的探头输出：0-不关联，1-关联
    uint32 record[MAX_CH];      //联动录像 关联的录像通道：0-不关联，1-关联
    uint32 presetenable[MAX_CH];//联动跳预置点
    uint32 snap[MAX_CH];        //联动抓拍
    /*INVALID*/
    uint32 local_record[MAX_CH];      //联动本地通道录像 关联的录像通道：0-不关联，1-关联
    uint32 ipc_record[MAX_CH];      //联动IPC通道录像 关联的录像通道：0-不关联，1-关联
    uint32 local_presetenable[MAX_CH];//本地通道联动跳预置点
    uint32 ipc_presetenable[MAX_CH];//IPC通道联动跳预置点
    uint32 local_snap[MAX_CH];        //本地通道联动抓拍
    uint32 ipc_snap[MAX_CH];        //IPC通道联动抓拍
    /*INVALID*/
} PT_ALMLINKPLAN_S, *PPT_ALMLINKPLAN_S;

//整个主机预案配置参数
typedef struct
{
    PT_LINKOUTPARAM_S  almout[MAX_AMOUT];
    PT_LINKRECPARAM_S   rec[MAX_CH];
    PT_LINKPRESETPARAM_S  preset[MAX_AM];       //本地探头报警联动预置点
    PT_LINKPRESETPARAM_S  ipc_preset[MAX_CH];   //远程探头报警联动预置点
    PT_LINKPRESETPARAM_S  mv_preset[MAX_CH];    //移动报警联动预置点
    PT_LINKSNAPPARAM_S   snap[MAX_CH];      
} PT_PLANCONFIG_S, *PPT_PLANCONFIG_S;

typedef struct
{
    PT_TMSCHEDULE_S schedule;       //布防时间设置
    PT_ALMLINKPLAN_S plan;          //报警联动预案
    uint16 enalmmax;                //报警最大化实时窗口使能，主要针对探头报警及移动侦测报警
    uint8 almoutbuzzer;             //报警送蜂鸣器
    uint8 almoutaudio;              //报警声音输出使能
    //chanaged by ypxiao 1112
    uint8 mail_enable;             //报警邮件使能  0-关闭 1-开启
    uint8 alm_durative;             //持续报警标志 0-非持续报警，1-持续报警     //added by ypxiao 1112
    uint8 motion_area_show_en;      //移动检测区域是否显示
    uint8 motion_sen_show_en;       //移动检测灵敏度是否显示
} PT_MOTIONRECPARAM_S, *PPT_MOTIONRECPARAM_S;

typedef struct
{
    uint32 sensitivity;             /* 移动侦测灵敏度 PT_SENSITIVITY_E*/
    uint32 block[18];               /* 移动侦测块设置侦测区域 22*18格子 */
} PT_IPCMOTIONRULES_S;

typedef struct
{
    sint32 col;
    sint32 row;
    uint32 blk_num;                 /* 移动块个数*/
    uint32 block[18];               /* 移动侦测块区域 22*18格子 */
} PT_IPCSMARTMOTION_S;

typedef struct
{
    PT_ALMLINKPLAN_S plan;          //报警联动预案
    uint16 reserve;                 //保留
} PT_ATMCARDRECPARAM_S, *PPT_ATMCARDRECPARAM_S;

typedef struct
{
    uint8  almin_name[MAX_STRING];  //探头名
    uint16 enalmmax;                //报警最大化实时窗口使能，主要针对探头报警及移动侦测报警
    uint8 almoutbuzzer;             //报警送蜂鸣器
    uint8 almoutaudio;              //报警声音输出使能
    PT_ALMTYPE_E almtype;           //探头类型 0-常闭 1-常开
    PT_TMSCHEDULE_S schedule;       //布防时间配置
    PT_ALMLINKPLAN_S plan;          //报警联动预案
    uint16 mail_enable;             //报警邮件使能  0-关闭 1-开启
    uint16 almin_attr;              //探头属性  0-本地 1-远程
} PT_ALARMINRECPARAM_S, *PPT_ALARMINRECPARAM_S;

typedef struct
{
    sint32 almtype;           //探头类型 0-常闭 1-常开 PT_ALMTYPE_E
    sint32 reserve[3];
} PT_IPCALARMINRECPARAM_S, *PPT_IPCALARMINRECPARAM_S;

typedef struct
{
    uint32            second : 6;   // 秒: 0~59
    uint32            minute : 6;   // 分: 0~59
    uint32            hour : 5;     // 时: 0~23
    uint32            day : 5;      // 日: 1~31
    uint32            month : 4;    // 月: 1~12
    uint32            year : 6;     // 年: 2000~2063
} PT_MFSTIME_S, *PPT_MFSTIME_S;

typedef struct
{
    PT_MFSTIME_S  begin_time, end_time; //查询开始时间，结束时间
    uint32 lengh;                       //单位:字节
    uint8 ch;                           //通道名
    uint8 type;                         //录像类型
#if 1
    uint8 dev_type;						//设备类型
    uint8 dev_num;						//设备号
    uint8 use_stat;						//使用状态
#endif
} PT_RECSEGINFO_S, *PPT_RECSEGINFO_S;

typedef struct
{
    PT_TIME_S time_bg, time_ed;     //查询开始时间，结束时间
    PT_RECTYPE_E type;              //录像类型
    PT_RECSEGINFO_S * data;         //录像段信息buffer
    uint32 start;                   //读取像段的起始号（从0开始）
    uint32 limit;                   //想读取的录像段数(buffer_length / sizeof(PLATFORM_Mfs_RecSeg_Info))
    uint32 total_num;               //输出符合条件的录像段总数（output）
    uint32 realmum;                 //实际读出录像数量（output）
} PT_RECFILESEG_S, *PPT_RECFILESEG_S;

typedef struct
{
    sint32   channel;           //回放通道
    PT_TIME_S time;             //打开录像日期
    PT_RECTYPE_E type;          //打开录像类型
    uint32 openrec_handle;      //打开录像句柄(output)
} PT_SEGSTREAMREADOPEN_S, *PPT_SEGSTREAMREADOPEN_S;

typedef enum
{
    //放像控制命令
    SYSNETAPI_VOD_PLAY = 0,
    SYSNETAPI_VOD_PAUSE,
    SYSNETAPI_VOD_STOP,
    SYSNETAPI_VOD_FASTFORWARD,
    SYSNETAPI_VOD_SLOWFORWARD,
    SYSNETAPI_VOD_FASTBACKWARD,
    SYSNETAPI_VOD_SLOWBACKWARD, // 6
    SYSNETAPI_VOD_FRAMEFORWARD,
    SYSNETAPI_VOD_FRAMEBACKWARD,//帧退
    SYSNETAPI_VOD_SEEK,
    SYSNETAPI_VOD_TIMEJUMP,     //跳到指定时间
    SYSNETAPI_VOD_SPLITSET,     //该命令仅主机端有效 10
    SYSNETAPI_VOD_PIC_SPLITSET, //该命令仅主机端有效 10
    SYSNETAIP_VOD_PIC_PBTIME,   //图片自动播放时间间隔 11
    SYSNETAPI_VOD_PIC_FASTBACKWARD,//
    SYSNETAPI_VOD_PBPLAY_SPLITSET,
    SYSNETAPI_VOD_CHANNELJUMP,  //调到指定通道
} PT_PLAYBACKSTATUS_E;

typedef enum
{
    //放像速率
    SYSNETAPI_SPEED_2X,         //快放时为2倍快进 ,慢放时为1/2慢放
    SYSNETAPI_SPEED_4X,         //
    SYSNETAPI_SPEED_8X,
    SYSNETAPI_SPEED_16X,
} PT_PLAYBACKSPEED_E;

typedef union
{
    uint32  longtime;
    PT_MFSTIME_S fieldtime;
} PT_MFSTIME_U;

typedef struct
{
    PT_PLAYBACKSTATUS_E  status;
    uint32    param;//当status为SYSNETAPI_VOD_SEEK时param为0-99    当status为SYSNETAPI_VOD_TIMEJUMP时，param为PT_MFSTIME_U中的longtime参数
} PT_PLAYBACKPARA_S, *PPT_PLAYBACKPARA_S;

typedef enum
{
    //放像速率
    SYSNETAPI_READ_NORMAL = 0,
    SYSNETAPI_READ_FORWARD = 0x10,      // 关键帧进（不作为放像使用）
    SYSNETAPI_READ_FORWARD_1X = 0x11,   // 关键帧读出
    SYSNETAPI_READ_FORWARD_2X = 0x12,   // 2倍间隔关键帧读出
    SYSNETAPI_READ_FORWARD_3X = 0x13,   // 3倍
    SYSNETAPI_READ_FORWARD_4X = 0x14,   // 4倍
    SYSNETAPI_READ_FORWARD_5X = 0x15,   // 5倍
    SYSNETAPI_READ_BACKWARD = 0x20,     // 关键帧退（不作为放像使用）
    SYSNETAPI_READ_BACKWARD_1X = 0x21,  // 关键帧退
    SYSNETAPI_READ_BACKWARD_2X = 0x22,  // 2倍间隔关键帧退
    SYSNETAPI_READ_BACKWARD_3X = 0x23,  // 3倍
    SYSNETAPI_READ_BACKWARD_4X = 0x24,  // 4倍
    SYSNETAPI_READ_BACKWARD_5X = 0x25,  // 5倍
    SYSNETAPI_READ_SEEK = 0x40          // 读seek
} PT_READSPEED_E;

typedef struct
{
    uint32 openrec_handle;      //打开录像句柄
    PT_READSPEED_E speed;       //读数据速度
    uint32 size;                //读取数据大小buffer长度
    PT_TIME_S time;             //当前帧所在关键帧的所属时间(output)
    uint32 len;                 //实际读出的码流长度(output)
    sint8 * data;               //存放读书数据缓冲区地址(output)
} PT_ENCODESTREAMREAD_S, *PPT_ENCODESTREAMREAD_S;

typedef struct
{
    uint32 openrec_handle;      //打开录像句柄
    PT_READSPEED_E speed;       //读数据速度
    uint32 size;                //读取数据大小buffer长度
    uint32 percent;             //当speed == SYSNETAPI_READ_SEEK , 用此值定义定位百分比(0~99)
    uint32 len;                 //实际读出的码流长度(output)
    sint8 * data;               //存放读出数据缓冲区地址(output)
} PT_ENCODESTREAMREADSEG_S, *PPT_ENCODESTREAMREADSEG_S;

typedef enum
{
    PT_SHOW_DISABLE,            //不显示
    PT_SHOW_ENABLE,             //显示
} PT_SHOW_E;

typedef enum
{
    PT_DATE_YMD1 = 0,           // YYYY/MM/DD
    PT_DATE_MDY1 = 1,           // MM/DD/YYYY
    PT_DATE_DMY1 = 2,           // DD/MM/YYYY
    PT_DATE_YMD2 = 3,           // YYYY.MM.DD
    PT_DATE_MDY2 = 4,           // MM.DD.YYYY
    PT_DATE_DMY2 = 5,           // DD.MM.YYYY
    PT_DATE_YMD3 = 6,           // YYYY-MM-DD
    PT_DATE_MDY3 = 7,           // MM-DD-YYYY
    PT_DATE_DMY3 = 8,           // DD-MM-YYYY
} PT_DATEFORMAT_E;

typedef enum
{
    PT_TIME_24HOUR,         // 24小时制
    PT_TIME_12HOUR,         // 12小时制
} PT_TIMEFORMAT_E;

typedef struct
{
    sint32 date_format;     /* PT_DATEFORMAT_E */
    sint32 time_format;     /* PT_TIMEFORMAT_E */
} PT_TIME_CFG_S;

typedef enum
{
    CUSTOM      = 0,    /*坐标*/
    UPPERLEFT   = 1,    
    UPPERRIGHT  = 2,
    LOWERLEFT   = 3,
    LOWERRIGHT  = 4,
} PT_OSD_POSTYPE_E;

typedef struct
{
    PT_SHOW_E en_title;     // 1-显示OSD名0-不显示
    uint8 title[PT_MAX_STRING_EXT];// OSD名
    sint32 pos_type;        //OSD位置类型，PT_OSD_POSTYPE_E
    PT_AREA_S pos_title;    //OSD名的坐标信息，pos_type = 0 时有效
} PT_OSDATTRI_S, *PPT_OSDATTRI_S;

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

typedef struct
{
    PT_OSDATTRI_S osd[MAX_OSD_NUM];

    uint16  osdnum;          //osd数目
    uint16  osdattrib;      //OSD属性0-不透明 1 -透明
    uint16  format_date;         //日期格式 如果有日期OSD则该参数有用,PT_DATEFORMAT_E
    uint16  format_time;         //时间显示格式 如果有日期OSD则该参数有用,PT_TIMEFORMAT_E
    PT_SHOW_E en_week;          //是否显示星期 如果有日期OSD则该参数有用
    uint8   en_src_type;        /* 是否显示视频源信息,如960H,1080p等 */
    uint8   en_atm_type;		/* 是否ATM机型，ATM机型 osd[1].title 设置为 通道名+'&'+卡号*/
    uint8   refresh_osd;        /* 是否刷新osd 0-默认刷新  1-不刷新*/
    uint8   reserve[1];         /* 保留位 */
    PT_SHOW_E en_logo_watermark;			// 是否使能OSD前叠加logo水印图片
    PT_AREA_S pos_logo_watermark;    		//logo水印图片的坐标信息
} PT_OSDPARAM_S, *PPT_OSDPARAM_S;

typedef struct
{
    uint16 enalmmax;            // 1-senor or move alarm to chang one real window
    uint8 almoutbuzzer;         //报警送蜂鸣器
    uint8 almoutaudio;          //报警声音输出使能
    PT_ENABLE_E enable;         // 视频丢失报警使能
    PT_ALMLINKPLAN_S plan;      //报警联动预案
    uint32 mail_enable;         //报警邮件使能  0-关闭 1-开启
} PT_VLOSTLINKPLAN_S, *PPT_VLOSTLINKPLAN_S;
typedef struct
{
    uint32 ch_host;             //用来对应唯一主机 input
    PT_TIME_S date;             //查询日志时间input
    uint32 totalnum;            //查询指定时间内的日志总数output
} PT_QUERYLOGNUM_S, *PPT_QUERYLOGNUM_S;

typedef enum
{
    PT_PRI_OPERATE, // 操作
    PT_PRI_ALARM,   // 报警
    PT_PRI_ERROR,   // 异常
    PT_PRI_MAX,
} PT_PRITYPE_E;
typedef enum
{
    PT_OP_PTZ,              // 云台控制   0
    PT_OP_PLAYBACK,         // 回放1
    PT_OP_UPGRADE,          // 升级2
    PT_OP_TALKBACK_START,   // 对讲开始3
    PT_OP_TALKBACK_STOP,    // 对讲结束4
    PT_OP_GETSTATUS,        // 获取状态5
    PT_OP_SETCONFIG,        // 配置6
    PT_OP_GETCONFIG,        // 获取配置7
    PT_OP_TRANSCOM_OPEN,    // 建立透明通道8
    PT_OP_TRANSCOM_CLOSE,   // 断开透明通道9
    PT_OP_RECORD_START,     // 启动录像10
    PT_OP_RECORD_STOP,      // 停止录像11
    PT_OP_LOGIN,            // 登陆12
    PT_OP_LOGOUT,           // 注销13
    PT_OP_SETTIME,          // 设置系统时间14
    PT_OP_SHUTDOWN,         // 关机15
    PT_OP_REBOOT,           // 重启16
    PT_OP_POWERON,          // 开机17
    PT_OP_FORMAT_DISK,      // 格式化硬盘18
    PT_OP_DEFAULT,          // 恢复缺省19
    PT_OP_CLR_ALARM,        // 清除报警20
    PT_OP_BACKUP,           // 备份21
    PT_OP_STREAM_OPEN,      // 开启网络预览22
    PT_OP_STREAM_CLOSE,     // 关闭网络预览23
    PT_OP_ARMING,           // 布防
    PT_OP_DISARMING,        // 撤防
    PT_OP_MAILUPLOAD_SUCCE, // 邮件上传成功
    PT_OP_MAILUPLOAD_ERROR, // 邮件上传失败
    PT_OP_FILE_LOCK,        // 锁定文件
    PT_OP_FILE_UNLOCK,      // 解锁文件
    PT_OP_FILE_DELETE,      // 删除文件
    PT_OP_SNAPSHOT_START,   // 开始截图  31
    PT_OP_SNAPSHOT_STOP,    // 开始截图  32
    PT_OP_TIME_BACKUP,      //定时备份
    PT_OP_TIME_REBOOT,      //定时重启
    PT_OP_ALARM_MANUAL,     //  手动报警

    PT_OP_PLAYBACK_CUT,        // 回放剪辑
    PT_OP_RAID_CREATE,         /* RAID盘创建 */
    PT_OP_RAID_DEL,            /* RAID盘删除 */
    PT_OP_REBUILD,			  /* RAID盘重建 */
    PT_OP_HD_PLUGIN,           /* 磁盘插入 40*/
    PT_OP_HD_PLUGOUT,           /* 磁盘拔出 41*/
    PT_OP_NTP_SETSUC,           /* NTP校时成功 42*/
    PT_OP_IPC_SEARCH,			/* IPC查找 */
    PT_OP_IPC_ADD,           /* IPC添加 */
    PT_OP_IPC_EDIT,		    /* IPC编辑 */
    PT_OP_IPC_DEL,		        /* IPC删除 */
    PT_OP_IPC_STREAM_OPEN,     /* ipc流开启 */
    PT_OP_IPC_STREAM_CLOSE,    /* ipc流断开 */
    PT_OP_BAOXIU,        //深广 用户报修信息上传 41
    PT_OP_WEIXIU,		//深广  维修信息上传 42
    PT_OP_WEIBAO,		//深广  维保信息上传43
    PT_OP_TESTPIC_UPLOAD,			//深广  测试图片上传44
    PT_OP_BAOYANGPIC_UPLOAD,		//深广  保养图片上传45
    PT_OP_YANSHOUPIC_UPLOAD,		//深广  验收图片上传46
    PT_OP_ALMLINKPIC_UPLOAD,		//深广  报警联动图片上传47
    PT_OP_DAILYPIC_UPLOAD,			//深广	日常图片上传  48
    PT_OP_TYPE_MAX,         //24
} PT_OPERATETYPE_E;

typedef enum
{
    PT_ALM_SENSORIN,        // 报警输入
    PT_ALM_SENSOROUT,       // 报警输出
    PT_ALM_MOTION_START,    // 移动侦测开始
    PT_ALM_MOTION_STOP,     // 移动侦测结束
    PT_ALM_CARDID_START,    // 卡号录像开始
    PT_ALM_CARDID_STOP,     // 卡号录像结束
    PT_ALM_PTZ_OPERATE,     // 云台操作
    PT_ALM_MAIL_UPLOAD,     // 邮件上传

    PT_ALM_ATMI_FACE_BLOCK,         //人脸遮挡
    PT_ALM_ATMI_FACE_UNUSUAL,       //人脸异常

    PT_ALM_ATMI_PANEL_BLOCK,        //面板遮挡
    PT_ALM_ATMI_PANEL_PASTE,        //贴条
    PT_ALM_ATMI_PANEL_KEYBOARD,     //装假键盘
    PT_ALM_ATMI_PANEL_KEYMASK,      //破坏密码防护罩
    PT_ALM_ATMI_PANEL_CARDREADER,   //破坏读卡器
    PT_ALM_ATMI_PANEL_TMIEOUT,      //超时报警

    PT_ALM_ATMI_MONEY_UNUSUAL,      //加钞间异常,即有人闯入加钞间

    PT_ALM_ATMI_ENVI_GATHER,        //多人聚集
    PT_ALM_ATMI_ENVI_MANYPEOPLEINREGION,    //违规取款
    PT_ALM_ATMI_ENVI_LINGERING,             //人员徘徊
    PT_ALM_ATMI_ENVI_LIEDOWN,               //人员倒地
    PT_ALM_ATMI_ENVI_FORBIDREGION,          //非法进入警戒区
    PT_ALM_ATMI_ENVI_LEAVEOBJECT,           //物品遗留
    PT_ALM_RAID_DEGRADE,                   /* 降级 */
    PT_ALM_TYPE_MAX,
} PT_ALARMMTYPE_E;

typedef enum
{
    PT_ERR_VIDEOLOST,       // 视频丢失
    PT_ERR_HD_ERROR,        // 磁盘错误
    PT_ERR_HD_FULL,         // 磁盘满
    PT_ERR_LOGIN_FAIL,      // 登陆失败
    PT_ERR_FIFO_ERROR,      // 缓冲错误
    PT_ERR_TEMP_HI,         // 温度过高
    PT_ERR_HD_PFILE_INDEX,  // 磁盘主索引错误
    PT_ERR_HD_DEV_FATAL,    // 磁盘设备致命错误
    PT_ERR_VIDEO_COVER,     // 视频遮挡
    PT_ERR_HD_RW_SLOW,     /* 磁盘速度慢 */
    PT_ERR_HD_LINK_ERR,  /* 磁盘链接错误*/
    PT_ERR_HD_IDX_ERR, /*  主索引文件异常*/
    PT_ERR_HD_IDX_ADX_ERR, /*主辅索引异常 */
    PT_ERR_HD_LOG_ERR, /* 日志文件异常 */
    PT_ERR_TYPE_MAX,
} PT_ERRORTYPE_E;

typedef enum
{
    PT_PAR_START,           // 操作开始
    PT_PAR_COMMON,          // 通用设置
    PT_PAR_MANUAL,          // 手动录像
    PT_PAR_TIME,            // 定时录像
    PT_PAR_MOTION,          // 移动录像
    PT_PAR_SENSOR,          // 探头报警
    PT_PAR_CHCONFIG,        // 通道配置
    PT_PAR_NTP,             // NTP配置
    PT_PAR_NETWORK,         // 网络配置
    PT_PAR_PPPOE,           // PPPOE配置
    PT_PAR_DDNS,            // DDNS配置
    PT_PAR_ALARM_SERV,      // 报警服务器
    PT_PAR_CMS_SERV,        // CMS服务器
    PT_PAR_UART,            // 串口设置
    PT_PAR_PTZ,             // 云台配置
    PT_PAR_ACCOUNT,         // 账户管理
    PT_PAR_OSD,             // OSD配置
    PT_PAR_POLL,            // 轮训配置
    PT_PAR_VENC,            // 编码参数
    PT_PAR_CARDID_REC,      // 卡号录像
    PT_PAR_ALARM_LINKAGE,   // 报警联动
    PT_PAR_VMODE_MODIFY,    // 制式修改
    PT_PAR_SNAPSHOT_MANUAL, // 手动截图设置
    PT_PAR_SNAPSHOT_TIME, // 定时截图设置
    PT_PAR_SNAPSHOT_MOTION, // 移动截图设置
    PT_PAR_SNAPSHOT_ALARM, // 报警截图设置
    PT_PAR_HDD_GROUP, // 硬盘分组
    PT_PAR_REC_GROUP, // 录像分组
    PT_PAR_COMPLEX, // 复合通道设置
    PT_PAR_ADVANCE, // 存储高级设置
    PT_PAR_EMAIL_SET,       // 邮件设置
    PT_PAR_INPUT,           // 输入源配置
    PT_PAR_REBUILD_START,     /* 开始重建 */
    PT_PAR_REBUILD_DONE,        /* 重建完成 */
    PT_PAR_ESATA_MODIFY,
    PT_PAR_TYPE_MAX,
} PT_PARAMTYPE_E;

typedef struct
{
    PT_MFSTIME_S time;  // 记录日志时间
    uint8 pri_type;     // 主类型
    uint8 sec_type;     // 次类型
    uint8 param;        // 操作类型
    uint8 channel;      // 通道号
    uint32 host;        // 0-主机 其他 –远程IP如0xc0a80006
    uint8 user[17];     // 用户名
    uint8 hard_driver;  // 硬盘号
    uint8 sensor_in;    // 报警输入
    uint8 sensor_out;   // 报警输出
    uint8 reserve[32];  // 保留
} PT_LOGINFO_S, *PPT_LOGINFO_S;

typedef struct
{
    PT_MFSTIME_S time;  // 记录日志时间
    uint16 pri_type;     // 主类型
    uint16 sec_type;     // 次类型
    uint8 segconf[8];     //MFS_SEGCONF_S segconf;      /* segconf */
    sint16 channel;
    uint8 rev_key[24];          /* 保留关键字 */
    uint8 area_flag[PT_MAX_INTEL_BLOCK_NUM];
    uint8 ref_reserve[36];          /* 保留位 */
} PT_INTEL_LOGINFO_S, *PPT_INTEL_LOGINFO_S;     /*扩展日志专用，多留些保留位方便后续扩展 128字节*/

typedef enum
{
    PT_DEVTYPE_NULL,           /* Null device */
    PT_DEVTYPE_IDE,            /* IDE hard or SATA hard disk */
    PT_DEVTYPE_RAM,            /* RAM disk */
    PT_DEVTYPE_FLASH,          /* Flash memory */
    PT_DEVTYPE_SD,             /* SD Card */
    PT_DEVTYPE_USB,            /* USB host device */
    PT_DEVTYPE_CDDVD,          /* CDDVD Rom */
    PT_DEVTYPE_ESATA,          /* ESATA device */
    PT_DEVTYPE_NETWORK,        /* network device */
    PT_DEVTYPE_MAX
} PT_DEVTYPE_E;

typedef struct
{
    uint32 ch_host;     //用来对应唯一主机 input
    PT_TIME_S date;     //查询日志时间input
    uint16 start;       //起始
    uint16 limit;       //想要获取日志的条数(info的大小 /sizeof(PT_LOGINFO_S)) input
    uint32 realnum;     //读出的实际日志数  (output)
    uint32 total_num;   //
    sint16  pri_type;   // 主类型
    sint16  sec_type;   // 辅类型
    sint16  dev_no;     // 设备序号
    sint16  dev_type;   // 设备类型 ,见PT_DEVTYPE_E input
    PT_LOGINFO_S * info; //日志具体信息(output)
} PT_QUERYLOGINFO_S, *PPT_QUERYLOGINFO_S;

typedef enum
{
    PT_RECOVERMODE_MANU,
    PT_RECOVERMODE_AUTO,
} PT_RECOVERMODE_E;
typedef struct
{
    uint32 ch_host;     //用来对应唯一主机 input
    uint32 covermode;	//录像覆盖方式 1-自动、0-手动
    uint32 reserve; 	/* 保留位 */
} PT_RECCOVERMODE_S, *PPT_RECCOVERMODE_S;

/*typedef enum
{
    PT_DEV_NORMAL,      //正常
    PT_DEV_DISK_ERROR,  //磁盘错误
    PT_DEV_FS_FAILED    //文件系统出错
}PT_DEVSTATUS_E;*/

typedef enum
{
    PT_DEVSTAT_NORMAL   = 0x00, // 设备工作正常状态
    PT_DEVSTAT_STANDBY  = 0x01, // 设备处于待命状态(用PT_DEVSTAT_NORMAL可立即唤醒硬盘)
    PT_DEVSTAT_SLEEP    = 0x02, // 设备处于睡眠状态(用PT_DEVSTAT_NORMAL并不能立即唤醒硬盘,只有真正读写硬盘时才去唤醒)----暂时未使用这个方式
    PT_DEVSTAT_ERROR    = 0x03, // 设备处于错误状态
} PT_DEVSTATUS_E;

typedef enum
{
    PT_DEV_RAID_NORMAL,     // raid 正常
    PT_DEV_RAID_DEGRED,     // raid 降级
    PT_DEV_RAID_REBUILDING, // raid 重建
    PT_DEV_RAID_BROKEN,     // raid 损坏
    PT_DEV_RAID_NO_RAID,    // raid 没有建立
    PT_DEV_RAID_UNKOWN      // NO USE STAUS NOW
} PT_RAIDSTATUS_E;

typedef enum
{
    PT_SYSCOLOR_PAL = 0, //PAL制式
    PT_SYSCOLOR_NTSC443 = 1,// NTSC4.43制式
    PT_SYSCOLOR_NTSC358 = 2, // NTSC3.58制式
} PT_SYSCOLOR_E;

typedef enum
{
    PT_STANDARD_H264,       //H.264
    PT_STANDARD_MPG4,       // MPG4
} PT_STANDARD_E;
typedef enum
{
    PT_LOGSIZ_32M,          // 32M
    PT_LOGSIZ_64M,          // 64M
    PT_LOGSIZ_128M,         // 128M
    PT_LOGSIZ_256M,         // 256M
    PT_LOGSIZ_512M,         // 512M
} PT_LOGSIZE_E;

typedef struct
{
    uint64 serial_num;      //主板序列号
    uint8 rec_port;         //录像通道数4;8;16
    uint8 rec_format;       //录像分辨率CIF;D1   PT_RESOLUTION_E
    uint8 rec_colorsystem;  //录像制式Ntsc;Pal  PT_SYSCOLOR_E
    uint8 rec_standard;     //录像压缩算法H264;MPG4   PT_STANDARD_E
    PT_TIME_S sys_time;     //系统最后访问磁盘时间
    uint8 log_size;         // PT_LOGSIZE_E
    uint8 esata_enable;     //esata设备位置使能  PT_ENABLE_E
    uint8 sys_hd_num;       //当前系统支持的最大硬盘数
    uint8 reserve1[5];      //保留
} PT_SYSINFO_S, *PPT_SYSINFO_S;
typedef enum
{
    PT_RAID_LEVEL_NULL,           /*未组成raid模式*/
    PT_RAID_LEVEL_0,              /*RAID 0*/
    PT_RAID_LEVEL_1,              /*RAID 1*/
    PT_RAID_LEVEL_2,              /*RAID 2*/
    PT_RAID_LEVEL_3,              /*RAID 3*/
    PT_RAID_LEVEL_4,              /*RAID 4*/
    PT_RAID_LEVEL_5,              /*RAID 5*/
    PT_RAID_LEVEL_10              /*RAID 10*/
} PT_Raid_Level_E;

#if 0
typedef struct
{
    uint8 Name[64];         //型号
    uint64 dev_capabilty;   //容量
} PT_RAIDDEVINFO_S, *PPT_RAIDDEVINFO_S;
#endif

/* RAID 配置信息*/
typedef struct
{
    uint8 disktab[5];       /*创建RAID 成员的磁盘序号*/
    uint8 count;            /*创建RAID 磁盘个数*/
    uint8 level;            /*RAID级别 */
    uint8 reserve[2];       /*保留位 */
} PT_RAID_DISK_COUNT_S, *PPT_RAID_DISK_COUNT_S;

/* RAID设备信息 */
typedef struct
{
    char Name[32];    /* 磁盘的型号 */
    uint64 dev_capabilty;               /* 磁盘的容量 */
} PT_RAIDDEVINFO_S, *PPT_RAIDDEVINFO_S;

#if 0
typedef struct
{
    PT_RAIDSTATUS_E raid_status;        //设备raid状态  PT_RAIDSTATUS_E
    PT_Raid_Level_E raid_level;         //设备raid 模式的级别
    uint32          raid_dev_table;     //每个raid组上的设备存在位置情况
    PT_RAIDDEVINFO_S raid_dev_info[10]; //每个磁盘的型号和容量
} PT_RAIDINFO_S, *PPT_RAIDINFO_S;
#endif

typedef struct
{
    uint8 stat;  /* 磁盘状态，正常或异常 */
    uint8 reserve[3];

    uint8 raid_status;         /* 设备RAID状态(MFS_RAIDSTAT_E) */
    uint8 raid_level;        /* 设备RAID模式的级别(MFS_RAIDLEVEL_E) */
    uint8 raid_ctrlor;  /* 控制器序号*/
    uint8 PortIndex;    /* 改硬盘在控制下的位置*/
    uint32 raid_dev_table;       /* 每个RAID组上的设备存在位置情况 */
    PT_RAIDDEVINFO_S raid_dev_info[10];
} PT_RAIDINFO_S, *PPT_RAIDINFO_S;

typedef struct
{
    uint16        type;     // SATA口类型, GUI_SATA_PORT_TYPE_E
    uint16        state;    // SATA口状态, GUI_SATA_PORT_STATE_E
} PT_DISK_LOAD_INFO_S, *PPT_DISK_LOAD_INFO_S;

/* 硬盘加载状态 */
typedef struct
{
    uint32                port_num;       // 接口总数
    PT_DISK_LOAD_INFO_S   info[18];   // 各个SATA口类型及状态
} PT_DISK_LOAD_DATA_S, *PPT_DISK_LOAD_DATA_S;

typedef struct
{
    uint16 dev_num;                 //设备挂载通道号(和物理插槽有关联)
    uint16 dev_type;                //设备类型（默认硬盘）,PT_DEVTYPE_E
    uint32 removable;               //设备是否可移动设置（默认否）
    uint32 backup;                  //设备是否备份设置（默认否）
    PT_DEVSTATUS_E dev_status;      //设备状态
    uint32 is_raid_dev;             //设备是否raid 装置(默认否)
    PT_RAIDINFO_S raid_info;        //当前设备raid装置的详细信息
    uint32 active;                  //设备工作状态（休眠或者活动）
    uint64 device_capabilty;        //设备容量(字节) 平台根据各自需要进行相应转换
    uint32  mfs_fs_active;          //设备文件系统是否格式化，0-未格式化，1-已格式化，2-预分配
    uint64 mfs_capability;          //文件系统可用容量（格式化后的容量字节）平台根据各自需要进行相应转换
    uint64 mfs_free;                //当前可用容量(字节)平台根据各自需要进行相应转换
    PT_MFSDEV_HANDLE device_handle; //设备操作句柄
    PT_SYSINFO_S device_sys_info;   //磁盘上录像相关的系统信息
} PT_DEVICEINFO_S, *PPT_DEVICEINFO_S;

typedef enum
{
    PT_COVERMODE_ALM,               //报警覆盖
    PT_COVERMODE_CYCLE,             //循环覆盖
} PT_COVERMODE_E;

typedef struct
{
    PT_COVERMODE_E cycle_overlay;   //磁盘覆盖方式
    uint32 dev_table;               //存储设备列表，按位表示
    uint32 usb_table;
    uint32 esata_table;
    uint32 cddvd_table;
    PT_DEVICEINFO_S disk_info[MAX_DEV_DISK];
    PT_DEVICEINFO_S usb_info[MAX_DEV_USB];
    PT_DEVICEINFO_S esata_info[MAX_DEV_ESATA];
    PT_DEVICEINFO_S cddvd_info[MAX_DEV_CDDVD];
} PT_DISKINFO_S, *PPT_DISKINFO_S;

typedef struct
{
    uint32 Preset[MAX_PRESET];      //每个预置点1-255之间
    PT_ENABLE_E PresetPoll;         //多预置点轮巡开启或关闭表示
    uint32 presettime;              //多预置点轮巡时间(1s~99s)
} PT_PRESETPOLL_S, *PPT_PRESETPOLL_S;

typedef enum
{
    PT_UPGRADE_READY = 0,   //准备升级,主要用于通知关模块
    PT_UPGRADE_START,       //开始升级
    PT_UPGRADE_PROGRESS,    //升级进度
    PT_UPGRADE_FINISH,      //升级完成
    PT_UPGRADE_ERROR,       //升级失败,错误类型见PT_UPDATE_ERR_STATUS_E
} PT_UPGRADE_STATUS_E;
typedef enum
{
    PT_SCAN_ROUTER_SUCC = 0,   //扫描路由器成功
    PT_SCAN_ROUTER_FAILED, //扫描路由器失败
    PT_ADD_PORTMAP,       //添加端口映射
} PT_UPNP_STATUS_E;

typedef struct
{
    uint8 * data;       //升级文件缓冲指针
    uint32 size;        //升级文件大小
} PT_NETUPGRADE_S, *PPT_NETUPGRADE_S;

typedef enum
{
    OEM_TYPE_HB = 0,    //汉邦
    OEM_TYPE_ZX,        //中性
    OEM_TYPE_OEM,       //一般OEM客户
    OEM_TYPE_NH,        //广州农行
    OEM_TYPE_ZXLW,      //中兴力维
    OEM_TYPE_XJSX,      //先进视讯
    OEM_TYPE_HYGJ,      //恒业国际
    OEM_TYPE_XMBL,      //厦门宝龙
    OEM_TYPE_WHWW,      //武汉万维
    OEM_TYPE_OSK,       //欧思卡
    OEM_TYPE_2D1,       //  2D1软件版本      10
    OEM_TYPE_SHJC,      // 上海检测版本
    OEM_TYPE_YBDZ,      // 友邦电子           80T  增加esata
    OEM_TYPE_SHGL,      // 上海冠林版本
    OEM_TYPE_ISPT,      // Innotec Solutions Pte Ltd
    OEM_TYPE_LILIN,     //广州利凌
    OEM_TYPE_BJJT,      // 北京骏图
    OEM_TYPE_YTAF,      //英特安防
    OEM_TYPE_OEM_9_PIC, //9图标OEM客户

    OEM_TYPE_PBS = 20,  //鹏博士商铺监控
    OEM_TYPE_AUTOCOP,
    OEM_TYPE_SZSM,      //神州数码
    OEM_TYPE_SGPT,      //深广平台
    OEM_TYPE_XM,	    //讯美
    OEM_TYPE_QZRX,      //泉州日兴
} PT_OEM_TYPE_E;

typedef enum
{
    PT_DEVTYPE_7000T = 0,
    PT_DEVTYPE_8000T,
    PT_DEVTYPE_8200T,
    PT_DEVTYPE_8000ATM,
    PT_DEVTYPE_8600T,//8600T
    PT_DEVTYPE_6200T,
    PT_DEVTYPE_8004AH,
    PT_DEVTYPE_8004AI,
    PT_DEVTYPE_7000H,
    PT_DEVTYPE_7200H,
    PT_DEVTYPE_7000M = 12,
    PT_DEVTYPE_8000M,
    PT_DEVTYPE_8200M,
    PT_DEVTYPE_7000L,
    PT_DEVTYPE_2201TL = 16,
    PT_DEVTYPE_2600T,		    //ATM智能分析盒
    PT_DEVTYPE_2600TB,	        //人流统计智能分析盒
    PT_DEVTYPE_2600TC,	        //车牌识别智能分析盒
    PT_DEVTYPE_HB9304 = 170,    //机型:可唯一标识一种具体机型
    PT_DEVTYPE_HB9308,
    PT_DEVTYPE_HB9404,
    PT_DEVTYPE_HB9408,
    PT_DEVTYPE_HB7216XT3,
    PT_DEVTYPE_HB7016X3,
    PT_DEVTYPE_HB7208XT3,
} PT_DEV_TYPE_E;

typedef struct
{
    uint32 lang_ver;        //语言版本  0：中文；1：英文
    uint32 logo_ver;        //logo版本 0：汉邦；1：中性
    sint8  internal_ver[16]; //内部版本号
    PT_OEM_TYPE_E oem_type; //OEM 类型，用来区分不同的客户,见OEM_TYPE_E
    uint32 dev_type;	    //设备型号，见PT_DEV_TYPE_E
    uint8  full_pb_flag;    //全回放标志
    uint8  reserve1;        //保留1
    uint16 reserve2;        //保留2
    sint8   oem_name[MAX_STRING];
} PT_KEYINFO_S, *PPT_KEYINFO_S;

typedef struct
{
    uint16 starttm;         //hour<<8|min
    uint16 endtm;           //hour<<8|min
    PT_SYSCOLOR_S param;    //视频参数
    sint32 bselect;         //0:标准 1:室内 2:室外 3:弱光 4:自定义1 5:自定义2
} PT_VPARAM_SEG_S, *PPT_VPARAM_SEG_S;

#if 0 //新增视频参数场景设置字段
typedef struct
{
    sint32 bselect;                     //reserve
    PT_VPARAM_SEG_S  videoparam[2];     //   0-时间段1  1-时间段2   参数
    PT_SYSCOLOR_S     defvparam;        //一天除去时间段1及时间段2以外的时间段
} PT_VIDEOPARAM_EXT_S, *PPT_VIDEOPARAM_EXT_S;
#else
typedef struct
{
    PT_VPARAM_SEG_S  videoparam[2];     //   0-时间段1  1-时间段2   参数
    PT_SYSCOLOR_S     defvparam;        //一天除去时间段1及时间段2以外的时间段
    sint32 bselect_def;                     //0:未定义 1:标准 2:室内 3:室外 4:弱光 5:自定义1 6:自定义2
} PT_VIDEOPARAM_EXT_S, *PPT_VIDEOPARAM_EXT_S;
#endif

typedef enum
{
    PT_AUTH_GUI2 = 0, //gui1.0时期权限模式(7000L,8000T等使用的黑色风格gui)
    PT_AUTH_GUI3 = 1, //gui2.0权限模式(7000L上使用的横条gui)
    PT_AUTH_GUI4 = 2, //gui3.0权限模式(9000上使用的横条gui)
} PT_AUTHORITY_MODE_E;

typedef struct
{
    uint32 audioin_no;          	// 音频输入数
    uint32 videoin_no;          	// 视频输入数
    /*INVALID*/
    uint32 ipc_videoin_no;
    /*INVALID*/
    uint32 sensorin_no;         	// 报警输入数
    uint32 sensorout_no;        	//报警输出数
    uint32 spot_support;        	// SPOT输出支持
    uint32 cvbs_support;        	// CVBS支持
    uint32 vga_support;         	// VGA支持
    uint32 hdmi_support;        	//HDMI输出支持
    uint32 color_system;        	// 0-PAL, 1-NTSC
    PT_RESOLUTION_E max_res;                // 最大视频分辨率
    uint32 max_hd;                          // 最大支持磁盘个数
    sint8  dev_machine_type[PT_MAX_STRING_EXT];	// DVR/NVR/HVR
    sint8  host_type[PT_MAX_STRING_EXT];    //主机类型  如7004T
    uint32 modelno;                         //主机类型号如7T04
    sint8  serialnumber[MAX_STRING];        //主板序列号
    sint8  fbversion[MAX_STRING];           //前面板版本号
    sint8  pri_res_support[PT_MAX_RESNUM];  //0-不支持 1-支持      主码流支持的分辨率
    sint8  sec_res_support[PT_MAX_RESNUM];  //0-不支持 1-支持     主码流支持的分辨率
    uint32 lang_ver;            	//语言版本  0：中文；1：英文
    uint32 logo_ver;            	//logo版本 0：汉邦；1：中性

    uint8 mix_support;          	// 混音支持
    uint8 esata_support;        	// ESATA支持
    uint8 raid_support;         	// RAID支持
    uint8 videomatrix_support;  	// 视频矩阵支持

    uint8 vga_auto;             	// 0-手动 1-自动
    uint8 vga_mode;             	// VGA分辨率, 0-800x600, 1-1024x768, 2-1280x1024, 3-1440*900, 4-1280*720P, 5-1920*1080I, 6-1920*1080P
    uint8 chip_no;              	// 主芯片个数
    uint8 output_dev;

    uint8 mcu_support;          	//7000L机型有效
    uint8 authority_mode;
    uint8 digital_audio_support;	//是否支持数字音频
    uint8 input_set_support;    	//是否支持输入设置

    uint8 uart232_support;      	//是否支持uart232
    uint8 uart485_support;      	//是否支持uart485
    uint8 sdi485_support;       	//是否支持SDI485
    uint8 slowbackpb_support;   	//是否支持慢退回放

    uint8 weekshow_support;     	//是否支持星期显示
    uint8 videozoomin_pause_support;//是否支持
    uint8 wireless3g_support;     	//是否支持
    uint8 buzzer_support;         	//是否支持蜂鸣器

    uint8 max_esata_support;
    uint8 hdd_map_support;
    uint8 full485_support;       	/* 全双工485是否支持 */
    uint8 pic_support;	         	/* 是否支持抓图 0 --不支持	1--支持 */

    uint8 talk_support;	         	/* 是否支持对讲 0 --不支持	1--支持 */
    uint8 zero_support;	         	/* 是否支持复合通道 0 --不支持	1--支持*/
    uint8 alm_support;          	/*是否支持报警功能*/
    uint8 remoter_support;      	/* 是否支持遥控器 */

    uint8 wlan_support;         	/*是否支持wlan*/
    uint8 autodown_player;      	/* 自动下载播放器*/
    uint8 pb_switch_ch;         	/* 回放界面切换通道 */
    uint8 player_support;       	/* 系统自带播放器 */

    uint8 lcd_support;				/*是否支持LCD屏幕触控 0--不支持 1--支持*/
    uint8 shake_alarm_support; 		/*是否支持震动报警功能 0--不支持 1--支持*/
    uint8 card_rec_support;  		/*是否支持卡号录像功能 0--不支持 1--支持*/
    uint8 ch_enable_flag;       	/*通道使能接口 1为可以修改通道名 0为不可以修改*/

    uint8 logo_watermask_support;	/*是否支持logo水印*/
    uint8 full_playback_support; 	/*是否支持全回放选项*/
    uint8 multi_scene_support; 		/*是否支持多场景设置*/
    uint8 auto_fps_support;     	/*是否支持自动分配帧率*/

    uint8 ipserver_upload_support; 	/*是否支持ipserver,upload主动上传功能，0--不支持，1--支持*/
    uint8 net_upgrade_type;
    uint8 usb_upgrade_type;
    uint8 pback_zoomin_support; 	/*是否支持回放区域放大*/

    uint8 cd_burning_support;   	/*是否支持CD刻录*/
    uint8 NRT_support;          	/*是否支持非实时*/
    uint8 video_in_adjust_support;  /*视频输入调节*/
    uint8 video_out_adjust_support; /*视频输出调节*/

    uint8 network_manage_support;         /* 是否支持组网管理 */
    uint8 conffile_import_export_support; /* 是否支持配置文件导入导出 */

    uint8 auto_format_support;   	/*是否支持自动格式化硬盘*/
    uint8 rec_packtime_support;		/*是否支持录像打包时间设定*/
    uint8 allch_timeshow_support;  	/*是否所有通道实时GUI界面显示时间*/
    uint8 logo_delay;              	/*logo延时显示 0-禁用  其他--延时秒数*/

    uint8 update_logo_support;      //gui需要据此flag，对应是否加载logo并显示"正在升级..."
    uint8 shutdown_logo_support;    //gui需要据此flag，对应是否加载logo并显示"正在关机..."
    uint8 preivew_split_support;    /*预览显示是否支持分屏*/
    uint8 popmenu_split_support;    /*鼠标右键界面是否显示分屏格式选项*/

    uint8 preview_set_support;      /*是否支持预览设置；0-不支持，1-支持  */
    uint8 coveralm_support;         /*是否支持遮挡报警*/
    uint8 avi_playback_support;     /*是否支持avi备份数据本地播放*/
    uint8 audioout_support;         /*是否支持音频输出*/
    uint8 poe_ctrl_support;         /* 是否支持POE功率控制功能 0-不支持，1-支持 */
    uint8 intel_search_support;     /* 是否支持智能搜索  1---支持；0---不支持 */
    uint8 poe_port_no;              /*支持POE网口数*/
    uint8 pb_view_support;          /*是否支持小窗口预览*/
    uint32 system_id;               /*主板加密ID*/
    uint32 poe_power;               /*支持POE输出总功率*/
    uint32 total_bitrate;           /*支持总码率,按比例扩大过,比如150M显示为200M*/
    uint32 real_bitrate;            /*实际支持的总码率*/
    uint8 preview_policy_support;   /*支持预览策略选择*/
    uint8 muti_network_port_support;//多网口支持 
	uint8 multicast_support;		/* 是否支持多播功能 add by xcli 2015/11/25*/
    uint8 alarm_push_support;      /* 是否支持报警推送 0 -- 不支持，1 -- 支持 */
} PT_IOCONFIG_S, *PPT_IOCONFIG_S;

/*************************************************************
* 结构体介绍：logo限制信息描述
*             集合元素含义:0-uboot 1-状态 2-无视频信号 3-水印 4-osd右上角 5-IE  6-9 扩展
*************************************************************/
typedef struct
{
    uint8       file_path[MAX_FILENAME_LENTH];       //带完整路径的图片名称
    uint32      logo_support;         //是否支持：1-支持, 0-不支持
    uint32      file_format;          //bit:0-支持的图片格式为jpg ,1-支持的图片格式为bmp , 2-支持的图片格式为YUV
    uint32      max_width;            //图片最大宽;
    uint32      max_height;           //图片最大高;
    uint32      min_width;            //图片最小宽;
    uint32      min_height;           //图片最小高
    uint32      logo_bitdepth;        //图片位深度，例：位深为8，第7位为1，位深为12，第11位为1，依次类推
    uint32      logo_size;            //图片大小;
    uint32      reserver;             //保留;
} LOGO_IMG_INFO_S;

typedef struct
{
    uint8               key_devinfo_path[MAX_FILENAME_LENTH];   //key、devinfo.ini的路径
    sint8               host_type[PT_MAX_STRING_EXT];           //主机类型,从脚本配置中获取的
    sint8               host_model[PT_MAX_STRING_EXT];           //主机类型名称，界面显示的
    LOGO_IMG_INFO_S     logo_img_info_arr[MAX_LOGO_NUM];
} PT_LOGO_LIMIT_INFO_S;

/*************************************************************
* 结构体介绍：key 文件88 字节
*************************************************************/
typedef struct
{
    sint8   internal_ver[16]; //内部版本号
    sint8   external_ver7004t[16]; //外部版本号7004t
    sint8   external_ver7008t[16]; //外部版本号7008t
    sint8   external_ver7016t[16]; //外部版本号7016t
    sint8   external_ver8004t[16]; //外部版本号8004t
    sint8   external_ver8008t[16]; //外部版本号8008t
    sint8   external_ver8016t[16]; //外部版本号8016t
    sint8   external_ver700xt[16]; //外部版本号700xt
    sint8   external_ver800xt[16]; //外部版本号800xt
    uint32 lang_ver; //语言版本  0：中文；1：英文
    uint32 logo_ver; //logo版本 0：汉邦；1：中性2: OEM
    uint32  lang_maskl;                         //支持的语言掩码低32 位代表32种语言
    uint32  lang_maskh;                         //支持的语言掩码高32 位代表另外32种语言
    uint16  oem_type;                   // OEM 类型，用来区分不同的客户
    sint8   full_pb_flag;			//是否支持全回放 0不支持,1支持
    sint8   reserve[21];
} PT_KEY_FIELD_S;
typedef enum
{
    PT_AUDIO_NONE       = 0,    /* 无音频 */
    PT_AUDIO_DIGITAL    = 1,    /* 只有数字音频 */
    PT_AUDIO_ANALOG     = 2,    /* 只有模拟音频 */
    PT_AUDIO_AAD        = 3,    /* both ANALOG and DIGITAL */
} PT_AUDIO_TYPE_E;

typedef enum
{
    PT_CAMERA_ANALOG_D1             = 0,    /* 只支持模拟D1 */
    PT_CAMERA_ANALOG_D1_960H        = 1,    /* 支持模拟D1与960H */
    PT_CAMERA_ANALOG_D1_ENCODE_CIF  = 2,    /* 输入模拟D1,但只用于CIF编码 */
    PT_CAMERA_ANALOG_D1_ENCODE_6FPS = 3,    /* 输入模拟D1,但D1编码只有6帧 */

    PT_CAMERA_DIGITAL_1080P = 10,  /* 数字源1080p */
    PT_CAMERA_DIGITAL_720P  = 11,
} PT_CAMERA_TYPE;

typedef struct
{
    uint32 audio_type;  /* PT_AUDIO_TYPE_E */
    uint32 camera_type; /* PT_CAMERA_TYPE */
} PT_CHANNEL_CONFIG_S;

typedef enum
{
    PT_DEV_UNDEF = -1,  /* 未指定输出设备 */
    PT_DEV_PRI  = 0,    /* 主输出设备 */
    PT_DEV_SEC  = 1,    /* 辅输出设备 */
    PT_DEV_SPOT = 2,
    PT_DEV_ALL  = 0xFF, /* 所有输出设备 */
} PT_OUTPUT_DEV_E;      /* 主辅输出设备 */

typedef struct
{
    uint8 auto_logout;      // 自动锁定；0-禁用，其他-空闲分钟数                                 n
    uint8 gui_alpha;        // GUI透明度0~255                                                      n
    uint8 gui_lang;         // GUI语言选项，0-中文、1-英文、2-...                                   n
    uint8 alarm_delay;      // 延时报警开关；0-禁用，其他-报警延时时间，单位：秒                 n
    uint8 mute;             // 静音；0-不静音、1-静音                                               n
    uint8 mix;              // 混音；0-不混音、1-混音                                                n
    uint8 r1;               /* 该设置不提供操作性质的属性 */
    uint8 alarm_snapshot;   // 报警抓拍图片，0-禁用，1-启用                               n
    uint8 vga_auto;         // 0-手动 1-自动                                                    n
    uint8 gui_dflicker;     // 0-不去抖 1-去抖                                               n
    uint8 talkback_type;    // 对讲输入类型；0-麦克风，1-拾音器                                n
    uint8 reclight_enable;  // 录像状态指示灯启用开关，0-禁用，1-启用                        n
    uint8 esata_enable;     // ESATA使能，0-关闭，1-启用                                     n
    uint8 softraid_enable1; // softraid使能，0-关闭，1-启用                               n
    uint16 audio_alarm;     // 声音报警；0-禁用，1-启用，其他-声音报警时间（单位：秒）          n
    uint8 reclight[MAX_CH]; // 录像状态指示灯，按位表示各通道状态 ?                    n
    uint8 ao_mode;          // 音频输出模式, 0--BNC输出 1--MIC输出                               n
    uint8 r2;
    uint8 set_guide;        // 是否启用开机向导0: 不启用 1: 启用                              n
    uint8 montion_beep;     // 移动报警蜂鸣器报警；0-禁用，1-启用(特殊用户有效, 一般版本无效First Option)    n
    uint32 screen_saver;    // 屏幕保护，0-禁用，其他-空闲分钟数                           n
    uint32 lang_mask;       // 支持语言，按位表示
    uint8 set_output_dev;   // 开机是否显示设备显示框. 1显示 0不显示
    uint8 toolbar_enable;   //是否显示和隐藏工具栏0; 隐藏，1-显示
    uint8 without_login_mode; //是否开启免登模式0-关闭；1-开启
    uint8 ipc_manage_mode;  /*IPC管理模式 PT_IPC_MANAGE_MODE_E*/
} PT_COMMON_CONFIG, *PPT_COMMON_CONFIG;

typedef enum
{
    PT_FRAMETYPE_P,     //P帧
    PT_FRAMETYPE_I,     //I帧
    PT_FRAMETYPE_AUDIO, //音频帧
} PT_FRAMETYPE_E;

typedef struct
{
    uint32 flag;        // MSHEAD_FLAG
    uint32 mshsize;     // 媒体头信息, MAX size=511
    uint32 msdsize;     // 媒体数据流大小, Max size=512K-1
    uint32 algorithm;   // 媒体编码标准ISO_...
    PT_FRAMETYPE_E type;
    uint32 width;       //如为视频表示宽度（单位16像素）， 如为音频表示采样位宽（单位bit）
    uint32 height;      //如为视频表示高度（单位16像素）， 如为音频表示采样率（单位K【1000】）
    uint32 serial_no;   // 0~511循环计数，用于标准的帧连续判断，当间隔两帧序号不连续时，表示中间帧丢失。
    uint32 time_msec;   //当前帧时间（单位10毫秒）
    uint32 time_sec;    //当前帧时间（单位秒）表示从1970年1月1日0时0分0秒算起至今的UTC时间所经过的秒数
    uint32 fcount;      // 用于码流的帧计数
    PT_TIME_S time;     //帧具体时间
} PT_FRAMEHEADINFO_S, *PPT_FRAMEHEADINFO_S;



typedef struct
{
    PT_RECTYPE_E type;      //录像类型
    PT_ENABLE_E status;     //录像使能
} PT_RECENABLE_S, *PPT_RECENABLE_S;


typedef struct pt_msg_buf
{
    long    type;           // 消息类型,必须>0
    int     buffer[4];      // 消息内容
} PT_MSG_BUF, *PPT_MSG_BUF;

typedef enum
{
    NETKEY_CMD_GUI_LOGIN,       // 登录
    NETKEY_CMD_GUI_DN,          //主机号                                      1
    NETKEY_CMD_GUI_STOP,        //STOP                                            2
    NETKEY_CMD_GUI_RETURN,      // 返回                                    3
    NETKEY_CMD_GUI_ENTER,       //确认                                       4
    NETKEY_CMD_GUI_UP,          //上                                                 5
    NETKEY_CMD_GUI_DOWN,        // 下                                            6
    NETKEY_CMD_GUI_LEFT,        //左                                              7
    NETKEY_CMD_GUI_RIGHT,       //右                                            8
    NETKEY_CMD_GUI_INFO,        //信息                                          9
    NETKEY_CMD_GUI_RECORD,      //录像                                       10
    NETKEY_CMD_GUI_PLAYBACK,    //回放                                   11
    NETKEY_CMD_GUI_SETUP,       //设置                                         12
    NETKEY_CMD_GUI_BACKUP,      //备份                                       13
    NETKEY_CMD_GUI_ZOOM_INC,        //摄像头近                                   14
    NETKEY_CMD_GUI_ZOOM_DEC,         //摄像头远                                    15
    NETKEY_CMD_GUI_FOCUS_INC,       // 摄像头变焦近(ZOOM+)      16
    NETKEY_CMD_GUI_FOCUS_DEC,       // 摄像头变焦远(ZOOM-)    17
    NETKEY_CMD_GUI_IRIS_INC,        // 摄像头光圈+                  18
    NETKEY_CMD_GUI_IRIS_DEC,        // 摄像头光圈-                   19
    NETKEY_CMD_GUI_PAGEUP,      //上页                                       20
    NETKEY_CMD_GUI_PAGEDOWN,    // 下页                                  21
    NETKEY_CMD_GUI_PRESET_SET,  //摄像头预置                  22
    NETKEY_CMD_GUI_PRESET_GET,  // 摄像头调用                23
    NETKEY_CMD_GUI_CN,          // 中文 70                                          24
    NETKEY_CMD_GUI_AUTO,        // 自动                                           25
    NETKEY_CMD_GUI_MUTE,        // 静音                                          26
    NETKEY_CMD_GUI_F1,          //F1                                                       27
    NETKEY_CMD_GUI_F2,          //F2                                                       28
    NETKEY_CMD_GUI_REFRESH,     // REAL GUI USE 110                       29
    NETKEY_CMD_GUI_IGEFORMAT,   // 画面格式 100                30
    NETKEY_CMD_GUI_IGESWITCH,   // 画面轮换                      31
    NETKEY_CMD_GUI_SHUTDOWN,    // 电源,关机申请            32
    NETKEY_CMD_GUI_MOUSESTATUS, //  鼠标                           33
    NETKEY_CMD_GUI_VIDEOPARAM,  // 视频参数                              34
    NETKEY_CMD_GUI_DIGIT,       // 数字(参数为0,1,2,3,4,5,6,7,8,9)          35
    NETKEY_CMD_GUI_CHAR,        // 字符(参数为A,B,C,...,X,Y,Z,*,#)            36
    NETKEY_CMD_GUI_F1VGA2TV,    // vga与电视切换                       37
    NETKEY_CMD_GUI_STEP,        // 帧进                                            38
    NETKEY_CMD_GUI_PLAY,        // 播放                                            39
    NETKEY_CMD_GUI_FASTF,       // 快进                                          40
    NETKEY_CMD_GUI_FASTB,       // 快退                                          41
    NETKEY_CMD_GUI_REFRESHTIME, // REAL GUI USE                      42
    NETKEY_CMD_GUI_PWDRST,      //密码复位                              43
} PT_NETKEYCMD_E;

typedef enum
{
    // SERIAL SEND GUI
    SYSNETAPI_SERIAL_GUI_LOGIN = 100,   // 登录512
    SYSNETAPI_SERIAL_GUI_RECORD,        // 录像
    SYSNETAPI_SERIAL_GUI_PLAYBACK,      // 回放
    SYSNETAPI_SERIAL_GUI_SETUP,         // 设置
    SYSNETAPI_SERIAL_GUI_BACKUP,        // 备份
    SYSNETAPI_SERIAL_GUI_DN,            // 主机号
    SYSNETAPI_SERIAL_GUI_CN,            // 中文
    SYSNETAPI_SERIAL_GUI_DIGIT,         // 数字(参数为0,1,2,3,4,5,6,7,8,9)
    SYSNETAPI_SERIAL_GUI_CHAR,          // 字符(参数为A,B,C,...,X,Y,Z,*,#)  520
    SYSNETAPI_SERIAL_GUI_BKSPACE,       // 删除
    SYSNETAPI_SERIAL_GUI_UP,            // 上                110
    SYSNETAPI_SERIAL_GUI_DOWN,          // 下
    SYSNETAPI_SERIAL_GUI_LEFT,          // 左
    SYSNETAPI_SERIAL_GUI_RIGHT,         // 右
    SYSNETAPI_SERIAL_GUI_PAGEUP,        // 上页
    SYSNETAPI_SERIAL_GUI_PAGEDOWN,      // 下页
    SYSNETAPI_SERIAL_GUI_RETURN,        // 返回
    SYSNETAPI_SERIAL_GUI_ENTER,         // 确认
    SYSNETAPI_SERIAL_GUI_ZOOM_INC,      // 摄像头远近+
    SYSNETAPI_SERIAL_GUI_ZOOM_DEC,      // 摄像头远近-
    SYSNETAPI_SERIAL_GUI_FOCUS_INC,     // 摄像头变焦+
    SYSNETAPI_SERIAL_GUI_FOCUS_DEC,     // 摄像头变焦-
    SYSNETAPI_SERIAL_GUI_IRIS_INC,      // 摄像头光圈+
    SYSNETAPI_SERIAL_GUI_IRIS_DEC,      // 摄像头光圈-
    SYSNETAPI_SERIAL_GUI_PRESET_SET,    // 摄像头预置
    SYSNETAPI_SERIAL_GUI_PRESET_GET,    // 摄像头调用//80
    SYSNETAPI_SERIAL_GUI_AUTO,          // 摄像头自动
    SYSNETAPI_SERIAL_GUI_MUTE,          // 静音
    SYSNETAPI_SERIAL_GUI_INFO,          // 信息//540
    SYSNETAPI_SERIAL_GUI_STEP,          // 帧进
    SYSNETAPI_SERIAL_GUI_PLAY,          // 播放
    SYSNETAPI_SERIAL_GUI_FASTF,         // 快进
    SYSNETAPI_SERIAL_GUI_FASTB,         // 快退
    SYSNETAPI_SERIAL_GUI_CLRALT,        // 报警清除
    SYSNETAPI_SERIAL_GUI_F1,            // F1
    SYSNETAPI_SERIAL_GUI_F2,            // F2//90
    SYSNETAPI_SERIAL_GUI_IGEFORMAT,     // 画面格式
    SYSNETAPI_SERIAL_GUI_IGESWITCH,     // 画面轮换
    SYSNETAPI_SERIAL_GUI_STOP,          // STOP //550
    SYSNETAPI_SERIAL_GUI_SHUTDOWN,      // 电源,关机申请
    SYSNETAPI_SERIAL_GUI_PWDRST,        // 密码复位
    SYSNETAPI_SERIAL_GUI_PWDNRST,       //密码不复位
    SYSNETAPI_SERIAL_GUI_F1VGA2TV,      // vga与电视切换
    SYSNETAPI_SERIAL_GUI_MOUSESTATUS,   // 鼠标
    SYSNETAPI_SERIAL_GUI_VIDEOPARAM,    // 视频参数
    SYSNETAPI_SERIAL_GUI_BRUSH,         // 雨刷
    SYSNETAPI_SERIAL_GUI_PTZ,           // PTZ//100
    SYSNETAPI_SERIAL_GUI_REFRESH,       // REAL GUI USE
    SYSNETAPI_SERIAL_GUI_REFRESHTIME,   // REAL GUI USE//560
    SYSNETAPI_SERIAL_GUI_TEMPERATURE,   // 前面板温度
    SYSNETAPI_SERIAL_GUI_SETSYSTIME,    //设置系统时间
    SYSNETAPI_SERIAL_GUI_REBOOT,        //系统重启
    SYSNETAPI_SERIAL_GUI_CLOSE,         //系统关机
    SYSNETAPI_SERIAL_GUI_PS2STATUS,     //PS2鼠标状态
    SYSNETAPI_SERIAL_GUI_SET,           //110
    SYSNETAPI_SERIAL_GUI_DELAY_SHUTDOWN,//延时关机

    // KEYBOARD CMD
    SYSNETAPI_SERIAL_KEYB_GETADDR = 200,        // 获取串口键盘地址码,param(int *)
    SYSNETAPI_SERIAL_KEYB_SETADDR,              // 设置串口键盘地址码,param(int(0~512)),

    SYSNETAPI_SERIAL_GUI_LCDSTATE,
    SYSNETAPI_SERIAL_GUI_VIDEOMATRIX_SINGLE,    //设置视频矩阵单通道输出
    SYSNETAPI_SERIAL_GUI_VIDEOMATRIX_MUTI,      //设置视频矩阵多通道输出
    SYSNETAPI_SERIAL_GUI_VIDEOMATRIX_POLL,      //设置视频矩阵轮询
    SYSNETAPI_SERIAL_GUI_MAINPIC_SWITCH_MODE,   //设置主画面显示格式
    SYSNETAPI_SERIAL_CMD_GUI_DOOR_STATE,  //前面板门的状态，开门1，关门0，状态改变的时候上报
    SYSNETAPI_SERIAL_GUI_OTREC,//一键录像
} SYSNETAPI_SERIAL_GUI_E;
typedef struct
{

    int status; // 0 -- 关屏   1 -- 开屏
    sint32 reserve;
} PT_LCDCTRL_S;

typedef struct
{
    PT_NETKEYCMD_E cmd;
    uint32 keycode;
} PT_NETKEY_S, *PPT_NETKEY_S;

/* 备份文件导入导出*/
typedef enum
{
    PT_BACK_TYPE_GUI = 1,
    PT_BACK_TYPE_NET, 
    PT_BACK_TYPE_UNKNOW,
}PT_BACK_TYPE_E;

typedef struct
{
    uint32 choose_flag;//导入选项标志　　0XFF---权限　　其他－－－－部分导入
    uint8 sys_general_im;//系统设置是否导入  0--不导入 1--导入
    uint8 output_im;// 输出设置是否导入   0--不导入 1--导入
    uint8 rec_param_im;//编码参数是否导入   0--不导入 1--导入
    uint8 rec_plan_im;//定时录像是否导入   0--不导入 1--导入
    
    uint8 alm_set_im;//报警设置是否导入  0--不导入 1--导入
    uint8 uart_set_im;//串口设置是否导入  0--不导入 1--导入
    uint8 ptz_set_im;//云台设置是否导入  0--不导入 1--导入
    uint8 net_set_im;//网络设置是否导入  0--不导入 1--导入
    
    uint8 card_set_im;//卡号录像设置是否导入  0--不导入 1--导入
    uint8 sys_time_set_im;//系统时间设置是否导入  0--不导入 1--导入
    uint8 storage_set_im;//存储设置是否导入  0--不导入 1--导入
    uint8 time_reboot_im;//定时重启是否导入  0--不导入 1--导入

    uint8 input_set_im;//输入设置是否导入  0--不导入 1--导入
    uint8 usr_manage_im;//用户管理参数是否导入   0--不导入 1--导入
    uint8 reserve[2];
}PT_IMPORT_S, *PPT_IMPORT_S;

typedef struct
{
    uint32 backup_type;					//U盘备份-1； 网络备份-2；  PT_BACK_TYPE_E
    uint8  file_path[256];				//U盘备份-文件路径
    uint8  file_name[PT_MAX_STRING_EXT];   //导入或者导出配置文件名称　
    uint32 file_len;					//网络备份-文件数据长度
    void * file_addr;					//网络备份-文件数据指针  外部申请内存传入
    PT_IMPORT_S import_choose;          //导入选项----暂不支持
} PT_CONFIG_BACKUP_S, *PPT_CONFIG_BACKUP_S;

/* 用户配置文件信息 */
typedef struct
{
    sint32 conf_size;  //配置文件大小
} PT_USERCONF_INFO_S, *PPT_USERCONF_INFO_S;
/* 用户信息 */
typedef struct
{
    uint8 user[MAX_STRING];         // 用户名
    uint8 pwd[MAX_STRING];          // 用户密码
    uint8 grp_name[MAX_STRING];     // 所在分组名

    // 每位代表一个通道,bit0~bit63表示0~63通道,本地最多32种权限.远程最多16种权限.
    uint64 local_authority[32];     // 本地用户使用权限;
    uint64 remote_authority[16];    // 远程权限

    uint32 bind_ipaddr;             // 远程绑定IP
    uint8 bind_macaddr[8];          // 远程绑定MAC
} PT_ACCOUNT_S, *PPT_ACCOUNT_S;

/* 用户组信息 */
typedef struct
{
    uint8 name[MAX_STRING];           // 分组名

    uint64 local_authority[32];       // 本地用户使用权限;
    uint64 remote_authority[16];      //远程权限
} PT_GROUPACCOUNT_S, *PPT_GROUPACCOUNT_S;

/* 用户管理 */
typedef struct
{
    uint8 count;                // 用户数量
    uint8 grp_count;            // 用户组数量
    uint16 list_enable;         // 登陆时是否显示用户列表
    PT_ACCOUNT_S        cur_user;                       // 本地当前登录用户
    PT_ACCOUNT_S        accounts[PT_MAX_ACCOUNT];       // 用户列表
    PT_GROUPACCOUNT_S   grp_accounts[PT_GRP_ACCOUNT];   // 用户组列表
} PT_ACCOUNT_CONFIG_S, *PPT_ACCOUNT_CONFIG_S;

typedef struct
{
    uint16 enalmmax;            //报警最大化使用标识，0--未使能，1--使能
    uint8 almoutbuzzer;         //报警送蜂鸣器
    uint8 almoutaudio;          //报警声音输出使能

    PT_TMSCHEDULE_S schedule;   //布防时间设置
    PT_ALMLINKPLAN_S plan;      //报警联动预案
    PT_AREA_S    coverarea[MAX_MASK];
    uint32 mail_enable;         //报警邮件使能  0-关闭 1-开启
} PT_MASKRECPARAM_S, *PPT_MASKRECPARAM_S;

typedef struct
{
    uint16  enalmmax;           //报警最大化使用标识，0--未使能，1--使能
    uint16  almoutbuzzer;       //报警送蜂鸣器
    uint16  almoutaudio;        //报警声音输出使能
    uint16  almoutsec;          //报警输出时间
    PT_TMSCHEDULE_S schedule;   //布防时间设置
} PT_ALARMOUTPARAM_S, *PPT_ALARMOUTPARAM_S;

typedef struct
{
    uint32 open_bk_handle;       // 已打开的备份句柄
    uint32 size;                 // 想备份数据大小，根据实际需要来传
    sint8 * data;                // 备份数据，传入buf大小不得小于size
} PT_BACKUPREAD_S, *PPT_BACKUPREAD_S;


typedef struct
{
    char name[16];
    ptptz_control func;
} PT_PTZLIST_S, *PPT_PTZLIST_S;

typedef struct
{
    uint8 server[MAX_STRING];   // 服务器
    uint16 port;                // 端口
    uint8 auto_enbale;          // 开启ntp服务,0- 不启用 ,1-表示自动 ，2-表示手动
    uint8 server_index;         // 服务器索引号
    uint16 sync_period;         // 同步周期，
    uint16 sync_unit;           // 同步周期，0-分钟 1-小时 2-天 3-星期 4-月
    uint16 sync_time;           // 同步时间，格式 小时:分钟
    uint16 reserve;             // 保留位
    int    time_zone;           // 时区
} PT_NTPCONFIG_S, *PPT_NTPCONFIG_S;

typedef struct
{
    uint8   host[PT_MAX_SMTP_HOST];     // 发送邮件的SMTP服务器，例如：126信箱的是smtp.126.com
    uint32 port;                        // 服务器端口，发送邮件(SMTP)端口：默认值25
    uint8  user[MAX_STRING];            // 邮件用户名
    uint8  pwd[MAX_STRING];             // 邮件用户密码
    uint8 send_addr[PT_MAX_SMTP_HOST];  // FROM：邮件地址
    uint8 recv_addr[PT_MAX_SMTP_ADDR];  // TO：邮件地址，最多8个邮箱地址
    uint16 send_period;                 // 上传周期,单位(分钟,最大值120)
    uint16 snap_enable: 1;              // 是否抓拍上传
    uint16 ssl_enable : 1;              // ssl加密使能，0-关闭 1-开启
    uint16 starttls_enable : 1;         // 0-关闭 1-开启
    uint16 reserves : 13;               // 保留位
    uint8  reserve[MAX_STRING];         // 保留字节
} PT_SMTPCONFIG_S, *PPT_SMTPCONFIG_S;


// 实时图像轮训
typedef struct
{
    uint8 enable;               // 启用？0-禁用，1-启用
    uint8 period;               // 轮训间隔，单位秒
    uint16 format;              // 画面格式：0-0ff, 1-1, 2-2, 4-2x2, 9-3x3, 16-4x4
    uint16 ch_list[MAX_CH];      // 取值[0，n-1]或者0xff，n是通道数，oxff表示该数组无效
    uint32 lock_time;                // 锁定时间 单位 分钟
} PT_POLLCONFIG_S, *PPT_POLLCONFIG_S;

typedef struct
{
    uint8 matrix_channel[PT_MAX_MATRIX];    // 视频矩阵对应通道 从1开始，0xff表示关闭
    uint8 reserve[MAX_STRING];              // 保留位
} PT_VIDEOMATRIX_S, *PPT_VIDEOMATRIX_S;


typedef struct
{
    uint8 hderr_enable;         // 磁盘错误使能
    uint8 temp_enable;          // 温度报警使能
    uint8 temp_show;            // 温度是否显示，0-不显示，1-显示
    uint8 temp_unit;            // 温度单位，0-摄氏度，1-华氏度
    uint8 threshold_enable;     // 使能
    uint8 threshold_high;       // 磁盘高阀值0-100
    uint8 threshold_low;        // 磁盘低阀值0-100
    uint8 net_down_enable : 1;  // 网络掉线使能
    uint8 ip_collision_enable : 1; //IP冲突使能
    uint8 alarminfo_send : 1;   // 报警信息是否发送0: 上传 1:不上传(特殊: 为使与之前版本统一)
    uint8 usb_ico_show : 1;     // usb图标是否显示
    uint8 email_ico_shaow : 1;  // email图标是否显示
    uint8 hderr_mail_enable : 1;// 磁盘报警联动邮件上传使能，0-不上传，1-上传
    uint8 temp_mail_enable : 1; // 温度报警联动邮件上传使能，0-不上传，1-上传
    uint8 reserve : 1;          // 保留

    uint8 hdfull_alm_enable;
    uint8 hdfull_mail_enable;
    uint16 temp_limit;          // 温度上限，单位摄氏度
    uint32 sensor_out;          // 联动探头输出
} PT_ERRALARM_S, *PPT_ERRALARM_S;

typedef struct
{
    uint8 video_stat[MAX_CH];    // 视频丢失状态
    uint8 motion_detect[MAX_CH]; // 移动帧测报警状态
    uint8 sensor_detect[MAX_AM];	// 探头报警输入状态
    uint8 ipc_sensor_detect[MAX_CH];	// IPC探头报警输入状态
    uint8 sensor_out[MAX_AMOUT]; // 各通道探头输出状态
    uint8 vcover_detect[MAX_CH];	// 遮挡报警状态
    uint8 poeconfict_detect[MAX_CH];	// POEt通道接入冲突报警状态
    uint8 rectype[MAX_CH];      // 各通道录像类型
    uint8 manual_rec[MAX_CH];
    uint8 time_rec[MAX_CH];
    uint8 motion_rec[MAX_CH];
    uint8 sensor_rec[MAX_CH];   // 各通道各类型录像状态
    uint16 disk_err; 			// 磁盘报警状态
    uint16 disk_full_alm;       //磁盘满报警
    uint16 temp_error;          // 磁盘和系统温度错误
    uint16 net_down;            // 网络掉线错误
    uint8 pic_rectype[MAX_CH];  // 各通道录像类型
} PT_IOSTATUS_S, *PPT_IOSTATUS_S;

typedef struct
{
    char    name[MAX_STRING];   // 用户名
    uint32  ip;                 // IP
    PT_MFSTIME_S login_time;    // 登录时间
    uint32  usr_id;             // 用户ID，唯一
    uint32 reserve;             //
} PT_ONLINE_USER_S, *PPT_ONLINE_USER_S;

//在线状态
typedef struct
{
    uint32                  user_num;               //在线用户数
    PT_ONLINE_USER_S  online_user[PT_MAX_USER];     //用户信息
    uint32                  reserve;                //当前用户正在观看的通道
} PT_ONLINE_USER_INFO_S, *PPT_ONLINE_USER_INFO_S;

//格式化设备信息
typedef struct
{
    sint32  dev_num;    //存储设备挂载通道
    sint32  dev_type;   //存储设备类型，PT_DEVTYPE_E
    sint32  reserve;    //保留位
} PT_FORMAT_DEV_S;
//格式化请求结构体
typedef struct
{
    uint32          format_num;                 //需要格式化设备个数
    uint32          format_log_flg;	            //是否格式化日志标志，0--不格式化，1--格式化
    PT_FORMAT_DEV_S dev_info[PT_MAX_DEV_NUM];   //每个要格式化设备的信息
} PT_FORMATINFO_S, *PPT_FORMATINFO_S;

typedef enum
{
    SYSNETAPI_DISK_INFORMAT = 0,//磁盘正在被格式化
    SYSNETAPI_DISK_FORMATEND,   //格式化结束
    SYSNETAPI_DISK_ALL_FMTEND,  //所有磁盘格式化结束
    SYSNETAPI_FARMAT_ERR ,      //格式化错误

    SYSNETAPI_DISK_NOEXIST,     //要格式化的磁盘不存在
    SYSNETAPI_DISK_LOST,        //格式化中途错误
    SYSNETAPI_DISK_BUSY,        //磁盘正在被使用
} PT_FORMATTYPE_E;

typedef struct
{
    uint16 dev_num;         //格式化的磁盘号
    uint16 dev_type;        //格式化的磁盘类型
    uint16 percentstate;    //当前进度只在format_state为SYSNETAPI_DISK_INFORMAT时有效
    uint8  format_state;    //格式化状态，见PT_FORMATTYPE_E
    uint8  err_status;      //保留
} PT_FORMATSTATE_S, *PPT_FORMATSTATE_S;


typedef struct
{
    uint16 enable;              //0-撤防，1-布防
    uint16 time;                //布防延时时间
    uint32 reserver[4];         //保留
} PT_REAL_DEFENCE_S, *PPT_REAL_DEFENCE_S;

typedef struct
{
    uint16 alm_ch;              //报警通道
    uint16 alm_type;            //报警类型0-无报警1-探头报警2-移动侦测3-视频丢失
    PT_MFSTIME_S time;          //报警发生时间点
} PT_ALMINFO_S, *PPT_ALMINFO_S;
typedef struct
{
    uint32 alm_count;                   //掉线期间报警总数
    PT_ALMINFO_S alminfo[MAX_AM_COUNT]; //每次报警的相关信息，只存储最新的16次报警
    uint32 reserver[4];  			    //保留
} PT_DISCONN_ALMSTAT_S, *PPT_DISCONN_ALMSTAT_S;

typedef enum
{
    SIZE_8M = 0,		//8M
    SIZE_16M ,			//16M
    SIZE_32M ,			//32M
    SIZE_64M ,			//64M
    SIZE_128M ,		    //128M
    SIZE_256M ,		    //256M
    SIZE_512M ,		    //512M
    SIZE_1024M,		    //1024M
} PT_MEMSIZE_E;
typedef struct
{
    uint16	mem_size;	        //主机物理内存大小,定义见PT_MEMSIZE_E
    uint16	flash_size;         //主机flash大小,定义见PT_MEMSIZE_E
    uint16  disk_free_percent;  //当前主机磁盘可用容量百分比
    uint16  hdd_num;            //主机当前已接磁盘个数
    uint16  encrypt;            //主机是否非法标志，0--合法，非0--非法
    uint16  serial_num;         //主机支持串口个数
    uint16  pb_num;             //主机支持录像回放通道
    uint16  pic_pb_num;         //主机支持图片回放通道
    uint16  esata_num;          //数据盘的ESATA盘数
    uint16  reserve;            //保留
    sint8   android[PT_CLIENT_DL_ADDR];     //安卓手机客户端下载地址
    sint8   ios[PT_CLIENT_DL_ADDR];         //IOS手机客户端下载地址
} PT_HOST_SYSINFO_S, *PPT_HOST_SYSINFO_S;

typedef struct
{
    uint32 enable;
    uint8 chlist[MAX_CH];
    PT_ENCCONFIG_S venc_conf;
    uint32 reserve;
} PT_ZERO_VENC_CONFIG_S, *PPT_PZERO_VENC_CONFIG_S;

typedef struct
{
    uint8 vcover_enable;        //遮挡报警使能，1-启用，0-不启用
    uint8 vcover_email_enable;  //遮挡报警使能，1-启用，0-不启用
    uint8 vcover_sensitivity;   //遮挡报警灵敏度 (0-5)              //added by ypxiao 1112
    uint8 reserve;              //保留位
    uint32 sensor_out;          //联动报警输出，按位表示，1-联动，0-不联动
} PT_VCOVER_ALM_CONFIG_S, *PPT_VCOVER_ALM_CONFIG_S;

typedef struct
{
    uint8 enable;               //POE通道冲突报警使能，主要发生在POE口被非POE设备占用的情况
    uint8 mail_enable;          //POE通道冲突报警联动邮件上传使能，0-不上传，1-上传
    uint16 reserve;             //保留
} PT_POE_CONFLICT_CONFIG_S, *PPT_POE_CONFLICT_CONFIG_S;

//MFS2.0 新增功能
//磁盘组信息
typedef struct
{
    sint16  hdd_attri;      // 磁盘属性0:读写；1 只读 ；2 冗余
    sint8   hdd_group;      // 盘组号
    sint8   hdd_devno;      // 当为ESATA盘时，存ESATA设备号
    sint16  dev_type;
    sint16  hdd_type;      // 磁盘属性0: 数据区 1 备份区 ；2 冗余
} PT_HDD_GROPE_INFO_S, *PPT_HDD_GROPE_INFO_S;

//录像通道组信息
typedef struct
{
    sint16  hdd_group;      //归属盘组
    sint16  reserve;        //保留
} PT_REC_GROPE_INFO_S, *PPT_REC_GROPE_INFO_S;

typedef struct
{
    uint8 dev_tbl[PT_DEVTYPE_MAX][PT_MAX_DEV_NUM]; /* 硬盘配置表,PT_DEVTYPE_E,每种类型设备最多支持MAX_DSK个硬盘 */
    uint8 ch_tbl[MAX_CH];                   /* 通道配置表,最大支持MAX_CH个通道 */
    uint8 group;                            /* 分组序号(0~63) */
    uint8 reserve[3];                       /* 保留位 */
} PT_DISK_GROUP_INFO_S, *PPT_DISK_GROUP_INFO_S;

//截图设置
//手动截图参数
typedef struct
{
    sint8 resolution;       //图片清晰度0:CIF 1:D1
    sint8 quality;          //图片质量 1~6
    sint16 reserve;
} PT_MANUAL_SANPSHOT_CONFIG_S, *PPT_MANUAL_SANPSHOT_CONFIG_S;

//定时截图参数
typedef struct
{
    sint8 resolution;       //图片清晰度0:CIF 1:D1
    sint8 quality;          //图片质量 1~6
    uint8 period;           //截图间隔(1~255S)
    uint8 num;              //截图图片数量(1~255S)
    PT_TMSCHEDULE_S schedule;
    sint32 reserve;
} PT_TIME_SANPSHOT_CONFIG_S, *PPT_TIME_SANPSHOT_CONFIG_S;

//移动截图参数
typedef struct
{
    sint8 resolution;       //图片清晰度0:CIF 1:D1
    sint8 quality;          //图片质量 1~6
    uint8 period;           //截图间隔(1~255S)
    uint8 num;              //截图图片数量
    uint8 snap_bind[MAX_CH];//联动截图
    PT_TMSCHEDULE_S schedule;
    sint32 reserve;
} PT_MOTION_SANPSHOT_CONFIG_S, *PPT_MOTION_SANPSHOT_CONFIG_S;

//探头截图参数
typedef struct
{
    sint8 resolution;       //图片清晰度0:CIF 1:D1
    sint8 quality;          //图片质量 1~6
    uint8 period;           //截图间隔(1~255S)
    uint8 num;              //截图图片数量
    uint8 snap_bind[MAX_CH];//联动截图
    PT_TMSCHEDULE_S schedule;
    sint32 reserve;
} PT_SENSOR_SANPSHOT_CONFIG_S, *PPT_SENSOR_SANPSHOT_CONFIG_S;

/* 存储数据参数信息 */
typedef struct
{
    uint16 rec_priority;    /* 录像数据存储优先级(级别按大小由低到高[0-15]) */
    uint16 rec_time;        /* 录像数据时间设置(单位: 天[0-4096]) */
    uint16 pic_priority;    /* 图片数据存储优先级(级别按大小由低到高[0-15]) */
    uint16 pic_time;        /* 图片数据时间设置(单位: 天[0-4096]) */
    uint16 channel;         /* 通道号[0-255] */
    uint16 enable;          /* 自动删除功能使能标志(1-使能 0-非使能) */
    uint32 reserve;         /* 保留位 */
} PT_STORE_PARAM_INFO_S, *PPT_STORE_PARAM_INFO_S;

typedef struct
{
    uint32 tm_uint;		//0~23 设置存储删除触发时间
    uint32 reserve;    /* 保留位 */
} PT_STORE_DEL_TIME_S, *PPT_STORE_DEL_TIME_S;

//图片存储设置
typedef struct
{
    sint16  snapshot_type;          // 截图类型:手动、定时、移动、报警,PT_RECTYPE_E
    uint16  snapshot_resolution;    // 清晰度:CIF
    uint8   snapshot_quality;       // 质量:1~6
    uint8   snapshot_period;        // 截图间隔
    uint16  snapshot_num;           // 截图张数
    uint8   snapshot_link[MAX_CH];  // 联动截图通道
    PT_TMSCHEDULE_S snapshot_plan;  // 定时截图时间
    uint8  snapshot_en_plan;        // 截图开关定时
    uint8  snapshot_en_motion;      // 截图开关移动
    uint8  snapshot_en_alm;         // 截图开关报警
    uint8  snapshot_en_manu;        // 截图开关手动
    uint32 reserve;//
} PT_SNAPSHOT_CONFIG_S, *PPT_SNAPSHOT_CONFIG_S;

// 夏令时按周设置时间
typedef struct
{
    uint16    month;        //夏令时按周设置，月
    uint16    weeks;        //夏令时按周设置，周
    uint16    week;         //夏令时按周设置，星期
    uint16    hour;         //夏令时按周设置,     时
    uint16    min;          //夏令时按周设置，分
    uint16    sec;          //夏令时按周设置，分
} PT_DST_WEEK_TIME_S;

//夏令时时间设置
typedef struct
{
    sint16  dst_en;                     //夏令时使能键
    uint16  dsttype_en;                 //按周设置为0, 按日期设置为1

    PT_MFSTIME_S start_date;            //按日期设置的开始时间
    PT_MFSTIME_S end_date;              //按日期设置的结束时间
    PT_DST_WEEK_TIME_S  start_time;     //按周设置的开始时间
    PT_DST_WEEK_TIME_S  end_time;       //按周设置的结束时间
    uint32  reserve;
} PT_DST_TIME_S;


typedef enum
{
    SECFILE_QUERY_MONTH = 0,    //录像文件月历查询
    SECFILE_QUERY_DATA,         //录像数据查询
    SECFILE_QUERY_PAGEUP,       //录像数据查询翻页，上翻
    SECFILE_QUERY_PAGEDOWN,     //录像数据查询翻页，下翻
    SECFILE_QUERY_PAGEGOTO,     //录像数据查询翻页，跳转
} PT_SECFILE_OP_TYPE_E;

/*备份方式选择，目前支持按段、按天、按月备份*/
typedef enum
{
    BACKUP_BY_SEG = 0,
    BACKUP_BY_DAY,
    BACKUP_BY_MON,
    BACKUP_BY_YEAR,
    BACKUP_BY_TIMESEG,          //按时间段备份，可以兼容跨天 跨月等
    BACKUP_BY_FILES,            //按文件备份
} PT_SECFILE_BACKUP_TYPE_E;

typedef enum
{
    DATA_CODETYPE_REC = 0x00,       /* 视频流 */
    DATA_CODETYPE_PIC = 0x80,       /* 图片流 */
    DATA_CODETYPE_PIC_IPC = 0x90,   /* 网络图片流 */
    DATA_CODETYPE_BACKUP = 0x100,   /* 备份流*/
    DATA_CODETYPE_IPPRI = 0x10,     /* 网络主视频流*/
    DATA_CODETYPE_IPSEC = 0x11,     /* 网络次视频流 */
    DATA_CODETYPE_IPTHR = 0x12,     /* 网络第三视频流 */
    DATA_CODETYPE_MULTI = 0x13,      /* 零通道视频流 */
    DATA_CODETYPE_CARD = 0xFF,      /*卡号视频流*/
} PT_DATA_CODETYPE_E;


/* 存储文件属性(按位表示),最多支持8种属性 */
typedef enum
{
    PT_FILEATTR_UNKNOWN = 0x00,
    PT_FILEATTR_RREAD = 0x01,      /* 可读 */
    PT_FILEATTR_WRITE = 0x02,      /* 可写 */
    PT_FILEATTR_LOCK = 0x04,       /* 锁定 */
    PT_FILEATTR_DELETE = 0x08,     /* 删除 */
} PT_FILEATTR_E;

/* 存储数据其他公司的类型代码,最多支持255个 */
typedef enum
{
    PT_COMPANYCODE_HBGK = 0x00,        /* 汉邦高科 */
    PT_COMPANYCODE_HIKVISION = 0x01,   /* 海康威视 */
    PT_COMPANYCODE_DAHUA = 0x02,       /* 浙江大华 */
} PT_COMPANYCODE_E;

typedef enum
{
    OPT_NORMAL = 0,
    OPT_REPLAY,
    OPT_FORMAT,
    OPT_BACKUP,
    OPT_UPGRADE,
    OPT_LOCK,
    OPT_UNLOCK,
    OPT_DEL,
    OPT_OTHER,
} PT_OPT_TYPE_E;

/* 文件格式 */
typedef enum
{
    PT_FILELAYOUT_DAT,      /* 汉邦专有文件,扩展名为.dat */
    PT_FILELAYOUT_AVI,      /* 标准AVI视频,扩展名为.avi */
    PT_FILELAYOUT_JPG,      /* 标准JPG图片,扩展名为.jpg */
    PT_FILELAYOUT_LOG,      /* 汉邦专有文件,扩展名为.log */
} PT_FILELAYOUT_E;

// 录像数据查询结果(图片，录像),每段的信息
typedef struct
{
    PT_MFSTIME_S time_start;// 数据段开始时间
    PT_MFSTIME_S time_stop; // 数据段结束时间
    uint64  data_size;      // 段数据长度,字节
    uint16  idx_amount;     // 如果存储数据为音视频数据,则表示I帧索引项总数;如果存储数据为图片,则表示图片总数
    uint8   channel;        // 段数据通道号(0~255)
    uint8   store_type;     // 段数据属性(PT_RECTYPE_E)
    uint8   code_type;      // 存储数据编码类型(PT_DATA_CODETYPE_E)
    uint8   dev_type;       // 设备类型(PT_DEVTYPE_E)
    uint8   dev_num;        // 设备号(0~63)
    uint8   dev_part;       // 分区数(0~31)
    uint16  file_num;       // 文件序号(0~16383)
    uint8   file_attr;      // 文件或文件段类型标记(PT_FILEATTR_E)
    uint8   company_code;   // 厂商的类型代码(PT_COMPANYCODE_E)
    uint8   segment;        // 存储数据段信息序号(0~254)
    uint8   use_stat;       // 该数据段使用状态
    uint8   is_link;        // 是否拼接(MFS_FLASE-未拼接,MFS_TRUE-已拼接)
    uint8   reserve;        // 保留位
} PT_RECFILE_SEGINFO_S, *PPT_RECFILE_SEGINFO_S;

// 文件管理查询(包括月历查询)
typedef struct
{
    sint32     ch_no;			    // 通道号
    uint8      dev_type;            // 源设备类型 ,见PT_DEVTYPE_E
    uint8      dev_no;              // 查询设备号
    uint8      data_type;		    // 数据类型,见PT_DATA_CODETYPE_E
    uint8      rec_type;			// 记录类型 :手动，定时，移动，报警，全部,PT_RECTYPE_E
    sint8      card_no[32];         // 卡号
    uint16     data_attri;			// 读写属性；0--全部，1--锁定，2--未锁定
    uint16     file_type;           // 备份的文件格式 0---汉邦 1---AVI 2-jpg
    uint32     start_num;           // 查询起始条数，默认为0,SYSNETAPI_CMD_QUERY_REC_DATA时有效
    uint32     limit_num;           // 期望查询条数，SYSNETAPI_CMD_QUERY_REC_DATA时有效
    uint32     rec_status;     	    // 日历掩码，SYSNETAPI_CMD_QUERY_REC_DATE时此参数为输出参数，按位表示有数据的日期
    PT_MFSTIME_S    start_date;	    // 查询开始日期
    PT_MFSTIME_S    end_date;	    // 查询结束日期，按时间段查询时有效
    uint8      move_area[PT_MAX_INTEL_BLOCK_NUM];      // 智能搜索区域标记，按位表示，1代表选中，总计22*18=396位，按顺序排列，智能搜索查询时有效
    uint16     intel_flag;//智能搜索标记，为1时，move_area有效
    uint16     intel_mode;//智能搜索模式，1:自动 0:手动
} PT_RECFILE_QUERY_S, *PPT_RECFILE_QUERY_S;


typedef struct
{
    uint32 query_num;   // 实际查出来的条数
    uint32 total_num;   // 当前查询条件下的总条数
    PPT_RECFILE_SEGINFO_S   recfile_seginfo;    //每条数据段的信息，此数据buf由外部申请
} PT_RECFILE_QUERYINFO_S, *PPT_RECFILE_QUERYINFO_S;


typedef struct
{
    PT_RECFILE_QUERY_S        query_condition;  // 查询所需条件
    PT_RECFILE_QUERYINFO_S    query_info;       // 查询反馈结果
} PT_QUERY_RECFILE_ALL_S, *PPT_QUERY_RECFILE_ALL_S;

//文件管理操作
typedef struct
{
    uint32  op_type;            // 操作类型 : 锁定，解锁，删除，备份,见PT_OPT_TYPE_E
    uint8	bk_ch[PT_MAX_REC_CH_NUM];   // 操作通道 1位代表一个通道
    uint32	rec_type;           // 录像类型：手动、定时、移动、报警,PT_RECTYPE_E
    uint32  data_type;          // 数据类型  图片 、录像，见PT_DATA_CODETYPE_E定义
    uint32  backup_type;        // op_type为OPT_BACKUP时有效，见PT_SECFILE_BACKUP_TYPE_E
    uint32  backup_dev_ch;      // op_type为OPT_BACKUP时有效，备份设备挂载通道
    uint32  backup_dev_type;    //备份设备类型，见PT_DEVTYPE_E
    uint16  backup_foramt;      //op_type为OPT_BACKUP时有效，备份文件格式(.dat .avi .jpg等，见PT_FILELAYOUT_E)
    uint16  data_attri;			// 读写属性；0--全部，1--锁定，2--未锁定
    PT_MFSTIME_S start_time;    // 开始时间，按时间段、按天、按月等备份时有效
    PT_MFSTIME_S end_time;      // 结束时间，按时间段、按天、按月等备份时有效
    uint32  op_num;             // 默认为0，要对指定数据段进行操作时有效，表示选定的数据条数
    uint32	backup_opt;			// 备份操作 0--手动备份 1--快速备份 2--定时备份 见PT_BACKUP_OP_E
    PPT_RECFILE_SEGINFO_S   recfile_seginfo;// 默认为NULL，要对指定数据段进行操作时有效，选定的每条数据段的信息
} PT_RECFILE_OP_S, *PPT_RECFILE_OP_S;

// 日志管理查询
typedef struct
{
    PT_MFSTIME_S date;          // 日期  input
    sint16  pri_type;           // 主类型
    sint16  sec_type;           // 辅类型
    uint32  log_status;         // 月-日    日志状态，用掩码表示 output
    PT_DEVTYPE_E  dev_type;     // 源设备类型 ,见PT_DEVTYPE_E input
} PT_QUERY_LOGMASK_S, *PPT_QUERY_LOGMASK_S; //按月查询获取日志掩码

typedef struct
{
    sint32      ch_no;			    // 通道号
    sint32      data_type;		    // 数据类型,见PT_DATA_CODETYPE_E
    PT_MFSTIME_S    start_date;	    // 查询开始日期
    PT_MFSTIME_S    end_date;	    // 查询结束日期，按时间段查询时有效
    uint8      move_area[PT_MAX_INTEL_BLOCK_NUM];      // 智能搜索区域标记，按位表示，1代表选中，总计22*18=396位，按顺序排列，智能搜索查询时有效
    uint16     intel_mode;//智能搜索模式，1:自动 0:手动
} PT_INTEL_PB_S, *PPT_INTEL_PB_S;

typedef struct
{
    sint32      ch_no;			    // 通道号
    sint32      data_type;		    // 数据类型,见PT_DATA_CODETYPE_E
    PT_MFSTIME_S    start_date;	    // 查询开始日期
    PT_MFSTIME_S    end_date;	    // 查询结束日期，按时间段查询时有效
    uint8       move_area[PT_MAX_INTEL_BLOCK_NUM];      // 智能搜索区域标记，按位表示，1代表选中，总计22*18=396位，按顺序排列，智能搜索查询时有效
    uint32      limit_num;          // 期望查询条数
    uint32      query_num;          // 实际查出来的条数
    PPT_RECFILE_SEGINFO_S   recfile_seginfo;//每条数据段的信息，此数据buf由外部申请
} PT_INTEL_QUERYINFO_S, *PPT_INTEL_QUERYINFO_S;


//一个点的坐标
typedef struct
{
    sint16	x;          //横坐标
    sint16	y;          //纵坐标
} PT_POINT_S, *PPT_POINT_S;

/**************** 智能模块使用信息****************/

//矩形坐标
typedef struct
{
    uint32 left;            //矩形左坐标
    uint32 top;             //矩形上坐标
    uint32 right;           //矩形右坐标
    uint32 bottom;          //矩形下坐标
} PT_ATMI_RECT, *PPT_ATMI_RECT;

//多边形表示结构体，带区域类型
typedef struct
{
    PT_POINT_S  point[10];      //多边形顶点坐标
    sint32 	   point_num;       //点的个数
    sint32      region_type;    //区域类型
} PT_ATMI_POLYGON_S, *PPT_ATMI_POLYGON_S;

//矩形区域，带区域类型
typedef struct
{
    PT_ATMI_RECT region;        //矩形区域坐标
    sint32 region_type;         //区域类型
} PT_ATMI_RECT_TYPE_S, *PPT_ATMI_RECT_TYPE_S;

//人脸感兴趣区域以及该区域中人脸的大小
typedef struct
{
    PT_ATMI_RECT_TYPE_S roi;    //坐标
    sint32 min_face;            //最小尺寸
    sint32 max_face;            //最大尺寸
} PT_ATMI_FACE_ROI_S, *PPT_ATMI_FACE_ROI_S;

// 1.人脸通道中所设置的区域
typedef struct
{
    sint32 num;
    PT_ATMI_FACE_ROI_S face_roi[10];
} PT_ATMI_FACEROI_ALL_S, *PPT_ATMI_FACEROI_ALL_S;

// 2.面板通道中所设置的区域
typedef struct
{
    sint32 num;
    PT_ATMI_POLYGON_S atmi_panel_region[20];
} PT_ATMI_PANEL_REGION_S, *PPT_ATMI_PANEL_REGION_S;

// 3.加钞间通道中所设置的区域及参数
typedef struct
{
    PT_ATMI_POLYGON_S pol_proc_region;	// 处理区域，默认4个点，包含全图
    PT_ATMI_RECT_TYPE_S no_process[10]; // 不处理区域
    sint32 no_process_num;		        // 不处理区域个数 (0)
    sint32 warn_interval;	            // 两次报警时间间隔，(100 秒)
} PT_ATMI_DISTRICTPARA_S, *PPT_ATMI_DISTRICTPARA_S;

// 4.场景通道中所设置的区域
typedef	struct
{
    PT_ATMI_POLYGON_S pol_proc_region;  // 图像中的处理区域，多边形表示

    /*用于ATM机前尾随取款检测的参数，标识ATM前人站立的区域*/
    PT_ATMI_POLYGON_S tail_region[10];  // Region in polygon.
    sint32 tail_num;				    // Region number. default: 0

    /*用于禁止区域进入报警，标识选定的禁止进入的区域*/
    PT_ATMI_POLYGON_S forbid_region[10];// Region in polygon.
    sint32 forbid_num;					// Region number.	default: 0

    //sint32 obj_height;		        // 目标（人）在图像中的高度，默认85
    PT_ATMI_POLYGON_S obj_height;
} PT_ATMI_SCENE_COMMONPARA_S, *PPT_ATMI_SCENE_COMMONPARA_S;

// 5.环境通道设置的参数,以下以帧为单位的，我们在界面上做为秒，然后在内部再转化为帧数
typedef struct
{
    /*物品遗留算法相关参数*/
    sint32 objlv_frames_th;				// 物品遗留时间阈值(帧) (30)

    /*人员徘徊算法相关参数*/
    sint32 mv_block_cnt;			    // 移动距离(20，0表示此规则无效)
    sint16 mv_stay_frames;			    // 场景中出现时间阈值(帧),存在总时间(0表示此规则无效)
    sint16 mv_stay_valid_frames;	    // ATM区域停留时间阈值(帧),ATM区域前停留时间(200, 0表示此规则无效)

    /*多人聚集算法相关参数*/
    sint16 gather_cnt;				    // 最多聚集人数(4)
    sint16 gather_interval_frames;	    // 报警间隔时间(帧)(1000 frames,约100秒)
    sint32 gather_frame_cnt;		    // 多人聚集时间阈值(帧) (100)

    /*人员躺卧算法相关参数*/
    sint32 liedown_frame_cnt;		    // 躺卧时间阈值(帧).(20 frames)

    /*尾随取款算法相关参数*/
    sint16 after_frame_cnt;				// 可疑行为时间阈值(帧)(20 frames)
    sint16 after_interval_frames;	    // 报警间隔时间(帧)(1000 frames,约100秒)

    /*禁止进入算法相关参数*/
    sint16 forbid_frame_cnt;		    // 禁止站立时间阈值(帧)(20 frames)
    sint16 reserve;                                            // 保留
} PT_ATMI_SCENE_WARN_PARAM_S, *PPT_ATMI_SCENE_WARN_PARAM_S;

// 1.人脸通道设置结构体
typedef struct
{
    sint16 face_unusual;                //是否打开异常人脸（戴口罩、蒙面等）检测功能，1 为打开，0 为关闭。默认为 0
    sint16 output_oneface;              //设置人脸只输出一次与否，0为否，1为是，默认为1
    sint32 fd_rate;                     //设置人脸检测跟踪间隔
    PT_ATMI_FACEROI_ALL_S face_roi;     //人脸通道的区域及其它参数
} PT_ATMI_SET_FACE_S, *PPT_ATMI_SET_FACE_S;

// 2.面板通道设置结构体
typedef struct
{
    sint32 timeout_enable;              //超时时间
    PT_ATMI_PANEL_REGION_S panel_region;//面板通道区域及其它参数
} PT_ATMI_SET_PANEL_S, *PPT_ATMI_SET_PANEL_S;

// 3.加钞间通道设置结构体
typedef struct
{
    PT_ATMI_DISTRICTPARA_S money_para; //加钞间通道区域及其它参数
} PT_ATMI_SET_MONEY_S, *PPT_ATMI_SET_MONEY_S;

// 4.环境通道设置结构体
typedef struct
{
    PT_ATMI_SCENE_WARN_PARAM_S envi_para;   //环境通道参数
    PT_ATMI_SCENE_COMMONPARA_S envi_region; //环境通道区域
} PT_ATMI_SET_ENVI_S, *PPT_ATMI_SET_ENVI_S;

//GUI设置到主控的总的结构体
typedef struct
{
    sint32 chn;                             //通道号
    sint32 chn_attri;                       //通道属性(人脸、面板、加钞、环境)，目前未用，防止以后用

    sint16 channel_enable;                  //通道开关，0关闭，1打开
    sint16 if_pic;                          //是否需要抓取图片
    sint16 enc_type;                        //抓取图片的格式
    sint16 email_linkage;                   //联动email
    uint32 sensor_num;                      //探头输出,位表示
    uint32 rec_linkage;                     //联动录像，位表示

    /*按通道号分别取下面的结构，每次只能对应一个*/
    PT_ATMI_SET_FACE_S face_set_para;       //人脸通道设置结构体
    PT_ATMI_SET_PANEL_S panel_set_para;     //面板通道设置结构体
    PT_ATMI_SET_MONEY_S money_set_para;     //加钞间通道设置结构体
    PT_ATMI_SET_ENVI_S envi_set_para;       //环境通道设置结构体
} PT_ATMI_NET_SYS_S, *PPT_ATMI_NET_SYS_S;

//报警类型及位置信息
typedef struct
{
    sint32 alarm_type;          //类型,GUI_ATMI_ALARM_TYPE_E
    PT_ATMI_RECT position;      //坐标位置
} PT_ATMI_ALARM_POSITION_S, *PPT_ATMI_ALARM_POSITION_S;

// 1.人脸通道报警结构体
typedef struct
{
    sint32 alarm_num;                           //报警个数
    PT_ATMI_ALARM_POSITION_S alarm_area[10];    //报警坐标值,一共有alarm_num个，后面的全为0
} PT_ATMI_FACE_ALARM_S, *PPT_ATMI_FACE_ALARM_S;

// 2.面板通道报警结构体
typedef struct
{
    sint32 alarm_num;                           //报警个数
    PT_ATMI_ALARM_POSITION_S alarm_area[10];    //报警坐标值,一共有alarm_num个，后面的全为0
} PT_ATMI_PANEL_ALARM_S, *PPT_ATMI_PANEL_ALARM_S;

// 3.加钞间检测输出信息
typedef struct
{
    sint32 type; //是否有人闯入，0表示无，1表示有
} PT_ATMI_MONEY_ALARM_S, *PPT_ATMI_MONEY_ALARM_S;

// 4.环境报警结构体,alarm_num所对应的区域在前，track_num所对应的区域紧跟在alarm_num区域后
typedef struct
{
    sint32 alarm_num;  //报警目标数量
    sint32 track_num;   //跟踪目标数量
    PT_ATMI_ALARM_POSITION_S envi_alarm_region[25];
} PT_ATMI_ENVI_ALARM_S, *PPT_ATMI_ENVI_ALARM_S;

//报警信息，回调给主控，再传给GUI
enum
{
    PT_ATMI_FACE_BLOCK = 0,                 //人脸遮挡
    PT_ATMI_FACE_NOSIGNAL,                  // 有脸通道视频丢失
    PT_ATMI_FACE_UNUSUAL,                   //人脸异常
    PT_ATMI_FACE_NORMAL,                    //人脸正常

    PT_ATMI_PANEL_BLOCK  = 40,              //面板遮挡
    PT_ATMI_PANEL_NOSIGNAL,                 //面板通道视频丢失
    PT_ATMI_PANEL_PASTE,                    //贴条
    PT_ATMI_PANEL_KEYBOARD,                 //装假键盘
    PT_ATMI_PANEL_KEYMASK,                  //破坏密码防护罩
    PT_ATMI_PANEL_CARDREADER,               //破坏读卡器
    PT_ATMI_PANEL_TMIEOUT,                  //超时报警

    PT_ATMI_ENTER,                          //有人进入
    PT_ATMI_EXIT,                           //人撤离

    PT_ATMI_MONEY_BLOCK = 80,               //加钞间视频遮挡
    PT_ATMI_MONEY_NOSIGNAL,                 //加钞间通道视频丢失
    PT_ATMI_MONEY_UNUSUAL,                  //加钞间异常,即有人闯入加钞间

    PT_ATMI_ENVI_BLOCK = 120,               //环境通道视频遮挡
    PT_ATMI_ENVI_NOSIGNAL,                  //环境通道视频丢失
    PT_ATMI_ENVI_GATHER,                    //多人聚集
    PT_ATMI_ENVI_MANYPEOPLEINREGION,        //违规取款
    PT_ATMI_ENVI_LINGERING,                 //人员徘徊
    PT_ATMI_ENVI_LIEDOWN,                   //人员倒地
    PT_ATMI_ENVI_FORBIDREGION,              //非法进入警戒区
    PT_ATMI_ENVI_LEAVEOBJECT,               //物品遗留
} PT_ATMI_ALARM_TYPE_E;


//图片信息
typedef struct
{
    sint32 pic_alarm_type;  //PT_ATMI_ALARM_TYPE_E
    sint32 pic_format;      //图片格式CIF:0  D1:1
    uint32 pic_size;        //图片大小
} PT_ATMI_ALARM_PICINFO_S, *PPT_ATMI_ALARM_PICINFO_S;

//报警时传给主控的总结构体
typedef struct
{
    sint32 chn;                             // 通道号,每次报警后，根据通道号，去读取下面四个结构体中对应的那一个

    /*按通道号分别取下面的结构，每次只能对应一个*/
    PT_ATMI_FACE_ALARM_S atmi_face_alarm;   // 1.人脸通道报警结构体
    PT_ATMI_PANEL_ALARM_S atmi_panel_alarm; // 2.面板通道报警结构体
    PT_ATMI_MONEY_ALARM_S atmi_money_alarm; // 3.加钞间通道报警结构体
    PT_ATMI_ENVI_ALARM_S atmi_envi_alarm;   // 4.环境通道报警结构体

    PT_ATMI_ALARM_PICINFO_S   alarm_picinfo;// 报警图片信息
    PT_MFSTIME_S alarmtime;                 //报警时间
} PT_ATMI_ALARM_INFO_S, *PPT_ATMI_ALARM_INFO_S;


/*****************视频参数扩展结构体*************************/

//关键帧相关的结构体
typedef struct
{
    PT_AUSTREAMADD_E byStreamType;          //视频流类型
    PT_RESOLUTION_E byResolution;           //视频分辨率
    PT_BITRATETYPE_E byBitrateType;         //码率类型
    PT_VQUALITY_E byPicQuality;             //图像质量
    uint16 dwVideoBitrate;                  //视频码率 实际码率
    uint16 dwVideoFrameRate;                //帧率 PAL 2-30 N 2-30
    uint16 quant;                           //量化因子 1-31
    uint16 key_interval;                    // 关键帧间隔0-65535
} PT_ENCCONFIG_EXL_S, *PPT_ENCCONFIG_EXL_S;

typedef struct
{
    PT_STREAMTYPE_E streamtype;             //要设置或者获取的码流类型
    PT_RECTYPE_E       rectype;             //录像类型
    PT_ENCCONFIG_EXL_S enc;                 //编码参数
} PT_STREAMENCPARAM_EXL_S, *PPT_STREAMENCPARAM_EXL_S;

typedef struct
{
    PT_VERSION_S swver;             // 主控类型
    sint8 oem_ver[32];              // oem版本类型  不使用的话请全部置0
    sint32 reserve;
} PT_SYSVERSION_S, *PPT_SYSVERSION_S;

//模块版本结构体
typedef struct
{
    int   num;//获取版本号的模块数
    sint8 vi[MAX_VER_LEN];
    sint8 vo[MAX_VER_LEN];
    sint8 venc[MAX_VER_LEN];
    sint8 vdec[MAX_VER_LEN];
    sint8 ai[MAX_VER_LEN];
    sint8 ao[MAX_VER_LEN];
    sint8 rec[MAX_VER_LEN];
    sint8 pb[MAX_VER_LEN];
    sint8 statm[MAX_VER_LEN];
    sint8 upgrade[MAX_VER_LEN];
    sint8 uart[MAX_VER_LEN];
    sint8 ptz[MAX_VER_LEN];
    sint8 event[MAX_VER_LEN];
    sint8 fifo[MAX_VER_LEN];
    sint8 mshead[MAX_VER_LEN];
    sint8 mfs[MAX_VER_LEN];
    sint8 timer[MAX_VER_LEN];
    sint8 shmem[MAX_VER_LEN];
    sint8 msg[MAX_VER_LEN];
    sint8 ddns[MAX_VER_LEN];
    sint8 network[MAX_VER_LEN];
    sint8 trans_uart[MAX_VER_LEN];
    sint8 daemon[MAX_VER_LEN];
    sint8 aenc[MAX_VER_LEN];
    sint8 adec[MAX_VER_LEN];
    sint8 m_uboot[MAX_VER_LEN];
    sint8 m_kernel[MAX_VER_LEN];
    sint8 sdk[MAX_VER_LEN];
    sint8 serial[MAX_VER_LEN];
    sint8 svn_info[MAX_VER_LEN];
    sint8 p2p_sn[MAX_VER_LEN];

    sint8 reserve[13][MAX_VER_LEN];//保留,供扩展
} PT_COMPVERSION_S, *PPT_COMPVERSION_S;


// 图像画面边缘调整
typedef struct
{
    uint16 x, y; // xy坐标
    uint16 w, h; // 宽度和高度
} PT_RECT, *PPT_RECT;

typedef struct
{
    uint16  channel;        // 通道
    uint16  enable;    //开/关EQ
    uint16  type;      //线类型
    uint16  length;    //线长度
} PT_EQ_CONFIG, *PPT_EQ_CONFIG;

typedef struct
{
    uint32 split;                   // 分割方式1-1, 2-2 4-2x2, 9-3x3, 16-4x4
    uint32 anti_flicker;      // 是否开启CVBS抗闪 0-不开 1-开启
    PT_RECT vo_coordinate;          // 视频输出偏移，x,y起始坐标 w-x方向上的增量 h-y方向上的增量
    PT_RECT vi_coordinate[MAX_CH];  // 视频输入偏移
} PT_VRECT_CONFIG, *PPT_VRECT_CONFIG;

typedef enum
{
    PT_CONFIG_CHANAGE = 0X100,	    //通知平台配置文件有变化
    PT_STATUS_NOTIFY,			    //平台状态主动通知
} PT_SGPT_NOTIFY_E;

typedef struct
{
    uint8 dvr_start;                //DVR系统启动，0-未启动，1-启动
    uint8 dvr_normal_shutdown;      //DVR系统退出，0-未退出，1-退出
    uint8 dvr_abnormal_down;        //DVR异常退出，0-未发生，1-发生
    uint8 dvr_setparam;             //DVR参数设置，0-未发生，1-发生
    uint8 dvr_videolost;            //DVR视频丢失，0-未发生，1-发生
    uint8 dvr_motion_detection;     //DVR移动侦测，0-未发生，1-发生
    uint8 dvr_outtigger;            //DVR外部触发，0-未发生，1-发生
    uint8 dvr_alarmremove;          //系统报警解除，0-未发生，1-发生
    uint8 dvr_illegal_quit;         //DVR非法退出，0-未发生，1-发生
    uint8 dvr_local_playback;       //DVR本地回放，0-未发生，1-发生
    uint8 dvr_remote_playback;      //DVR远程回放，0-未发生，1-发生
    uint8 dvr_disk_err;             //DVR磁盘错误，0-未发生，1-发生
    uint8 sys_heart_out;            //系统心跳超时，0-未发生，1-发生
    uint8 sys_heart_remove;         //系统心跳恢复，0-未发生，1-发生
    uint8 other_videothing;         //视频其他事件，0-未发生，1-发生
    uint8 reserver[9];
} PT_SGPT_STATUE_S, *PPT_SGPT_STATUE_S; //平台状态结构体

typedef enum
{
    OSD_NOTIFY,
    NET_NOTIFY,
    MFS_NOTIFY,
    SERIAL_NOTIFY,
    NETMS_PRI_DATA,
    NETMS_SEC_DATA,
} CALLBACK_TYPE_E; //注册PNETAPICALLBACK时的回调类型


typedef struct
{
    uint32 en_time_reboot;
    uint32 week;                        //重启时间-日(0-每天，1---7对应周一到周日)
    uint32 hour;
    uint32 reserve;
} PT_TIME_REBOOT_S, *PPT_TIME_REBOOT_S;

// 定时备份
typedef struct
{
    uint8 ch;                           //定时备份设备挂载通道
    uint8 dev_type;                     //备份设备类型
    sint8 rec_type;                     //录像类型 -1---全部，0---手动录像，1---定时录像， 2---移动录像，3---报警录像
    uint8 en_time_backup;               //是否开启定时备份  0---不开启， 1---开启
    uint8 cycle;                        //备分周期  0---每天，1-7---周一至周日
    uint8 ch_no[PT_MAX_REC_CH_NUM];        //有效定时备份通道号(1为选中，0为未选中)
    uint8 time;                         //0-23---0点至23点
    uint8 cover_mode;                   //磁盘满覆盖模式 0---自动覆盖, 1---手动覆盖
    sint8 file_type;                    // 备份的文件格式 0---汉邦 1---AVI
    sint8 reserve[2];
} PT_TIME_BACKUP_S, *PPT_TIME_BACKUP_S;


//时间条录像状态
typedef enum
{
    PT_TIME_RULE_NONE,
    PT_TIME_RULE_MANUAL,
    PT_TIME_RULE_TIME,
    PT_TIME_RULE_MOTION,
    PT_TIME_RULE_ALARM,
    PT_TIME_RULE_CARD,
    PT_TIME_RULE_INTELSEARCH,
} PT_REC_STAT_TYPE_E;

typedef struct
{
    char data_mask[PT_GRAPH_DATA_MASK_NUM]; //24小时12分钟精度，2小时1分钟精度，1小时30秒精度，半小时15秒精度  PT_REC_STAT_TYPE_E
} PT_SEARCH_REC_DATA_GRAPH_MAKS_S;

typedef struct
{
    PT_SEARCH_REC_DATA_GRAPH_MAKS_S	graph_data[PT_REC_DATA_GRAPH_PAGE_NUM];	//图形显示掩码数据
    sint32 precision;													    //图形精度，单位为秒
} PT_SEARCH_REC_DATA_GRAPH_DATA_S;

typedef struct
{
    sint16		ch_s[PT_GRAPH_REC_CH_NUM];				    //通道数据，目前设计一次查8个通道，存放选中的通道号
    PT_MFSTIME_S 	start_time;								//开始时间
    PT_MFSTIME_S 	end_time;								//结束时间，目前的时间段应该是24小时，2小时，1小时，半小时中的一种情况
    sint32 		dev_no;									    //设备号，查询备份设备使用，暂时不使用
    sint16		rec_type;								    //录像数据类型,目前设置的应该都是全类型
    sint16      data_type;                                  //0x00-视频流,  0x80-图片流
    PT_SEARCH_REC_DATA_GRAPH_DATA_S	data_graph_data;
    uint32 	    reserve;
} PT_SEARCH_REC_DATA_GRAF_S;

typedef struct
{
    sint32  type;       /* PT_RECTYPE_E */
    PT_MFSTIME_S start_time;
    PT_MFSTIME_S end_time;
} PT_REC_SEG_S;

typedef struct
{
    PT_MFSTIME_S query_date;
    sint16  rec_type;   /* PT_RECTYPE_E */
    sint16  file_type;  /* 备份的文件格式 0---汉邦 1---AVI 2-jpg */
    sint16  data_type;  /* PT_DATA_CODETYPE_E */
    sint16  dev_type;   /* 数据源设备类型 ,见PT_DEVTYPE_E */
    sint32  seg_max;    /* 缓冲区大小 buf_size/sizeof(PT_REC_SEG_S) */
    sint32  seg_num;    /* 返回总共读取的段数 */
    uint8      move_area[PT_MAX_INTEL_BLOCK_NUM];      // 智能搜索区域标记，按位表示，1代表选中，总计22*18=396位，按顺序排列，智能搜索查询时有效
    uint16     intel_flag;//智能搜索标记，为1时，move_area有效
    PT_REC_SEG_S * rec_seg;
} PT_REC_DATE_SEG_S;

typedef struct
{
    PT_SEARCH_REC_DATA_GRAPH_MAKS_S	graph_data;	//图形显示掩码数据
    sint32 precision;   //图形精度，单位为秒
} PT_SMART_SEARCH_DATA_GRAPH_DATA_S;

typedef struct
{
    sint32		ch;				                            //通道数据，目前设计一次查8个通道，存放选中的通道号
    PT_MFSTIME_S 	start_time;								//开始时间
    PT_MFSTIME_S 	end_time;								//结束时间，目前的时间段应该是24小时，2小时，1小时，半小时中的一种情况
    PT_SMART_SEARCH_DATA_GRAPH_DATA_S data_graph_data;
} PT_SMART_SEARCH_DATA_GRAF_S;

typedef struct
{
    uint16 x;
    uint16 y;
    uint16 w;
    uint16 h;
} PT_RCWH_S;

//视频局部放大
typedef struct
{
    sint32 enable; 					// 使能 1-启用区域放大 0-取消区域放大
    sint32 video_mode; 			    // 0-预览 1-回放
    sint32 ch_no; 					// 预览下--实际通道号，从0开始  回放下---0
    sint32 output_dev;              /* 需区域放大的输出设备 */  
    PT_RCWH_S src_area;             // 源区域
    PT_RCWH_S dest_area;            // 目标区域
} PT_VIDEO_ZOOMIN_S;

typedef enum
{
    SDK_SPLIT_ONE = 1,
    SDK_SPLIT_TWO = 2,
    SDK_SPLIT_FOUR = 4,
    SDK_SPLIT_SIX = 6,          // 只有设备HD支持
    SDK_SPLIT_EIGHT = 8,        // 8路机器
    SDK_SPLIT_NINE = 9,         // 16路机器
    SDK_SPLIT_NINE_EX = 10,     //9画面扩展不规则分屏,实际显示6画面(1大+5小)
    SDK_SPLIT_TWELVE = 12,
    SDK_SPLIT_SIXTEEN = 16,
    SDK_SPLIT_SIXTEEN_EX = 17,  //16画面扩展不规则分屏,实际显示8画面(1大+7小)
    SDK_SPLIT_SIXTEEN_EX2 = 18, //16画面扩展不规则分屏,实际显示13画面(中间1大+四周12小)
    SDK_SPLIT_TWENTY = 20,
    SDK_SPLIT_TWENTYFOUR = 24,
    SDK_SPLIT_TWENTYFIVE = 25,
    SDK_SPLIT_THIRTYTWO = 32,
    SDK_SPLIT_THIRTYSIX = 36,
    SDK_SPLIT_TWENTYFIVE_EX = 40,///* 25画面不规则分屏,实际显示13画面,大4+小9,9012X3机型 */
    SDK_SPLIT_THIRTYSIX_EX = 41, ///* 36画面不规则分屏,实际显示24画面,大4+小20,9020X3机型 */
    SDK_SPLIT_PATTERN144    = 44,/* 12*12画面规则分屏 */
    SDK_SPLIT_PATTERN144_EX = 45,/* 12*12画面不规则分屏,实际显示20画面,大4+小16，9020X3机型 */
} SDK_SPLIT_E;

/* 当前实时回放状态 */
typedef enum
{
    PT_VIDEO_MODE_LIVE = 0,
    PT_VIDEO_MODE_REPLAY = 1,
    PT_VIDEO_MODE_NVD = 2,      /* 组网预览模式 */
} PT_VIDEO_MODE_E;

/* 组网预览时切换类型 */
typedef enum
{
    PT_IPD_MODE_NVD = 0,
    PT_IPD_MODE_IPC = 1,
}PT_IPD_MODE_E;

typedef enum
{
    PT_SPLIT_SCREEN0 = 0,
    PT_SPLIT_SCREEN1 = 1,
    PT_SPLIT_SCREEN2 = 2,
    PT_SPLIT_SCREEN3 = 3,
    PT_SPLIT_SCREEN4 = 4,
    PT_SPLIT_SCREEN5 = 5,
    PT_SPLIT_SCREEN6 = 6,
    PT_SPLIT_SCREEN7 = 7,
    PT_SPLIT_SCREEN8 = 8,
    PT_SPLIT_SCREEN9 = 9,

    PT_SPLIT_SCREEN_PREV = 0xFE,    /* previous 上一屏 */
    PT_SPLIT_SCREEN_NEXT = 0xFF,    /* 下一屏 */
} PT_SPLIT_SCREEN_E;

//分屏设置获取
typedef struct
{
    uint16  type;                           // SDK_SPLIT_E 分割方式1-1,4-2x2,6-3x2,9-3x3,16-4x4
    uint16  video_mode;                     // 0--live;	1--replay PT_VIDEO_MODE_E
    sint16  ch_list[PT_MAX_REC_CH_NUM];     // 通道顺序
    uint16  main_ch;                        /* 指定音频通道,需是ch_list中的通道 */
} PT_IMAGE_SPLIT_S, *PPT_IMAGE_SPLIT_S;

/* 按指定格式向前后切屏 */
typedef struct
{
    sint32 type;                /* SDK_SPLIT_E */
    sint32 screen;              /* PT_SPLIT_SCREEN_E */
}PT_SCREEN_SPLIT_S;

//视频输出样式
typedef struct
{
    uint32 split_ch_num;        //该种分屏格式拥有的通道数
    uint16 x_cell_num;          //横分次数
    uint16 y_cell_num;          //纵分次数
    PT_RECT ch_info[PT_MAX_REC_CH_NUM];
} PT_VOSPLIT_S;

typedef enum
{
    LAMP_NETWORK,        //网络灯
    LAMP_ALARM,          //报警灯
    LAMP_PTZ,            //云台操作指示灯
    LAMP_REC,            //录像指示灯
    LAMP_PPPOE,          //拨号指示灯
    LAMP_REMOTE_LOCK,    //遥控锁定指示灯
} PT_LAMP_TYPE_E;


//网络状态
typedef enum
{
    PT_NET_STAT_COMMON = 0,     //正常
    PT_NET_STAT_IP_CONFLICT,    //IP冲突
    PT_NET_STAT_DISCONNECT,     //网络断开
    PT_NET_INTERNET_OK,         //广域网连接正常，状态栏图标显示正常的图标*/
    PT_NET_INTERNET_ERR,        //广域网连接失败，状态栏图标显示带感叹号的图标*/
} PT_NET_STAT;

//wifi状态
typedef enum
{
    PT_WIFI_CARD_ERR = 20, //网卡被异常拔出
    PT_WIFI_CARD_IN, // 网卡已插入
    PT_WIFI_CARD_OUT, // 网卡已拔出
} PT_WIFI_STAT;

typedef enum
{
    PT_PPPOE_STAT_NOCONNECT,    // 未连接
    PT_PPPOE_STAT_CONNECTING,   // 正在连接
    PT_PPPOE_STAT_CONNECTED,    // 已连接
    PT_PPPOE_STAT_CONNECTERR    // 连接错误
} PT_PPPOE_STAT_E;

/* 备份操作类型 --add by xcli 2015/11/25 */
typedef enum
{
    PT_BACKUP_OP_MANUAL = 0,    /* 手动备份 */
    PT_BACKUP_OP_FAST,   		/* 快速备份 */
    PT_BACKUP_OP_TIME,    		/* 定时备份 */
} PT_BACKUP_OP_E;

typedef struct
{
    sint32      pb_cmd;         //回放控制命令(控制时有效) PT_PLAYBACKSTATUS_E
    sint32 		source;		    //存储介质类型，0-本地磁盘，1-USB设备，2-esata 3-CD/DVD设备
    sint32 		rec_type; 	    //录像类型，PT_RECTYPE_E
    sint32      data_type;      //数据类型,见PT_DATA_CODETYPE_E定义
    SYSTIME 	start_time;	    //录象开始时间
    SYSTIME     end_time;       //录像结束时间(磁盘回放时该值无效)
    sint32      percent;        //用于跳转命令时传递百分比
    sint32      pb_handle;      //回放流句柄(主机回放时无效)输出参数.

    /*以下为主机端回放使用*/
    uint32 		length;		    //数据文件长度
    uint32 		ch;			    //主通道
    uint32 		ch_mask;	    //回放通道掩码
    uint8 		sync; 		    //同步标志
    uint8 		pb_split;	    //回放画面格式SDK_SPLIT_E
    uint16      reserve;
} PT_PLAYBCK_S;

typedef struct
{
    SYSTIME start;  /* 起始时间 */
    SYSTIME stop;   /* 结束时间 */
} PT_PLAYBACK_SETTIME;

typedef enum
{
    PT_ATTR_STATUS_OK = 0,		    /* 该属性正常,未出现问题 */
    PT_ATTR_STATUS_FAILED_BEFORE,   /* 该属性曾经出现问题 */
    PT_ATTR_STATUS_FAILING          /* 该属性当前出现问题 */
} PT_ATTR_STATUS;

typedef struct
{
    sint8   attr_name[32];          /* 名字 */
    sint8   raw_string[32];         /* 原始值 */
    uint16  current;			    /* 当前值 */
    uint16  worst;			        /* 最差值 */
    uint16  flags;                  /* 标志位 */
    uint16  type;                   /* 类型(解析自flags) */
    uint16  update;                 /* 更新类型(解析自flags) */
    uint16  threshold;              /* 阈值 */
    uint16  attr_status;            /* 当前状态PT_ATTR_STATUS_ ( OK | FAILED_BEFORE | FAILING ) 见枚举PT_ATTR_STATUS */
    uint16  reserve;
} PT_SMART_ATTR_S, *PPT_SMART_ATTR_S;

#define PT_MAX_SMART_ATTR_NUM  32
typedef struct
{
    uint32          attr_bit_table;
    PT_SMART_ATTR_S attrs[PT_MAX_SMART_ATTR_NUM];

    char  hdd_type[64];             //磁盘型号
    char  hdd_serial_no[64];        //磁盘序列号
    char  hdd_firmware_ver[64];     //固件版本
    uint16  hdd_entire_status;      //综合健康状态(需要底层定义有那些健康状态)
    uint16  hdd_tmp;                //磁盘温度
    uint32	reserve;
} PT_SMART_INFO_S, *PPT_SMART_INFO_S;

//邮件发送状态
typedef enum
{
    PT_SSMTP_STAT_NOCMD, 			// 没有命令操作
    PT_SSMTP_STAT_SENDINGMAIL, 	    // 正在发送邮件,是一个错误信息
    PT_SSMTP_STAT_SENDMAILOK, 		// 发送邮件成功
    PT_SSMTP_STAT_SENDMAILERR, 	    // 发送邮件失败
    PT_SSMTP_STAT_AUTHFAIL,		    // 认证失败，用户名或密码错误
    PT_SSMTP_STAT_STARTMAIL		    // 开始发送邮件
} PT_SSMTP_STAT_E;

typedef struct
{
    uint32  mdev_num;
    uint32  lckdev_num;
} PT_DEV_NUM, *PPT_DEV_NUM;

//回放OSD 信息
typedef struct
{
    uint32  x;                    // X轴坐标（单位为像素）
    uint32  y;                    // Y轴坐标（单位为像素）
    uint8   data[MAX_STRING];     // 段信息数据内容，如为字符串则包含了结束符'\0'
    uint32  reserve;
} PT_PB_OSD_S, *PPT_PB_OSD_S;

typedef struct
{
    PT_PB_OSD_S gui_pb_name[PT_MAX_PB_NAME];
    uint32  pb_name_type;/*0: 刷主通道OSD； 1:刷回放限制OSD提示*/
} PT_PB_OSD_CH_S, *PPT_PB_OSD_CH_S;

//回放OSD 通道名
typedef struct
{
    uint16 			chlist[PT_MAX_REC_CH_NUM];	    //通道的顺序列表
    PT_PB_OSD_CH_S  ch_name[PT_MAX_REC_CH_NUM];    	//物理顺序排列的OSD
    uint16  		main_ch;						//主通道号
    uint16 			pb_split;						//回放画面格式
} PT_PB_OSD_MULTIPLE_S, *PPT_PB_OSD_MULTIPLE_S;
typedef struct
{
    uint16 			chlist[MAX_CH];	    //回放通道的限制状态1-正常，0-资源不足
} PT_PB_CH_LIMIT_S, *PPT_PB_CH_LIMIT_S;

typedef struct
{
    PT_MFSTIME_S     start_time;//剪辑开始时间
    PT_MFSTIME_S     end_time;  //剪辑结束时间
    uint64      bkup_cap;       //备份所需容量
    uint8       file_num;       //备份文件数目
    uint8       bkup_dev;       //备份设备
    uint8       player_flag;    //是否备份播放器   0---不备份，1---备份
    uint8       file_type;      //保存剪辑文件类型 0---DVR，   1---AVI
    uint32 		ch_mask;		//回放通道掩码
    sint32 		rec_type; 		//当前回放类型
    uint8       cut_flag;       //获取参数或执行剪辑的标志，0-获取信息，1-执行剪辑
    uint8       dev_type;       //设备类型 0-无设备
    uint8       reserve[2];
} PT_PB_CUT_S, *PPT_PB_CUT_S;

typedef struct
{
    char  ip_addr[MAX_IPADDR_STR_LEN];
    PT_RECT rect;                   /* 窗口位置(万分比) */
} PT_DISCOVER_VIEW_S;

typedef struct
{
    SYSTIME start_time;	            /* 录象数据开始时间 */
    PT_RECT rect;                   /* 窗口位置(万分比) */
} PT_PB_WINDOW_VIEW_S;

typedef enum
{
    PT_REALPB_CTRL_PLAY = 0,
    PT_REALPB_CTRL_PAUSE = 1,
} PT_REALPB_CTRL_E;

typedef struct
{
    uint16  stat; // RAID成员盘状态
    uint16  dev_type;               // 设备类型 0-无设备
    uint16  hdd_id;
    uint16  is_raid_dev;            // 是否是RAID硬盘: 1-普通硬盘; 2-RAID硬盘; 3-热备盘
    uint64  capacity;               // 硬盘容量
} PT_HDD_RAID_INFO_S;

typedef struct
{
    uint16  raid_lev;                   // Raid级别: 0-无级别,没有创建RAID; 1-RAID5, 已创建RAID;
    uint16  status_mode;                // 状态模式: 0-正常; 1-降级; 2-重建; 3-损坏
    uint16  percent;                    // 重建模式百分比: 1-100
} PT_GRP_STATE_S, *PPT_GRP_STATE_S;

// 新结构体RAID信息
typedef struct
{
    PT_GRP_STATE_S     raid_state[2];
    PT_HDD_RAID_INFO_S disk_info[10];   // 控制器端口所挂硬盘信息
} PT_RAID_INFO_S, *PPT_RAID_INFO_S;

// 新结构体RAID信息
typedef struct
{
    PT_RAID_INFO_S raid_info;   // RAID组信息, 两组: 0组, 1组
    uint32  reserve;
} PT_RAIDINFO_GRP_S, *PPT_RAIDINFO_GRP_S;


/* RAID信息 */
typedef struct
{
    uint8 stat;         /* 设备RAID状态(MFS_RAIDSTAT_E) */
    uint8 level;        /* 设备RAID模式的级别(MFS_RAIDLEVEL_E) */
    uint8 raid_ctrlor;  /* 控制器序号*/
    uint8 PortType;     /* Port type (Null, Disk, RAID, Optical Drive,Bad Port)*/
    uint32 table;       /* 每个RAID组上的设备存在位置情况 */
    PT_RAIDDEVINFO_S infos[PT_MAX_RAID_DEV_NUM];
} PT_RAIDINFOS_S, *PPT_RAIDINFOS_S;


/* 存储设备信息 */
typedef struct
{
    uint8 dev_type;             /* 设备类型(MFS_DEVTYPE_E默认硬盘) */
    uint8 dev_stat;             /* 设备状态(MFS_DEVSTAT_E) */
    uint8 dev_num;              /* 设备号(0~63) */
    uint8 dev_attr;             /* 存储设备属性(MFS_DEVATTR_E) */
    uint8 partitions;           /* 设备分区数 */
    uint8 fs_stat;              /* 设备文件系统是格式化(MFS_FSSTAT_E) */
    uint8 removable;            /* 设备是否可移动装置(默认否) */
    uint8 backup;               /* 设备是否备份装置(默认否) */
    uint8 is_raid;              /* 设备是否RAID装置(0-默认否,1-SOFT RAID,2-HARD RAID) */
    uint8 wufile_num;           /* 将要用文件数(0~255) */
    uint16 rwfile_num;          /* 读写文件数(0~65535) */
    uint8 group;                /* 所在分组(0~63) */
    sint8 alloc_dat_fsize;      /* 预分配数据文件大小 MFS_DATAFILESIZE_E*/
    sint8 alloc_log_fsize;      /* 预分配日志文件大小 MFS_LOGFILESIZE_E*/
    uint8 reserve;              /* 保留位 */
    uint64 capability;          /* 设备容量(字节) */
    uint64 format_capability;   /* 文件系统可用容量(格式化后的容量(字节)) */
    uint64 format_free;         /* 当前可用容量(字节) */
    PT_RAIDINFOS_S raidinfos;   /* 当前设备RAID装置的详细信息 */
} PT_DEVINFO_S, *PPT_DEVINFO_S;

/* 存储设备状态信息 */
typedef struct
{
    uint64 dev_stat_tab;        /* 存储设备状态,按位表示0-不存在,1-存在 */
    PT_DEVINFO_S devinfos[PT_MAX_DEV_NUM];
} PT_DEVSTATINFO_S, *PPT_DEVSTATINFO_S;

/* 存储设备分组统计信息*/
typedef struct
{
    PT_DEVSTATINFO_S dev_info;  /*分组磁盘在位信息*/
    uint64 grp_capability;      /*分组总容量*/
    uint64 grp_fmt_capability;  /*分组格式化总容量*/
    uint64 grp_fmt_free;        /*分组剩余容量*/
    uint32 strm_rate;           /*分组上的流速率估计octets per sec*/
    uint64 freespace2sec;       /*分组剩余空间统计，估计能够存储的时间长度,秒数*/
    uint8 grp_ch_tbl[PT_MAX_REC_CH_NUM];    /*通道配置表，非0为配置该通道*/
} PT_STOREGRP_STATS_INFO_S, *PPT_STOREGRP_STATS_INFO_S;

typedef enum
{
    PT_VOSD_TIME_24H = 0,
    PT_VOSD_TIME_12H = 1
} PT_VOSD_TIMEFORAMT_E;

typedef struct
{
    PT_RESOLUTION_E pri_vtype;              //主码流编码类型
    PT_RESOLUTION_E sec_vtype;              //子码流编码类型
    PT_RESOLUTION_E snap_vtype;             //子码流编码类型
    uint8  show_chname;                     //是否叠通道名,1:叠加,0或其它不叠加,以下同
    uint8  show_date;                       //是否叠加日期
    uint8  show_time;                       //是否叠加时间
    uint8  show_week;                       //是否叠加星期
    PT_POINT_S chname_pos;                  //通道名位置
    PT_POINT_S datetime_pos;                //日期时间位置
    uint8  chname[PT_MAX_STRING_EXT + 1];          //叠加通道名
    PT_TIMEFORMAT_E     timeshow_format;
    PT_DATEFORMAT_E     dateshow_format;
} PT_VOSD_OVERLAYPARAM_S, *PPT_VOSD_OVERLAYPARAM_S;

typedef enum
{
    PT_NETALM_UN = 1,//关闭网络报警使能
    PT_NETALM_EN,//打开网络报警使能
} PT_NETALM_TYPE_E;

typedef enum
{
    PT_DST_MANU_CLOSE = 0,//手动关闭夏令时
    PT_DST_START,//夏令时开始
    PT_DST_END ,//正常结束
} PT_DSTTIME_TYPE_E; //夏令时类型

/*录像统计*/
typedef struct
{
    uint32  code_type;       /*录像类型*/
    uint32  total_day;       /* 录像总天数*/
    SYSTIME time_start;      /* 开始时间 */
    SYSTIME time_stop;       /* 结束时间 */
    uint64  file_count;      /* 文件总数 */
    uint64  times;           /* 总时间 */
    uint64  data_size;       /* 总长度 */
} PT_STORAGE_INFO_S, *PPT_STORAGE_INFO_S;

typedef struct
{
    int storage_cov_day;			//指定硬盘上覆盖录像时，录像不足天数报警的天数值
    int reserve[3];           		//保留
} PT_STORAGE_COV_DAY_S, *PPT_STORAGE_COV_DAY_S;

typedef struct
{
    uint32 day;  			   /* 录像实际天数*/
    uint32 store_days_thres; /* 录像覆盖设置报警天数*/
} PT_DAY_INFO_S, *PPT_DAY_INFO_S;

typedef struct
{
    uint32 addr;    /* 字库读取到内存中的首地址 */
    sint32 size;    /* 字库大小,读取时不能超过此大小. */
    uint32 addr16;  /* 16点阵字库地址 */
    sint32 size16;
} PT_FONT_ADDR_S;

typedef struct
{
    uint32 ptz_type;          //云台协议类型
    uint32 ptz_baudrate;      //波特率
    uint32 reserve[4];        //保留字段
} PTZ_PARAM, *PPTZ_PARAM;

typedef struct
{
    uint8 stop_flag;               //停止位 1停止 0运行
    uint8 show_split_time;         //显示画面分割时间
    uint8 show_page_time;          //显示页面时间
    uint8 switch_screen_time;      //切屏时间
    uint8 playback_channel[64];    //回放通道
    uint32 playback_time;          //回放时间
    uint32 alarm_out_time;         //报警输出时间
    PT_MFSTIME_S sys_time;         //系统时间
    PTZ_PARAM ptz_param;           //设置云台参数
    uint32 show_disk_info_time;     //显示磁盘信息管理界面时间+
    uint32 show_logo_time;          //显示logo的时间+
    uint32 show_system_info_time;   //显示系统信息的时间+
    uint32 reserved[5];
} PT_AUTO_TEST, *PPT_AUTO_TEST;    //生产自动化测试

//预览splits设置

/* 显示设备类型 */
typedef enum
{
    PT_VGA0_HDMI0_CVBS0 = 0,    //三个都同源，且在数组0中存储。数组指的是  下面的 display_setting[PT_MAX_DISPLAY_TYPE_NUM]
    PT_VGA0_HDMI0_CVBS1,        //VGA和HDMI同源，在数组0中,CVBS在数组1中
    PT_VGA0_HDMI1_CVBS1,        //VGA在结构体数组0中，HDMI和CVBS同源在数组1中
    PT_VGA0_HDMI1_CVBS0,        //VGA和CVBS同源在数组0中，HDMI在数组1中
    PT_VGA0_HDMI1_CVBS2,        //VGA在数组0，HDMI在数组1，CVBS在数组2
    PT_VGA0_HDMI0,              //VGA和HDMI同源,不支持CVBS
    PT_VGA0_HDMI1,              //VGA在数组0,HDMI在数组1，不支持CVBS
    PT_VGA0_CVBS0,              //VGA和CVBS同源,不支持HDMI
    PT_VGA0_CVBS1,              //VGA在数组0,CVBS在数组1,不支持HDMI
    PT_HDMI0_CVBS0,             //HDMI和CVBS同源在数组0,不支持VGA
    PT_HDMI0_CVBS1,             //HDMI在数组0，CVBS在数组1，不支持VGA
    PT_VGA0,                    //VGA在数组0，不支持CVBS和HDMI
    PT_HDMI0,                   //HDMI在数组0，不支持CVBS和VGA
    PT_CVBS0,                   //CVBS在数组0，不支持VGA和HDMI
} PT_DISPLAY_TYPE_E;

typedef enum
{
    NET_UPGRADE,
    USB_UPGRADE,
    FTP_UPGRADE,
} SYS_UPGRADE_AVENUE;

typedef enum
{
    FILE_COPY_UPGRADE,  //拷贝文件方式升级
    POINTER_ROUT_UPGRADE, //传递指针方式升级
} SYS_UPGRADE_TYPE;

typedef struct
{
    uint16  main_ch;                        /* 主通道 */
    uint16  splite_type;                    /* 当前画面格式 */
    uint32  reserve;
    uint16  ch_list[PT_MAX_REC_CH_NUM];     /* 多画面通道顺序 */
} PT_PREVIEW_SPLITS_SETTING_S, *PPT_PREVIEW_SPLITS_SETTING_S;

typedef struct
{
    uint16  dif_origin;
    uint16  display_type;        /* 显示设备类型 */
    uint32  reserve;
    PT_PREVIEW_SPLITS_SETTING_S  display_setting[PT_MAX_DISPLAY_TYPE_NUM];  /* 数据据结构体数组 */
} PT_PAGE_PREVIEW_S, *PPT_PAGE_PREVIEW_S;

typedef struct
{
    uint16 pb_num; 			/* 回放路数 */
    uint16 venc_resolution;	/* 编码清晰度 */
    uint32 venc_frams; 		/* 限制的最大编码帧率 */
    uint32 pri_bitrate_max;    /* 限制最大主码流 0---不限制；非0值---限制值*/

    sint16 sec_venc_limit_flag; /* 限制子码流标志*/
    sint16 sec_venc_frame;      /* 限制子码流时的帧率大小*/
    sint16 sec_venc_bitrate;    /* 限制子码流时的码率大小 0---不限制；非0值---限制值*/
    sint16 reserve;
} PT_VENC_CFG_LIMIT_S;

/* 获取剩余帧率*/
typedef struct
{
    int cif_frame;     /* CIF剩余帧率 */
    int fd_frame;	     /* FD1剩余帧率*/
    int qh_frame;      /* Q960剩余帧率 */
    int h_frame;	     /* 960剩余帧率*/
    int reserve[2];    /* 保留 */
} PT_REMAIN_FRAME_S, *PPT_REMAIN_FRAME_S;

/* 获取适合帧率*/
typedef struct
{
    int channel;      /*通道数*/
    int resolution;   /* 分辨率 */
    int frame;        /* 帧率 */
    int reserve[2];   /* 保留*/
} PT_CALC_FRAME_S, *PPT_CALC_FRAME_S;

typedef struct
{
    int resolution;   /* 分辨率 */
    int frame;        /* 帧率 */
    int reserve[2];   /* 保留 */
} MEDIA_USE_FRAME_S;

#if 1
#define AGENTID_LEN  16
//#define IP_LEN  128
#define PSD_LEN 32
#define MAX_CH_NUM 32

typedef enum
{
    SGPT_ING_TALK_FAULT = 0,                       //楼宇对讲故障
    SGPT_PERIMETER_ALARM_FAULT,                      //周界报警故障
    SGPT_NET_ALARM_FAULT,                              //联网报警故障
    SGPT_LOCAL_ALARM_FAULT,                             //本地报警故障
    SGPT_VIDEO_MONITOR_FAULT,                           //视频监控故障
    SGPT_IOCTROL_FAULT,                                 //出入控制故障
    SGPT_ELECTRONIC_PATROL_FAULT,                     //电子巡更故障
    SGPT_OTHER_SYS_FAULT,                            //其他系统故障
} SGPT_PT_WARNAME_E;

typedef enum
{
    SGPT_FRONT_FAULT = 0,                       //前端故障
    SGPT_TERMINAL_FAULT,                         //终端故障
    SGPT_SYSTEM_FAULT,                           //系统故障
} SGPT_PT_WARSYS_E;

typedef enum
{
    SGPT_NOTHING = 0,                      //不选
    SGPT_NOMAL,                            //正常
    SGPT_ABNOMAL_REPAIRED,                 //异常已修复
    SGPT_ABNOMAL_NOREPAIR,                 //异常未修复
} SGPT_PT_REPAIR_E;

typedef struct
{
    int            second ; // 秒: 0~59
    int            minute ; // 分: 0~59
    int            hour ; // 时: 0~23
} PT_TIME_OEM_S;

typedef struct
{
    char AgentID[AGENTID_LEN];           //agentID
    char addr[128];          //监控服务器IP
    int port;                 //服务器端口号
    int run_statue;                       //运行状态启用   0-不启用，1-启用
    int alm_pic_enable;//报警图片使能
    int normal_pic_enable;//日常截图使能
} PT_INFO_S, *LPPT_INFO_S;

typedef struct
{
    SGPT_PT_WARNAME_E pt_warname;         //报修系统名称
    SGPT_PT_WARSYS_E pt_warsys;           //报修系统类型
} PT_WARRANTY_S, *LPPT_WARRANTY_S;

typedef struct
{
    SGPT_PT_REPAIR_E pt_maintenance;         //设备维护
    SGPT_PT_REPAIR_E pt_repair;            //设备维修
} PT_MAINTREPAIR_S, *LPPT_MAINTREPAIR_S;

typedef struct
{
    int testpic_upload;            //测试图片上传，0-不上传，1-上传
    int maintpic_upload;           //保养图片上传，0-不上传，1-上传
    int channel[24];           //通道号
} PT_TESTMAINT_S, *LPPT_TESTMAINT_S;

typedef struct
{
    int intfront_time;              //前置时间   1-60秒
    int intinterval_time;           //间隔时间   1-5秒
    int probe;                  //输入端子(探头)
    int intdyrecard_time;          //延录时间  1-60秒
    int channel[24];
} PT_ALARMLINK_S, *LPPT_ALARMLINK_S;

typedef struct
{
    int enable1;       //时间1使能，0-不选、则时间1不上传图片，1-选、则在时间1上传相应通道图片
    int enable2;
    int channel1[24];
    int channel2[24];
    PT_TIME_OEM_S time1;               //时间1具体值
    PT_TIME_OEM_S time2;
} PT_DAILYUPLOAD_S, *LPPT_DAILYUPLOAD_S;

typedef struct
{
    char password[PSD_LEN];           //密码
    int  intacceptenceusrID;              //验收员ID
    int result;              //验收是否通过，0-未通过，1-通过
    int channel[24];
} PT_ACCEPTANCEUPLOAD_S, *LPPT_ACCEPTANCEUPLOAD_S;

typedef struct
{
    int ch_no;       //对应表示探头号
    PT_ALARMLINK_S pt_alarmlink[24];           //报警联动界面结构体
} PT_ALARMPAGE_S, *LPPT_ALARMPAGE_S;

#if 0
typedef struct
{
    short int guipage_id;                   //GUI界面ID，对应表示正在操作的GUI
    界面
    short int save_flag;                    //0-保存，1-上传
    PT_INFO_S pt_info;                      //平台配置界面结构体
    PT_WARRANTY_S pt_warranty;              //用户报修界面结构体
    PT_MAINTREPAIR_S pt_maintrepair;        //维修维保界面结构体
    PT_TESTMAINT_S pt_testmaint;            //测试保养界面结构体
    PT_ACCEPTANCEUPLOAD_S pt_acceptanceupload;
//验收图片上传界面结构体
    PT_ALARMPAGE_S pt_almpic;          		 //报警联动界面结构体
    PT_DAILYUPLOAD_S pt_dailyupload;        //日常图片上传界面结构体
} PT_SGPT_INFO_S, *PPT_SGPT_INFO_S; 			//深广平台配置结构体
#endif

typedef struct
{
    sint32 guipage_id;                   //GUI界面ID，对应表示正在操作的GUI界面
    sint32 save_flag;                    //0-保存，1-上传
    PT_INFO_S pt_info;                      //平台配置界面结构体
    PT_WARRANTY_S pt_warranty;              //用户报修界面结构体
    PT_MAINTREPAIR_S pt_maintrepair;        //维修维保界面结构体
    PT_TESTMAINT_S pt_testmaint;            //测试保养界面结构体
    PT_ACCEPTANCEUPLOAD_S pt_acceptanceupload;             //验收图片上传界面结构体
    PT_ALARMPAGE_S pt_almpic;          		 //报警联动界面结构体
    PT_DAILYUPLOAD_S pt_dailyupload;        //日常图片上传界面结构体
} PT_SGPT_INFO_S, *PPT_SGPT_INFO_S; 			//深广平台配置结构体

#endif

typedef struct
{
    sint16 hbydt_support;                       /* 一点通功能支持 0: 不支持 1: 支持 */
    sint16 hbydt_enable;                        /* 一点通功能启用 0: 关闭 1: 开启 ， 仅在hbydt_support为1时有效*/
    uint8  hbydt_domain[PT_MAX_YDTDOMAIN];      /* 一点通域名地址 汉邦: www.hbydt.cn 中性: www.ivview.com */
} PT_HBYDT_S;                                   /* 一点通功能结构体 */

typedef struct
{
    sint16 p2p_status;  //p2p 状态， 0: 未上线  1:已上线  -2:无效密钥 -3:无效UUID
    sint16 reserve;
} PT_P2P_STATUS_S;

typedef struct 
{
    sint16 alarm_push_status;
    sint16 reserve;
}PT_ALARM_PUSH_STATE_S;

typedef struct 
{
    sint16 alarm_push_enable;
    sint16 reserve;
}PT_ALARM_PUSH_CONF_S;

/*IPC相关*********************************************************************/
#define IPC_IPDEV_CMD_NUM 64    /*IPDEV模块最大支持命令数*/
#define IPC_SEARCH_MAX_NUM 256  /*IPDEV支持最大搜索设备数*/

enum
{
    PT_MSG_IPC_INVALID,
    PT_MSG_IPC_AUTH_ERR,       // IPC用户名或密码错误
    PT_MSG_IPC_NET_DISCONNECT, // 网络断开或设备不存在
    PT_MSG_IPC_BATCH_ADD_ERR,       // IPC批量添加错误
} PT_MSG_IPC_RET_E;

/*IPC 设备协议族*/
typedef enum
{
    IPC_IPDEV_PROTOCOL_HB = 0,    /* 汉邦协议 */
    IPC_IPDEV_PROTOCOL_ONVIF = 1, /* ONVIF 协议 */
    IPC_IPDEV_PROTOCOL_NUM,
    IPC_IPDEV_PROTOCOL_MAX = 8,
} IPC_IPDEV_PROTOCOL_TYPE_E;

typedef enum
{
    PT_IPD_TYPE_DVR = 0x1,      /* IP设备类型为DVR,对应id为nvd_id */
    PT_IPD_TYPE_IPC = 0x8,      /* IP设备类型为IPC,对应id为ipc_id */
    PT_IPD_TYPE_NVR = 0x10,     /* IP设备类型为NVR,对应id为nvd_id */
    PT_IPD_TYPE_ALL = 0xFF,
}PT_IPD_TYPE_E;/* 暂未使用的预留 */

typedef enum
{
    PT_STAT_LOSE        = 0,    /* 主子流丢 */
    PT_STAT_PRI_LOSE    = 1,    /* 主流丢失 */
    PT_STAT_SEC_LOSE    = 2,    /* 子流丢失 */
    PT_STAT_NORMAL      = 3,    /* 正常 */
} PT_STRM_STAT_E;


typedef struct
{
    sint32 support;
    uint32 devid;
    sint32 port;
} PT_IPC_PROTOCOL_S;

typedef struct
{
    uint32 devid;                   /* 设备id号(对ipc_id及nvd_id统称) */
    uint32 ipd_type;                /* 设备类型PT_IPD_TYPE_E,支持PT_IPD_TYPE_IPC|PT_IPD_TYPE_NVR这种格式 */
    sint8  ip_addr[BUFF_SIZE_128];  /* ip addr*/
    sint8  mac_addr[BUFF_SIZE_32];  /* mac addr*/
    char vendor_name[BUFF_SIZE_32]; /*厂商名(由设备发现结果中解析出来)*/
    char memo[BUFF_SIZE_32];        /* 设备说明 (汉邦协议搜索出的结果，对前缀为HBxxxx,DVRxxxx的DVR做过滤处理)*/
    sint32 authority;               /* 账号密码是否已探测成功,如果已探测成功,添加时可以不用输入账号密码  */
    PT_RES_S resolution;            /* 搜索出的设备分辨率,设备类型为IPC且探测成功时有效 */
    PT_IPC_PROTOCOL_S protocol[IPC_IPDEV_PROTOCOL_MAX]; /* 设备支持能力及协议*/
} PT_IPC_DEVSEARCHCONTENT_S;

typedef struct
{
    sint32 count; /*搜到的IPC设备数量*/
    PT_IPC_DEVSEARCHCONTENT_S ipc_devsearch_content[IPC_SEARCH_MAX_NUM]; /* 搜到的IPC设备内容*/
} PT_IPC_DEVSEARCHINFO_S,PT_IPD_DEVSEARCHINFO_S;

typedef struct
{
    char manufacture[BUFF_SIZE_32]; /* 厂商名 */
    char model[BUFF_SIZE_32];       /* 型号  */
    char firmware_ver[BUFF_SIZE_32];/* 固件版本 */
}PT_IPC_INFO_S;

typedef struct
{
    PT_STRM_STAT_E dev_stream;  /*流状态*/
    PT_STRM_STAT_E pic_stream;   /* 图片流状态 PT_STAT_LOSE:丢失 PT_STAT_NORMAL:正常*/
} PT_IPC_DEVSTATUS_S, *PPT_IPC_DEVSTATUS_S;

/* 设备登陆信息 */
typedef struct
{
    uint32  devid;                  /* 设备id号(对ipc_id及nvd_id统称) */
    uint32  protocol;               /* 协议,自动添加时无效  */
    sint32  poe_ch;                 /* 添加的是否为poe通道 0--否，1--是*/
    sint32  port;                   /* 端口号 */
    char    username[BUFF_SIZE_32]; /* ipc用户名 */
    char    password[BUFF_SIZE_32]; /* ipc连接认证密码 */
    char    ipaddr[BUFF_SIZE_128];  /* IP 地址 */
}PT_IPD_LOGIN_S;

/* nvd设备登陆信息汇总 */
typedef struct
{
    sint32 count;
    PT_IPD_LOGIN_S login[PT_MAX_NVD];
}PT_NVD_CFG_S;

/* 获取NVR基本信息 */
typedef struct
{
    sint32 status;                  /* 登陆是否成功状态 */
    sint32 video_no;
    char device_name[BUFF_SIZE_32];
    char manufacture[BUFF_SIZE_32]; /* 厂商名 */
    char model[BUFF_SIZE_32];       /* 型号  */
    char firmware_ver[BUFF_SIZE_32];/* 固件版本 */
    PT_VOSPLIT_S split;             /* 复合通道分屏格式 */
}PT_NVD_INFO_S;

typedef struct
{
    uint32 nvd_id;
    sint32 channel;                 /* 被nvr添加到哪个通道 */
    char ipaddr[BUFF_SIZE_32];
    char dev_name[BUFF_SIZE_32];
    char username[BUFF_SIZE_32];
    char password[BUFF_SIZE_32];    
}PT_ALLOT_NVD_S;

/*
* 组网信息,每个ipc对应的nvr信息
*/
typedef struct
{
    uint32 ipc_id;
    uint32 authority;
    uint32 port;
    uint32 nvd_cnt;                 /* 同时被几个nvr添加,为0表示未被NVR添加 */
    char ipaddr[BUFF_SIZE_32];
    char osd_name[BUFF_SIZE_32];
    PT_RES_S resolution;            /* ipc主码流分辨率 */
    PT_ALLOT_NVD_S allot_nvd[PT_MAX_ALLOT_NVD];  /* 被多个nvr添加的信息列表*/
}PT_ALLOT_IPC_S;

typedef struct
{
    sint32 view_mode;   /* PT_IPD_MODE_E */
    sint32 nvd_idx;     /* 当view_mode由PT_IPD_MODE_NVD切换到PT_IPD_MODE_IPC模式时,需告知nvd索引 */
}PT_NVD_VIEW_MODE_S;

/* 老结构体不再使用 */
typedef struct
{
    sint32      ch;                 /* IP通道通道号 */
    sint32      poech;              /* 是否为POE设备,0否,1是(添加时该值为0) */
    uint32      devid;              /* 设备id,自动添加时无效 */
    uint32      protocol;           /* 协议,自动添加时无效  */
    char        usrname[32];        /* ipc用户名 */
    char        pwd[32];            /* ipc连接认证密码 */
    char        ip_addr[MAX_IPADDR_STR_LEN];       /* IP 地址 */
    sint32      port;               /* 端口号 */
    sint32      dev_ch_num;         /* 设备通道数 */
    sint32      dev_ch;             /* 设备通道(码流编号，从0开始) */
    sint32      ch_list_idx;        /*指定位置添加IPC时，传当前分屏的位置索引，非指定位置时传-1*/
    char        vendor_name[32];    /*厂商名*/
    char        memo[32];           /*设备型号*/
    char        firmware_ver[32];   /*ipc固件版本号*/
} PT_IPC_CONFIG_S, *PPT_IPC_CONFIG_S;

typedef struct
{
    sint32      ch;                 /* 本地通道 */
    char        ch_name[32];        /* 通道名称*/
    char        dev_name[32];       /* 设备名称*/
    uint8       mac_addr[8];        /* MAC地址 */
    uint32      dev_resol;          /* 设备分辨率 PT_RESOLUTION_E*/
    char        dev_softver[32];    /* 设备软件版本号 */
    uint8       dev_type;           /* 设备类型*/
    uint8       reserve[3];           /* 保留位*/
} PT_IPC_DEVINFO_S, *PPT_IPC_DEVINFO_S;

typedef struct
{
    sint32 ptz_support;             /* ipc网络云台支持 */
    sint32 motion_support;          /* 移动报警支持 */
    sint32 snap_support;            /* 抓图支持(包括抓图预览,抓图录像) */
    sint32 sensor_support;          /* 探头报警输入支持 */
    sint32 sensorout_support;       /* 探头报警输出支持 */
} PT_IPC_CAPABILITIES_S;

typedef struct
{
    sint32      ch;                 /* 本地通道 */
    char        ip_addr[MAX_IPADDR_STR_LEN];       /* IP 地址 */
    uint8       subnet_mask[8];     /* 子网掩码 */
    uint8       gateway[8];         /* 网关 */
    uint8       dns_server[8];      /* dns服务器 */
    sint32      port;               /* 端口号 */
    sint32      http_port;          /* http端口号 */
} PT_IPC_NETWORKCFG_S, *PPT_IPC_NETWORKCFG_S;

typedef struct
{
    sint32 count;
    PT_RES_S list[PT_MAX_LIST];
} PT_RES_LIST_S;

typedef struct
{
    PT_RES_LIST_S pri_res;  /*IPC主码流分辨率 PT_RESOLUTION_E*/
    PT_RES_LIST_S sec_res;  /*IPC次码流分辨率 PT_RESOLUTION_E*/
} PT_IPC_COMMONRANGE_S, *PPT_IPC_COMMONRANGE_S; //通用范围

typedef enum 
{ 
    PT__VideoEncoding__H264 = 0,  
    PT__VideoEncoding__H265 = 1,
    PT__VideoEncoding__JPEG = 2, 
    PT__VideoEncoding__MPEG4 = 3, 
    PT__VideoEncoding__MAX,
} PT_VIDEO_ENCODING_E;
typedef struct
{
    PT_RES_S resolution;            /* PT_RES_S 传入参数*/

    PT_RANGE_S pri_frame_rate;      /*IPC主码流帧率*/
    PT_RANGE_S pri_bit_rate;        /*IPC主码流码率*/
    PT_RANGE_S pri_quality;         /* 图像质量范围 */
    PT_LIST_S  pri_encode;          /*编码类型列表，PT_VIDEO_ENCODING_E*/

    PT_RANGE_S sec_frame_rate;      /*IPC次码流帧率*/
    PT_RANGE_S sec_bit_rate;        /*IPC次码流码率*/
    PT_RANGE_S sec_quality;
    PT_LIST_S  sec_encode;          /*编码类型列表，PT_VIDEO_ENCODING_E*/
} PT_IPC_ENCPARAM_RANGE_S, *PPT_IPC_ENCPARAM_RANGE_S;

typedef enum
{
    PT_IPC_NOT_ADD = 0,         /* 通道未添加设备 */
    PT_IPC_ADDED = 1,           /* 通道已添加设备 */
    PT_IPC_POE_CONNECT = 2,     /* POE设备接入 */
    PT_IPC_POE_DISCONNECT = 3,  /* POE设备断开 */
} PT_CH_STAT_E;

typedef struct
{
    uint32 channel;
    sint32 ch_stat;     /* PT_CH_STAT_E */
} PT_CH_STATUS_S;

typedef enum
{
    PT_IPC_TEST_CONNECT = 1,
    PT_IPC_TEST_PROTOCAL = 2,
    PT_IPC_TEST_STREAM  = 3,
    PT_IPC_TEST_DETAIL  = 4,
} PT_IPC_TEST_STEP_E;

typedef enum
{
    PT_RESULT_TEST_FAILED   = 0,
    PT_RESULT_TEST_PASSED   = 1,
    PT_RESULT_CONNECT_FAILED = 11,  /*网络不通 建议:(1)检查电源 (2)检查网络连接 */
    PT_RESULT_AUTH_FAILED   = 12,   /*账号密码错误 建议:(1)用户名密码错误 */
    PT_RESULT_NO_RESPONSE   = 13,   /*设备无响应 建议:(1)确认设备 (2)确认支持onvif (3)尝试重启ipc */
    PT_RESULT_NOT_SUPPORT   = 14,   /*设备不支持 建议: (1)尝试复位ipc (2)咨询设备厂商解决 */
    PT_RESULT_STREAM_ERROR  = 15,   /* 数据流打开错误 建议:(1)检查被其他设备连接 (2)尝试重启ipc */
    PT_RESULT_RES_ERROR     = 16,   /* 分辨率太高不支持 建议:(1)分辨率高不支持,调低分辨率 */
} PT_IPC_TEST_RESULT_E;

typedef struct
{
    sint32 step;    /* PT_IPC_TEST_STEP_E */
    sint32 result;  /* PT_IPC_TEST_RESULT_E */
} PT_IPC_TEST_S;

typedef struct
{
    sint32 section;     //诊断状态0-未诊断,1-诊断成功,2-诊断失败*//*说明：由于广域网诊断时，要随机选择三个域名进行诊断，因此要对每个域名的诊断状态进行说明
    char server[64];    //广域网地址
} PT_NET_DIAGNOSIS_SERVER_S;//诊断的广域网地址

typedef enum 
{
	PT_NET_DIAGNOSIS_LAN_START, /*开始局域网诊断*/
	PT_NNET_DIAGNOSIS_LAN_END, /*局域网诊断结束，诊断的结果请看DIAGNOSIS_RESULT_S 结构体的result 字段*/
	PT_NNET_DIAGNOSIS_NET_START,/* 开始广域网诊断*/
	PT_NNET_DIAGNOSIS_NET_END,/* 广域网诊断结束，诊断的结果请看DIAGNOSIS_RESULT_S 结构体的result 字段*/
	PT_NNET_DIAGNOSIS_END, /*全部诊断结束*/
	PT_NNET_DIAGNOSIS_STOP, /*诊断中断*/
} PT_NET_DIAGNOSIS_STEP_E; /*诊断步骤*/

typedef enum 
{
	PT_NET_DIAGNOSIS_ETH_DOWN=0, /*网线未连接，（提示语：网线断开，请确认网线是否正常插上）*/
	PT_NET_DIAGNOSIS_NET_OK, /*广域网连接正常*/
	PT_NET_DIAGNOSIS_NET_ERR, /*广域网连接失败*/
	PT_NET_DIAGNOSIS_LAN_OK,/*局域网连接正常*/
	PT_NET_DIAGNOSIS_LAN_ERR,/*局域网连接失败*/
	PT_NET_DIAGNOSIS_REPAIR_ERR=5,/*修复失败,请确认DHCP服务器是否正常开启服务*/
	PT_NET_DIAGNOSIS_REPAIR_IP_ERR,/*修复失败，ip地址与自动获取的网关不在同一网段上，请修改ip，网关，dns*/
	                        /*说明：此提示针对手动设置ip的场景，如果为自动获取ip，则不会有此提示*/
	PT_NET_DIAGNOSIS_REPAIR_ROUTE_ERR,/*修复失败，请确认DVR与路由器之间的网络是否正常*/
	PT_NET_DIAGNOSIS_REPAIR_DNS_ERR,/*修复失败，DNS服务器设置错误，请修改DNS*/
	PT_NET_DIAGNOSIS_REPAIR_NET_ERR,/*修复失败，请确认路由器是否能正常上外网*/
	PT_NET_DIAGNOSIS_REPAIR_GW_ERR,/*修复失败，请确认网络设置页面上的网关是否正常设置*/
	PT_NET_DIAGNOSIS_IP_CONFLICT,/*ip冲突*/
} PT_NET_DIAGNOSIS_STAT_E; /*诊断结果*/

typedef struct
{
    sint32 step;        //诊断步骤:0-开始局域网诊断,1-局域网诊断结束,2-开始广域网诊断,3-广域网诊断结束,4-全部诊断结束（具体对应NET_DIAGNOSIS_STEP_E）
    sint32 result;      //诊断结果，即GUI提示语，诊断结束时，本字段才有意义，NET_DIAGNOSIS_STAT_E
    PT_NET_DIAGNOSIS_SERVER_S server[3];    //广域网具体域名
} PT_NET_DIAGNOSIS_RESULT_S;                //诊断回调结构体

typedef struct
{
    sint32 type;        /* 主子码流 PT_STREAMTYPE_E */
    void * user_data;   /* 用户数据的首地址(读数据时会原样回调出去) */
    sint32 data_size;   /* 用户数据长度(会回调出去) */
    sint32 ipv4;        /* ip地址(可选,建议填上) */
    sint32 flag;        /* 平台标识(如 *(sint32 *)"rtmp"等),同mac不同flag,会用不同线程发送 */
    char   macstr[32];  /* 接入设备的mac地址,用户管理标识,字符串,如"E4:7D:5A:0B:DB:81" */
    PNETDATACALLBACK datacb; /* 注册数据回调函数 */
} PT_STRM_REQUEST_S;

typedef struct
{
    uint64 running_sec; // 连续运行时间 s
    uint32 port_power; // 获取到的port口功率mA*V
} PT_POECTRL_POWER_STAT_PORT_S;

typedef struct
{
    PT_POECTRL_POWER_STAT_PORT_S port_params[PT_MAX_POE_NUM]; // 端口参数
    uint32 total_power; // 获取到的所有port口总功率mA*V
} PT_POECTRL_POWER_STAT_S, *PPT_POECTRL_POWER_STAT_S;

typedef struct
{
    uint32 max_bitrate;     /* 系统支持的最大码率*/
    uint32 total_bitrate;   /* 系统当前最大码率*/
} PT_BITRATE_PARAM, *PPT_BITRATE_PARAM;

typedef enum
{
    PT_OUTPUT_MODE_STANDARD,    /* 标准 */
    PT_OUTPUT_MODE_BRIGHT,      /* 明亮 */
    PT_OUTPUT_MODE_SOFT,        /* 柔和 */
    PT_OUTPUT_MODE_VIVID,       /* 鲜艳 */
    PT_OUTPUT_MODE_SHARP,       /* 锐利 */
    PT_OUTPUT_MODE_BUTT
} PT_VO_OUTPUT_MODE_E;

typedef enum
{
    PT_AO_DEV_NORMAL,   /* 通用音频输出 */
    PT_AO_DEV_HDMI,     /* HDMI音频输出 */
    PT_AO_DEV_ALL,      /* 所有音频输出 */
    PT_AO_DEV_BUTT
} PT_AO_DEV_E;



#define  PT_MAX_UART_DEV_NUM  (4)
typedef struct
{
   uint32 uart_dev_no;
   char   uart_dev_type[32];
   char   uart_dev_name[32];
   uint16 full_duplex_support;//全双工
   uint16 half_duplex_support;//半双工
}PT_CFG_UART_DEV_PARA, *PPT_CFG_UART_DEV_PARA;
typedef struct
{
    uint32 dev_count;
    PT_CFG_UART_DEV_PARA dev_list[PT_MAX_UART_DEV_NUM];
}PT_CFG_UART_DEV_LIST, *PPT_CFG_UART_DEV_LIST;
#endif

