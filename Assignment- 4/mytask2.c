#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<string.h>
#include<unistd.h>
#include<string.h>
#include<dirent.h>

char newLine[] ={"\n"} ;

void read_d(char path[],char command[],struct stat sb)
{
		DIR * in_dir = opendir (path);
		struct dirent * entry;
		struct stat sb2;
		char a[100];
		strcpy(path,"/");
		while( entry = readdir (in_dir) )
		{
		 	
		 	strcpy(a,entry->d_name);
		 	strcpy(path,a);
		 	if(!strcmp(command,"-A")||!strcmp(command,"-k" ))
		 	{
		 		if(a[0]=='.')
		 			continue;
		 		write(1,a,strlen(a));
				write(1,newLine,2);
		 	}
		 	else if(!strcmp(command,"-a"))
		 	{
				write(1,a,strlen(a));
				write(1,newLine,2);

			}
			else if(!strcmp(command,"-f"))	
			{
				write(1,a,strlen(a));
				write(1,newLine,2);
			}
			else if(!strcmp(command,"-F"))
			{
				if (stat(path, &sb2) == -1)
		 	       perror("stat");
		 	    if(a[0]=='.')
		 			continue;
		 		else
		 		{
				    switch(sb2.st_mode & S_IFMT) 
					{
						
						case S_IFREG:
							write(1,a,strlen(a));
							write(1,"*",1);
							write(1,newLine,2);
							break;
						 case S_IFLNK:
						 	write(1,a,strlen(a));
						 	write(1,"%",1);
						 	write(1,newLine,2);
							break;
						 case S_IFSOCK:
						 	write(1,a,strlen(a));
						 	write(1,"=",1);
						 	write(1,newLine,2);
							break;
						case S_IFDIR:
							write(1,a,strlen(a));
							write(1,"/",1);
							write(1,newLine,2);
							break;
						case S_IFIFO:
							write(1,a,strlen(a));
						 	write(1,"|",1);
						 	write(1,newLine,2);
						  	break;
						default:
						 	write(1,a,strlen(a));
						 	write(1,"@",1);
						 	write(1,newLine,2);
						  break;
						
					}
				}
			}
			else if(!strcmp(command,"-i"))
			{
				lstat(a,&sb2);
		 	    if(a[0]=='.')
		 			continue;
		 		else
		 		{
		 			printf("%ld",sb2.st_ino);
		 			//write(1,sb2.st_ino,sizeof(long));
		 			write(1," ",1);
		 			write(1,a,strlen(a));
		 			write(1,newLine,2);
		 		}
			}
			else if(!strcmp(command,"-h"))
			{
				struct stat sb2;
				stat(path,&sb2);
			    if(sb2.st_blocks*512<1024) printf("%ld %s \n",sb2.st_blocks*512,a);

			    else if(sb2.st_blocks*512>=1024 && sb2.st_blocks*512<1024*1024)
			        printf("%ld.%ldK %s\n",(sb2.st_blocks*512)/1024,(sb2.st_blocks*512)%1024,a);
			    else if(sb2.st_blocks*512>=1024*1024 && sb2.st_blocks*512<1024*1024*1024)
			        printf("%ld.%ldM %s\n",(sb2.st_blocks*512)/(1024*1024),(sb2.st_blocks*512)%(1024*1024),a);
			    else if(sb2.st_blocks*512>=1024*1024*1024)
			        printf("%ld.%ldG %s\n",(sb2.st_blocks*512)/(1024*1024*1024),(sb2.st_blocks*512)%(1024*1024*1024),a);
		        else printf("%ld %s",sb2.st_blocks/2,a);
			}
			int is_l=0;
			if(!strcmp(command,"-l") || !strcmp(command,"-n") || !strcmp(command,"-o"))
	    	{
	    		struct stat sb2;
				stat(path,&sb2);
				is_l=1;

				if(S_ISDIR(sb2.st_mode)) printf("d");
				else if(S_ISCHR(sb2.st_mode)) printf("c");
				else if(S_ISBLK(sb2.st_mode)) printf("b");
				else if(S_ISFIFO(sb2.st_mode)) printf("p");
				else if(S_ISLNK(sb2.st_mode)) printf("l");
				else if(S_ISSOCK(sb2.st_mode)) printf("s");
				else if(S_ISREG(sb2.st_mode)) printf("-");


				for(int i=8;i>=0;i--)
				{
				    int k = (sb2.st_mode & (1<<i));
				    if(i%3==0) printf("%s",k?"x":"-");
				    else if(i%3==1) printf("%s",k?"w":"-");
				    else printf("%s",k?"r":"-");
				}


				printf(" %ld ",sb2.st_nlink);



				if(!strcmp(command,"-n"))
				{
				    printf("%d ",sb2.st_uid );
				    if(!strcmp(command,"-o")==0) printf("%d ",sb2.st_gid);
				}

				if(!strcmp(command,"-h"))
				{
				    if(sb2.st_size<1024) 
				    	printf("%ld ",sb2.st_size);
				    	
				    else if(sb2.st_size>=1024 && sb2.st_size<1024*1024)
				        printf("%ld.%ldK ",sb2.st_size/1024,sb2.st_size%1024);
				    else if(sb2.st_size>=1024*1024 && sb2.st_size<1024*1024*1024)
				        printf("%ld.%ldM ",sb2.st_size/(1024*1024),sb2.st_size%(1024*1024));
				    else if(sb2.st_size>=1024*1024*1024)
				        printf("%ld.%ldG ",sb2.st_size/(1024*1024*1024),sb2.st_size%(1024*1024*1024));

				}
				else printf("%ld ",sb2.st_size);
				printf(" %s",a);
				printf("\n");
			}

		}
}
int main (int argc, char *argv[])
{
	struct stat sb;
	
		
			
	if(argc==3 && !strcmp(argv[1],"ls"))
	{
		 

		char path[1000];
		strcpy(path,get_current_dir_name());
		if (stat(path, &sb) == -1) {
		        perror("stat");
		        //exit(EXIT_FAILURE);
		}
		read_d(path,argv[2],sb);
	}

	else if(argc==4 && !strcmp(argv[1],"ls"))
	{
		if (stat(argv[3], &sb) == -1) {
		        perror("stat");
		        //exit(EXIT_FAILURE);
	    }

		switch(sb.st_mode & S_IFMT) 
		{
			char path[1000];
			case S_IFDIR: 
				
				strcpy(path,get_current_dir_name());
				strcpy(path,"/");
				strcpy(path,argv[3]);
				read_d(path,argv[2],sb);
				break;
		    default :
				write(1,argv[3],strlen(argv[2]));
				write(1,newLine,2);
				break;
		}
	}

	return 0;
}
