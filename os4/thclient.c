#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>

const int MAX_LINE=2048;
const int PORT=6001;
//서버의 메시지를 수신하여 화면에 출력하는 역할을 하는 함수로 스레드내에서 실행됩니다.
void *recv_message(void *fd)
{
	int sockfd=*(int *)fd;
	char buf[MAX_LINE];
	while(1)
	{
		memset(buf,0,MAX_LINE);
		int n;
		if((n=recv(sockfd,buf,MAX_LINE,0))==-1)
		{
			perror("recv error.\n");
			exit(1);
		}
	buf[n]='\0';
	//서버가 갑자기 접속을 끊은 경우 처리
	if(n==0)
	{
		printf("SErver is closed.\n");
		close(sockfd);
		exit(0);
	}
	//exit문자열을 받으면 종료
	if(strcmp(buf,"exit")==0)
	{
		printf("server is closed.\n");
		close(sockfd);
		exit(0);
	}
	
	printf("\nServer:%s\n",buf);
	}
}
	

int maint(int argc,char **argv)
{
	//(1)
	int sockfd;
	//(2)
	pthread_t recv_tid;

	//(3)
	struct sockaddr_in servaddr;
	
	//(4)
	if(argc!=2)
	{
		perror("usage:tcpcli <IPaddress>");
		exit(1);
	}
	
	//(5)
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-10)
	{
		perror("socket error");
		exit(1);
	}

	//(6)
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(PORT);
	
	//(7)
	if(inet_pton(AF_INET,argv[1],&servaddr.sin_addr)<0)
	{
		printf("inet_pton error for %s\n",argv[1]);
		exit(1);
	}
	//(8)
	if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
	{
		perror("connect error");
		exit(1);
	}
		
	//(9) 메시지 수신하는 스레드 생성
	if(pthread_create(&recv_tid,NULL,recv_message,&sockfd)==-1)
	{
		perror("pthread create error.\n");
		exit(1);
	}

	//(10) 클라이언트가 입력한 메시지 전송
	char msg[MAX_LINE];
	memset(msg,0,MAX_LINE);
	while(fgets(msg,MAX_LINE,stdin)!=NULL)
	{
		if(strcmp(msg,"exit\n")==0)
		{
			close(sockfd);
			exit(0);
		}
		if(send(sockfd,msg,strlen(msg),0)==-1)
		{
			perror("send error.\n");
			exit(1);
		}
	}
	
}

