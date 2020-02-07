#include"disasm.h"
#include"stdlib.h"

// Print instruction helper function
static void pi(cpu_t*cpu,ram_t*ram,int n,const char*fmt,...)
{

	// Print binary hexdump
	if(n==1)
		printw( "\t%02x\t\t", ram->ram[cpu->pc] );
	else if(n==2)
		printw( "\t%02x %02x\t\t", ram->ram[cpu->pc],
			ram->ram[cpu->pc+1] );
	else if(n==3)
		printw( "\t%02x %02x %02x\t", ram->ram[cpu->pc],
			ram->ram[cpu->pc+1], ram->ram[cpu->pc+2] );

	// Print rest of vararg stuff (insn name, operands)
	va_list list;
	va_start(list,fmt);
	vwprintw(win,fmt,list);
	va_end(list);
}

// Print disassembly
void da_print_disassembly(cpu_t*cpu,ram_t*ram)
{
	int y=8;
	cpu_t*cpuc=alloca(sizeof(cpu_t));

	// Create copy of cpu
	if(!cpuc)
	{
		puterr("%s: Failed to allocate copy of CPU\n",__func__);
		return;
	}
	memcpy(cpuc,cpu,sizeof(cpu_t));

	// Disassemble 12 lines
	for(int i=0; i<12; ++i)
	{

		// Print offset
		attron(COLOR_PAIR(5));
		mvprintw(y,0,"%04x",cpuc->pc);
		attroff(COLOR_PAIR(5));

		// Opcodes
		switch(ram->ram[cpuc->pc])
		{

		case 0xA0: // ldy imm
			pi( cpuc, ram, 2, "ldy #$%02x", ram->ram[cpuc->pc+i+1] );
			++cpuc->pc;
			goto clear_rest;

		case 0xA5: // ldy imm
			pi( cpuc, ram, 2, "lda zp $%02x", ram->ram[cpuc->pc+i+1] );
			++cpuc->pc;
			goto clear_rest;

		case 0xA9: // lda #
			pi( cpuc, ram, 2, "lda #$%02x", ram->ram[cpuc->pc+i+1] );
			++cpuc->pc;
			goto clear_rest;

		case 0xA2: // ldx imm
			pi( cpuc, ram, 2, "ldx #$%02x", ram->ram[cpuc->pc+i+1] );
			++cpuc->pc;
			goto clear_rest;

		case 0x4C: // jmp abs
			pi( cpuc, ram, 3, "jmp abs $%04x", ram->ram[cpuc->pc+1] | (ram->ram[cpuc->pc+2]<<8) );
			cpuc->pc+=2;
			goto clear_rest;

		case 0x6C: // jmp ind
			pi( cpuc, ram, 3, "jmp ind (%04x) <%04x>",
				ram->ram[cpuc->pc+1] | (ram->ram[cpuc->pc+2]<<8),
				ram->ram[ ram->ram[ ram->ram[ cpuc->pc+1] |
					(ram->ram[cpuc->pc+2]<<8) ] ] );
			cpuc->pc+=2;
			goto clear_rest;

		case 0xEA: // nop
			pi( cpuc, ram, 1, "nop");
			goto clear_rest;

		case 0x00: // brk
			pi( cpuc, ram, 1, "brk");
			goto clear_rest;

		clear_rest:
			printw("                     ");
			break;

		default:
			mvprintw(y,0,"-                                         ");
		}

		// Next line of disassembly
		cpuc->pc+=1;
		++y;
	}
}
