#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main(void)
{
	int fd;
	int x=0xea;

	fd=open("nes.nes",O_CREAT|O_RDWR);
	if(fd<0) fputs("failed to open file\n",stderr);
	write(fd,&x,sizeof(x));
}
