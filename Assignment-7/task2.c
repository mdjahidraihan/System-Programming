#include <sys/mman.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include<stdlib.h>
#include<string.h>
#define MX 1000
int main(int argc,char *argv[])
{
	char src[1000],dest[1000];
	strcpy(src,argv[2]);
	strcpy(dest,argv[3]);
	int fd_in, fd_out;
    char *p1, *p2;
    struct stat s;
    size_t filesize;

    fd_in = open(src,O_RDONLY);
    if (fd_in  == -1) 
	{
	  perror ("open");
		 return 1;
	}
    filesize = lseek(fd_in ,0, SEEK_END);

    p1 = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, fd_in, 0);

    fd_out = open(dest, O_RDWR | O_CREAT, 0777);

    ftruncate(fd_out, filesize);

    p2 = mmap(NULL, filesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd_out, 0);


    memcpy(p2, p1, filesize);

    munmap(p1, filesize);
    munmap(p2, filesize);

    close(fd_in);
    close(fd_out);
   
    return 0;
}
