
#include<signal.h>//소프트웨어 인터럽트의 일종인 시그널
#include<unistd.h>
#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
int count;
//void alrm_action(int);
void main(){
	int p[2];
	int pipe_size;
	char c='x';
// 	static struct sigaction act;
//	act.sa_handler=alrm_action; //시그널 처리를 위해 미리 함수를 지정해놓음
//	sigfillset(&(act.sa_mask));
	if(pipe(p)==-1){
		perror("pipe call");
		exit(1);
	}
	pipe_size=fpathconf(p[0],_PC_PIPE_BUF);
	printf("Maximum size of write to pipe : %d bytes \n",pipe_size);
//	sigaction(SIGALRM,&act,NULL);//alarm 시그널이 수행된 경우 동작할 행동을 등록함
	while(1){
//		alarm(20);//20초 뒤 수행
		write(p[1],&c,1);
//		alarm(0);//0초 뒤 수행
		if((++count %1024)==0)
			printf("%d characters in pipe \n",count);
		if(pipe_size==count)
			break;
	}

}

//void alrm_action(int signo){
//	printf("write blocked after %d aharacters \n",count);
//	exit(0);
//}

