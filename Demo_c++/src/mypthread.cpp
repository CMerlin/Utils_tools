/******************************************************************************
* Pthread module
******************************************************************************/
#include "mypthread.h"
#include <pthread.h>

#if 1 /********************************************************/
int restartDiscovery(char *dev_name);
void handle_quit(int signo);
void handle_quit_main(int signo);

char  air_dev_name1[32] = {"hello"};
pthread_t thread_id1 = 0;
pthread_t thread_id2 = 0;
pthread_attr_t attr1;
pthread_attr_t attr2;
static long long last_restart_time = 0;

/*****************************************************************************************
* Brief:
******************************************************************************************/
void *pthread_func_control(void *arg){

	#if 1 /************************************************************************/
	printf("[RES][%s][%d]:pth1=%ld pth2=%ld\n", __func__, __LINE__, thread_id1, thread_id1);
	while(1){
		printf("[RES][%s][%d]:\n", __func__, __LINE__);
		long long now = time(NULL);
		if((last_restart_time<=0) || (5 <= (now-last_restart_time))){
			printf("[RES][%s][%d]:whill be start thread=%lld\n", __func__, __LINE__, (llong_64)thread_id2);
			#if 1
			usleep(1000 * 1000);
			if(thread_id2 <= 0){
				continue;
			}
			printf("[RES][%s][%d]:whill be start thread=%lld\n", __func__, __LINE__, (llong_64)thread_id2);
			//pthread_kill(thread_id2, SIGTERM);
			pthread_kill(thread_id2, SIGQUIT);
			#endif
			//restartDiscovery(air_dev_name1);
			last_restart_time = now;
			//pthread_detach(&thread_id1);
		}
		usleep(1000 * 1000);
	}
	pthread_exit(NULL);
	return NULL;
	#endif /************************************************************************/
}

/*****************************************************************************************
* Brief:
******************************************************************************************/
void *pthread_func_contro2(void *arg){
	#if 1 /**************************************************************************/
		//signal(SIGTERM, handle_quit);
	signal(SIGQUIT, handle_quit);
	pthread_t pthread = pthread_self();
	while(1){
		printf("[RES][%s][%d]:pth=%lld-%lld\n", __func__, __LINE__, (llong_64)pthread, (llong_64)thread_id2);
		usleep(1000 * 1000);
	}
	pthread_exit(NULL);
	return NULL;
	#endif /**************************************************************************/
}


/*****************************************************************************************
* Brief:
******************************************************************************************/
int pthread_control(){
#if 1
	//pthread_t thread_id = -1;
	//pthread_attr_t attr;

	//setDevName(air_dev_name);
	printf("[AIR][De][%s][%d]:th1=%lld th2=%lld\n", __func__, __LINE__, (llong_64)thread_id1, (llong_64)thread_id2);
	pthread_attr_init(&attr1);
	pthread_attr_setdetachstate(&attr1, PTHREAD_CREATE_DETACHED);
	pthread_create(&thread_id1, &attr1, pthread_func_control, (void *)NULL);
	//pthread_detach(thread_id1);
	return 0;
#endif
}

void handle_quit_main(int signo) {
    printf("[RES][%s][%d]:pthread exit\n", __func__, __LINE__);
    //pthread_exit(0);
	return;
}

void handle_quit(int signo) {
    printf("[RES][%s][%d]:pthread exit\n", __func__, __LINE__);
    pthread_exit(0);
	thread_id2 = 0;
	return;
}

/*****************************************************************************************
* Brief:
******************************************************************************************/
int restartDiscovery(char *dev_name){
#if 1

	#if 0
	pthread_t th = 0;
	int ret = 1;
	printf("[AIR][De][%s][%d]:th1=%lld th2=%lld-%lld\n", __func__, __LINE__, thread_id1, thread_id2, th);
	if(th < thread_id2){
		printf("[RES][%s][%d]:Release the thread discovery thread_id2=%lld\n", __func__, __LINE__, thread_id2);
		ret = pthread_detach(thread_id2);
		ret = pthread_join(thread_id2, NULL);
		//ret = pthread_cancel(thread_id2);
		thread_id2 = -1;
		printf("[RES][%s][%d]:ret=%d info=%s\n", __func__, __LINE__, ret, strerror(errno));
	}
	#endif

	#if 0
		if(thread_id2 > 0){
			pthread_kill(thread_id2, SIGQUIT);
		}
		while(1){
			printf("[RES][%s][%d]:thread_id2=%uld\n", __func__, __LINE__, thread_id2);
			usleep(1000 * 1000);
			if(thread_id2 <=0){
				break;
			}
		}
	#endif

			//pthread_t thread_id = -1;
			//pthread_attr_t attr;
		
			//setDevName(air_dev_name1);
			printf("[AIR][De][%s][%d]:start\n", __func__, __LINE__);
			memset(&attr2, 0, sizeof(pthread_attr_t));
			pthread_attr_init(&attr2);
			pthread_attr_setdetachstate(&attr2, PTHREAD_CREATE_DETACHED);
			pthread_create(&thread_id2, &attr2, pthread_func_contro2, (void *)NULL);
			//ret = pthread_detach(thread_id2);
			return 0;
#endif
}


/*****************************************************************************************
* Brief:
******************************************************************************************/
int test_pthread1(){
#if 1
	pthread_control();
	restartDiscovery(air_dev_name1);
	return 0;
#endif
}
#endif /********************************************************/


