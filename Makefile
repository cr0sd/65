AS65= xa
AS65FLAGS= -C

PROG= 65
OBJS= 65.o cpu.o ram.o rom.o disasm.o

CFLAGS = -Wfatal-errors
LDFLAGS += -lncurses

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
	@echo "RM	*.o $(PROG) *.nes"
	@$(RM) *.o $(PROG) *.nes
	@make clean -C test
.SUFFIXES: .nes .o65 .a65 .c .o
.PHONY: all clean test
