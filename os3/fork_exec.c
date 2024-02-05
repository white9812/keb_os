#include <stdio.h>
#include <stdlib.h>//for system(exit() etc...)
#include <unistd.h> //for execl(),fork()
#include <wait.h> //for wait()

int main()
{
 	int pid;
	int counter=1;
	pid = fork();
	if(pid<0)
	{	/*error occured*/
	 	fprintf(stderr,"Fork Failed");//파일을 지정하여  printf,현재는 포준에러출력(모니터)
		exit(-1);//에러로 인한 종료
	}
	else if(pid==0)
	{/*child process*/ //자식이면 0,부모는 자식의 pid값을 받는다.
		printf("child here!\n");
		printf("execl start!!\n");//자식 프로세스는 exec를 호출하여 새로운 프로세스를 생성하고 자식 프로세스는 종료된다.
		//다른 말로 자식프로세스는 exec를 호출하여 새로운 코드를 덮어쓰게 된다. (자식의 자식이 아닌 새로운 프로세스로 변경)
		execl("/bin/ls","ls","-l",NULL);
		printf("if you read this message,fail creating execl execl func..\n");
	}
	else
	{/*parent process*/
		printf("i'm parent!\n");
		wait(NULL);//부모프로세스는 자식(exec로 생성된)이 종료될때까지 대기
		printf("process Complete!\n");
	}

	return 0;
}
