A65=../nescom-1.2.0/nescom
LD65=../nescom-1.2.0/neslink

PROG= 65
OBJS= 65.o cpu.o ram.o rom.o

CFLAGS=-Wfatal-errors
CFLAGS=-lncurses

$(PROG):$(OBJS)
	$(CC) $(OBJS) -o $(PROG) $(CFLAGS) $(LDFLAGS)
.o65.nes:
	$(LD65) $*.o65 -f nes -o $*.nes
.a65.o65:
	$(A65) $*.a65 -f o65 -o $*.o65
clean:
	$(RM) *.o *.o65 $(PROG)
.SUFFIXES: .nes .o65 .a65
.PHONY: all rom clean
