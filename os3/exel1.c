#include<stdio.h>
#include<unistd.h>
int main()
{//int main(int argc,char *argv[])//명령행 인자를 받기위한 인자개수,포인터배열
        char *argv[]={"ls","-l",NULL};
        printf("execv start!\n");
        execv("/bin/ls",argv);//exel은 인자 하나하나 불러와야하지만 execv는 포[>
        //execl("/bin/ls","ls","-l",NULL)와 같다.
        printf("if you read this message,fail creating execv func.\n");
        return 0;
}
