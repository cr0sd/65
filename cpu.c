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

// Microinstructions
// Ex: lda $X : lda(fetch())
// Get next byte
// Load to pc
// Load to a
// Load to x
// Load to y

// Addressing mode micro-insns
#define zp(x) ram->ram[x]
#define ab(x) ram->ram[x]
#define imm() ram->ram[cpu->pc+=1]

// Move micro-insns
#define lda(x) cpu->a=(x)
#define ldx(m) cpu->x=m
#define ldy(x) cpu->y=(x)
#define ldpc(x) cpu->pc=(x)
#define nop()
#define brk()

// Execute next instruction in RAM
// through CPU
void cpu_exec(cpu_t*cpu,ram_t*ram)
{

	// NOTE: Don't handle pc incrementing
	// here
	switch(ram->ram[cpu->pc])
	{

		// Get RAM value at address X
		#define zp(x) ram->ram[x]

		case 0xA0: ldy( imm() ); break;
		case 0xA2: ldx( imm() ); break;
		case 0xA5: lda( zp( imm() ) ); break;
		case 0xA9: lda( imm() ); break;
		case 0x4C: ldpc( imm() | (imm()<<8) ); break;
		case 0x00: brk(); break;
		case 0xEA: nop();
		default: break;

	}
}
