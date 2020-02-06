#include"disasm.h"

char*da_print_nextop(cpu_t*cpu,ram_t*ram)
{
	static char b[512];
	switch(ram->ram[cpu->pc])
	{
	case 0xa0:
		sprintf(b,"%04x    %02x %02x  ldy %02x",cpu->pc,ram->ram[cpu->pc],ram->ram[cpu->pc+1],ram->ram[cpu->pc+1]);
		break;
	default:
		sprintf(b,"-                           ");
	}
	return b;
}
