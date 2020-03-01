CFLAGS	= -Wfatal-errors
LDFLAGS	+= -lncurses
AS65	= xa -C
RM		= rm -f # for BSDmake
PROG	= 65
OBJS	= 65.o cpu.o ram.o rom.o disasm.o joy.o vis.o

$(PROG): $(OBJS)
	@echo "CC	$@"
	@$(CC) $(OBJS) -o $(PROG) $(CFLAGS) $(LDFLAGS)
test:
	@make -C test
all: $(PROG) test
.c.o:
	@echo "CC	$*.o"
	@$(CC) -c $*.c $(CFLAGS) $(LDFLAGS)
clean:
	@echo "RM	$(PROG) *.o *.nes"
	@$(RM) *.o $(PROG) *.nes
	@echo "RM	test/*.nes"
	@$(RM) test/*.nes
.SUFFIXES: .nes .o65 .a65 .c .o
.PHONY: all clean test
