#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
	int shmid;
	char *shmptr1,*shmptr2;
	int i;
	shmid=shmget(IPC_PRIVATE,10*sizeof(char),IPC_CREAT|0666);//shared memory 생성
	if (shmid==-1){
		printf("shmget failed\n");
		exit(0);
	}
	//지금부터 프로세스 생성
	if(fork()==0){//자식 프로세스
		shmptr1=(char *) shmat(shmid,NULL,0);//shared memory 연결,참조
		for (i=0;i<10;i++)
			shmptr1[i] =i*10;
		shmdt(shmptr1);//자식 프로세스와 shared memory간의 연결,참조 해제
		exit(0);
	}
	else{//부모 프로세스
		wait(NULL);
		shmptr2=(char *) shmat(shmid,NULL,0);//shared memory 연결,참조
		for(i=0;i<10;i++)
			printf("%d\n",shmptr2[i]);
		shmdt(shmptr2);//부모 프로세스와 shared meomory간의 연결,참조 해제
		if(shmctl(shmid,IPC_RMID,NULL)==-1)//shared memory 제어,IPC_RMID 여기에선 공유 메모리를 os상에서 삭제		
			printf("shmct1 failed\n");
	}
	return 0;
}

