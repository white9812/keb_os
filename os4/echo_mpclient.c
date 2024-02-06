// mpclient.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char* message);
void read_routine(int sock, char *buf);
void write_routine(int sock, char *buf);

int main(int argc, char* argv[])
{
   int sock;
   pid_t pid;
   char buf[BUF_SIZE];
   struct sockaddr_in serv_adr;
   if(argc != 3)
   {
      printf("Usage : %s <IP> <port> \n", argv[0]);
      exit(1);
   }

   sock = socket(PF_INET, SOCK_STREAM, 0);
   memset(&serv_adr, 0, sizeof(serv_adr));
   serv_adr.sin_family = AF_INET;
   serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
   serv_adr.sin_port = htons(atoi(argv[2]));

   if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
      error_handling("connect() error!");

   pid = fork();
   if(pid == 0)                 
      write_routine(sock, buf); // write_routine 함수에는 데이터 출력에 관련된 코드만 존재함
   else
      read_routine(sock, buf);  // read_routine 함수에는 데이터 입력에 관련된 코드만 존재
// 이렇게 입출력 루틴을 구분해서 각각의 함수로 정의하면 구현의 편의를 가져다줌

   close(sock);
   return 0;
}

void read_routine(int sock, char *buf)
{
   while(1)
   {
      int str_len = read(sock, buf, BUF_SIZE);
      if(str_len == 0)
         return;

      buf[str_len] = 0;
      printf("Message from server : %s", buf);
   }
}

void write_routine(int sock, char *buf)
{
   while(1)
   {
      fgets(buf, BUF_SIZE, stdin);
      if(!strcmp(buf, "q\n") || !strcmp(buf, "Q\n"))
      {
         shutdown(sock, SHUT_WR);  // 서버에게 EOF 전달을위해 셧다운 함수 호출
         return;      // return 실행 후에 main 함수 끝에 close 함수 호출로 EOF 전달을 기대할 수 있지만,
                      // 현재 커넥스 밑의 fork 함수 호출을 통해 파일 디스크립터가 복사된 상황이다.
                      // 그리고 이런 상황에서는 한번의 close 함수호출로 EOF 전달을 기대할 수 없다.
                      // 따라서 반드시 shutdown 함수호출을 통해 EOF 전달을 별도로 명시해야함.
      }
      write(sock, buf, strlen(buf));
   }
}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}


