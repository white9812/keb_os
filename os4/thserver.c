#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <pthread.h>

const int MAX_LINE =2048;
const int PORT =6001;
const int BACKLOG= 10;
const int LISTENQ=6666;
const int  MAX_CONNECT=20;

//클라이언트의 메시지를 수신하여 화면에 출력하는 역할을 하는 함수로 스레드내에서 실행됩니다.
void *recv_message(void *fd)fd;
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

		//클라이언트가 갑자기 접속을 끊은 경우 처리
		if(n==0)
		{
			printf("Client closed.\n");
			close(sockfd);
			exit(1);
		}
		
		//quit문자열을 받으면 종료
		if(strcmp(buf,"exit")==0)
		{
			printf("Client closed.\n");
			close(sockfd);
			exit(1);
		}
		//클라이언트ㅏㄱ 보낸 메시지를 화면에 출력합니다.
		printf("\nClient:%s\n",buf);
	}

}

int main()
{
	//(1)
	int listedfd,connfd;

	//(2)
	pthread_t recv_tid;

	//(3)
	struct sockaddr_in servaddr,cliaddr;

	//(4)소켓 생성
	if((listenfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("socket error.\n");
		exit(1);
	}
		
	//(5) sockaddr_in 구조체 설정
	bzero(&servaddr,sizeof(servaddr));
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(PORT);
	
	//bind 오류 해결.사용했던 ip라고 뜨는 에러
	int val=1;
	if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,(char *)&val,sizeof val)<0){
		perror("setsockopt");
		close(listenfd);
		return -1;
	}
	//(6)소켓 생성
	if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
	{
		perror("binf error.\n");
		exit(1);
	}
	
	//(7)
	if(listen(listenfd,LISTENQ)<0)
	{
		perror("listen error.\n");
		exit(1);
	}

	//(8)클라이언트 연결 요청 수락
	socklen_t clilen =sizeof(cliaddr);
	if((connfd=accept(listenfd,(struct sockaddr*)&cliaddr,%clilen))<0)
	{
		perror("accept error.\n");
		exit(1);
	}
	//(9)서버에 접속한 클라이언트의 주소 출력
	printf("server:got connection from %s\n",inet_ntoa(cliaddr.sin_addr));
	
	//(10)메시지 수신하는 스레드 생성
	if(pthread_create(&recv_tid,NULL,recv_message,&connfd)==-1)
	{
		perror("pthread create error.\n");
		exit(1);
	}
	
	//(11)서버가 입력한 메시지 전송
	char msg[MAX_LINE];
	memset(msg,0,MAX_LINE);
	while(fgets(msg,MAX_LINE,stdin)!=NULL)
	{
		if(strcmp(msg,"exit\n")==0)
		{
			close(connfd);
			exit(0);
		}
		
		if(send(connfd,msg,strlen(msg),0)==-1)
		{
			perror("send error.\n");
			exit(1);
		}
	}	

}
