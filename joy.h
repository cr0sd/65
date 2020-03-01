#pragma once
#include"cpu.h"
#include"ram.h"
#include<stdlib.h>
#include<stdint.h>
#include<unistd.h>
#include<ncurses.h>
#include<pthread.h>

#define K_UP	0x81
#define K_DOWN	0x82
#define K_LEFT	0x83
#define K_RIGHT	0x84

typedef struct joy_t
{
	uint16_t mem_addr;
	pthread_mutex_t mut;
	int button;
}joy_t;

joy_t*joy_init(uint16_t addr,int n);
void*joy_thread_update(void*d);
void joy_del(joy_t*joy);
void joy_update_ram(joy_t*joy,ram_t*ram);
