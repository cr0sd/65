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
	fd=open("nes.nes",O_CREAT|O_TRUNC|O_RDWR);

	write(fd,"NES",4);

	for(int i=1;i<1024;++i)
	{
		uint8_t j=i; // cast to 8-bit int
		write(fd,&j,1);
	}

	lseek(fd,6,SEEK_SET);
	x=0;
	write(fd,&x,1);

	//if(fd<0) fputs("failed to open file\n",stderr);

	//// Write 16-bit header
	//for(int i=0;i<16;++i)
		//write(fd,h,1);

	//// Write opcode
	//write(fd,&x,sizeof(x));
}
