#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

#define MSGSIZE 63
char *fifo="testfifo";
void main(int argc,char **argv){
int fd,j,nwrite;
char msgbuf[MSGSIZE+1];
if(argc<2){
	fprintf(stderr,"usage:sendmessage msg ... \n"); exit(1);
}
if((fd=open(fifo,O_WRONLY|O_NONBLOCK))<0)
	fprintf(stderr,"fifo open failed");
for(j=1;j<argc;j++){
	strcpy(msgbuf,argv[j]);
	if((nwrite=write(fd,msgbuf,MSGSIZE+1))==-1)
		fprintf(stderr,"message write failed");
	}
	exit(0);
}
