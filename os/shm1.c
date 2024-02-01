#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
	int shmid;
	key_t key;
	char *shmaddr;
	
	key=ftok("helloshm",1);
	shmid=shmget(key,1023,IPC_CREAT|0644);//shared memory 생성
	//key를 사용하여 size 크키의 공유 메모리를 생성하고
	//생성된 공유메모리의  ID를 반환함
	if (shmid==-1){
		perror("shmget");
		exit(1);
	}

	printf("shmid: %d",shmid);
	shmaddr=(char *) shmat(shmid,NULL,0);//shared memory 연결
	//shmid(shared memory를 메모리 위치 shmaddr에 연결하고 주소를 반환
	strcpy(shmaddr,"hello shared memory");
	return 0;
}
