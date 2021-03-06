#pragma once
#include"65.h"
#include"cpu.h"
#include"rom.h"

#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

// Define RAM struct
// for 16-bit address space
typedef struct ram_t
{
	uint8_t*ram;
}ram_t;

ram_t*ram_init(void);
void ram_del(ram_t*ram);
uint16_t ram_indirect_address(ram_t*ram,uint16_t src);
void ram_asl(ram_t*ram,uint16_t byte);
void ram_lsr(ram_t*ram,uint16_t byte);
