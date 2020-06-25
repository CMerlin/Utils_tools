#ifndef _ISAPI_LOCAL_H_
#define _ISAPI_LOCAL_H_

#include "common.h"
#include "log.h"
#include "goahead.h"

#define MAX_UPGRADE_SIZE    (0x800000 * 4 + 0x800)  /* 升级文件最大限制为32Mb + 2Kb(2K是预留另外9个FILE_HEADER_S结构体空间的大小) */
#define ISAPI_CMD_MAX_NUM   16
#define ISAPI_CMD_MAX_LEN   128
#define ISAPI_MAX_STRLEN    256
#define ISAPI_IPLEN   4

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

extern  ISAPI_FD_S isapi_fd;

#endif
