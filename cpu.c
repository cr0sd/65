#include"cpu.h"
#include"ram.h"

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

	// NOTE: Don't handle pc incrementing
	// here
	switch(ram->ram[cpu->pc])
	{
		case 0xa9:
			cpu->pc+=1;
			cpu->a=ram->ram[cpu->pc];
			break;
		case 0x00:
			break;
		case 0x0a:
			break;
		case 0xEA:
			break;
		default:
			break;
	}
}
