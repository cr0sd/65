#pragma once
#include"65.h"
#include"rom.h"
#include"ram.h"
#include"cpu.h"

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
// 1975, baby!

typedef struct ram_t ram_t;

typedef struct cpu_t
{
	uint16_t pc;		// Program counter
	uint8_t a;		// Accumulator
	uint8_t x;
	uint8_t y;

	union			// Status register
	{
		uint8_t reg;	// Entire 8-bit register
		struct
		{
			int8_t n:1;	// Negative
			int8_t v:1;	// Overflow
			int8_t _:1;	// Ignored
			int8_t b:1;	// Break
			int8_t d:1;	// Decimal (BCD)
			int8_t i:1;	// Interrupt (enable/disable)
			int8_t z:1;	// Zero
			int8_t c:1;	// Carry
		}bits;			// Access individual bit flags
	}sr;

	uint8_t sp;		// Stack pointer
}cpu_t;

// Micro-instructions ---------------------------
// Ex: lda $1f : lda( fetch() )
#ifdef __cpu
#	undef __cpu
#endif

// General purpose "micro-insns"/macros
#define __cpu cpu
#define fetch()		(ram->ram[cpu_fetch(__cpu)])		// Get immediate binary value
#define fetch16()	( fetch() | (fetch()<<8) )		// Get immediate 16-bit binary value

// Addressing mode "micro-insns"
#define imm		fetch
#define imm16	fetch16						// Get immediate 16-bit binary value
#define zp		fetch					// Get value at $0000 + x
#define ab		imm16						// Get 16-bit address
#define ind()	ram_indirect_address(ram,fetch16())

#define xidx(m)	__cpu->x+m					// Get value at y + (m)
#define yidx(m)	__cpu->y+m					// Get value at x + (m)

// Peek (without fetching)
#define imm_pk(x)	ram->ram[__cpu->pc+x]	// Peek immediate
#define imm16_pk(x) ( imm_pk(x) | (imm_pk(x+1)<<8) )		// Peek immediate 16-bit

// Move micro-insns
#define lda(x)	__cpu->a=(x)
#define ldx(m)	__cpu->x=m
#define ldy(x)	__cpu->y=(x)
#define ldpc(x)	__cpu->pc=(x)
#define nop()
#define brk()

#define sta(x) ram->ram[x]=__cpu->a

// Arithmetic micro-insns
#define incpc(x)	__cpu->pc+=x

// Status register micro-insns
#define sr_n(x)	__cpu->sr.bits.n=(x<0) 		// Negative
#define sr_v(x)	__cpu->sr.bits.v=?			// Overflow
#define sr_b(x)	__cpu->sr.bits.b=?			// Break
#define sr_d(x)	__cpu->sr.bits.d=?			// Decimal (BCD)
#define sr_i(x)	__cpu->sr.bits.i=x			// Interrupt (enable/disable)
#define sr_z(x)	__cpu->sr.bits.z=(x==0)		// Zero
#define sr_c(x)	__cpu->sr.bits.c=?			// Carry
#define sr_nz(x)	sr_n(x);sr_z(x)
// ----------------------------------------------

cpu_t*cpu_init(void);
void cpu_exec(cpu_t*cpu,ram_t*ram);
uint16_t cpu_fetch(cpu_t*cpu);
