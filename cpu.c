#include"cpu.h"

// Execute next instruction in RAM
// through CPU
void cpu_exec(cpu_t*cpu,ram_t*ram)
{
	#define name(x) puts(#x);
	//#define name(x)
	switch(ram->mem[cpu->pc])
	{
		case 0xEA: name(nop);
		default: break;
	}
	#undef name
}
