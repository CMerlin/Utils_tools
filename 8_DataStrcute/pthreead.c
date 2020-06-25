#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#define     MAXNITEMS        1000000
#define     MAXNTHREADS     100

int nitems;

struct
{
    pthread_mutex_t     mutex;
    int                 buff[MAXNITEMS];
    int                 nput;
    int                 nval;
} shared = {
    PTHREAD_MUTEX_INITIALIZER
};
//条件变量
struct {
    pthread_mutex_t mutex;  
    pthread_cond_t  cond;
    int nready;
}nready = {
  PTHREAD_MUTEX_INITIALIZER,PTHREAD_COND_INITIALIZER
};

void *produce(void*);
void *consume(void*);

int main(int argc,char *argv[])
{
    int     i,nthreads,count[MAXNTHREADS];
    pthread_t tid_produce[MAXNTHREADS],tid_consume; //线程标识
    if(argc != 3)
    {
        printf("usage: producongs2 <#itmes> <#threads>.\n");
        exit(0);
    }
    nitems = atoi(argv[1]);
    nthreads = atoi(argv[2]);
	printf("****************************\n");
	printf("shared npt:%d nval:%d \n", shared.nput, shared.nval);
	printf("nready nready:%d\n", nready.nready);
	printf("****************************\n");
	//printf("func:%s line:%d **********\n", __func__, __LINE__);
	printf("func:%s line:%d nitems:%d nthreads:%d **********\n", __func__, __LINE__, nitems, nthreads);
    pthread_setconcurrency(nthreads+1); //告诉系统可创建的线程的个数，此作用是为了移植性的考虑
    /*创建生产者线程*/
	printf("func:%s line:%d creat produce nthreads:%d  **********\n", __func__, __LINE__, nthreads);
	for(i=0;i<nthreads;++i)
    {
        count[i] = 0;
        pthread_create(&tid_produce[i],NULL,produce,&count[i]);
    }
	/*创建消费者线程*/
	printf("func:%s line:%d create consume **********\n", __func__, __LINE__);
    pthread_create(&tid_consume,NULL,consume,NULL);

	/* 等待所有的生产者线程结束*/
    for(i=0;i<nthreads;i++)
    {
        pthread_join(tid_produce[i],NULL);
        printf("count[%d] = %d\n",i,count[i]);
    }
	/*等待消费者线程结束*/
    pthread_join(tid_consume,NULL);
    exit(0);
}

void *produce(void *arg)
{
    //printf("func :%s line:%d arg:%d producer begins work\n", __func__, __LINE__ ,  (int)(*arg));
	int src = (*(int*)arg);
       // *((int*) arg) += 1;
    printf("func :%s line:%d arg:%d producer begins work\n", __func__, __LINE__ ,  src);
    for(; ;)
    {
        pthread_mutex_lock(&shared.mutex);
        if(shared.nput >= nitems)
        {
			printf("func:%s line:%d nput >= nitems\n", __func__, __LINE__);
            pthread_mutex_unlock(&shared.mutex);
            return ;
        }
        shared.buff[shared.nput] = shared.nval;
        shared.nput++;
        shared.nval++;
        pthread_mutex_unlock(&shared.mutex);
        pthread_mutex_lock(&nready.mutex);
        if(nready.nready == 0)
            pthread_cond_signal(&nready.cond); //通知消费者
        nready.nready++;
        pthread_mutex_unlock(&nready.mutex);
        *((int*) arg) += 1;
    }
}
void *consume(void *arg)
{
    int     i;
	int src = (int)(arg);
    //printf("func:%s line:%d arg:%d consuemer begins work.\n", __func__, __LINE__, (int)(*arg));
    printf("func:%s line:%d arg:%d consuemer begins work.\n", __func__, __LINE__, src);
    for(i=0;i<nitems;i++)
    {
        pthread_mutex_lock(&nready.mutex);
        while(nready.nready == 0)
            pthread_cond_wait(&nready.cond,&nready.mutex); //等待生产者
        nready.nready--;
		printf("func:%s line:%d nready:%d\n", __func__, __LINE__, nready.nready);
        pthread_mutex_unlock(&nready.mutex);
        if(shared.buff[i] != i)
            printf("buff[%d] = %d\n",i,shared.buff[i]);
    }
    return;
}
