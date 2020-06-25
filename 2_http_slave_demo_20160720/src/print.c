/****************************************************************
 * FileName:print.c
 * Author:merlin
 * Version:v1
 * Time:20160613
 * Description:print log
 * *************************************************************/

#include "common.h"

static int current_plevel = 0; //0:release 1:error 2:trace :debug
static pthread_mutex_t Plock;

/******************************************************************************
 * Description：初始化打印级别，从环境变量中获取到当前的打印级别
 * Return：0
 * *****************************************************************************/
int init_print_level()
{
	char *p = NULL;
	p = getenv("PRINT_LEVEL");
	if(p == NULL)
		p = "release";
	else if(!strcmp(p, "error"))
		current_plevel = ERROR;
	else if(!strcmp(p, "trace"))
		current_plevel = TRACE;
	else if(!strcmp(p, "debug"))
		current_plevel = DEBUG;
	else
		current_plevel = RELEASE;
	printf("[%s]:current_plevel=%d LINE:%d\n", __func__, current_plevel, __LINE__);
	pthread_mutex_init(&Plock, NULL);

	return 0;
}

/******************************************************************************
 * Description：系统时间转换为格式化的字符串
 * Output systime 传出的格式化字符串
 * Return：0
 * *****************************************************************************/
int get_sys_time(char *systime)
{
	/*年月日 时分秒*/
	time_t now;
	now = time(NULL);
	struct tm *tm = localtime(&now);
	/*微秒*/
	struct timeval tv;
	struct timezone tz;
	gettimeofday(&tv, &tz);

	//sprintf(systime, "%d-%02d-%02d %02d:%02d:%02d", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
	sprintf(systime, "%d%02d%02d %02d:%02d:%02d.%ld", 
			tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, tv.tv_usec);
	
	return 0;
}

/******************************************************************************
 * Description：获取进程和线程ID
 * Output id：已将格式化好的ID 
 * Return：0-成功 -1-失败
 * *****************************************************************************/
int get_pid_ttid(char *id)
{
	pid_t pid = getpid();
	sprintf(id, "%d.%lu", pid, pthread_self());
	return 0;
}

/******************************************************************************
 * Description：打印用户的相关信息, 如果当前环境打印级别(current_plevel)小于用户函数输入的打印级别(plevel) ,
 * 				 用户的的相关信息被输出到终端。此函数是一个线程安全的函数
 * Input plevel:打印级别，暂时只支持两个打印级别 relesas 和debug 
 * Input format：格式化字符串
 * Return：0
 * *****************************************************************************/
int trace(const int plevel, const char *format, ...)
{
	va_list ap;
	char date[32] = {0}, id[64] = {0};

	//printf("[%s]:plevel=%d current_plevel=%d LINE:%d\n", __func__, plevel, current_plevel, __LINE__);
	pthread_mutex_lock(&Plock);
	get_sys_time(date); //获取系统时间
	get_pid_ttid(id); //获取进程和线程ID

	va_start(ap, format);

	if(plevel <= current_plevel)
	{
		fprintf(stdout, "[%s][%s]", date, id);
		if(plevel == RELEASE)
			fprintf(stdout, "[%s]:", "RELEASE");
		else if(plevel == ERROR)
			fprintf(stdout, "[%s]:", "ERROR");
		else if(plevel == TRACE)
			fprintf(stdout, "[%s]:", "TRACE");
		else if(plevel == DEBUG)
			fprintf(stdout, "[%s]:", "DEBUG");
		vprintf(format, ap);
	}

	//vsyslog(LOG_USER | LOG_INFO, format, ap);
	va_end(ap);

	pthread_mutex_unlock(&Plock);

	return 0;
}

