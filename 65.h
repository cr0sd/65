#pragma once
//#include"cpu.h"
//#include"ram.h"
//#include"rom.h"

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdarg.h>

#define PROG "65"
#define new(x) malloc(sizeof(x))

void puterr(const char*msg,...);
