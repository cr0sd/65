AS65= xa
AS65FLAGS= -C

PROG= 65
OBJS= 65.o cpu.o ram.o rom.o disasm.o

CFLAGS = -Wfatal-errors
LDFLAGS += -lncurses

$(PROG): $(OBJS)
	$(CC) $(OBJS) -o $(PROG) $(CFLAGS) $(LDFLAGS)
test:
	make -C test
clean:
	$(RM) *.o $(PROG) *.nes
	make clean -C test
.SUFFIXES: .nes .o65 .a65
.PHONY: all clean test
