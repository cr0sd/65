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
		rom_print_header_info(rom);
		//for(int i=0;i<100;++i)
			//printf("%2x",ram->mem[i]);
		//puts("");
	}

	// Execute ROM
	if(rom->data)
	{
		// Read instructions for testing purposes
		#define INSNS 4
		printf("Displaying %d instructions:\n",INSNS);
		for(int i=0;i<INSNS;++i)
		{
			//printf("pc: 0x%04x\t",cpu->pc);
			//printf("ac: 0x%02x",cpu->ac);
			//puts("");
			printf("0x%04x: 0x%02x\n",cpu->pc,ram->mem[cpu->pc]);
			cpu_exec(cpu,ram);
			cpu->pc+=1;
		}
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
