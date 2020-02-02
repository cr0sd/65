A65= xa

PROG= 65
OBJS= 65.o cpu.o ram.o rom.o

TESTDIR= tests
TESTOBJS= nes.nes

CFLAGS= -Wfatal-errors
CFLAGS= -lncurses

$(PROG): $(OBJS)
	$(CC) $(OBJS) -o $(PROG) $(CFLAGS) $(LDFLAGS)
tests: $(foreach x,$(TESTOBJS),$(TESTDIR)/$(x))
.a65.nes:
	$(A65) $*.a65 -o $*.nes
clean:
	$(RM) *.o $(TESTDIR)/*.nes $(PROG) $(TESTOBJS)
.SUFFIXES: .nes .o65 .a65
.PHONY: all clean tests
