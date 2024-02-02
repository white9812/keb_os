#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

void *threadRoutine(void *arg){
	pthread_t tid =pthread_self();
	//TID를 반환하고 출력 
	printf("thread ID :: %lu\n",tid);
	while(1){
		printf("a\n");
	}
	return NULL;
}
int main(){
	pthread_t threadID;
	char tmp[10];
	scanf("%s",tmp);//잠깐 프로세스 실행을 중간에 중시 시키고  pstree보려고
	pthread_create(&threadID,NULL,threadRoutine,NULL);
	//아까 생성한 스레드를 defach
	scanf("%s",tmp);//마찬가지로 잠깐 중지시키고 pstree보려고
	pthread_detach(threadID);
	while(1){
		printf("b\n");
	}
}
