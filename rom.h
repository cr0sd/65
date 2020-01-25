#pragma once

#include"ram.h"

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<fcntl.h>
#include<unistd.h>

// Define ROM struct to contain
// information about loaded NES rom
typedef struct romNES_t
{
	//int fd;				// File descriptor associated with ROM file on host machine
	const char*filepath;	// File name associated with ROM file on host machine
	uint8_t*data;			// ROM loaded into (host) RAM
}rom_t;

void rom_load_file(rom_t*,const char*);
void rom_del(rom_t*rom);
void rom_map(rom_t*rom,ram_t*ram);
