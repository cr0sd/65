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

uint16_t cpu_fetch(cpu_t*cpu)
{
	return cpu->pc+=1;
}

// Execute next instruction in RAM
// through CPU
void cpu_exec(cpu_t*cpu,ram_t*ram)
{

	switch(ram->ram[cpu->pc])
	{

		// Set 'mode' to main cpu
		#define __cpu cpu

		// Move/load/transfer ---
		// a
		//case 0xA1: lda( xidx( zp() ) );	sr_nz(cpu->a); incpc(1);	break;
		//case 0xA1: lda( ind( xidx( fetch() ) ) );	sr_nz(cpu->a); break;
		case 0xA5: lda( zp() );			sr_nz(cpu->a); incpc(1);	break;
		case 0xA9: lda( imm() );				sr_nz(cpu->a); incpc(1);	break;
		case 0xAD: lda( ab() );		sr_nz(cpu->a); incpc(1);	break;
		//case 0xB1: lda( ind( zp() ) );	sr_nz(cpu->a);			break;
		//case 0xB5: lda( xidx( zp() ) );	sr_nz(cpu->a); incpc(1);	break;
		//case 0xB9: lda( yidx( fetch() ) );	sr_nz(cpu->a); incpc(1);	break;
		//case 0xBD: lda( xidx( fetch() ) );	sr_nz(cpu->a); incpc(1);	break;

		case 0x85: sta( fetch() );				incpc(1);	break;
		// x
		case 0xA2: ldx( fetch() );				sr_nz(cpu->x); incpc(1);	break;
		// y
		case 0xA0: ldy( fetch() );				sr_nz(cpu->y); incpc(1);	break;

		// Jump/branch ---
		case 0x4C: ldpc( ab() );				break;
		case 0x6C: ldpc( ind() );		break;
		case 0xEA: nop();						incpc(1);	break;
		case 0x00: brk(); 						incpc(1);	break;
		default:											break;

	}
}
