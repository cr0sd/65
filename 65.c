#include"65.h"

void puterr(const char*fmt,...)
{
	va_list list;
	va_start(list,fmt);
	fprintf(stderr,PROG": ");
	vfprintf(stderr,fmt,list);
	va_end(list);
}

// Entry point
int main(int argc,char**argv)
{
	cpu_t*cpu=new(cpu_t);
	rom_t*rom=new(rom_t);
	ram_t*ram=ram_init();
	if(argc>1)
		printf("loading rom \"%s\"\n",argv[1]),
		rom_load(rom,argv[1]);
}
