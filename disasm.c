#include"disasm.h"

void da_print_disassembly(cpu_t*cpu,ram_t*ram)
{
	int y=8;

	for(int i=0;i<4;++i)
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
				break;

			case 0xa2: // ldx imm
				printw( "\t%02x %02x", ram->ram[cpu->pc+i], ram->ram[cpu->pc+i+1] );
				printw( "\tldx $%02x", ram->ram[cpu->pc+i+1] );
				break;

			case 0xea: // nop
				printw( "\t%02x", ram->ram[cpu->pc+i], ram->ram[cpu->pc+i+1] );
				printw( "\tnop" );
				break;

			default:
				mvprintw(y,0,"-                               ");

		}
		++y;
	}
}
