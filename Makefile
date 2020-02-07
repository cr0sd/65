AS65= xa
AS65FLAGS= -C

PROG= 65
OBJS= 65.o cpu.o ram.o rom.o disasm.o

TESTDIR= test
TESTOBJS= nes.nes

CFLAGS = -Wfatal-errors
LDFLAGS += -lncurses

$(PROG): $(OBJS)
	$(CC) $(OBJS) -o $(PROG) $(CFLAGS) $(LDFLAGS)
test: $(foreach x,$(TESTOBJS),$(TESTDIR)/$(x))
	cp $(TESTDIR)/nes.nes .
.a65.nes:
	$(AS65) $(AS65FLAGS) $*.a65 -o $*.nes
clean:
	$(RM) *.o $(TESTDIR)/*.nes $(PROG) $(TESTOBJS)
.SUFFIXES: .nes .o65 .a65
.PHONY: all clean tests
