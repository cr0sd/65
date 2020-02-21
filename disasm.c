#include"disasm.h"
#include"stdlib.h"
#include"stdarg.h"

static int oper[8];

// Print instruction helper function
static void pi(cpu_t*cpu,ram_t*ram,int n,const char*fmt,...)
{

	#undef __cpu
	#define __cpu cpu

	//printw("\t(pc:$%04X)\t",cpu->pc);

	// pre calculate operands (because ABI is
	// reversing the evaluation of stack-sensitive
	// values:
	int oper[3];
	oper[0] = ram->ram[ cpu->pc ];

	// Print binary representation
	if(n==1)
	{
		printw( "\t%02X\t\t", oper[0] );
	}
	else if(n==2)
	{
		oper[1]=fetch();
		printw( "\t%02X %02X\t\t", oper[0], oper[1] );
	}
	else if(n==3)
	{
		oper[1]=fetch();
		oper[2]=fetch();
		printw( "\t%02X %02X %02X\t", oper[0], oper[1], oper[2] );
	}
	else if(n==0)
		;

	// Print rest of vararg stuff (insn name, operands)
	va_list list;
	va_start(list,fmt);
	vwprintw(win,fmt,list);
	va_end(list);

	//printw(" (pc:$%04X)\t",cpu->pc);
}

#define p0(...) pi(cpuc,ram,0,__VA_ARGS__)
#define p1(...) pi(cpuc,ram,1,__VA_ARGS__)
#define p2(...) pi(cpuc,ram,2,__VA_ARGS__)
#define p3(...) pi(cpuc,ram,3,__VA_ARGS__)
#define end() goto clear_rest

// Print disassembly
void da_print_disassembly(cpu_t*cpu,ram_t*ram)
{
	// Set 'mode' to this copy of cpu
	#undef __cpu
	#define __cpu cpuc

	int y=9;	// Which line to draw on
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
		mvprintw(y,0,"%04X",cpuc->pc);
		attroff(COLOR_PAIR(5));

		// Opcodes
		switch(ram->ram[cpuc->pc])
		{

		// Move/transfer
		// Load a
		case 0xA1: p2( "lda ($%02X,x)", imm_pk(1) ); end();
		case 0xB1: p2( "lda ($%02X),y", imm_pk(1) ); end();
		case 0xA5: p2( "lda zp $%02X", imm_pk(1) ); end();
		case 0xA9: p2( "lda #$%02X", imm_pk(1) ); end();
		case 0xAD: p3( "lda abs $%04X", imm16_pk(1) );  end();
		case 0xB5: p2( "lda zp $%02X,x", imm_pk(1) ); end();
		case 0xB9: p3( "lda abs $%04X,y", imm16_pk(1) ); end();
		case 0xBD: p3( "lda abs $%04X,x", imm16_pk(1) ); end();

		// Store a
		case 0x85: p2( "sta zp $%02X", imm_pk(1) ); end();
		case 0x95: p2( "sta zp $%02X,x", imm_pk(1) ); end();
		case 0x8D: p3( "sta abs $%04X", imm16_pk(1) ); end();
		case 0x9D: p3( "sta abs $%04X,x", imm16_pk(1) ); end();
		case 0x99: p3( "sta abs $%04X,y", imm16_pk(1) ); end();
		case 0x81: p2( "sta ind ($%02X,x)", imm_pk(1) ); end();
		case 0x91: p2( "sta ind ($%02X),y", imm_pk(1) ); end();

		// Store x
		case 0x86: p2( "stx zp $%02X", imm_pk(1) ); end();
		case 0x96: p2( "stx zp $%02X,y", imm_pk(1) ); end();
		case 0x8E: p3( "stx abs $%04X", imm16_pk(1) ); end();
		// Load x
		case 0xA2: p2( "ldx #$%02X", imm_pk(1) ); end();
		case 0xA6: p2( "ldx zp $%02X", imm_pk(1) ); end();
		case 0xB6: p2( "ldx zp $%02X,y", imm_pk(1) ); end();
		case 0xAE: p3( "ldx abs $%04X", imm16_pk(1) ); end();
		case 0xBE: p3( "ldx abs $%04X,y", imm16_pk(1) ); end();

		// Store y
		case 0x84: p2( "sty zp $%02X", imm_pk(1) ); end();
		case 0x94: p2( "sty zp $%02X,x", imm_pk(1) ); end();
		case 0x8C: p3( "sty abs $%04X", imm16_pk(1) ); end();
		// Load y
		case 0xA0: p2( "ldy #$%02X", imm_pk(1) ); end();
		case 0xA4: p2( "ldy zp $%02X", imm_pk(1) ); end();
		case 0xB4: p2( "ldy zp $%02X,x", imm_pk(1) ); end();
		case 0xAC: p3( "ldy abs $%04X", imm16_pk(1) ); end();
		case 0xBC: p3( "ldy abs $%04X,x", imm16_pk(1) ); end();

		// Transfer
		case 0xA8: p1( "tay" ); end();
		case 0xBA: p1( "tsx" ); end();
		case 0x8A: p1( "txa" ); end();
		case 0x9A: p1( "txs" ); end();
		case 0x98: p1( "tya" ); end();

		// Arithmetic
		case 0x65: p2( "adc zp $%02X", imm_pk(1) ); end();
		case 0x69: p2( "adc #$%02X", imm_pk(1) ); end();
		case 0x75: p2( "adc zp $%02X,x", imm_pk(1) ); end();
		case 0x6D: p3( "adc abs $%04X", imm16_pk(1) ); end();
		case 0x7D: p3( "adc abs $%04X,x", imm16_pk(1) ); end();
		case 0x79: p3( "adc abs $%04X,y", imm16_pk(1) ); end();
		// TODO fix these two:
		case 0x61: p2( "adc ind ($%02X,x)", imm_pk(1) ); end();
		case 0x71: p2( "adc ind ($%02X),y", imm_pk(1) ); end();

		// INC/DEC
		case 0xE6: p2( "inc zp $%02X", imm_pk(1) ); end();
		case 0xF6: p2( "inc zp $%02X,x", imm_pk(1) ); end();
		case 0xEE: p3( "inc abs $%04X", imm16_pk(1) ); end();
		case 0xFE: p3( "inc abs $%04X,x", imm16_pk(1) ); end();

		case 0xC8: p1( "iny" ); end();
		case 0xE8: p1( "inx" ); end();

		// Bitwise
		// AND
		case 0x29: p2( "and #$%02X", imm_pk(1) ); end();
		case 0x25: p2( "and zp $%02X", imm_pk(1) ); end();
		case 0x35: p2( "and zp $%02X,x", imm_pk(1) ); end();
		case 0x2D: p3( "and abs $%04X", imm16_pk(1) ); end();
		case 0x3D: p3( "and abs $%04X,x", imm16_pk(1) ); end();
		case 0x39: p3( "and abs $%04X,y", imm16_pk(1) ); end();
		// TODO Verify these work ($LL,x) & ($LL),y
		case 0x21: p2( "and zp ($%02X,x)", imm_pk(1) ); end();
		case 0x31: p2( "and zp ($%02X),y", imm_pk(1) ); end();

		// EOR
		case 0x49: p2( "eor #$%02X", imm_pk(1) ); end();
		case 0x45: p2( "eor zp $%02X", imm_pk(1) ); end();
		case 0x55: p2( "eor zp $%02X,x", imm_pk(1) ); end();
		case 0x4D: p3( "eor abs $%04X", imm16_pk(1) ); end();
		case 0x5D: p3( "eor abs $%04X,x", imm16_pk(1) ); end();
		case 0x59: p3( "eor abs $%04X,y", imm16_pk(1) ); end();
		// TODO Verify these work ($LL,x) & ($LL),y
		case 0x41: p2( "eor zp ($%02X,x)", imm_pk(1) ); end();
		case 0x51: p2( "eor zp ($%02X),y", imm_pk(1) ); end();

		// ORA
		case 0x09: p2( "ora #$%02X", imm_pk(1) ); end();
		case 0x05: p2( "ora zp $%02X", imm_pk(1) ); end();
		case 0x15: p2( "ora zp $%02X,x", imm_pk(1) ); end();
		case 0x0D: p3( "ora abs $%04X", imm16_pk(1) ); end();
		case 0x1D: p3( "ora abs $%04X,x", imm16_pk(1) ); end();
		case 0x19: p3( "ora abs $%04X,y", imm16_pk(1) ); end();
		// TODO Verify these work ($LL,x) & ($LL),y
		case 0x01: p2( "ora zp ($%02X,x)", imm_pk(1) ); end();
		case 0x11: p2( "ora zp ($%02X),y", imm_pk(1) ); end();

		// ASL
		case 0x0A: p1( "asl a" ); end();
		case 0x06: p2( "asl zp $%02X", imm_pk(1) ); end();
		case 0x16: p2( "asl zp $%02X,x", imm_pk(1) ); end();
		case 0x0E: p3( "asl abs $%04X", imm16_pk(1) ); end();
		case 0x1E: p3( "asl abs $%04X,x", imm16_pk(1) ); end();

		// LSR
		case 0x4A: p1( "lsr a" ); end();
		case 0x46: p2( "lsr zp $%02X", imm_pk(1) ); end();
		case 0x56: p2( "lsr zp $%02X,x", imm_pk(1) ); end();
		case 0x4E: p3( "lsr abs $%04X", imm16_pk(1) ); end();
		case 0x5E: p3( "lsr abs $%04X,x", imm16_pk(1) ); end();

		// Jump/branch
		case 0x4C: p3( "jmp abs $%04X", imm16_pk(1) ); end();
		case 0x6C: p3( "jmp ind ($%04X) <%04X>", imm16_pk(1), *(uint16_t*)(ram->ram+imm16_pk(1)) ); end();
		case 0xEA: p1( "nop" ); end();
		case 0x00: p1( "brk" ); end();

		clear_rest:
			printw("                         ");
			break;

		default:
			mvclr(y,0);
			mvprintw(y,0,"-");
			incpc();
		}

		// Next line of disassembly
		incpc();
		++y;
	}
}
