#pragma once
#include<ncurses.h>
#include<yaml.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"ram.h"

// TODO: Describe opcodes (preferably in
// well-defined format like YAML) so that
// they can be printed/disassembled programmatically

/* ^^^ For example (as65_def.yml): ^^^ */

		// ldy:
		//   description: load into Y
		//   opcode: 0xBC
		//   bytes: 3
		// pla:
		//   description: pull accum. from stack
		//   opcode: 0x68
		//   bytes: 1
		//   ...

yaml_parser_t parser;
yaml_event_t event;

void da_print_disassembly(cpu_t*cpu,ram_t*ram);
