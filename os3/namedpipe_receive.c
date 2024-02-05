#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

#define MSGSIZE 63
char *fifo ="testfifo";

void main(int argc,char **argv){
	int fd,j,nwrite;
	char msgbuf[MSGSIZE+1];
	
	if(mkfifo(fifo,0666)==-1){
		fprintf(stderr,"namedpipe 이미 있어서 생성 안해도 됨\n");
	}
	if((fd=open(fifo,O_RDWR))<0)
		fprintf(stderr,"fifo open failed");
	for(;;){
		if(read(fd,msgbuf,MSGSIZE+1)<0)
			fprintf(stderr,"message read failed");
		printf("message received : %s\n",msgbuf);
	}
}
