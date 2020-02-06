#include"disasm.h"

void da_print_disassembly(cpu_t*cpu,ram_t*ram)
{
	int y=8;

	for(int i=0; i<12; ++i)
	{

		// Print offset
		attron(COLOR_PAIR(3));
		mvprintw(y,0,"%04x",cpu->pc+i);
		attroff(COLOR_PAIR(3));

		// Opcodes
		switch(ram->ram[cpu->pc+i])
		{

		case 0xa0: // ldy imm
			printw( "\t%02x %02x", ram->ram[cpu->pc+i], ram->ram[cpu->pc+i+1] );
			printw( "\tldy $%02x", ram->ram[cpu->pc+i+1] );
			++i;
			goto clear_rest;

		case 0xa2: // ldx imm
			printw( "\t%02x %02x", ram->ram[cpu->pc+i], ram->ram[cpu->pc+i+1] );
			printw( "\tldx $%02x", ram->ram[cpu->pc+i+1] );
			++i;
			goto clear_rest;

		case 0x4C: // jmp
			printw( "\tjmp");
			//printw( "\t%02x %02x", ram->ram[cpu->pc+i], ram->ram[cpu->pc+i+1] );
			//printw( "\tldx $%02x", ram->ram[cpu->pc+i+1] );
			++i;
			++i;
			goto clear_rest;

		case 0xea: // nop
			printw( "\t%02x", ram->ram[cpu->pc+i], ram->ram[cpu->pc+i+1] );
			printw( "\tnop" );
			goto clear_rest;

		clear_rest:
			printw("                  ");
			break;

		default:
			mvprintw(y,0,"-                               ");
		}
		// Next line of disassembly
		++y;
	}
}
