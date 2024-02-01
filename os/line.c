#include <stdio.h>

int main(int argc,char *argv[])// 여기서  char  *argv[]는 char **argv로 써도 됨
{
	int i;
	printf("argc=%d\n",argc);
	for (i=0;i<argc;i++)
		printf("*argv[%d]= %s\n",i,argv[i]);
	return 0;

}

