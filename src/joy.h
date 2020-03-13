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

#define JOY_A		'z'
#define JOY_B		'x'
#define JOY_SELECT	'a'
#define JOY_START	's'

typedef struct joy_t
{
	uint16_t mem_addr;
	pthread_mutex_t mut;

	// Buttons
	union
	{
		uint8_t reg;
		struct
		{
			int up:1;
			int down:1;
			int right:1;
			int left:1;
			int a:1;
			int b:1;
			int select:1;
			int start:1;
		}bits;
	}buttons;

}joy_t;

joy_t*joy_init(uint16_t addr,int n);
void*joy_thread_update(void*d);
void joy_del(joy_t*joy);
void joy_update_ram(joy_t*joy,ram_t*ram);
