#pragma once
#include"65.h"
#include"rom.h"

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

cpu_t*cpu_init(void);
void cpu_exec(cpu_t*cpu,ram_t*ram);
