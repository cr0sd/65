#pragma once
#include"65.h"

#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

// Define RAM struct
// for 16-bit address space
typedef struct ram16_t
{
	uint8_t*mem;
}ram_t;

ram_t*ram_init(void);
void ram_del(ram_t*ram);
