#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<string.h>
#include<unistd.h>
#include<string.h>
#include<dirent.h>
char newLine[] ={"\n"} ;
void read_d(char path[])
{
		DIR * in_dir = opendir (path);
		struct dirent * entry;
		
		char a[100];
		while( entry = readdir (in_dir) )
		{
		 	
		 	strcpy(a,entry->d_name);
		 	if(a[0]=='.')
		 		continue;
		 		
			write(1,a,strlen(a));
			write(1,newLine,2);
		}
}
int main (int argc, char *argv[])
{
	struct stat sb;
	
	if(argc==2 && !strcmp(argv[1],"ls"))
	{
		char path[1000];
		strcpy(path,get_current_dir_name());
		read_d(path);
	}

	else if(argc==3 && !strcmp(argv[1],"ls"))
	{
			 if (stat(argv[2], &sb) == -1) {
		        perror("stat");
		        //exit(EXIT_FAILURE);
		    }

		switch(sb.st_mode & S_IFMT) 
		{
			char path[1000];
			case S_IFDIR: 
				
				strcpy(path,get_current_dir_name());
				strcpy(path,"/");
				strcpy(path,argv[2]);
				read_d(path);
				break;
		    default :
				write(1,argv[2],strlen(argv[2]));
				write(1,newLine,2);
				break;
		}
	}

	return 0;
}
