#include"65.h"
//#include"65db.h"
#include"ram.h"
#include"rom.h"
#include"cpu.h"
#include"joy.h"
#include<ctype.h>
#include<stdbool.h>
#include<unistd.h>

#define PROG "65da"

// from 65da_disasm.c
void da_print_disassembly(cpu_t*cpu,ram_t*ram);

// Entry point
int main(int argc,char**argv)
{
	cpu_t*cpu=cpu_init();
	rom_t*rom=new(rom_t);
	ram_t*ram=ram_init();

	char*title=NULL;

	uint16_t hex_offset=0x0000;	// Where start drawing memory hexdump

	// Parse command line arguments
	if(argc>1)
	{
		rom_load_file(rom,argv[1]);
		title=argv[1];
		//rom_print_header_info(rom);

		// Map ROM into $8000 by default
		// TODO: Learn where exactly to map 'PRG-ROM'
		rom_map(rom,ram,0x0000);
		hex_offset=0x0000;
	}

	// Verify ROM is loaded
	if(rom->rom)
		cpu->pc=0x0000;
	else
	{
		puterr("%s: No ROM loaded\n",__func__);
		goto quit;
	}

	// Print disassembly
	printf("%s\n",title);
	da_print_disassembly(cpu,ram);

quit:
	// Free memory
	free(cpu);
	rom_del(rom);
	free(rom);
	ram_del(ram);
	free(ram);
}

// Print formatted error message
void puterr(const char*fmt,...)
{
	va_list list;
	va_start(list,fmt);
	printf(PROG": ");
	printf("Error: ");
	vprintf(fmt,list);
	va_end(list);
}
