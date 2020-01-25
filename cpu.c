#include"cpu.h"

// Create new cpu_t object with
// default values
cpu_t*cpu_init(void)
{
	cpu_t*cpu=new(cpu_t);
	memset(cpu,0,sizeof(cpu_t));
	return cpu;
}

// Execute next instruction in RAM
// through CPU
void cpu_exec(cpu_t*cpu,ram_t*ram)
{
	#define name(x) puts(#x);
	//#define name(x)
	switch(ram->mem[cpu->pc])
	{
		case 0x0a:
			name(asl);
			++cpu->pc;
			break;
		case 0xEA:
			name(nop);
			++cpu->pc;
			break;
		default: break;
	}
	#undef name
}
