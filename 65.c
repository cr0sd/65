#include"65.h"
#include"ram.h"
#include"rom.h"
#include"cpu.h"

void puterr(const char*fmt,...)
{
	va_list list;
	va_start(list,fmt);
	fprintf(stderr,PROG": Error: ");
	vfprintf(stderr,fmt,list);
	va_end(list);
}

// Entry point
int main(int argc,char**argv)
{
	cpu_t*cpu=cpu_init();
	rom_t*rom=new(rom_t);
	ram_t*ram=ram_init();

	// Parse command line arguments
	if(argc>1)
	{
		rom_load_file(rom,argv[1]);
		rom_map(rom,ram);
	}

	// Execute ROM
	if(rom->data)
	{
		// Read 3 instructions for testing purposes
		for(int i=0;i<3;++i)
			cpu_exec(cpu,ram);
	}
	else
		puterr("%s: No ROM loaded\n",__func__);

	// Free memory
	free(cpu);
	rom_del(rom);
	free(rom);
	ram_del(ram);
	free(ram);
}
