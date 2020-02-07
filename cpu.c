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

		// Set 'mode' to main cpu
		#define __cpu cpu

		// Move/load/transfer ---
		// a
		case 0xA1: lda( xidx( ind( imm() ) ) );	sr_nz(cpu->a); incpc(1);	break;
		case 0xA5: lda( zp( imm() ) );			sr_nz(cpu->a); incpc(1);	break;
		case 0xA9: lda( imm() );				sr_nz(cpu->a); incpc(1);	break;
		case 0xAD: lda( ab( imm16() ) );		sr_nz(cpu->a); incpc(1);	break;
		case 0xB1: lda( yidx( zp( imm() ) ) );	sr_nz(cpu->a); incpc(1);	break;
		case 0xB5: lda( xidx( zp( imm() ) ) );	sr_nz(cpu->a); incpc(1);	break;
		case 0xB9: lda( yidx( ab( imm() ) ) );	sr_nz(cpu->a); incpc(1);	break;
		case 0xBD: lda( xidx( ab( imm() ) ) );	sr_nz(cpu->a); incpc(1);	break;
		case 0x85: sta( imm() );				incpc(1);	break;
		// x
		case 0xA2: ldx( imm() );				sr_nz(cpu->x); incpc(1);	break;
		// y
		case 0xA0: ldy( imm() );				sr_nz(cpu->y); incpc(1);	break;

		// Jump/branch ---
		case 0x4C: ldpc( imm16() );				break;
		case 0x6C: ldpc( ind( imm16() ) );		break;
		case 0xEA: nop();						incpc(1);	break;
		case 0x00: brk(); 						incpc(1);	break;
		default:											break;

	}
}
