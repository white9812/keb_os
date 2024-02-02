#include<stdio.h>
void *threadRoutine(void *arg){
	int count=0;
	pthread_t tid=pthread_self();
	//TID를 반환하고 출력
	printf("thread ID ::%lu\n",tid);
	while(count<100){
		printf("a\n");
		count++;
	}
	pthread_exit(arg);//추가 변경
}
int main(){
	pthread_t threadID;
	int status;//추가
	void *result;//추가
	char tmp[10];
	scanf("%s",tmp)//잠깐 프로세를 실행을 중간에 중지시키고 pstree보려고

