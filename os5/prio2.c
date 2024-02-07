#include <stdio.h>
#include <string.h>
#include <pthread.h>

static int count=0;
pthread_attr_t attr[2];

void *threadFunc1(void *arg)
{
	char *s=(char *)arg;
	struct sched_param sched;
	while(1)
	{
		pthread_attr_getschedparam(&attr[0],&sched);
		sched.sched_priority=1;
		pthread_attr_setschedparam(&attr[0],&sched);

		count++;
		printf("%s[%d]\n",s,count);
		pthread_attr_getschedparam(&attr[0],&sched);
		printf("threadFunc1 priority=%d\n",sched.sched_priority);
		//printf("pthrad_self value =%d\n",pthread_self());
		//usleep(100);
	}
	return (void *)strlen(s);
}

void *threadFunc2(void *arg)
{
	char*s=(char*)arg;
	struct sched_param sched;
	while(1)
	{
		count--;
		if(count<0)
			count=0;
		pthread_attr_getschedparam(&attr[1],&sched);
		sched.sched_priority=90;
		pthread_attr_setschedparam(&attr[1],&sched);
		
		printf("%s[%d]\n",s,count);
		pthread_attr_getschedparam(&attr[1],&sched);
		//sched.sched_priority=1;

		//printf("threadFunc2 priority=%d\n",pthread_self());
//usleep(100);
	}
	return (void *)strlen(s);
}

int main(int argc,char *argv[])
{
	printf("pthread test start!\n");
	struct sched_param sched;
	pthread_t tid[2];
	void *res;
	int retval;
	pthread_attr_init(&attr[0]);
	pthread_attr_init(&attr[1]);
	pthread_attr_setinheritsched(&attr[0],PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setinheritsched(&attr[1],PTHREAD_EXPLICIT_SCHED);
	
	printf("Message from main()\n");
	pthread_attr_getschedparam(&attr[0],&sched);
	printf("threadFUnc1 priority =%d\n",sched.sched_priority);
	sched.sched_priority=1;
	pthread_attr_setschedparam(&attr[0],&sched);
	printf("threadFunc1 priority=%d\n",sched.sched_priority);
		
	pthread_attr_getschedparam(&attr[1],&sched);
	printf("threadFunc2 priority=%d\n",sched.sched_priority);
	sched.sched_priority=90;
	pthread_attr_setschedparam(&attr[1],&sched);
	printf("threadFunc2 priority=%d\n",sched.sched_priority);


	retval=pthread_create(&tid[0],&attr[0],threadFunc1,"threadFunc1");
	if(retval!=0)
	{
		printf("pthread_create error\n");
	}
	retval=pthread_create(&tid[1],&attr[1],threadFunc2,"threadFunc2");
	if(retval!=0)
	{
		printf("pthread_create error\n");
	}
	retval=pthread_join(tid[0],&res);

	if(retval!=0)
	{
		printf("pthread_join error\n");
	}
	retval=pthread_join(tid[1],&res);
	if(retval!=0)
	{
		printf("pthread_join error\n");
	}
	printf("tid[0]=%d Thread returned %ls\n",tid[0],(long)res);
	printf("tid[0]=%d Thread returned %ls\n",tid[1],(long)res);
	
	return 0;

}

