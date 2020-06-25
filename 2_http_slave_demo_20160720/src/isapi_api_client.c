/****************************************************************
 * Copyright(C), 2016, Hanbang Tech.Co.,Ltd
 * File Name:slave_http
 * Author:merlin
 * Version:v1
 * Data:20160613
 * Description:以下接口是提供给其他模块使用的,调用这些接口可以测试ISAPI模块
 * History:
 * *************************************************************/
#include "isapi_api_client.h"

/******************************************************************************
 * Description：获取网络设置功能中interfaces相关的信息(URL:GET ISAPI/System/Network/interfaces)
 * Input handler：模块句柄，暂时无效
 * Input request：封装http请求包需要用到的参数 
 * Output response：获取到的参数
 * Return：0-成功 <0-错误代码
 * *****************************************************************************/
sint32 isapi_get_network_interfaces(sint32 handler, ISAPI_NULL_S *request, NETWORK_DEVICE_INFO_S *response)
{
	sint32 rx_len = 10240, ret = 0;
	uint32 tx_buffer[1240] = {0};
	void *rx_buffer = NULL;

	if(response == NULL) //检测输入参数
	{
		return NULL_VALUE;
	}

	rx_buffer = malloc(rx_len); //分配缓存空间
	if(rx_buffer == NULL)
	{
		trace(ERROR, "[%s]:malloc=%s LINE:%d\n", __func__, strerror(errno), __LINE__);
		return MEMORY_FAILURE;
	}

	ret = http_package(HTTP_GET, "/ISAPI/System/Network/interfaces", tx_buffer, rx_buffer, rx_len); //完整的http数据帧
	if(ret < 0)
	{
		trace(ERROR, "[%s]:deal with http failure! %d\n", __func__, __LINE__);
		free(rx_buffer);
		return ret;
	}

	ret = ParseXmlNetworkInterfaces((char*)rx_buffer, response); /*解析获取到的xml数据帧*/
	if(ret < 0)
	{
		free(rx_buffer);
		return ret;
	}
	free(rx_buffer);

	return 0;
}

/******************************************************************************
 * Description：获取邮件设置相关的信息 (URL:GET /ISAPI/System/Network/mailing)
 * Input handler：模块句柄，暂时无效
 * Input request：封装http请求包需要用到的参数
 * Output response：解析响应包得到的信息
 * Return：0-成功 <0-错误代码
 * *****************************************************************************/
sint32 isapi_get_network_mailing(sint32 handler, ISAPI_NULL_S *request, NETWORK_SMTP_S *response)
{
	sint32 rx_len = 10240, ret = 0;
	uint32 tx_buffer[1240] = {0};
	void *rx_buffer = NULL;

	if(response == NULL) //检测输入参数
	{
		return NULL_VALUE;
	}

	rx_buffer = malloc(rx_len); //分配缓存空间
	if(rx_buffer == NULL)
	{
		trace(ERROR, "[%s]:malloc=%s LINE:%d\n", __func__, strerror(errno), __LINE__);
		return MEMORY_FAILURE;
	}

	ret = http_package(HTTP_GET, "/ISAPI/System/Network/mailing", tx_buffer, rx_buffer, rx_len); //完整的http数据帧
	if(ret < 0)
	{
		trace(ERROR, "[%s]:deal with http failure! %d\n", __func__, __LINE__);
		free(rx_buffer);
		return ret;
	}

	ret = ParseXmlMailing((char*)rx_buffer, response);
	if(ret < 0)
	{
		free(rx_buffer);
		return ret;
	}
	free(rx_buffer);

	return 0;
}

/******************************************************************************
 * Description：设置邮件设置相关的信息 (URL:PUT /ISAPI/System/Network/mailing)
 * Input handler：模块句柄，暂时无效
 * Input request：封装http请求包需要用到的参数
 * Output response：解析响应包得到的信息
 * Return：0-成功 <0-错误代码
 * *****************************************************************************/
sint32 isapi_put_network_mailing(sint32 handler, NETWORK_SMTP_S *request, COMMON_RESPONSE_S *response)
{
	sint32 tx_len = 1024, rx_len = 10240, ret = 0;
	uint32 tx_buffer[1240] = {0};
	void *rx_buffer = NULL;

	if(response == NULL) //检测输入参数
	{
		return NULL_VALUE;
	}

	rx_buffer = malloc(rx_len); //分配缓存空间
	if(rx_buffer == NULL)
	{
		trace(ERROR, "[%s]:malloc=%s LINE:%d\n", __func__, strerror(errno), __LINE__);
		return MEMORY_FAILURE;
	}

	GenXmlMailing((char*)tx_buffer, tx_len, request); //消息正文，xml数据帧
	if(0 >= strlen((char*)tx_buffer)) //组装xml文件失败
	{
		trace(ERROR, "[%s]:create xml data failure! LINE:%d\n", __func__, __LINE__);
		return CREATE_XML;
	}

	ret = http_package(HTTP_PUT, "/ISAPI/System/Network/mailing", tx_buffer, rx_buffer, rx_len); //完整的http数据帧
	if(ret < 0)
	{
		trace(ERROR, "[%s]:deal with http failure! %d\n", __func__, __LINE__);
		free(rx_buffer);
		return ret;
	}

	ret = ParseXmlCommonResponse((char*)rx_buffer, response); //响应正文，xml数据帧
	if(ret < 0)
	{
		free(rx_buffer);
		return ret;
	}
	free(rx_buffer);

	return 0;
}


/******************************************************************************
 * Description：获取权限相关的信息(URL:GET /ISAPI/System/Network/interfaces/capabilities)
 * Input handler：模块句柄，暂时无效
 * Input request：封装http请求包需要用到的参数
 * Output response：解析响应包得到的信息
 * Return：0-成功 <0-错误代码
 * *****************************************************************************/
sint32 isapi_get_network_interfaces_capabilities(sint32 handler, ISAPI_NULL_S *request, NETWORK_DEVICE_INFO_S *response)
{
	sint32 rx_len = 10240, ret = 0;
	uint32 tx_buffer[1240] = {0};
	void *rx_buffer = NULL;

	if(response == NULL) //检测输入参数
	{
		return NULL_VALUE;
	}

	rx_buffer = malloc(rx_len); //分配缓存空间
	if(rx_buffer == NULL)
	{
		trace(ERROR, "[%s]:malloc=%s LINE:%d\n", __func__, strerror(errno), __LINE__);
		return MEMORY_FAILURE;
	}

	ret = http_package(HTTP_GET, "/ISAPI/System/Network/interfaces/capabilities", tx_buffer, rx_buffer, rx_len); //完整的http数据帧
	if(ret < 0)
	{
		trace(ERROR, "[%s]:deal with http failure! %d\n", __func__, __LINE__);
		free(rx_buffer);
		return ret;
	}

	ret = ParseXmlNetworkInterfaces((char*)rx_buffer, response);
	if(ret < 0)
	{
		free(rx_buffer);
		return ret;
	}
	free(rx_buffer);

	return 0;
}
	
/******************************************************************************
 * Description：获取权限相关的信息(URL: GET /ISAPI/System/Network/UPnP/ports/status)
 * Input handler：模块句柄，暂时无效
 * Input request：封装http请求包需要用到的参数
 * Output response：解析响应包得到的信息
 * Return：0-成功 <0-错误代码
 * *****************************************************************************/
sint32 isapi_get_network_UPnP_ports_status(sint32 handler, ISAPI_NULL_S *request, NETWORK_UPNP_S *response)
{
	sint32 tx_len = 1024, rx_len = 40960, ret = 0;
	uint32 tx_buffer[1240] = {0};
	void *rx_buffer = NULL;

	if(response == NULL) //检测输入参数
	{
		return NULL_VALUE;
	}

	rx_buffer = malloc(rx_len); //分配缓存空间
	if(rx_buffer == NULL)
	{
		trace(ERROR, "[%s]:malloc=%s LINE:%d\n", __func__, strerror(errno), __LINE__);
		return MEMORY_FAILURE;
	}

	memset(tx_buffer, 0, tx_len);
	ret = http_package(HTTP_GET, "/ISAPI/System/Network/UPnP/ports/status", tx_buffer, rx_buffer, rx_len); //完整的http数据帧
	if(ret < 0)
	{
		trace(ERROR, "[%s]:deal with http failure! %d\n", __func__, __LINE__);
		free(rx_buffer);
		return ret;
	}

	ret = ParseXmlUPnPPortList((char*)rx_buffer, response); //响应正文，xml数据帧
	if(ret < 0)
	{
		free(rx_buffer);
		return ret;
	}
	free(rx_buffer);

	return 0;
}

/******************************************************************************
 * Description：获取权限相关的信息(URL: GET /ISAPI/System/Network/UPnP)
 * Input handler：模块句柄，暂时无效
 * Input request：封装http请求包需要用到的参数
 * Output response：解析响应包得到的信息
 * Return：0-成功 <0-错误代码
 * *****************************************************************************/
sint32 isapi_get_network_UPnP(sint32 handler, ISAPI_NULL_S *request, NETWORK_UPNP_S *response)
{
	sint32 tx_len = 1024, rx_len = 40960, ret = 0;
	uint32 tx_buffer[1240] = {0};
	void *rx_buffer = NULL;

	if(response == NULL) //检测输入参数
	{
		return NULL_VALUE;
	}

	rx_buffer = malloc(rx_len); //分配缓存空间
	if(rx_buffer == NULL)
	{
		trace(ERROR, "[%s]:malloc=%s LINE:%d\n", __func__, strerror(errno), __LINE__);
		return MEMORY_FAILURE;
	}

	memset(tx_buffer, 0, tx_len);
	ret = http_package(HTTP_GET, "/ISAPI/System/Network/UPnP", tx_buffer, rx_buffer, rx_len); //完整的http数据帧
	if(ret < 0)
	{
		trace(ERROR, "[%s]:deal with http failure! %d\n", __func__, __LINE__);
		free(rx_buffer);
		return ret;
	}

	ret = ParseXmlUPnP((char*)rx_buffer, response); //响应正文，xml数据帧
	if(ret < 0)
	{
		free(rx_buffer);
		return ret;
	}
	free(rx_buffer);

	return 0;
}

/******************************************************************************
 * Description：获取权限相关的信息(URL: PUT /ISAPI/System/Network/UPnP)
 * Input handler：模块句柄，暂时无效
 * Input request：封装http请求包需要用到的参数
 * Output response：解析响应包得到的信息
 * Return：0-成功 <0-错误代码
 * *****************************************************************************/
sint32 isapi_put_network_UPnP(sint32 handler, NETWORK_UPNP_S *request, COMMON_RESPONSE_S *response)
{
	sint32 tx_len = 1024, rx_len = 40960, ret = 0;
	uint32 tx_buffer[1240] = {0};
	void *rx_buffer = NULL;

	if(response == NULL) //检测输入参数
	{
		return NULL_VALUE;
	}

	rx_buffer = malloc(rx_len); //分配缓存空间
	if(rx_buffer == NULL)
	{
		trace(ERROR, "[%s]:malloc=%s LINE:%d\n", __func__, strerror(errno), __LINE__);
		return MEMORY_FAILURE;
	}
	memset(tx_buffer, 0, tx_len);
	GenXmlUPnP((char*)tx_buffer, tx_len, request); //消息正文，xml数据帧
	if(0 >= strlen((char*)tx_buffer)) //组装xml文件失败
	{
		trace(ERROR, "[%s]:create xml data failure! LINE:%d\n", __func__, __LINE__);
		return CREATE_XML;
	}

	ret = http_package(HTTP_PUT, "/ISAPI/System/Network/UPnP", tx_buffer, rx_buffer, rx_len); //完整的http数据帧
	if(ret < 0)
	{
		trace(ERROR, "[%s]:deal with http failure! %d\n", __func__, __LINE__);
		free(rx_buffer);
		return ret;
	}

	ret = ParseXmlCommonResponse((char*)rx_buffer, response); //响应正文，xml数据帧
	if(ret < 0)
	{
		free(rx_buffer);
		return ret;
	}
	free(rx_buffer);

	return 0;
}

/******************************************************************************
 * Description：获取权限相关的信息(URL: PUT /ISAPI/System/Network/DDNS)
 * Input handler：模块句柄，暂时无效
 * Input request：封装http请求包需要用到的参数
 * Output response：解析响应包得到的信息
 * Return：0-成功 <0-错误代码
 * *****************************************************************************/
sint32 isapi_put_network_ddns(sint32 handler, NETWORK_DDNS_S *request, COMMON_RESPONSE_S *response)
{
	sint32 tx_len = 1024, rx_len = 40960, ret = 0;
	uint32 tx_buffer[1240] = {0};
	void *rx_buffer = NULL;

	if(response == NULL) //检测输入参数
	{
		return NULL_VALUE;
	}

	rx_buffer = malloc(rx_len); //分配缓存空间
	if(rx_buffer == NULL)
	{
		trace(ERROR, "[%s]:malloc=%s LINE:%d\n", __func__, strerror(errno), __LINE__);
		return MEMORY_FAILURE;
	}

	memset(tx_buffer, 0, tx_len);
	GenXmlDDNS((char*)tx_buffer, tx_len, request); //消息正文，xml数据帧
	if(0 >= strlen((char*)tx_buffer)) //组装xml文件失败
	{
		trace(ERROR, "[%s]:create xml data failure! LINE:%d\n", __func__, __LINE__);
		return CREATE_XML;
	}

	ret = http_package(HTTP_PUT, "/ISAPI/System/Network/DDNS", tx_buffer, rx_buffer, rx_len); //完整的http数据帧
	if(ret < 0)
	{
		trace(ERROR, "[%s]:deal with http failure! %d\n", __func__, __LINE__);
		free(rx_buffer);
		return ret;
	}

	ret = ParseXmlCommonResponse((char*)rx_buffer, response); //响应正文，xml数据帧
	if(ret < 0)
	{
		free(rx_buffer);
		return ret;
	}
	free(rx_buffer);

	return 0;
}

/******************************************************************************
 * Description：获取权限相关的信息(URL: GET /ISAPI/System/Network/DDNS/capabilities)
 * Input handler：模块句柄，暂时无效
 * Input request：封装http请求包需要用到的参数
 * Output response：解析响应包得到的信息
 * Return：0-成功 <0-错误代码
 * *****************************************************************************/
sint32 isapi_get_network_ddns_capabilities(sint32 handler, ISAPI_NULL_S *request, NETWORK_DDNS_S *response)
{
	sint32 tx_len = 1024, rx_len = 40960, ret = 0;
	uint32 tx_buffer[1240] = {0};
	void *rx_buffer = NULL;

	if(response == NULL) //检测输入参数
	{
		return NULL_VALUE;
	}

	rx_buffer = malloc(rx_len); //分配缓存空间
	if(rx_buffer == NULL)
	{
		trace(ERROR, "[%s]:malloc=%s LINE:%d\n", __func__, strerror(errno), __LINE__);
		return MEMORY_FAILURE;
	}

	memset(tx_buffer, 0, tx_len);
	ret = http_package(HTTP_GET, "/ISAPI/System/Network/DDNS/capabilities", tx_buffer, rx_buffer, rx_len); //完整的http数据帧
	if(ret < 0)
	{
		trace(ERROR, "[%s]:deal with http failure! %d\n", __func__, __LINE__);
		free(rx_buffer);
		return ret;
	}

    ret = ParseXmlDDNS((char*)rx_buffer, response);
	if(ret < 0)
	{
		free(rx_buffer);
		return ret;
	}
	free(rx_buffer);

	return 0;
}

/******************************************************************************
 * Description：获取权限相关的信息(URL: GET /ISAPI/Security/adminAccesses)
 * Input handler：模块句柄，暂时无效
 * Input request：封装http请求包需要用到的参数
 * Output response：解析响应包得到的信息
 * Return：0-成功 <0-错误代码
 * *****************************************************************************/
sint32 isapi_get_adminAccesses(sint32 handler, ISAPI_NULL_S *request, SECURITY_PORTINFO_S *response)
{
	sint32 tx_len = 1024, rx_len = 40960, ret = 0;
	uint32 tx_buffer[1240] = {0};
	void *rx_buffer = NULL;

	if(response == NULL) //检测输入参数
	{
		return NULL_VALUE;
	}

	rx_buffer = malloc(rx_len); //分配缓存空间
	if(rx_buffer == NULL)
	{
		trace(ERROR, "[%s]:malloc=%s LINE:%d\n", __func__, strerror(errno), __LINE__);
		return MEMORY_FAILURE;
	}

	memset(tx_buffer, 0, tx_len);
	ret = http_package(HTTP_GET, "/ISAPI/Security/adminAccesses", tx_buffer, rx_buffer, rx_len); //完整的http数据帧
	if(ret < 0)
	{
		trace(ERROR, "[%s]:deal with http failure! %d\n", __func__, __LINE__);
		free(rx_buffer);
		return ret;
	}

	ret = ParseXmlAdminAccesses(rx_buffer, response);
	if(ret < 0)
	{
		free(rx_buffer);
		return ret;
	}
	free(rx_buffer);

	return 0;
}

/******************************************************************************
 * Description：获取权限相关的信息(URL: PUT /ISAPI/Security/adminAccesses)
 * Input handler：模块句柄，暂时无效
 * Input request：封装http请求包需要用到的参数
 * Output response：解析响应包得到的信息
 * Return：0-成功 <0-错误代码
 * *****************************************************************************/
sint32 isapi_put_adminAccesses(sint32 handler, SECURITY_PORTINFO_S *request, COMMON_RESPONSE_S *response)
{
	sint32 tx_len = 1024, rx_len = 40960, ret = 0;
	uint32 tx_buffer[1240] = {0};
	void *rx_buffer = NULL;

	if(response == NULL) //检测输入参数
	{
		return NULL_VALUE;
	}

	rx_buffer = malloc(rx_len); //分配缓存空间
	if(rx_buffer == NULL)
	{
		trace(ERROR, "[%s]:malloc=%s LINE:%d\n", __func__, strerror(errno), __LINE__);
		return MEMORY_FAILURE;
	}

	memset(tx_buffer, 0, tx_len);
	GenXmlAdminAccesses((char*)tx_buffer, request); //消息正文，xml数据帧
	if(0 >= strlen((char*)tx_buffer)) //组装xml文件失败
	{
		trace(ERROR, "[%s]:create xml data failure! LINE:%d\n", __func__, __LINE__);
		return CREATE_XML;
	}

	ret = http_package(HTTP_PUT, "/ISAPI/Security/adminAccesses", tx_buffer, rx_buffer, rx_len); //完整的http数据帧
	if(ret < 0)
	{
		trace(ERROR, "[%s]:deal with http failure! %d\n", __func__, __LINE__);
		free(rx_buffer);
		return ret;
	}

	ret = ParseXmlCommonResponse((char*)rx_buffer, response); //响应正文，xml数据帧
	if(ret < 0)
	{
		free(rx_buffer);
		return ret;
	}
	free(rx_buffer);

	return 0;
}

/******************************************************************************
 * Description：(URL: GET /ISAPI/System/Network/DDNS/1)
 * Input：
 * Output ：
 * Output ：
 * Return：0-成功 -1-失败
 * *****************************************************************************/
sint32 isapi_get_network_ddns_channel(sint32 handler, ISAPI_NULL_S *request, sint32 channel, NETWORK_DDNS_S *response)
{
	sint32 rx_len = 10240, ret = 0;
	uint32 tx_buffer[1240] = {0}, url[256] = {0};
	void *rx_buffer = NULL;

	if(response == NULL) //检测输入参数
	{
		return NULL_VALUE;
	}

	rx_buffer = malloc(rx_len); //分配缓存空间
	if(rx_buffer == NULL)
	{
		trace(ERROR, "[%s]:malloc=%s LINE:%d\n", __func__, strerror(errno), __LINE__);
		return MEMORY_FAILURE;
	}

	sprintf((char*)url, "/ISAPI/System/Network/DDNS/%d", (int)channel);
	ret = http_package(HTTP_GET, url, tx_buffer, rx_buffer, rx_len); //完整的http数据帧
	if(ret < 0)
	{
		trace(ERROR, "[%s]:deal with http failure! %d\n", __func__, __LINE__);
		free(rx_buffer);
		return ret;
	}
	ret = ParseXmlDDNS((char*)rx_buffer, response); //响应正文，xml数据帧
	if(ret < 0)
	{
		free(rx_buffer);
		return ret;
	}
	free(rx_buffer);

	return 0;
}

/******************************************************************************
 * Description：(URL: PUT /ISAPI/System/Network/interfaces/1)
 * Input：
 * Output ：
 * Output ：
 * Return：0-成功 -1-失败
 * *****************************************************************************/
sint32 isapi_put_network_interfaces_channel(sint32 handler, NETWORK_DEVICE_INFO_S *request, sint32 channel, COMMON_RESPONSE_S *response)
{
	sint32 tx_len = 1024, rx_len = 10240, ret = 0;
	uint32 tx_buffer[1240] = {0}, url[256] = {0};
	void *rx_buffer = NULL;

	if(response == NULL) //检测输入参数
	{
		return NULL_VALUE;
	}

	rx_buffer = malloc(rx_len); //分配缓存空间
	if(rx_buffer == NULL)
	{
		trace(ERROR, "[%s]:malloc=%s LINE:%d\n", __func__, strerror(errno), __LINE__);
		return MEMORY_FAILURE;
	}

	memset(tx_buffer, 0, tx_len);
	GenXmlNetworkInterfacesChannel((char*)tx_buffer, tx_len, request, 0); //消息正文，xml数据帧
	if(0 >= strlen((char*)tx_buffer)) //组装xml文件失败
	{
		trace(ERROR, "[%s]:create xml data failure! LINE:%d\n", __func__, __LINE__);
		return CREATE_XML;
	}

	sprintf((char*)url, "/ISAPI/System/Network/interfaces/%d", (int)channel);
	ret = http_package(HTTP_PUT, url, tx_buffer, rx_buffer, rx_len); //完整的http数据帧
	if(ret < 0)
	{
		trace(ERROR, "[%s]:deal with http failure! %d\n", __func__, __LINE__);
		free(rx_buffer);
		return ret;
	}

	ret = ParseXmlCommonResponse((char*)rx_buffer, response); //响应正文，xml数据帧
	if(ret < 0)
	{
		free(rx_buffer);
		return ret;
	}
	free(rx_buffer);

	return 0;
}

/******************************************************************************
 * Description：(URL: GET /ISAPI/System/deviceInfo )
 * Input：
 * Output ：
 * Output ：
 * Return：0-成功 -1-失败
 * *****************************************************************************/
sint32 isapi_get_deviceInfo(sint32 handler, ISAPI_NULL_S *request, SYSTEM_DEVICE_INFO_S *response)
{
	sint32 tx_len = 1024, rx_len = 10240, ret = 0;
	uint32 tx_buffer[1240] = {0};
	void *rx_buffer = NULL;

	if(response == NULL) //检测输入参数
	{
		return NULL_VALUE;
	}

	rx_buffer = malloc(rx_len); //分配缓存空间
	if(rx_buffer == NULL)
	{
		trace(ERROR, "[%s]:malloc=%s LINE:%d\n", __func__, strerror(errno), __LINE__);
		return MEMORY_FAILURE;
	}

	memset(tx_buffer, 0, tx_len);
	ret = http_package(HTTP_GET, "/ISAPI/System/deviceInfo", tx_buffer, rx_buffer, rx_len); //完整的http数据帧
	if(ret < 0)
	{
		trace(ERROR, "[%s]:deal with http failure! %d\n", __func__, __LINE__);
		free(rx_buffer);
		return ret;
	}

	ret = ParseXmlDeviceInfo((char*)rx_buffer, response); //响应正文，xml数据帧
	if(ret < 0)
	{
		free(rx_buffer);
		return ret;
	}
	free(rx_buffer);

	return 0;
}

/******************************************************************************
 * Description：(URL: PUT /ISAPI/System/deviceInfo )
 * Input：
 * Output ：
 * Output ：
 * Return：0-成功 -1-失败
 * *****************************************************************************/
sint32 isapi_put_deviceInfo(sint32 handler, SYSTEM_DEVICE_INFO_S *request, COMMON_RESPONSE_S *response)
{
	sint32 tx_len = 1024, rx_len = 10240, ret = 0;
	uint32 tx_buffer[1240] = {0};
	void *rx_buffer = NULL;

	if(response == NULL) //检测输入参数
	{
		return NULL_VALUE;
	}

	rx_buffer = malloc(rx_len); //分配缓存空间
	if(rx_buffer == NULL)
	{
		trace(ERROR, "[%s]:malloc=%s LINE:%d\n", __func__, strerror(errno), __LINE__);
		return MEMORY_FAILURE;
	}

	memset(tx_buffer, 0, tx_len);
	GenXmlDeviceInfo((char*)tx_buffer, (*request));
	if(0 >= strlen((char*)tx_buffer)) //组装xml文件失败
	{
		trace(ERROR, "[%s]:create xml data failure! LINE:%d\n", __func__, __LINE__);
		return CREATE_XML;
	}

	ret = http_package(HTTP_PUT, "/ISAPI/System/deviceInfo", tx_buffer, rx_buffer, rx_len); //完整的http数据帧
	if(ret < 0)
	{
		trace(ERROR, "[%s]:deal with http failure! %d\n", __func__, __LINE__);
		free(rx_buffer);
		return ret;
	}

	ret = ParseXmlCommonResponse((char*)rx_buffer, response); //响应正文，xml数据帧
	if(ret < 0)
	{
		free(rx_buffer);
		return ret;
	}
	free(rx_buffer);

	return 0;
}

/******************************************************************************
 * Description：(URL: GET /ISAPI/System/deviceInfo/capabilities)
 * Input：
 * Output ：
 * Output ：
 * Return：0-成功 -1-失败
 * *****************************************************************************/
sint32 isapi_get_deviceInfo_capabilities(sint32 handler, ISAPI_NULL_S *request, SYSTEM_DEVICE_INFO_S *response)
{
	sint32 tx_len = 1024, rx_len = 10240, ret = 0;
	uint32 tx_buffer[1240] = {0};
	void *rx_buffer = NULL;

	if(response == NULL) //检测输入参数
	{
		return NULL_VALUE;
	}

	rx_buffer = malloc(rx_len); //分配缓存空间
	if(rx_buffer == NULL)
	{
		trace(ERROR, "[%s]:malloc=%s LINE:%d\n", __func__, strerror(errno), __LINE__);
		return MEMORY_FAILURE;
	}

	memset(tx_buffer, 0, tx_len);
	ret = http_package(HTTP_GET, "/ISAPI/System/deviceInfo/capabilities", tx_buffer, rx_buffer, rx_len); //完整的http数据帧
	if(ret < 0)
	{
		trace(ERROR, "[%s]:deal with http failure! %d\n", __func__, __LINE__);
		free(rx_buffer);
		return ret;
	}

	ret = ParseXmlDeviceInfo((char*)rx_buffer, response); //响应正文，xml数据帧
	if(ret < 0)
	{
		free(rx_buffer);
		return ret;
	}
	free(rx_buffer);

	return 0;
}


/******************************************************************************
 * Description：(URL: GET /ISAPI/ContentMgmt/Storage)
 * Input：
 * Output ：
 * Output ：
 * Return：0-成功 -1-失败
 * *****************************************************************************/
sint32 isapi_get_storage(sint32 handler, ISAPI_NULL_S *request, DEVICE_DISK_ATTR_S *response)
{
	sint32 tx_len = 1024, rx_len = 10240, ret = 0;
	uint32 tx_buffer[1240] = {0};
	void *rx_buffer = NULL;

	if(response == NULL) //检测输入参数
	{
		return NULL_VALUE;
	}

	rx_buffer = malloc(rx_len); //分配缓存空间
	if(rx_buffer == NULL)
	{
		trace(ERROR, "[%s]:malloc=%s LINE:%d\n", __func__, strerror(errno), __LINE__);
		return MEMORY_FAILURE;
	}

	memset(tx_buffer, 0, tx_len);
	ret = http_package(HTTP_GET, "/ISAPI/ContentMgmt/Storage", tx_buffer, rx_buffer, rx_len); //完整的http数据帧
	if(ret < 0)
	{
		trace(ERROR, "[%s]:deal with http failure! %d\n", __func__, __LINE__);
		free(rx_buffer);
		return ret;
	}

	ret = ParseXmlStorageInfo((char*)rx_buffer, response); //响应正文，xml数据帧
	if(ret < 0)
	{
		free(rx_buffer);
		return ret;
	}
	free(rx_buffer);

	return 0;
}

/******************************************************************************
 * Description：(URL: GET /ISAPI/System/time/ntpServers)
 * Input：
 * Output ：
 * Output ：
 * Return：0-成功 -1-失败
 * *****************************************************************************/
sint32 isapi_get_time_ntpservers(sint32 handler, ISAPI_NULL_S *request, SYSTEM_NTP_CFG_S *response)
{
	sint32 tx_len = 1024, rx_len = 10240, ret = 0;
	uint32 tx_buffer[1240] = {0};
	void *rx_buffer = NULL;

	if(response == NULL) //检测输入参数
	{
		return NULL_VALUE;
	}

	rx_buffer = malloc(rx_len); //分配缓存空间
	if(rx_buffer == NULL)
	{
		trace(ERROR, "[%s]:malloc=%s LINE:%d\n", __func__, strerror(errno), __LINE__);
		return MEMORY_FAILURE;
	}

	memset(tx_buffer, 0, tx_len);
	ret = http_package(HTTP_GET, "/ISAPI/System/time/ntpServers", tx_buffer, rx_buffer, rx_len); //完整的http数据帧
	if(ret < 0)
	{
		trace(ERROR, "[%s]:deal with http failure! %d\n", __func__, __LINE__);
		free(rx_buffer);
		return ret;
	}

	ret = ParseXmlSystemNtpServer((char*)rx_buffer, response); //响应正文，xml数据帧
	if(ret < 0)
	{
		free(rx_buffer);
		return ret;
	}
	free(rx_buffer);

	return 0;
}


/******************************************************************************
 * Description：(URL: PUT /ISAPI/System/time/ntpServers)
 * Input：
 * Output ：
 * Output ：
 * Return：0-成功 -1-失败
 * *****************************************************************************/
sint32 isapi_put_time_ntpservers(sint32 handler, SYSTEM_NTP_CFG_S *request, COMMON_RESPONSE_S *response)
{
	sint32 tx_len = 1024, rx_len = 10240, ret = 0;
	uint32 tx_buffer[1240] = {0};
	void *rx_buffer = NULL;

	if(response == NULL) //检测输入参数
	{
		return NULL_VALUE;
	}

	rx_buffer = malloc(rx_len); //分配缓存空间
	if(rx_buffer == NULL)
	{
		trace(ERROR, "[%s]:malloc=%s LINE:%d\n", __func__, strerror(errno), __LINE__);
		return MEMORY_FAILURE;
	}

	memset(tx_buffer, 0, tx_len);
	GenXmlSystemNtpServer((char*)tx_buffer, tx_len, request);
	if(0 >= strlen((char*)tx_buffer)) //组装xml文件失败
	{
		trace(ERROR, "[%s]:create xml data failure! LINE:%d\n", __func__, __LINE__);
		return CREATE_XML;
	}

	ret = http_package(HTTP_PUT, "/ISAPI/System/time/ntpServers", tx_buffer, rx_buffer, rx_len); //完整的http数据帧
	if(ret < 0)
	{
		trace(ERROR, "[%s]:deal with http failure! %d\n", __func__, __LINE__);
		free(rx_buffer);
		return ret;
	}

	ret = ParseXmlCommonResponse((char*)rx_buffer, response); //响应正文，xml数据帧
	if(ret < 0)
	{
		free(rx_buffer);
		return ret;
	}
	free(rx_buffer);

	return 0;
}


/******************************************************************************
 * Description：(URL: GET /ISAPI/System/time)
 * Input：
 * Output ：
 * Output ：
 * Return：0-成功 -1-失败
 * *****************************************************************************/
sint32 isapi_get_time(sint32 handler, ISAPI_NULL_S *request, SYSTEM_TIME_CFG_S *response)
{
	sint32 tx_len = 1024, rx_len = 10240, ret = 0;
	uint32 tx_buffer[1240] = {0};
	void *rx_buffer = NULL;

	if(response == NULL) //检测输入参数
	{
		return NULL_VALUE;
	}

	rx_buffer = malloc(rx_len); //分配缓存空间
	if(rx_buffer == NULL)
	{
		trace(ERROR, "[%s]:malloc=%s LINE:%d\n", __func__, strerror(errno), __LINE__);
		return MEMORY_FAILURE;
	}

	memset(tx_buffer, 0, tx_len);
	ret = http_package(HTTP_GET, "/ISAPI/System/time", tx_buffer, rx_buffer, rx_len); //完整的http数据帧
	if(ret < 0)
	{
		trace(ERROR, "[%s]:deal with http failure! %d\n", __func__, __LINE__);
		free(rx_buffer);
		return ret;
	}

	ret = ParseXmlSystemTime((char*)rx_buffer, response); //响应正文，xml数据帧
	if(ret < 0)
	{
		free(rx_buffer);
		return ret;
	}
	free(rx_buffer);

	return 0;
}

/******************************************************************************
 * Description：(URL: GET /ISAPI/ContentMgmt/InputProxy/pnp)
 * Input：
 * Output ：
 * Output ：
 * Return：0-成功 -1-失败
 * *****************************************************************************/
sint32 isapi_get_inputProxy_pnp(sint32 handler, ISAPI_NULL_S *request, COMMON_RESPONSE_S *response)
{
	sint32 tx_len = 1024, rx_len = 10240, ret = 0;
	uint32 tx_buffer[1240] = {0};
	void *rx_buffer = NULL;

	if(response == NULL) //检测输入参数
	{
		return NULL_VALUE;
	}

	rx_buffer = malloc(rx_len); //分配缓存空间
	if(rx_buffer == NULL)
	{
		trace(ERROR, "[%s]:malloc=%s LINE:%d\n", __func__, strerror(errno), __LINE__);
		return MEMORY_FAILURE;
	}

	memset(tx_buffer, 0, tx_len);
	ret = http_package(HTTP_GET, "/ISAPI/ContentMgmt/InputProxy/pnp", tx_buffer, rx_buffer, rx_len); //完整的http数据帧
	if(ret < 0)
	{
		trace(ERROR, "[%s]:deal with http failure! %d\n", __func__, __LINE__);
		free(rx_buffer);
		return ret;
	}

	ret = ParseXmlCommonResponse((char*)rx_buffer, response); //响应正文，xml数据帧
	if(ret < 0)
	{
		free(rx_buffer);
		return ret;
	}
	free(rx_buffer);

	return 0;
}

/******************************************************************************
 * Description：(URL: PUT /ISAPI/ContentMgmt/InputProxy/pnp)
 * Input：
 * Output ：
 * Output ：
 * Return：0-成功 -1-失败
 * *****************************************************************************/
sint32 isapi_put_inputProxy_pnp(sint32 handler, ISAPI_NULL_S *request, COMMON_RESPONSE_S *response)
{
	sint32 tx_len = 1024, rx_len = 10240, ret = 0;
	uint32 tx_buffer[1240] = {0};
	void *rx_buffer = NULL;

	if(response == NULL) //检测输入参数
	{
		return NULL_VALUE;
	}

	rx_buffer = malloc(rx_len); //分配缓存空间
	if(rx_buffer == NULL)
	{
		trace(ERROR, "[%s]:malloc=%s LINE:%d\n", __func__, strerror(errno), __LINE__);
		return MEMORY_FAILURE;
	}

	memset(tx_buffer, 0, tx_len);
	//GenXml_
	ret = http_package(HTTP_PUT, "/ISAPI/ContentMgmt/InputProxy/pnp", tx_buffer, rx_buffer, rx_len); //完整的http数据帧
	if(ret < 0)
	{
		trace(ERROR, "[%s]:deal with http failure! %d\n", __func__, __LINE__);
		free(rx_buffer);
		return ret;
	}

	ret = ParseXmlCommonResponse((char*)rx_buffer, response); //响应正文，xml数据帧
	if(ret < 0)
	{
		free(rx_buffer);
		return ret;
	}
	free(rx_buffer);

	return 0;
}

/******************************************************************************
 * Description：(URL: GET /ISAPI/ContentMgmt/InputProxy/channels/status)
 * Input：
 * Output ：
 * Output ：
 * Return：0-成功 -1-失败
 * *****************************************************************************/
sint32 isapi_get_inputProxy_channels_status(sint32 handler, ISAPI_NULL_S *request, INPUTPROXY_S *response)
{
	sint32 tx_len = 1024, rx_len = 40960, ret = 0;
	uint32 tx_buffer[1240] = {0};
	void *rx_buffer = NULL;

	if(response == NULL) //检测输入参数
	{
		return NULL_VALUE;
	}

	rx_buffer = malloc(rx_len); //分配缓存空间
	if(rx_buffer == NULL)
	{
		trace(ERROR, "[%s]:malloc=%s LINE:%d\n", __func__, strerror(errno), __LINE__);
		return MEMORY_FAILURE;
	}

	memset(tx_buffer, 0, tx_len);
	ret = http_package(HTTP_GET, "/ISAPI/ContentMgmt/InputProxy/channels/status", tx_buffer, rx_buffer, rx_len); //完整的http数据帧
	if(ret < 0)
	{
		trace(ERROR, "[%s]:deal with http failure! %d\n", __func__, __LINE__);
		free(rx_buffer);
		return ret;
	}

	ret = ParseXmlInputProxyChannelStatusList((char*)rx_buffer, response); //响应正文，xml数据帧
	if(ret < 0)
	{
		free(rx_buffer);
		return ret;
	}
	free(rx_buffer);

	return 0;
}


