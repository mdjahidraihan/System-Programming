#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

time_t t_array[3];
int sig_array[3],top;

void push(int signo)
{
    if(top==3)
    {
        t_array[0]=t_array[1];
        sig_array[0]=sig_array[1];

        t_array[1]=t_array[2];
        sig_array[1]=sig_array[2];

        top--;
    }
    t_array[top]=time(0);
    sig_array[top++]=signo;
}


void signal_handler (int signo)
{
    printf ("%s Caught by my program!!!\n",sys_siglist[signo]);

    push(signo);


    if(top==3 && sig_array[2]==SIGQUIT && sig_array[1]==SIGTSTP  && sig_array[0]==SIGINT)
    {
        if(t_array[2]-t_array[0]<=2)
        {
            puts("Expected Sequence Received\nProgram is Terminated");
            exit(0);
        }
    }



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


int main()
{
    top=0;

    printf("My PID is : %d\n",getpid());

    int ret;
    ret=install_handler(SIGINT,signal_handler);
    if(ret==-1) puts("problem occurred while installing handler");

    ret=install_handler(SIGQUIT,signal_handler);
    if(ret==-1) puts("problem occurred while installing handler");

    ret=install_handler(SIGTSTP,signal_handler);
    if(ret==-1) puts("problem occurred while installing handler");

    for(;;);


    return 0;
}







