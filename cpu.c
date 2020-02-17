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

// Increment cpu->a by x (for sequence point)
uint8_t cpu_adc(cpu_t*cpu,uint8_t x)
{
	return cpu->a+=x;
}

// Assign x to cpu->a (for sequence point)
uint8_t cpu_assign(cpu_t*cpu,uint8_t x)
{
	return cpu->a=x;
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
		// TODO Verify these are correct
		case 0x81: sta( fetch() + cpu->x );		incpc();	break;
		case 0x91: sta( fetch() + cpu->y );		incpc();	break;

		// x
		case 0xA2: ldx( fetch() );						sr_nz(cpu->x); incpc();	break;
		case 0xA6: ldx( deref( fetch() ) );				sr_nz(cpu->x); incpc();	break;
		case 0xB6: ldx( deref( fetch() + cpu->y ) );	sr_nz(cpu->x); incpc();	break;
		case 0xAE: ldx( deref( fetch16() ) );			sr_nz(cpu->x); incpc();	break;
		case 0xBE: ldx( deref( fetch16() + cpu->y) );	sr_nz(cpu->x); incpc();	break;

		// y
		case 0xA0: ldy( fetch() );						sr_nz(cpu->y); incpc();	break;
		case 0xA4: ldy( deref( fetch() ) );				sr_nz(cpu->y); incpc();	break;
		case 0xB4: ldy( deref( fetch() + cpu->x ) );	sr_nz(cpu->y); incpc();	break;
		case 0xAC: ldy( deref( fetch16() ) );			sr_nz(cpu->y); incpc();	break;
		case 0xBC: ldy( deref( fetch16() + cpu->x) );	sr_nz(cpu->y); incpc();	break;

		// Arithmetic ---
		// TODO Check ADC for DECIMAL FLAG for conditional behavior
		// TODO Fix C + V SR flags for these
		case 0x65: adc( deref( fetch() ) );	sr_nz(cpu->a);	incpc();	break;
		case 0x69: adc( fetch() );			sr_nz(cpu->a);	incpc();	break;
		case 0x75: adc( deref( fetch() + cpu->x ) );	sr_nz(cpu->a);	incpc();	break;
		case 0x6D: adc( deref( fetch16() ) );			sr_nz(cpu->a);	incpc();	break;
		case 0x7D: adc( deref( fetch16() + cpu->x ) );			sr_nz(cpu->a);	incpc();	break;
		case 0x79: adc( deref( fetch16() + cpu->y ) );			sr_nz(cpu->a);	incpc();	break;
		// TODO Verify these are correct (use ind() )
		case 0x61: adc( ind( fetch() + cpu->x ) );			sr_nz(cpu->a);	incpc();	break;
		case 0x71: adc( ind( fetch() + cpu->y ) );			sr_nz(cpu->a);	incpc();	break;

		// INC/DEC
		case 0xE8: cpu->x += 1;		incpc();		break;
		case 0xC8: cpu->y += 1;		incpc();		break;
		case 0xE6: ram->ram[ fetch() ] += 1;	incpc();	break;
		case 0xF6: ram->ram[ fetch() + cpu->x ] += 1;	incpc();	break;
		case 0xEE: ram->ram[ fetch16() ] += 1;	incpc();	break;
		case 0xFE: ram->ram[ fetch16() + cpu->x ] += 1;	incpc();	break;

		// Bitwise ---
		// AND
		case 0x29: and( fetch() ); incpc(); break;
		case 0x25: and( deref( fetch() ) ); incpc(); break;
		case 0x35: and( deref( fetch() + cpu->x ) ); incpc(); break;
		case 0x2D: and( deref( fetch16() ) ); incpc(); break;
		case 0x3D: and( deref( fetch16() + cpu->x ) ); incpc(); break;
		case 0x39: and( deref( fetch16() + cpu->y ) ); incpc(); break;
		case 0x21: and( deref( deref( fetch() + cpu->x ) ) ); incpc(); break;
		case 0x31: and( deref( deref( fetch() + cpu->y ) ) ); incpc(); break;

		// EOR
		// TODO Check if accumulator is changed, or memory
		// TODO Verify 0x4D onward work correctly
		case 0x49: eor( fetch() ); incpc(); break;
		case 0x45: eor( deref( fetch() ) ); incpc(); break;
		case 0x55: eor( deref( fetch() + cpu->x ) ); incpc(); break;
		case 0x4D: eor( deref( fetch16() ) ); incpc(); break;
		case 0x5D: eor( deref( fetch16() + cpu->x ) ); incpc(); break;
		case 0x59: eor( deref( fetch16() + cpu->y ) ); incpc(); break;
		case 0x41: eor( deref( deref( fetch() + cpu->x ) ) ); incpc(); break;
		case 0x51: eor( deref( deref( fetch() + cpu->y ) ) ); incpc(); break;

		// ORA
		case 0x09: ora( fetch() ); incpc(); break;
		case 0x05: ora( deref( fetch() ) ); incpc(); break;
		case 0x15: ora( deref( fetch() + cpu->x ) ); incpc(); break;
		case 0x0D: ora( deref( fetch16() ) ); incpc(); break;
		case 0x1D: ora( deref( fetch16() + cpu->x ) ); incpc(); break;
		case 0x19: ora( deref( fetch16() + cpu->y ) ); incpc(); break;
		case 0x01: ora( deref( deref( fetch() + cpu->x ) ) ); incpc(); break;
		case 0x11: ora( deref( deref( fetch() + cpu->y ) ) ); incpc(); break;

		// ASL
		// TODO Move memory, not accumulator
		// TODO make sure zp/similar offsets are WRAPPED to 8-bits!
		case 0x0A: asl( cpu->a ); incpc(); break;
		case 0x06: asl( deref( fetch() ) ); incpc(); break;
		case 0x16: asl( deref( fetch() + cpu->x ) ); incpc(); break;
		case 0x0E: asl( deref( fetch16() ) ); incpc(); break;
		case 0x1E: asl( deref( fetch16() + cpu->x ) ); incpc(); break;

		// Jump/branch ---
		case 0x4C: ldpc( fetch16() );				break;
		case 0x6C: ldpc( ind( fetch16() ) );				break;
		case 0xEA: nop();			incpc();	break;
		case 0x00: brk(); 			incpc();	break;
		default: incpc();						break;
	}
}
