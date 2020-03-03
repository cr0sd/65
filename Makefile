CFLAGS	= -Wfatal-errors
LDFLAGS	+= -lncurses -lpthread -pthread
RM		= rm -f # for BSDmake
PROG	= 65
OBJS	= cpu.o ram.o rom.o disasm.o joy.o vis.o

$(PROG): $(OBJS) $(PROG).o
	@echo "CC	$@"
	@$(CC) $@.o $(OBJS) -o $@ $(CFLAGS) $(LDFLAGS)
all: $(PROG) test 65v
65v: $(OBJS) 65v.o
	@echo "CC	$@"
	@$(CC) $@.o $(OBJS) -o $@ $(CFLAGS) $(LDFLAGS)
test:
	@make -C test
.c.o:
	@echo "CC	$*.o"
	@$(CC) -c $*.c $(CFLAGS) $(LDFLAGS)
clean:
	@echo "RM	$(PROG) 65v *.o *.nes"
	@$(RM) *.o $(PROG) 65v *.nes
	@echo "RM	test/*.nes"
	@$(RM) test/*.nes
.SUFFIXES: .nes .o65 .a65 .c .o
.PHONY: all clean test
