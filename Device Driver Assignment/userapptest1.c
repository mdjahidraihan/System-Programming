#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define DEVICE "/dev/koo"

int main(){
	char ch;
	char read_buf[100], write_buf[100];

	int fd = open(DEVICE, O_RDWR);
	if(fd == -1){
		printf("file  either does not exist or has been locked by others\n");
		exit(-1);
	}

	printf("r = read from device, w= write to device, enter command: ");
	scanf("%c" , &ch);
	getchar();
	int n;
	switch (ch)
	{
		case 'w':
		printf("Enter number of bytes to write:\n");
		scanf("%d",&n);
		getchar();
		printf("enter data: ");
		scanf("%[^\n]", write_buf);
		write(fd, write_buf, sizeof(write_buf));
		break;
		case 'r':
		printf("Enter number of bytes to read:\n");
		scanf("%d",&n);
		read(fd, read_buf, n);
		printf("sysprogdevice: %s\n", read_buf);
		break;

		default:
		printf("command not recognized\n");
		break;
	}
	return 0;
}
