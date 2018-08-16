#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/resource.h>


int main(int argc,char *argv[])
{

	struct timeval tv;
	if (argc>1)
	{

			pid_t pid= fork();

	
			gettimeofday(&tv,0);
			double t0 = (double)tv.tv_sec*1000.0+ (double)tv.tv_usec/1000.0;

			if(pid==0)
			{
				int ret;
				const char *a[]={argv[1],argv[2],NULL};

				ret=execvp(a[0],a);
			
				if (ret==-1){
				perror("no such command found\n");
				_exit(1);}
			}
			else  if(pid<0)
			{
				perror("fatal error occurred\n");
				exit(1);
			}

			struct rusage usage;

			wait3(0, 0, &usage);//wait for one of the child processes to terminate

			gettimeofday(&tv,0);
			double t1 = (double)tv.tv_sec*1000.0 + (double)tv.tv_usec/1000.0;



			double Time = (double)usage.ru_utime.tv_sec*1000.0
			+ (double)usage.ru_utime.tv_usec/1000.0;

			printf("User time consumed : %f ms\n",Time);

			Time = (double)usage.ru_stime.tv_sec*1000.0
			+ (double)usage.ru_stime.tv_usec/1000.0;

			printf("System time consumed : %f ms\n",Time);

			printf("Wall Clock time consumed : %f ms\n",t1-t0);

			printf("Voluntary context switches : %ld times\n",usage.ru_nvcsw);

			printf("Involuntary context switches : %ld times\n",usage.ru_nivcsw);

			printf("Number of hard page faults : %ld times\n",usage.ru_majflt);

			printf("Number of soft page faults : %ld times\n",usage.ru_minflt);

	}

	else
	{

		while(1)
		{

			printf("\n->");
			char c[200];
			char *str=NULL;
			char *s1="";
			char *s2="";
		 
		 	fgets(c, 200, stdin); 
		 	strtok_r(c," ",&str);
			strtok_r(c,"\n",&s1);
			strtok_r(str,"\n",&s2);

			if((strcmp(c, "exit") == 0))
			{
				break;
			}
			if((strcmp(c, "cd") == 0))
			{
		 
				int status;
				pid_t pid= fork();
		 		if(pid==0)
				{ 
					int ret;
			   		const char *a[]={c,str,NULL};

			   		ret=execvp(a[0],a);
		
			   		if (ret==-1)
			   		{
						perror("may be many of the system don't have cd its built in on shell,so we use here chdir()\n");
						chdir(a[1]);
						_exit(1);
					}
				}
						                  
				while (wait(&status) != pid)       /* wait for completion  */
					   ;
			 	printf("\n%s->",str);

			}
			else
			{
				pid_t pid= fork();


				gettimeofday(&tv,0);
				double t0 = (double)tv.tv_sec*1000.0+ (double)tv.tv_usec/1000.0;

				if(pid==0)
				{
					int ret;
				  	 if((strcmp(c, "ls") == 0)&&(strcmp(str, "") == 0))
					 {
							str=getenv("PWD");

					 }
					 const char *a[]={c,str,NULL};
					 ret=execvp(a[0],a);
		
				   	 if (ret==-1)
				   	 {
						perror("no such command found\n");
						_exit(1);
					 }
				}
				else  if(pid<0)
				{
					perror("fatal error occurred\n");
					exit(1);
				}
			   
				struct rusage usage;

				wait3(0, 0, &usage);//wait for one of the child processes to terminate

				gettimeofday(&tv,0);
				double t1 = (double)tv.tv_sec*1000.0
					+ (double)tv.tv_usec/1000.0;



				double Time = (double)usage.ru_utime.tv_sec*1000.0
				+ (double)usage.ru_utime.tv_usec/1000.0;

				printf("User time consumed : %f ms\n",Time);

				Time = (double)usage.ru_stime.tv_sec*1000.0
				+ (double)usage.ru_stime.tv_usec/1000.0;

				printf("System time consumed : %f ms\n",Time);

				printf("Wall Clock time consumed : %f ms\n",t1-t0);

				printf("Voluntary context switches : %ld times\n",usage.ru_nvcsw);

				printf("Involuntary context switches : %ld times\n",usage.ru_nivcsw);

				printf("Number of hard page faults : %ld times\n",usage.ru_majflt);

				printf("Number of soft page faults : %ld times\n",usage.ru_minflt);


			}

		}
	}
	return 0;

}
