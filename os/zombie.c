#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	pid_t childPid;
	childPid=fork();
	if(childPid>0){//부모
		printf("부모 pid : %d\n",
getpid());
		sleep(30);
		printf("부모 종료\n");
		exit(0);
	}
	else if (childPid==0){//자식
		printf("자식\n");
		sleep(1);
		printf("자식 종료\n");
		exit(0);
	}
	else{
		perror("fork Fail!\n");
		return -1;
	}
	return 0;
}
