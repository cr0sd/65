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

// Increment PC and return (does not
// reference RAM)
uint16_t cpu_fetch(cpu_t*cpu)
{
	return cpu->pc+=1;
}

uint8_t cpu_adc(cpu_t*cpu,uint8_t x)
{
	return cpu->a+=x;
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
		case 0xA1: lda( deref( deref( fetch() + cpu->x ) ) );		sr_nz(cpu->a); incpc(); break;
		case 0xB1: lda( deref( deref( fetch() + cpu->y ) ) );		sr_nz(cpu->a); incpc(); break;
		case 0xA5: lda( fetch() );		sr_nz(cpu->a); incpc();	break;
		case 0xA9: lda( fetch() );	sr_nz(cpu->a); incpc();	break;
		case 0xAD: lda( fetch16() );		sr_nz(cpu->a); incpc();	break;
		case 0xB5: lda( deref( fetch() + cpu->x ) );	sr_nz(cpu->a); incpc();	break;
		case 0xB9: lda( deref( fetch16() + cpu->y ) );	sr_nz(cpu->a); incpc();	break;
		case 0xBD: lda( deref( fetch16() + cpu->x ) );	sr_nz(cpu->a); incpc();	break;

		// Store: Do not dereference
		case 0x85: sta( fetch() );				incpc();	break;
		case 0x95: sta( fetch() + cpu->x );	incpc();	break;
		case 0x8D: sta( fetch16() );				incpc();	break;
		case 0x9D: sta( fetch16() + cpu->x );	incpc();	break;
		case 0x99: sta( fetch16() + cpu->y );	incpc();	break;
		case 0x81: sta( fetch() + cpu->x );		incpc();	break;
		case 0x91: sta( fetch() + cpu->y );		incpc();	break;

		// x
		case 0xA2: ldx( fetch() );				sr_nz(cpu->x); incpc();	break;
		// y
		case 0xA0: ldy( fetch() );				sr_nz(cpu->y); incpc();	break;

		// Arithmetic ---
		// TODO Check for DECIMAL FLAG for conditional behavior
		case 0x65: adc( deref( fetch() ) );	sr_nz(cpu->a);	incpc();	break;
		case 0x69: adc( fetch() );			sr_nz(cpu->a);	incpc();	break;
		case 0x75: adc( deref( fetch() + cpu->x ) );	sr_nz(cpu->a);	incpc();	break;
		case 0x6D: adc( deref( fetch16() ) );			sr_nz(cpu->a);	incpc();	break;
		case 0x7D: adc( deref( fetch16() + cpu->x ) );			sr_nz(cpu->a);	incpc();	break;

		// Jump/branch ---
		case 0x4C: ldpc( fetch16() );				break;
		case 0x6C: ldpc( ind() );				break;
		case 0xEA: nop();			incpc();	break;
		case 0x00: brk(); 			incpc();	break;
		default: incpc();						break;
	}
}
