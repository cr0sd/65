PROG= 65
OBJS= 65.o cpu.o ram.o rom.o

CFLAGS=-Wfatal-errors
CFLAGS=-lncurses

$(PROG):$(OBJS)
	$(CC) $(OBJS) -o $(PROG) $(CFLAGS) $(LDFLAGS)
clean:
	$(RM) *.o $(PROG)
