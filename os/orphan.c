#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	pid_t childPid;
	int i;
	childPid=fork();
	if(childPid>0){//parent
		printf("부모 pid :%d\n",getpid());
		sleep(2);
		printf("부모 종료\n");
		exit(0);
	}
	else if(childPid==0){
		printf("자식\n");
		for(i=0;i<10;i++){
			printf("자식 pid :%d,부모 pid:%d\n",getpid(),getppid());
		 	sleep(1);
		}
		printf("자식 종료\n");
		exit(0);
	}
	else{// fork  실패
		return -1;
	}
	return 0;
}

