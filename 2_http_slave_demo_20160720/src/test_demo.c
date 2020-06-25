/****************************************************************
 * Copyright(C), 2016, Hanbang Tech.Co.,Ltd
 * File Name:slave_http
 * Author:merlin
 * Version:v1
 * Data:20160613
 * Description:这是一个HTTP协议的客户端程序
 * History:
 * *************************************************************/
#include "isapi_api_client.h"

/***************************************************************************
 * Description：信号处理函数
 * Return：0-succed; -1-failure
 * *************************************************************************/
static void handle_term( int sig )
{
	printf("signal term received!\n");
}

/***************************************************************************
 * Description:信号处理函数
 * Return:0-succed; -1-failure
 * *************************************************************************/
static void handle_hup( int sig )
{
	const int oerrno = errno;
	
	printf("signal hup received!\n");
	(void) signal( SIGHUP, handle_hup );
	
	errno = oerrno;
}

/***************************************************************************
 * Description:SIGALRM 信号处理函数
 * Return:0-succed; -1-failure
 * *************************************************************************/
static void handle_alrm ( int sig )
{
	const int oerrno = errno;
	
	printf("signal alrm received!\n");
	(void) signal( SIGALRM, handle_alrm );
	
	errno = oerrno;
}

/***************************************************************************
 * Description:捕捉异常信号，并进行相关的处理
 * Return:0-succed; -1-failure
 * *************************************************************************/
int deal_with_signal()
{
	(void) signal( SIGTERM, handle_term );
	(void) signal( SIGINT, handle_term );
	//(void) signal( SIGCHLD, handle_chld );
	(void) signal( SIGPIPE, SIG_IGN );
	(void) signal( SIGHUP, handle_hup );
	(void) signal( SIGALRM, handle_alrm );

	return 0;
}

/***************************************************************************
 * Description：为程序的后续执行进行一些初始化工作
 * Return:0-succed; -1-failure
 * *************************************************************************/
int init()
{
	init_print_level(); //初始化打印级别
	deal_with_signal(); /*处理一些异常的信号*/

	return 0;
}

/***************************************************************************
 * Description:设置http通信协议相关的信息，这里的初始化信息将会用来用来建http连接
 *             和影响http头的封装
 * Return:0-succed; -1-failure
 * *************************************************************************/
sint32 test_set_http_attr()
{
	//HTTP_ATTR_S http_attr = {"192.168.30.99", 80, CLOSE};
	HTTP_ATTR_S http_attr;

	memset(&http_attr, 0, sizeof(http_attr));
	memcpy(http_attr.name, "admin", sizeof(http_attr.name));
	memcpy(http_attr.password, "888888", sizeof(http_attr.password));
	memcpy(http_attr.ip, "192.168.30.99", sizeof(http_attr.ip));
	http_attr.port = 80;
	http_attr.connection = CLOSE; //短连接
	//http_attr.connection = KEEP_ALIVE; //长连接
	isapi_set_http_attr(&http_attr);

	return 0;
}

/***************************************************************************
 * Description: URL:GET /ISAPI/System/Network/interfaces
 * Return:0-succed; -1-failure
 * *************************************************************************/
sint32 test_get_network_interfaces()
{
	sint32 ret = 0;
	NETWORK_DEVICE_INFO_S response;

	trace(TRACE, "\e[32m[%s]:****************************** line:%d\e[0m\n", __func__, __LINE__);
	memset(&response, 0, sizeof(NETWORK_DEVICE_INFO_S));
	ret = isapi_get_network_interfaces(0, NULL, &response);
	trace(TRACE, "[%s]:id=%d ip=%d netmask=%d errno=%d LINE:%d\n", __func__, response.id, response.ip.ipaddr, response.ip.netmask, ret, __LINE__);
	return 0;
}

/***************************************************************************
 * Description: URL: GET /ISAPI/System/Network/mailing
 * Return:0-succed; -1-failure
 * *************************************************************************/
sint32 test_get_network_mailing()
{
	sint32 ret = 0;
	NETWORK_SMTP_S response;
	
	trace(TRACE, "\e[32m[%s]:****************************** line:%d\e[0m\n", __func__, __LINE__);
	memset(&response, 0, sizeof(NETWORK_SMTP_S));
	ret = isapi_get_network_mailing(0, NULL, &response);
	trace(TRACE, "[%s]:id=%d host=%s errno=%d LINE:%d\n", __func__, response.id, response.host, ret,__LINE__);
	
	return 0;
}

/***************************************************************************
 * Description: URL: PUT /ISAPI/System/Network/mailing
 * Return:0-succed; -1-failure
 * *************************************************************************/
sint32 test_put_network_mailing()
{
	int ret = 0;
	COMMON_RESPONSE_S response;
	NETWORK_SMTP_S request, deviceInfo;

	memset(&request, 0, sizeof(request));
	memset(&response, 0, sizeof(response));
	memset(&deviceInfo, 0, sizeof(deviceInfo));
	trace(TRACE, "\e[32m[%s]:****************************** line:%d\e[0m\n", __func__, __LINE__);
	
	ret = isapi_get_network_mailing(0, NULL, &deviceInfo);
	if(ret < 0)
	{
		trace(TRACE, "[%s]:get initData failed! LINE:%d\n", __func__, __LINE__);
		return -1;
	}
	request = deviceInfo;
	ret = isapi_put_network_mailing(0, &request, &response);
	trace(TRACE, "[%s]:requestURL=%s statusCode=%d statusString=%s subStatusCode=%s errno=%d LINE:%d\n", __func__, response.requestURL, response.statusCode, response.statusString, response.subStatusCode, ret,__LINE__);

	return 0;
}

/***************************************************************************
 * Description: URL:GET /ISAPI/System/Network/interfaces/capabilities
 * Return:0-succed; -1-failure
 * *************************************************************************/
sint32 test_get_network_interfaces_capabilities()
{
	int ret = 0;
	NETWORK_DEVICE_INFO_S response;
	
	trace(TRACE, "\e[32m[%s]:****************************** line:%d\e[0m\n", __func__, __LINE__);
	memset(&response, 0, sizeof(NETWORK_DEVICE_INFO_S));
	ret = isapi_get_network_interfaces_capabilities(0, NULL, &response);
	trace(TRACE, "[%s]:id=%d ip=%d netmask=%d errno=%d LINE:%d\n", __func__, response.id, response.ip.ipaddr, response.ip.netmask, ret, __LINE__);
	
	return 0;
}

/***************************************************************************
 * Description: URL:GET /ISAPI/System/Network/UPnP/ports/status
 * Return:0-succed; -1-failure
 * *************************************************************************/
sint32 test_get_network_UPnP_ports_status()
{
	int ret = 0, index = 0;
	NETWORK_UPNP_S response;
	
	trace(TRACE, "\e[32m[%s]:****************************** line:%d\e[0m\n", __func__, __LINE__);
	memset(&response, 0, sizeof(NETWORK_DEVICE_INFO_S));
	ret = isapi_get_network_UPnP_ports_status(0, NULL, &response);
	for(index = 0; index < response.pat_count; index++)
	{
		trace(TRACE, "[%s]:index=%d server_name=%s dvr_port=%d errno=%d LINE:%d\n", __func__, index, response.pat_info[index].server_name, response.pat_info[index].dvr_port, ret, __LINE__);
	}
	
	return 0;
}

/***************************************************************************
 * Description:URL: GET /ISAPI/System/Network/UPnP;
 * Return:0-succed; -1-failure
 * *************************************************************************/
sint32 test_get_network_UPnP()
{
	int ret = 0;
	NETWORK_UPNP_S response;
	
	trace(TRACE, "\e[32m[%s]:****************************** line:%d\e[0m\n", __func__, __LINE__);
	memset(&response, 0, sizeof(NETWORK_DEVICE_INFO_S));
	ret = isapi_get_network_UPnP(0, NULL, &response);
	trace(TRACE, "[%s]:enabled=%d errno=%d LINE:%d\n", __func__, response.upnp_en, ret, __LINE__);
	
	return 0;
}

/***************************************************************************
 * Description: URL:PUT /ISAPI/System/Network/UPnP
 * Return:0-succed; -1-failure
 * *************************************************************************/
sint32 test_put_network_UPnP()
{
	int ret = 0;
	NETWORK_UPNP_S request;
	COMMON_RESPONSE_S response;
	
	trace(TRACE, "\e[32m[%s]:****************************** line:%d\e[0m\n", __func__, __LINE__);
	memset(&request, 0, sizeof(request));
	memset(&response, 0, sizeof(response));
	ret = isapi_put_network_UPnP(0, &request, &response);
	trace(TRACE, "[%s]:requestURL=%s statusCode=%d statusString=%s subStatusCode=%s errno=%d LINE:%d\n", __func__, response.requestURL, response.statusCode, response.statusString, response.subStatusCode, ret, __LINE__);
	
	return 0;
}

/***************************************************************************
 * Description: URL:PUT /ISAPI/System/Network/DDNS
 * Return:0-succed; -1-failure
 * *************************************************************************/
sint32 test_put_network_ddns()
{
	int ret = 0;
	NETWORK_DDNS_S request, initData;
	COMMON_RESPONSE_S response;
	
	trace(TRACE, "\e[32m[%s]:****************************** line:%d\e[0m\n", __func__, __LINE__);
	memset(&request, 0, sizeof(request));
	memset(&response, 0, sizeof(response));
	memset(&initData, 0, sizeof(initData));
	ret = isapi_get_network_ddns_capabilities(0, NULL, &initData);
	if(ret < 0)
	{
		trace(ERROR, "[%s]:get init data failed! LINE:%d\n", __func__, __LINE__);
		return -1;
	}
	request = initData;
	ret = isapi_put_network_ddns(0, &request, &response);
	trace(TRACE, "[%s]:requestURL=%s statusCode=%d statusString=%s subStatusCode=%s errno=%d LINE:%d\n", __func__, response.requestURL, response.statusCode, response.statusString, response.subStatusCode, ret,__LINE__);
	
	return 0;
}

/***************************************************************************
 * Description: URL:GET /ISAPI/System/Network/DDNS/capabilities
 * Return:0-succed; -1-failure
 * *************************************************************************/
sint32 test_get_network_ddns_capabilities()
{
	int ret = 0;
	NETWORK_DDNS_S response;
	
	trace(TRACE, "\e[32m[%s]: sizeof=%d****************************** line:%d\e[0m\n", __func__, sizeof(response), __LINE__);
	memset(&response, 0, sizeof(response));
	ret = isapi_get_network_ddns_capabilities(0, NULL, &response);
	trace(TRACE, "[%s]:id=%d server=%s errno=%d LINE:%d\n", __func__, response.index, response.server, ret, __LINE__);
	
	return 0;
}

/***************************************************************************
 * Description: URL:GET /ISAPI/Security/adminAccesses
 * Return:0-succed; -1-failure
 * *************************************************************************/
sint32 test_get_adminAccesses()
{
	int ret = 0;
	SECURITY_PORTINFO_S response;
	
	trace(TRACE, "\e[32m[%s]:****************************** line:%d\e[0m\n", __func__, __LINE__);
	memset(&response, 0, sizeof(response));
	ret = isapi_get_adminAccesses(0, NULL, &response);
	trace(TRACE, "[%s]:httpport=%d listenport=%d rtspport=%d rtmpport=%d upgradeport=%d errno=%d LINE:%d\n", __func__,  response.httpport, response.listenport, response.rtspport, response.rtmpport, response.upgradeport, ret, __LINE__);

	return 0;
}

/***************************************************************************
 * Description: URL: PUT /ISAPI/Security/adminAccesses
 * Return:0-succed; -1-failure
 * *************************************************************************/
sint32 test_put_adminAccesses()
{
	int ret = 0;
	SECURITY_PORTINFO_S request, initData;
	COMMON_RESPONSE_S response;
	
	trace(TRACE, "\e[32m[%s]:****************************** line:%d\e[0m\n", __func__, __LINE__);
	memset(&request, 0, sizeof(request));
	memset(&response, 0, sizeof(response));
	memset(&initData, 0, sizeof(initData));
	ret = isapi_get_adminAccesses(0, NULL, &initData);
	if(ret < 0)
	{
		trace(TRACE, "[%s]:get initData failed! LINE:%d\n", __func__, __LINE__);
		return -1;
	}
	request = initData;
	ret = isapi_put_adminAccesses(0, &request, &response);
	trace(TRACE, "[%s]:requestURL=%s statusCode=%d statusString=%s subStatusCode=%s errno=%d LINE:%d\n", __func__, response.requestURL, response.statusCode, response.statusString, response.subStatusCode, ret,__LINE__);
	
	return 0;
}

/***************************************************************************
 * Description: URL:GET /ISAPI/System/Network/DDNS/1
 * Return:0-succed; -1-failure
 * *************************************************************************/
sint32 test_get_network_ddns_channel()
{
	sint32 ret = 0;
	NETWORK_DDNS_S response;
	
	trace(TRACE, "\e[32m[%s]:****************************** line:%d\e[0m\n", __func__, __LINE__);
	memset(&response, 0, sizeof(response));
	ret = isapi_get_network_ddns_channel(0, NULL, 1, &response);
	trace(TRACE, "[%s]:user=%s ip_addr=%d errno=%d LINE:%d\n", __func__, response.user, response.ip_addr, ret, __LINE__);
	
	return 0;
}

/***************************************************************************
 * Description:使用此接口高速的给Web服务器端发送信息会导致Web服务器重启
 *             (URL: /PUT /ISAPI/System/Network/interfaces/1)
 * Return:0-succed; -1-failure
 * *************************************************************************/
sint32 test_put_network_interfaces_channel()
{
	sint32 ret = 0;
	NETWORK_DEVICE_INFO_S request, deviceInfo;
	COMMON_RESPONSE_S response;
	
	trace(TRACE, "\e[32m[%s]:****************************** line:%d\e[0m\n", __func__, __LINE__);
    memset(&request, 0, sizeof(request));
	memset(&deviceInfo, 0, sizeof(deviceInfo));
	memset(&response, 0, sizeof(response));
	
	ret = isapi_get_network_interfaces(0, NULL, &deviceInfo);
	if(ret < 0)
		return -1;
	request = deviceInfo;
	ret = isapi_put_network_interfaces_channel(0, &request, 1, &response);
	trace(TRACE, "[%s]:requestURL=%s statusCode=%d statusString=%s subStatusCode=%s errno=%d LINE:%d\n", __func__, response.requestURL, response.statusCode, response.statusString, response.subStatusCode, ret,__LINE__);

	return 0;
}

/***************************************************************************
 * Description: URL: GET /ISAPI/System/deviceInfo
 * Return:0-succed; -1-failure
 * *************************************************************************/
sint32 test_get_deviceInfo()
{
	sint32 ret = 0;
	ISAPI_NULL_S request;
	SYSTEM_DEVICE_INFO_S response;

	trace(TRACE, "\e[32m[%s]:****************************** line:%d\e[0m\n", __func__, __LINE__);
	memset(&request, 0, sizeof(request));
	memset(&response, 0, sizeof(response));
	ret = isapi_get_deviceInfo(0, &request, &response);
	trace(TRACE, "[%s]:dev_id=%s model=%s errno=%d LINE:%d\n", __func__, response.dev_id, response.dev_type, ret, __LINE__);

	return 0;
}

/***************************************************************************
 * Description:  URL: PUT /ISAPI/System/deviceInfo
 * Return:0-succed; -1-failure
 * *************************************************************************/
sint32 test_put_deviceInfo()
{
	sint32 ret = 0;
	SYSTEM_DEVICE_INFO_S request, initInfo;
	COMMON_RESPONSE_S response;

	trace(TRACE, "\e[32m[%s]:****************************** line:%d\e[0m\n", __func__, __LINE__);
	memset(&request, 0, sizeof(request));
	memset(&response, 0, sizeof(response));
	memset(&initInfo, 0, sizeof(initInfo));
	if(0 > isapi_get_deviceInfo(0, NULL, &initInfo))
	{
		trace(ERROR, "[%s]:get initInfo failed! LINE:%d\n", __func__, __LINE__);
		return -1;
	}
	request = initInfo;
	ret = isapi_put_deviceInfo(0, &request, &response);
	trace(TRACE, "[%s]:requestURL=%s statusCode=%d statusString=%s subStatusCode=%s errno=%d LINE:%d\n", __func__, response.requestURL, response.statusCode, response.statusString, response.subStatusCode, ret,__LINE__);

	return 0;
}

/***************************************************************************
 * Description: URL: GET /ISAPI/System/deviceInfo/capabilities
 * Return:0-succed; -1-failure
 * *************************************************************************/
sint32 test_get_deviceInfo_capabilities()
{
	sint32 ret = 0;
	ISAPI_NULL_S request;
	SYSTEM_DEVICE_INFO_S response;

	trace(TRACE, "\e[32m[%s]:****************************** line:%d\e[0m\n", __func__, __LINE__);
	memset(&request, 0, sizeof(request));
	memset(&response, 0, sizeof(response));
	ret = isapi_get_deviceInfo_capabilities(0, &request, &response);
	trace(TRACE, "[%s]:dev_id=%s model=%s errno=%d LINE:%d\n", __func__, response.dev_id, response.dev_type, ret, __LINE__);

	return 0;
}

/***************************************************************************
 * Description: URL: GET /ISAPI/ContentMgmt/Storage
 * Return:0-succed; -1-failure
 * *************************************************************************/
sint32 test_get_storage()
{
	sint32 ret = 0;
	ISAPI_NULL_S request;
	DEVICE_DISK_ATTR_S response;

	trace(TRACE, "\e[32m[%s]:****************************** line:%d\e[0m\n", __func__, __LINE__);
	memset(&request, 0, sizeof(request));
	memset(&response, 0, sizeof(response));
	ret = isapi_get_storage(0, &request, &response);
	trace(TRACE, "[%s]:hdd_attri=%d dev_type=%d errno=%d LINE:%d\n", __func__, response.hdd_attri, response.dev_type, ret, __LINE__);

	return 0;
}

/***************************************************************************
 * Description: URL: GET /ISAPI/System/time/ntpServers
 * Return:0-succed; -1-failure
 * *************************************************************************/
sint32 test_get_time_ntpservers()
{
	sint32 ret = 0;
	ISAPI_NULL_S request;
	SYSTEM_NTP_CFG_S response;

	trace(TRACE, "\e[32m[%s]:****************************** line:%d\e[0m\n", __func__, __LINE__);
	memset(&request, 0, sizeof(request));
	memset(&response, 0, sizeof(response));
	ret = isapi_get_time_ntpservers(0, &request, &response);
	trace(TRACE, "[%s]:ntp_host=%s errno=%d LINE:%d\n", __func__, response.ntp_host, ret, __LINE__);

	return 0;
}

/***************************************************************************
 * Description: URL: PUT /ISAPI/System/time/ntpServers
 * Return:0-succed; -1-failure
 * *************************************************************************/
sint32 test_put_time_ntpservers()
{
	sint32 ret = 0;
	SYSTEM_NTP_CFG_S request, initInfo;
	COMMON_RESPONSE_S response;

	trace(TRACE, "\e[32m[%s]:****************************** line:%d\e[0m\n", __func__, __LINE__);
	memset(&request, 0, sizeof(request));
	memset(&response, 0, sizeof(response));
	memset(&initInfo, 0, sizeof(initInfo));
	if(0 > isapi_get_time_ntpservers(0, NULL, &initInfo))
	{
		trace(ERROR, "[%s]:get initInfo failed! LINE:%d\n", __func__, __LINE__);
		return -1;
	}
	ret = isapi_put_time_ntpservers(0, &request, &response);
	trace(TRACE, "[%s]:requestURL=%s statusCode=%d statusString=%s subStatusCode=%s errno=%d LINE:%d\n", __func__, response.requestURL, response.statusCode, response.statusString, response.subStatusCode, ret,__LINE__);

	return 0;
}

/***************************************************************************
 * Description: URL:GET /ISAPI/System/time
 * Return:0-succed; -1-failure
 * *************************************************************************/
sint32 test_get_time()
{
	sint32 ret = 0;
	ISAPI_NULL_S request;
	SYSTEM_TIME_CFG_S response;

	trace(TRACE, "\e[32m[%s]:****************************** line:%d\e[0m\n", __func__, __LINE__);
	memset(&request, 0, sizeof(request));
	memset(&response, 0, sizeof(response));
	ret = isapi_get_time(0, &request, &response);
	trace(TRACE, "[%s]:year=%d month=%d day=%d errno=%d LINE:%d\n", __func__, response.dev_time.year, response.dev_time.month, response.dev_time.day, ret, __LINE__);

	return 0;
}

/***************************************************************************
 * URL:GET /ISAPI/ContentMgmt/InputProxy/pnp
 * Return:0-succed; -1-failure
 * *************************************************************************/
sint32 test_get_inputProxy_pnp()
{
	sint32 ret = 0;
	ISAPI_NULL_S request;
	COMMON_RESPONSE_S response;

	trace(TRACE, "\e[32m[%s]:****************************** line:%d\e[0m\n", __func__, __LINE__);
	memset(&request, 0, sizeof(request));
	memset(&response, 0, sizeof(response));
	ret = isapi_get_inputProxy_pnp(0, &request, &response);
	trace(TRACE, "[%s]:requestURL=%s statusCode=%d statusString=%s subStatusCode=%s errno=%d LINE:%d\n", __func__, response.requestURL, response.statusCode, response.statusString, response.subStatusCode, ret,__LINE__);

	return 0;
}

/***************************************************************************
 * Description: URL:PUT /ISAPI/ContentMgmt/InputProxy/pnp
 * Return:0-succed; -1-failure
 * *************************************************************************/
sint32 test_put_inputProxy_pnp()
{
	sint32 ret = 0;
	ISAPI_NULL_S request;
	COMMON_RESPONSE_S response;

	trace(TRACE, "\e[32m[%s]:****************************** line:%d\e[0m\n", __func__, __LINE__);
	memset(&request, 0, sizeof(request));
	memset(&response, 0, sizeof(response));
	ret = isapi_put_inputProxy_pnp(0, &request, &response);
	trace(TRACE, "[%s]:requestURL=%s statusCode=%d statusString=%s subStatusCode=%s errno=%d LINE:%d\n", __func__, response.requestURL, response.statusCode, response.statusString, response.subStatusCode, ret,__LINE__);

	return 0;
}

/***************************************************************************
 * Description: URL:GET /ISAPI/ContentMgmt/InputProxy/channels/status
 * Return:0-succed; -1-failure
 * *************************************************************************/
sint32 test_get_inputProxy_channels_status()
{
	sint32 ret = 0, i = 0;
	ISAPI_NULL_S request;
	INPUTPROXY_S response;

	trace(TRACE, "\e[32m[%s]:****************************** line:%d\e[0m\n", __func__, __LINE__);
	memset(&request, 0, sizeof(request));
	memset(&response, 0, sizeof(response));
	ret = isapi_get_inputProxy_channels_status(0, &request, &response);
	for(i = 0; i < 3; i++)
	{
		trace(TRACE, "[%s]:id=%d protocol=%d errno=%d LINE:%d\n", __func__, response.ich[i].id, response.ich[i].desc.proto, ret, __LINE__);
	}

	return 0;
}

/*******************************************************
 * Description:测试程序的入口函数
 * Return:0-succed; -1-failure
 * *****************************************************/
int main(int argc, const char *argv[])
{
	init();
	while(1)
	{
		usleep(1000000);
		printf("\n");
		test_set_http_attr(); 
		//设备参数
		test_get_inputProxy_channels_status(); //GET /ISAPI/ContentMgmt/InputProxy/channels/status
		test_get_inputProxy_pnp(); //GET /ISAPI/ContentMgmt/InputProxy/pnp
		test_put_inputProxy_pnp(); //PUT /ISAPI/ContentMgmt/InputProxy/pnp 没有封装xml
		test_get_time(); //GET GET /ISAPI/System/time 
		test_get_time_ntpservers(); //GET /ISAPI/System/time/ntpServers
		test_put_time_ntpservers(); //PUT /ISAPI/System/time/ntpServers
		test_get_storage(); //GET /ISAPI/ContentMgmt/Storage
		test_get_deviceInfo_capabilities(); //GET /ISAPI/System/deviceInfo/capabilities
		test_get_deviceInfo(); //GET /ISAPI/System/deviceInfo
		test_put_deviceInfo(); //ISAPI/System/deviceInfo
		//网络设置
		test_get_network_ddns_channel(); //GET /ISAPI/System/Network/DDNS/1
		//test_put_network_interfaces_channel(); //PUT /ISAPI/System/Network/interfaces/1
		test_get_network_interfaces(); //URL:GET /ISAPI/System/Network/interfaces
		test_put_network_mailing(); //URL: PUT /ISAPI/System/Network/mailing
		test_get_network_mailing(); //URL: GET /ISAPI/System/Network/mailing
		test_get_network_interfaces_capabilities(); //URL:GET /ISAPI/System/Network/interfaces/capabilities
		test_get_network_UPnP_ports_status(); //GET /ISAPI/System/Network/UPnP/ports/status
		test_get_network_UPnP(); //GET /ISAPI/System/Network/UPnP;
		test_put_network_UPnP(); //PUT /ISAPI/System/Network/UPnP      
		test_put_network_ddns(); //PUT /ISAPI/System/Network/DDNS
		test_get_network_ddns_capabilities(); //GET /ISAPI/System/Network/DDNS/capabilities
		test_get_adminAccesses(); //GET /ISAPI/Security/adminAccesses
		test_put_adminAccesses(); //PUT /ISAPI/Security/adminAccesses
	}

	return 0;
}

