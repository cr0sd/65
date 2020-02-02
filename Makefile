A65= ../nescom-1.2.0/nescom
LD65= ../nescom-1.2.0/neslink

PROG= 65
OBJS= 65.o cpu.o ram.o rom.o

TESTDIR= tests
TESTOBJS= nes.nes

CFLAGS= -Wfatal-errors
CFLAGS= -lncurses

$(PROG): $(OBJS)
	$(CC) $(OBJS) -o $(PROG) $(CFLAGS) $(LDFLAGS)
tests: $(foreach x,$(TESTOBJS),$(TESTDIR)/$(x))
.o65.nes:
	$(LD65) $*.o65 -fnes -o $*.nes
.a65.o65:
	$(A65) $*.a65 -fo65 -o $*.o65
clean:
	$(RM) *.o $(TESTDIR)/*.o65 $(PROG) $(TESTOBJS)
.SUFFIXES: .nes .o65 .a65
.PHONY: all clean tests
