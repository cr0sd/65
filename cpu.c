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

	switch(ram->ram[cpu->pc])
	{

		// Get RAM value at address X
		#define zp(x) ram->ram[x]

		case 0xA0: ldy( imm() ); incpc(1); break;
		case 0xA2: ldx( imm() ); incpc(1); break;
		case 0xA5: lda( zp( imm() ) ); incpc(1); break;
		case 0xA9: lda( imm() ); incpc(1); break;
		case 0x4C: ldpc( imm() | (imm()<<8) ); break;
		case 0x00: brk(); incpc(1); break;
		case 0xEA: nop(); incpc(1); break;
		default: break;

	}
}
