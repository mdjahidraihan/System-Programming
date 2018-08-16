#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#define mx 1000000

void signal_handler (int signo)
{
    printf ("%s Caught by my program!!!\n",sys_siglist[signo]);

}

int install_handler(int signum, void (*handler)(int))
{
    struct sigaction newAct;
    struct sigaction oldAct;

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set,SIGINT);
    sigaddset(&set,SIGQUIT);
    sigaddset(&set,SIGTSTP);

    newAct.sa_handler=handler;
    newAct.sa_mask=set;
    newAct.sa_flags=0;

    int ret=sigaction(signum,&newAct,&oldAct);
    return ret;
}

char buf[mx];

int read_and_echo()
{
    int ret;
    while( ret=read(0,buf,mx) )
    {

        if(ret==-1)
        {
            puts("Error while reading");
            return ret;
        }
        if(buf[0]=='\n') return 0;
        ret=write(1,buf,ret);
        if(ret==-1)
        {
            puts("Error while writing");
            return ret;
        }
    }


    return 0;
}

int main()
{
    int ret;
    ret=install_handler(SIGINT,signal_handler);
    if(ret==-1) puts("problem occurred while installing handler");

    ret=install_handler(SIGQUIT,signal_handler);
    if(ret==-1) puts("problem occurred while installing handler");

    ret=install_handler(SIGTSTP,signal_handler);
    if(ret==-1) puts("problem occurred while installing handler");

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set,SIGINT);
    sigaddset(&set,SIGQUIT);
    sigaddset(&set,SIGTSTP);

    sigprocmask(SIG_BLOCK,&set,NULL);


    ret=read_and_echo();

    sigprocmask(SIG_UNBLOCK,&set,NULL);

    if(ret==0) puts("SUCCESS");
    else puts("FAILURE");


    return 0;
}






