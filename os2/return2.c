#include<pthread.h>
#include<stdio.h>

void *threadRoutine(void*arg){
	long argument;
	argument=*((long *)arg);
	return (void *)(argument*10);//부모스레드에서 리턴값을 받기때문에
}
int main(){
	pthread_t threadID;
	printf("Create thread!\n");
	long argument=10;
	int status;
	void *value;
	status=pthread_create(&threadID,NULL,threadRoutine,(void*)&argument);
	printf("Main Thread is now waiting for Thread!\n");
	pthread_join(threadID,&value);
	printf("Return value (0:success)::%d\n",status);
	printf("receive value :: %ld\n",(long)value);

	return 0;
}

