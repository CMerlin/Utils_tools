/**************************************************************************
* Brief：
******************************************************************************/

#if 1 /*[B][call c func]:***********************************************/
#ifdef __cplusplus
extern "C" {
#endif

#include "rtc_queue.h"

unsigned char TAG[32] = {"[ME][sip_stream_sink.c]"};
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
	if (QueueEmpty(q))
		return;
	QNode* pDelNode = q->_front;
	if (pDelNode->_pNext == NULL)
		q->_back = q->_front = NULL;
	else {
		q->_front = pDelNode->_pNext;
	}
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

int release_rtc_queue(){
	int countv = QueueSize(rtc_queue_v);
	int counta = QueueSize(rtc_queue_a);
	LOGINFO("[%s][%s][%d]:countv=%d counta=%d\n", TAG, __func__, __LINE__, countv, counta);

	while(1){
		//if((countv<=0) && (countv<=0)){
		if((0 == QueueEmpty(rtc_queue_v)) && (0 == QueueEmpty(rtc_queue_a))){
			break;
		}
		if(0 != QueueEmpty(rtc_queue_v)){
			QueuePop(rtc_queue_v);
		}

		if(0 != QueueEmpty(rtc_queue_a)){
			QueuePop(rtc_queue_a);
		}
	}
	LOGINFO("[%s][%s][%d]:exit countv=%d counta=%d\n", TAG, __func__, __LINE__, countv, counta);
	return 0;
}

int write_video_to_sip(S_VIDEO_PKG *frame){
	if((0 >= frame->data_len) || (NULL == frame->data)){
		LOGERR("[Er][%s][%s][%d]:data_len=%d\n", TAG, __func__, __LINE__, (frame->data_len));
		return -1;
	}
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

	return 0;
}

static void *thread_rtc_task(void *arg)
{
	LOGINFO("[KK][%s][%s][%d]:runing\n", TAG, __func__, __LINE__);
	while(1){
		LOGINFO("[ME][%s][%s][%d]:\n", TAG, __func__, __LINE__);
		//release_rtc_queue();
		usleep(10 * 1000 * 1000);
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
}

#ifdef __cplusplus
}
#endif
#endif /*[E][call c func]:***********************************************/

#endif /* RTC_QUEUE ****************************************************************/



