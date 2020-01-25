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
	int16_t pc;		// Program counter
	int8_t ac;		// Accumulator
	int8_t x;
	int8_t y;

	union			// Status register
	{
		int n:1;	// Negative
		int v:1;	// Overflow
		int _:1;	// Ignored
		int b:1;	// Break
		int d:1;	// Decimal
		int i:1;	// Interrupt (enable/disable)
		int z:1;	// Zero
		int c:1;	// Carry
	}sr;

	int8_t sp;		// Stack pointer
}cpu_t;

cpu_t*cpu_init(void);
void cpu_exec(cpu_t*cpu,ram_t*ram);
