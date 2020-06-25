#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

pthread_mutex_t mutex;  ///< 互斥锁  
pthread_cond_t  cond;   ///< 条件变量  
//bool test_cond = false; 
//int test_cond[6] = {0, 0, 0, 0, 0, 0}; 
int test_cond = 1; 

void* producerFun1(void *arg)
{
	pthread_mutex_t mutex1;  ///< 互斥锁  
	pthread_mutex_init(&mutex1,NULL); 
	printf("func:%s arg:%d\n", __func__ , (*(int*)arg));
	while(1)
	{
		pthread_mutex_lock(&mutex1);
		//pthread_mutex_lock(&mutex);
		if(test_cond == 1)
		{
			test_cond++;
			//printf("func:%s test_cond++\n", __func__);
			printf("func:%s test_cond++:%d\n", __func__, test_cond);
		}
		pthread_cond_signal(&cond); //通知消费者
		pthread_mutex_unlock(&mutex1);
		//pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

void* producerFun2(void *arg)
{
	printf("func:%s arg:%d\n", __func__ , (*(int*)arg));
	while(1)
	{
		pthread_mutex_lock(&mutex);
		if(test_cond == 2)
		{
			test_cond++;
			//printf("func:%s test_cond++\n", __func__);
			printf("func:%s test_cond++:%d\n", __func__, test_cond);
		}
		pthread_cond_signal(&cond); //通知消费者
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

void* producerFun3(void *arg)
{
	printf("func:%s arg:%d\n", __func__ , (*(int*)arg));
	while(1)
	{
		pthread_mutex_lock(&mutex);
		if(test_cond == 3)
		{
			test_cond++;
			//printf("func:%s test_cond++\n", __func__);
			printf("func:%s test_cond++:%d\n", __func__, test_cond);
		}
		pthread_cond_signal(&cond); //通知消费者
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

void* producerFun4(void *arg)
{
	printf("func:%s arg:%d\n", __func__ , (*(int*)arg));
	while(1)
	{
		pthread_mutex_lock(&mutex);
		if(test_cond >= 3)
		{
			test_cond++;
			pthread_cond_signal(&cond); //通知消费者
			printf("func:%s test_cond++:%d\n", __func__, test_cond);
			if(test_cond>=6)
			{
				pthread_mutex_unlock(&mutex);
				return NULL;
			}
		}
		pthread_cond_signal(&cond); //通知消费者
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

void* producerFun(void *arg)
{
	printf("func:%s arg:%d\n", __func__ , (*(int*)arg));
	while(1)
	{
		pthread_mutex_lock(&mutex);
		if(test_cond >= 6)
		{
			//pthread_cond_signal(&cond); //通知消费者
			pthread_mutex_unlock(&mutex);
			return NULL;
		}
		if(test_cond >= 5)
			pthread_cond_signal(&cond); //通知消费者
		test_cond++;
		printf("func:%s test_cond:%d\n", __func__, test_cond);
		pthread_mutex_unlock(&mutex);
	}
	return arg;
}

void* consumerFun(void *arg)
{
	printf("func:%s arg:%d\n", __func__ , (*(int*)arg));
	while(1)
	{
		pthread_mutex_lock(&mutex);
		if(test_cond <=5)
		{
			pthread_cond_wait(&cond, &mutex); //通知消费者
			pthread_mutex_unlock(&mutex);
		}
		else
		{
			printf("func:%s pthread_cond_wait test_cond:%d\n", __func__, test_cond);
			pthread_mutex_unlock(&mutex);
			//exit(1);
			return NULL;
		}
	}
	return NULL;
}

int main(int argc, const char *argv[])
{
	int i = 0;
	int mData = 6;
	int nPthreads = 6;
	pthread_t producerID[10], consumerID;

	printf("hello, condition variable test\n"); 
	pthread_mutex_init(&mutex,NULL); 
	pthread_cond_init(&cond,NULL); 

	printf("func:%s line:%d create pthread consumer ***** ******\n", __func__, __LINE__);
	pthread_create(&consumerID,NULL,consumerFun, &mData); 
	//sleep(1);
#if 1
		pthread_create(&(producerID[0]),NULL,producerFun1, &mData); 	
		pthread_create(&(producerID[1]),NULL,producerFun2, &mData); 	
		pthread_create(&(producerID[2]),NULL,producerFun3, &mData); 	
		pthread_create(&(producerID[3]),NULL,producerFun4, &mData);
#if 1
	pthread_join(consumerID,NULL);
	printf("join consumerFun\n");

		for(i=0;i<nPthreads;i++)
		{
			if(producerID[i] != 0)
				pthread_join(producerID[i],NULL);
			//printf("producerID[%d]=%ld\n", i, (long int)(producerID[i]));
			printf("join producerID[%d]=%ld\n", i, (producerID[i]));
		}
#endif
		printf("YYYYYYYYYYYYYYY\n");
#endif
#if 0
		printf("func:%s line:%d create pthread producer ******\n", __func__, __LINE__);
		for(i = 0; i < nPthreads; i++)
	{
		pthread_create(&(producerID[i]),NULL,producerFun, &mData); 	
	}
	/* 等待所有的生产者线程结束*/
	for(i=0;i<nPthreads;i++)
	{
		pthread_join(producerID[i],NULL);
		//printf("producerID[%d]=%ld\n", i, (long int)(producerID[i]));
		printf("join producerID[%d]=%ld\n", i, (producerID[i]));
	}
#endif
	/*等待消费者线程结束*/
	pthread_join(consumerID,NULL);
	printf("join consumerFun\n");
	exit(0);

	return 0;
}
