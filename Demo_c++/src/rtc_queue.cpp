/**************************************************************************
* Brief：
******************************************************************************/

#if 1 /*[B][call c func]:***********************************************/
#ifdef __cplusplus
extern "C" {
#endif

#include "rtc_queue.h"

unsigned char TAG[32] = {"[ME][rtc_queue.c]"};
//char DTA[32] = {"hhh"};

#if RTC_QUEUE /* RTC_QUEUE ****************************************************************/

void QueueInit(Queue* q) {
	assert(q);
	q->_back = q->_front = NULL;
}

QNode* BuyQueueNode(QDataType data) {
	QNode* pNewNode = (QNode*)malloc(sizeof(QNode));
	if (pNewNode == NULL) {
		assert(0);
		return NULL;
	}
	pNewNode->_data = data;
	pNewNode->_pNext = NULL;
	return pNewNode;
}

void QueuePush(Queue* q, QDataType data) {
	assert(q);
	QNode* pNewNode = BuyQueueNode(data);
	if (QueueEmpty(q))
		q->_back = q->_front = pNewNode;//队列为空时，入队列
	else {
		q->_back->_pNext = pNewNode;//队列中已有节点，入队列
		q->_back = pNewNode;
	}
}

void QueuePop(Queue* q) {
	assert(q);
	if (QueueEmpty(q)){
		return;
	}
	QNode* pDelNode = q->_front;
	if (pDelNode->_pNext == NULL)
		q->_back = q->_front = NULL;
	else {
		q->_front = pDelNode->_pNext;
	}
	#if 1 /* --------------------- */
	QDataType *data = &(pDelNode->_data);
	printf("[%s][%d]:data=%s\n", __func__, __LINE__, (data->data));
	free(data->data);
	data->data = NULL;
	#endif /* --------------------- */
	free(pDelNode);
}

QDataType QueueFront(Queue* q) {
	assert(q);
	return q->_front->_data;
}
QDataType QueueBack(Queue* q) {
	assert(q);
	return q->_back->_data;
}
int QueueSize(Queue* q) {
	assert(q);
	int count = 0;
	QNode* pCur = q->_front;
	while (pCur) {
		count++;
		pCur = pCur->_pNext;
	}
	return count;
}

int QueueEmpty(Queue* q) {
	assert(q);
	return q->_front == NULL;
}
void QueueDestory(Queue* q) {
	assert(q);
	QNode* pCur = q->_front;
	while (pCur) {
		q->_front = pCur->_pNext;
		free(pCur);
		pCur = q->_front;
	}
	q->_front = q->_back = NULL;
}

/*---------------------------------------------------------------------------*/
Queue *rtc_queue_v = NULL; 
Queue *rtc_queue_a = NULL;
pthread_mutex_t mtx_v;
pthread_mutex_t mtx_a;

int init_av_queue(){
	rtc_queue_v = (Queue*)malloc(sizeof(Queue));
	rtc_queue_a = (Queue*)malloc(sizeof(Queue));
	memset(rtc_queue_v, 0, sizeof(Queue));
	memset(rtc_queue_a, 0, sizeof(Queue));
	pthread_mutex_init (&mtx_v, NULL);
	pthread_mutex_init (&mtx_a, NULL);
	//pthread_mutex_lock(&mutex);
	//pthread_mutex_unlock(&mutex);
	//record_init();
	return 0;
}

int release_rtc_queue(){
	int countv = QueueSize(rtc_queue_v);
	int counta = QueueSize(rtc_queue_a);
	LOGINFO("[%s][%s][%d]:countv=%d counta=%d\n", TAG, __func__, __LINE__, countv, counta);
	LOGINFO("[%s][%s][%d]:\n", TAG, __func__, __LINE__);

	while(1){
		//if((countv<=0) && (countv<=0)){
		int countv = QueueSize(rtc_queue_v);
		int counta = QueueSize(rtc_queue_a);
		int ret = QueueEmpty(rtc_queue_v);
		
		LOGINFO("[%s][%s][%d]: countv=%d counta=%d ret=%d\n", TAG, __func__, __LINE__, countv, counta, ret);
		if((1 == QueueEmpty(rtc_queue_v)) && (1 == QueueEmpty(rtc_queue_a))){
			break;
		}
		LOGINFO("[%s][%s][%d]:\n", TAG, __func__, __LINE__);
		if(1 != QueueEmpty(rtc_queue_v)){
			QueuePop(rtc_queue_v);
		}
		LOGINFO("[%s][%s][%d]:\n", TAG, __func__, __LINE__);
		if(1 != QueueEmpty(rtc_queue_a)){
			QueuePop(rtc_queue_a);
		}
		LOGINFO("[%s][%s][%d]:\n", TAG, __func__, __LINE__);
		//usleep(1000 * 1000);
	}
	LOGINFO("[%s][%s][%d]:exit countv=%d counta=%d\n", TAG, __func__, __LINE__, countv, counta);
	return 0;
}

//int video_count = 0;
int write_video_to_sip(S_VIDEO_PKG *frame){
	if((0 >= frame->data_len) || (NULL == frame->data)){
		LOGERR("[Er][%s][%s][%d]:data_len=%d\n", TAG, __func__, __LINE__, (frame->data_len));
		return -1;
	}
#if 1
	pthread_mutex_lock(&mtx_v);
	QDataType data;
	memset(&data, 0, sizeof(QDataType));
	data.data = (unsigned char*)malloc((frame->data_len));
	//sprintf((data.data), "[%d]:hello world\n", video_count);
	memset(data.data, 0, sizeof(frame->data_len));
	data.type = EAV_VIDEO;
	data.pts = frame->pts;
	memcpy(data.data, (frame->data), (frame->data_len));
	QueuePush(rtc_queue_v, data);
	pthread_mutex_unlock(&mtx_v);
#endif

	#if 0
		pthread_mutex_lock(&mtx_v);
		QDataType data;
		memset(&data, 0, sizeof(QDataType));
		data.data = (unsigned char*)malloc((frame->data_len));
		memset(data.data, 0, sizeof(frame->data_len));
		data.type = EAV_VIDEO;
		data.pts = frame->pts;
		memcpy(data.data, (frame->data), (frame->data_len));
		QueuePush(rtc_queue_v, data);
		pthread_mutex_unlock(&mtx_v);
	#endif


	#if 0
	pthread_mutex_lock(&mtx_v);
	QDataType *data = (QDataType*)malloc(sizeof(QDataType));
	memset(data, 0, sizeof(QDataType));
	data->data = (unsigned char*)malloc((frame->data_len));
	memset(data->data, 0, sizeof(frame->data_len));
	data->type = EAV_VIDEO;
	data->pts = frame->pts;
	memcpy(data->data, (frame->data), (frame->data_len));
	QueuePush(rtc_queue_v, (*data));
	pthread_mutex_unlock(&mtx_v);
	#endif

	return 0;
}

int queue_push_video(S_VIDEO_PKG *frame){
#if 1
	pthread_mutex_lock(&mtx_v);
	QDataType data;
	memset(&data, 0, sizeof(QDataType));
	data.data = (unsigned char*)malloc((frame->data_len));
	memset(data.data, 0, sizeof(frame->data_len));
	data.type = EAV_VIDEO;
	data.pts = frame->pts;
	memcpy(data.data, (frame->data), (frame->data_len));
	QueuePush(rtc_queue_v, data);
	pthread_mutex_unlock(&mtx_v);
#endif


	return 0;
}

int queue_relsese_video(){
	if(1 != QueueEmpty(rtc_queue_v)){
		QueuePop(rtc_queue_v);
	}

	return 0;
}

static void *thread_rtc_task(void *arg)
{
	LOGINFO("[KK][%s][%s][%d]:runing\n", TAG, __func__, __LINE__);
	int count = 0, v_count = 0;
	init_av_queue();
	while(1){
		//usleep(1 * 1000 * 1000);
		//usleep(500 * 1000);
		count++;
		v_count++;
		LOGINFO("[ME][%s][%s][%d]:\n", TAG, __func__, __LINE__);

		#if 1 /* -------------------------------- */
		S_VIDEO_PKG pkg;
		unsigned char buffer[2048] = {0};
		sprintf((char*)buffer, "[%d]:hello world\n", v_count);
		pkg.data = buffer;
		pkg.data_len = 2048;
		pkg.pts = time(NULL);
		write_video_to_sip(&pkg);
		#endif
		
		#if 0 /* -------------------------------- */
		S_VIDEO_PKG pkg;
		unsigned char buffer[2048] = {0};
		pkg.data = buffer;
		pkg.data_len = 2048;
		pkg.pts = time(NULL);
		write_video_to_sip(&pkg);
		#endif
		/* -------------------------------- */
		if(10 <= count){
			count = 0;
			release_rtc_queue();
		}
	}
	LOGINFO("[%s][%s][%d]:exit\n", TAG, __func__, __LINE__);
	return NULL;
}

int init_rtc_task(){
	pthread_t thread_id = -1;
	pthread_attr_t attr;
	
	LOGINFO("[%s][%s][%d]:\n", TAG, __func__, __LINE__);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&thread_id, &attr, thread_rtc_task, (void *)NULL);
	return 0;
}

int test_func_queue(){
	init_rtc_task();
	while(1){
		usleep(10 * 1000 * 1000);
	}
	return 0;
}

#if 1 /*[B]: audio test ------------------------------------------------------------*/

#define OLD_FILE_PATH "./in.pcm" 
#define VOL_FILE_PATH "./out.pcm"

int volume_adjust(short  * in_buf, short  * out_buf, float in_vol)
{
    int i, tmp;


	float vol = in_vol;
	//vol = 20;
	#if 0
    // in_vol[0, 100]
    float vol = in_vol - 98;
 
    if(-98<vol && vol<0){
		vol = 1/(vol*(-1));
	}
    else if(0<=vol && vol<=1){
		 vol = 1;
	}
       
    /*
    else if(1<=vol && vol<=2)
        vol = vol;
    */
    else if(vol<=-98){
		 vol = 0;
	}
       
    else if(vol>=2){
		vol = 40;  //这个值可以根据你的实际情况去调整
	}
       
 	#endif
	//printf("[%s][%d]:vol=%f\n", __func__, __LINE__, vol);
	
    tmp = (*in_buf)*vol; // 上面所有关于vol的判断，其实都是为了此处*in_buf乘以一个倍数，你可以根据自己的需要去修改
 
    // 下面的code主要是为了溢出判断
    if(tmp > 32767){
		tmp = 32767;

	}
       
    else if(tmp < -32768){
        tmp = -32768;
	}

   (*out_buf)  = tmp;
 
    return 0;
}

void pcm_volume_control(int volume) { 
	short s16In = 0;
	short s16Out = 0; 
	int size = 0;
	FILE *fp = fopen(OLD_FILE_PATH, "rb+");
	FILE *fp_vol = fopen(VOL_FILE_PATH, "wb+");

	printf("[%s][%d]:OLD_FILE_PATH=%s\n", __func__, __LINE__, OLD_FILE_PATH);
	while(!feof(fp)) { size = fread(&s16In, 2, 1, fp);
		if(size>0) { 
			volume_adjust(&s16In, &s16Out, volume); 
			fwrite(&s16Out, 2, 1, fp_vol);
		} 
	} 
	fclose(fp);
	fclose(fp_vol);
} 

int test_change_audio_vol(void)
{ 
	//pcm_volume_control(100);
	pcm_volume_control(20);
	return 0;
}
#endif /*[E]: audio test ------------------------------------------------------------*/


#ifdef __cplusplus
}
#endif
#endif /*[E][call c func]:***********************************************/

#endif /* RTC_QUEUE ****************************************************************/



