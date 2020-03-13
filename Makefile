CFLAGS			= -Wfatal-errors
LDFLAGS			+= -lncurses -lpthread -pthread
SDL2_CFLAGS		= `pkg-config --cflags sdl2`
SDL2_LDFLAGS	= `pkg-config --libs sdl2`
RM				= rm -f # for BSDmake
PROG			= 65
OBJS			= cpu.o ram.o rom.o disasm.o joy.o

$(PROG): $(OBJS) $(PROG).o
	@echo "CC	$@"
	@$(CC) $@.o $(OBJS) -o $@ $(CFLAGS) $(LDFLAGS)
all: $(PROG) test 65v 65sdl
65v: $(OBJS) 65v.o vis.o
	@echo "CC	$@"
	@$(CC) $@.o vis.o $(OBJS) -o $@ $(CFLAGS) $(LDFLAGS)
65sdl: $(OBJS) sdl.o 65sdl.o
	@echo "CC	$@"
	@$(CC) 65sdl.o sdl.o $(OBJS) -o $@ $(CFLAGS) $(LDFLAGS) $(SDL2_LDFLAGS) $(SDL2_CFLAGS)
test:
	@make -C test
.c.o:
	@echo "CC	$*.o"
	@$(CC) -c $*.c $(CFLAGS) $(LDFLAGS)
clean:
	@echo "RM	$(PROG) 65v *.o *.nes"
	@$(RM) *.o $(PROG) 65v 65sdl *.nes
	@echo "RM	test/*.nes"
	@$(RM) test/*.nes test/config
.SUFFIXES: .nes .o65 .a65 .c .o
.PHONY: all clean test
