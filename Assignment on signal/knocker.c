#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>

int main(int argc,char *argv[])
{
    int pid=atoi(argv[1]);
	int len = strlen(argv[2];
    for(int i=0;i<len);i++)
    {
        if(i>=1) 
        	sleep(1);
        if(argv[2][i]=='c')
        	 kill(pid,SIGINT);
        else if(argv[2][i]=='z')
        	 kill(pid,SIGTSTP);
        else if(argv[2][i]=='q') 
        	kill(pid,SIGQUIT);
    }

    return 0;
}






