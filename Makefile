PROG= 65
OBJS= 65.o cpu.o ram.o rom.o

CFLAGS=-Wfatal-errors

$(PROG):$(OBJS)
	$(CC) $(OBJS) -o $(PROG) $(CFLAGS) $(LDFLAGS)
clean:
	$(RM) *.o $(PROG)
