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

// Compare
void cpu_cmp(cpu_t*cpu,uint8_t x,uint8_t y)
{
	cpu->sr.bits.z=(x-y)==0;
	cpu->sr.bits.c=(x<y);
}

// Push byte, dec cpu SP
void cpu_push(cpu_t*cpu,ram_t*ram,uint8_t d)
{
	ram->ram[--cpu->sp]=d;
}

// Push byte, dec cpu SP
void cpu_pull(cpu_t*cpu,ram_t*ram,uint8_t*d)
{
	*d=ram->ram[cpu->sp++];
}

// Push word, dec cpu SP
void cpu_push16(cpu_t*cpu,ram_t*ram,uint16_t d)
{
	cpu->sp-=2;
	ram->ram[cpu->sp+1]=(uint8_t)(d>>8);
	ram->ram[cpu->sp]=(uint8_t)(d&0xff);
}

// Pull word, inc cpu SP
void cpu_pull16(cpu_t*cpu,ram_t*ram,uint16_t*d)
{
	*d=(ram->ram[cpu->sp]|(ram->ram[cpu->sp+1]<<8));
	cpu->sp+=2;
}

// Increment cpu->a by x (for sequence point)
uint8_t cpu_adc(cpu_t*cpu,uint8_t x)
{
	return cpu->a+=x;
}

// Increment cpu->a by x (for sequence point)
uint8_t cpu_sbc(cpu_t*cpu,uint8_t x)
{
	return cpu->a-=x;
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
		// Load a
		case 0xA1: lda( deref( deref( fetch() + cpu->x ) ) );	sr_nz(cpu->a); incpc(); break;
		case 0xB1: lda( deref( deref( fetch() + cpu->y ) ) );	sr_nz(cpu->a); incpc(); break;
		case 0xA5: lda( deref( fetch() ) );						sr_nz(cpu->a); incpc();	break;
		case 0xA9: lda( fetch() );						sr_nz(cpu->a); incpc();	break;
		case 0xAD: lda( fetch16() );					sr_nz(cpu->a); incpc();	break;
		case 0xB5: lda( deref( fetch() + cpu->x ) );	sr_nz(cpu->a); incpc();	break;
		case 0xB9: lda( deref( fetch16() + cpu->y ) );	sr_nz(cpu->a); incpc();	break;
		case 0xBD: lda( deref( fetch16() + cpu->x ) );	sr_nz(cpu->a); incpc();	break;

		// Store a: Do not dereference
		case 0x85: sta( fetch() );				incpc();	break;
		case 0x95: sta( fetch() + cpu->x );		incpc();	break;
		case 0x8D: sta( fetch16() );			incpc();	break;
		case 0x9D: sta( fetch16() + cpu->x );	incpc();	break;
		case 0x99: sta( fetch16() + cpu->y );	incpc();	break;
		// TODO Verify these are correct
		case 0x81: sta( fetch() + cpu->x );		incpc();	break;
		case 0x91: sta( fetch() + cpu->y );		incpc();	break;

		// Store x
		case 0x86: stx( fetch() );			incpc(); break;
		case 0x96: stx( fetch() + cpu->y );	incpc(); break;
		case 0x8E: stx( fetch16() );		incpc(); break;

		// Load x
		case 0xA2: ldx( fetch() );						sr_nz(cpu->x); incpc();	break;
		case 0xA6: ldx( deref( fetch() ) );				sr_nz(cpu->x); incpc();	break;
		case 0xB6: ldx( deref( fetch() + cpu->y ) );	sr_nz(cpu->x); incpc();	break;
		case 0xAE: ldx( deref( fetch16() ) );			sr_nz(cpu->x); incpc();	break;
		case 0xBE: ldx( deref( fetch16() + cpu->y) );	sr_nz(cpu->x); incpc();	break;

		// Store y
		case 0x84: sty( fetch() );			incpc(); break;
		case 0x94: sty( fetch() + cpu->y );	incpc(); break;
		case 0x8C: sty( fetch16() );		incpc(); break;

		// Load y
		case 0xA0: ldy( fetch() );						sr_nz(cpu->y); incpc();	break;
		case 0xA4: ldy( deref( fetch() ) );				sr_nz(cpu->y); incpc();	break;
		case 0xB4: ldy( deref( fetch() + cpu->x ) );	sr_nz(cpu->y); incpc();	break;
		case 0xAC: ldy( deref( fetch16() ) );			sr_nz(cpu->y); incpc();	break;
		case 0xBC: ldy( deref( fetch16() + cpu->x) );	sr_nz(cpu->y); incpc();	break;

		// Transfer
		case 0xA8: ldy( cpu->a );		sr_nz(cpu->a); incpc(); break;
		case 0xAA: ldx( cpu->a );						sr_nz(cpu->a); incpc(); break;
		case 0xBA: ldx( cpu->sp );		sr_nz(cpu->x); incpc(); break;
		case 0x8A: lda( cpu->x );		sr_nz(cpu->a); incpc(); break;
		case 0x9A: cpu->sp = cpu->x;	sr_nz(cpu->x); incpc(); break;
		case 0x98: lda( cpu->y );		sr_nz(cpu->a); incpc(); break;

		case 0x48: push( cpu->a );		incpc(); break;
		case 0x68: pull( &cpu->a );		incpc(); break;


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
		case 0x61: adc( deref( fetch() + cpu->x ) );			sr_nz(cpu->a);	incpc();	break;
		case 0x71: adc( deref( fetch() + cpu->y ) );			sr_nz(cpu->a);	incpc();	break;

		// SBC
		case 0xE5: sbc( deref( fetch() ) );				sr_nz(cpu->a); incpc(); break;
		case 0xE9: sbc( fetch() );						sr_nz(cpu->a); incpc(); break;
		case 0xF5: sbc( deref( fetch() + cpu->x ) );	sr_nz(cpu->a); incpc(); break;
		case 0xED: sbc( deref( fetch16() ) );			sr_nz(cpu->a); incpc(); break;
		case 0xFD: sbc( deref( fetch16() + cpu->x ) );	sr_nz(cpu->a); incpc(); break;
		case 0xF9: sbc( deref( fetch16() + cpu->y ) );	sr_nz(cpu->a); incpc(); break;
		// TODO Verify these are correct
		case 0xE1: sbc( deref( deref( fetch() + cpu->x ) ) );	sr_nz(cpu->a); incpc(); break;
		case 0xF1: sbc( deref( deref( fetch() + cpu->y ) ) );	sr_nz(cpu->a); incpc(); break;

		// INC/DEC
		case 0xE6: ram->ram[ fetch() ] += 1;	incpc();	break;
		case 0xF6: ram->ram[ fetch() + cpu->x ] += 1;	incpc();	break;
		case 0xEE: ram->ram[ fetch16() ] += 1;	incpc();	break;
		case 0xFE: ram->ram[ fetch16() + cpu->x ] += 1;	incpc();	break;

		case 0xC8: cpu-> y += 1; incpc(); sr_nz(cpu->y); break;
		case 0xE8: cpu-> x += 1; incpc(); sr_nz(cpu->x); break;

		// Bitwise ---
		// AND
		case 0x29: and( fetch() );								sr_nz(cpu->a); incpc(); break;
		case 0x25: and( deref( fetch() ) );						sr_nz(cpu->a); incpc(); break;
		case 0x35: and( deref( fetch() + cpu->x ) );			sr_nz(cpu->a); incpc(); break;
		case 0x2D: and( deref( fetch16() ) ); sr_nz(cpu->x);	incpc(); break;
		case 0x3D: and( deref( fetch16() + cpu->x ) );			sr_nz(cpu->a); incpc(); break;
		case 0x39: and( deref( fetch16() + cpu->y ) );			sr_nz(cpu->a); incpc(); break;
		case 0x21: and( deref( deref( fetch() + cpu->x ) ) );	sr_nz(cpu->a); incpc(); break;
		case 0x31: and( deref( deref( fetch() + cpu->y ) ) );	sr_nz(cpu->a); incpc(); break;

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
		case 0x0A: cpu->a = cpu->a << 1 ; incpc(); break;
		case 0x06: asl( ( fetch() ) ); incpc(); break;
		case 0x16: asl( ( fetch() + cpu->x ) ); incpc(); break;
		case 0x0E: asl( ( fetch16() ) ); incpc(); break;
		case 0x1E: asl( ( fetch16() + cpu->x ) ); incpc(); break;

		// LSR
		// TODO Move memory, not accumulator
		// TODO make sure zp/similar offsets are WRAPPED to 8-bits!
		case 0x4A: cpu->a = cpu->a >> 1; incpc(); break;
		case 0x46: lsr( fetch() ); incpc(); break;
		case 0x56: lsr( fetch() + cpu->x ); incpc(); break;
		case 0x4E: lsr( fetch16() ); incpc(); break;
		case 0x5E: lsr( fetch16() + cpu->x ); incpc(); break;

		// Jump/branch ---
		case 0x4C: ldpc( fetch16() );				break;
		case 0x6C: ldpc( deref( fetch16() ) );		break;
		case 0x20: push16( cpu->pc + 3 ); ldpc( fetch16() );	break;
		case 0xF0: ( cpu->sr.bits.z ) ? ( ldpc( cpu->pc + (int8_t)fetch() ) ) : ( 0 ); incpc(); incpc(); break;
		case 0xD0: ( !cpu->sr.bits.z ) ? ( ldpc( cpu->pc + (int8_t)fetch() ) ) : ( 0 ); incpc(); incpc(); break;
		case 0xB0: ( cpu->sr.bits.c ) ? ( ldpc( cpu->pc + (int8_t)fetch() ) ) : ( 0 ); incpc(); incpc(); break;
		case 0x90: ( !cpu->sr.bits.c ) ? ( ldpc( cpu->pc + (int8_t)fetch() ) ) : ( 0 ); incpc(); incpc(); break;

		// Comparison ---
		case 0xC9: cmp( cpu->a, fetch() );						incpc(); break;
		case 0xC5: cmp( cpu->a, deref( fetch() ) );				incpc(); break;
		case 0xD5: cmp( cpu->a, deref( fetch() + cpu->x ) );	incpc(); break;
		case 0xCD: cmp( cpu->a, deref( fetch16() ) );			incpc(); break;
		case 0xDD: cmp( cpu->a, deref( fetch16() + cpu->x ) );	incpc(); break;
		case 0xD9: cmp( cpu->a, deref( fetch16() + cpu->x ) );	incpc(); break;
		case 0xC1: cmp( cpu->a, deref( deref( fetch() + cpu->x ) ) );	incpc(); break;
		case 0xD1: cmp( cpu->a, deref( deref( fetch() + cpu->y ) ) );	incpc(); break;

		// Return ---
		case 0x60: pull16( &cpu->pc ); break;

		// Misc ---
		case 0xEA: nop();			incpc();	break;
		case 0x00: brk(); 			incpc();	break;
		default: incpc();						break;
	}
}
