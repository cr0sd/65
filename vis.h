#pragma once
#include"65.h"
#include"ram.h"
#include"cpu.h"

// Curses-based display of VRAM

#define VIS_WIDTH	20
#define VIS_HEIGHT	8

int vis_display(cpu_t*cpu,ram_t*ram);
