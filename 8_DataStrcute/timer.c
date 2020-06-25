#include <stdio.h>
#include <string.h>
#include <poll.h>
#include <assert.h>
#include <unistd.h>
#include <sys/timerfd.h>

long long tick = 0;
unsigned long  __timer_counter = 0;

/**
 * @brief timerfd方式基础定时器
 *
 * @return 成功返回0，失败返回-1 
*/
static int init_timerfd_timer(void)
{
	int tfd;
	struct itimerspec tv;

	printf("[%s]:****** line:%d ******\n", __func__, __LINE__);
	/*
	 * int timerfd_create(int clockid, int flags)
	 * @brief:生成一个定时器对象，返回对应的文件描述符
	 * @param1:当参数是CLOCK_REALTIME: 相对时间1970.1.1到目前的时间
	 * 当参数是CLOCK_MONOTONIC:使用绝对时间,系统重启到目前的时间
	 * @param2:控制的标志。TFD_NONBLOCK(非阻塞) TFD_CLOEXEC(阻塞)
	 * */
	tfd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK);
	if(tfd < 0)
	{
		perror("timerfd_create");
		//debug(RELEASE, "create timerfd error!\n");
		return -1;
	}

	memset(&tv, 0, sizeof(struct itimerspec));
	//tv.it_value.tv_sec = 1;             //秒
	tv.it_value.tv_sec = 0;             //纳秒
	tv.it_value.tv_nsec = 1000000;     //0.01秒
	//tv.it_value.tv_nsec = 10000000;     //0.01秒

	tv.it_interval = tv.it_value;       //间隔时间

	timerfd_settime(tfd, 0, &tv, NULL);  //设置时间,相当于启动定时器

	return tfd;
}

int userTimer()
{
	int ret = 0;
	struct pollfd fds[1];
	int tfd;

	tfd = init_timerfd_timer();
	if(tfd < 0)
		//assert(0);

	memset(fds, 0, sizeof(struct pollfd));
	fds[0].fd = tfd;
	fds[0].events = POLLIN;

	while(1)
	{
		ret = poll(fds, 1, 10);
		if(ret <= 0)
			continue;

		//read(fds[0].fd, &tick, sizeof(long long));
		int timeMerlin =  read(fds[0].fd, &tick, sizeof(long long));
		__timer_counter += tick;
		//printf("func:%s line:%d timeMerlin:%d \n", __func__, __LINE__, timeMerlin);
		printf("[merlin]:******timeMerlin:%d __timer_counter:%ld tick:%lld ******\n", timeMerlin,  __timer_counter, tick);
		sleep(1);
		//usleep(1000000);
	}

	return 0;
}

int main(int argc, const char *argv[])
{
#if 1
	userTimer();
	return 0;
#endif

#if 0
	DWORD old_timer_counter = 0;
	object_timer_t pt;
	sem_t *wait = (sem_t *)parameter;

#ifdef USING_TIMERFD
	int ret;
	long long tick;
	struct pollfd fds[1];
	int tfd;

	tfd = init_timerfd_timer();
	if(tfd < 0)
		assert(0);

	memset(fds, 0, sizeof(struct pollfd));
	fds[0].fd = tfd;
	fds[0].events = POLLIN;
#else
	init_sigalrm_timer();
#endif

	sem_post(wait);

	for(;;)
	{
#ifdef USING_TIMERFD
		ret = poll(fds, 1, 10);
		if(ret <= 0)
			continue;

		//read(fds[0].fd, &tick, sizeof(long long));
		int timeMerlin =  read(fds[0].fd, &tick, sizeof(long long));
		__timer_counter += tick;;
		printf("[merlin:%s]:******timeMerlin:%d __timer_counter:%ld tick:%lld ******\n", timeMerlin,  __timer_counter, tick);
#else
		sem_wait(&block);
#endif

		/*想目标对象发送定时器信号*/
		pthread_mutex_lock(&object_container[object_class_type_timer].lock);
		for(pt = (object_timer_t)object_iter(object_class_type_timer, NULL); 
				pt != NULL; 
				pt = (object_timer_t)object_iter(object_class_type_timer, (object_t)pt))
		{
			if(pt->run == TIMER_STOP)
				continue;

			pt->timeout_tick += (__timer_counter - old_timer_counter);
			if(pt->timeout_tick < 0)
				pt->timeout_tick = 0;

			if(pt->timeout_tick < pt->init_tick)
				continue;

			if(pt->type == TYPE_ASYNC)
				post_message(pt->hmod, MSG_TIMER, pt->id, 0); //直接将消息发送给目标线程
			else
				pt->timer_func(pt->parameter);   //直接调用目标线程的处理函数

			pt->timeout_tick = 0;
		}
		pthread_mutex_unlock(&object_container[object_class_type_timer].lock);

		//printf("[%s]:****** old_timer_counter:%ld __timer_counter:%ld line:%d ******\n", __func__, old_timer_counter, __timer_counter, __LINE__);
		old_timer_counter = __timer_counter;
	}

	return NULL;

	return 0;
#endif
}
