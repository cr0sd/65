#include<stdio.h>
#include<stdint.h>
#include<fcntl.h>
#include<unistd.h>
int main(void)
{
	int fd;
	uint8_t h[16]={0};
	int x=0xea;

	// Open nes.nes
	fd=open("nes.nes",O_CREAT|O_RDWR);
	if(fd<0) fputs("failed to open file\n",stderr);

	// Write 16-bit header
	write(fd,h,1);

	// Write opcode
	write(fd,&x,sizeof(x));
}
