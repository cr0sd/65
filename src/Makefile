# Makefile for lib65 + 65 simulator/debugger/disassembler
# Use `make help` to see targets

include include.mk

CFLAGS			= -Wfatal-errors
LDFLAGS			= -pthread
LIB				= lib65.a
OBJS			= cpu.o ram.o rom.o joy.o
RM				= rm -f # for BSDmake

all: 65 65sdl test
help:
	@echo "usage: make [65|65sdl|lib|test]"
65: 65.o 65_disasm.o $(LIB)
	@echo "CC	65"
	@$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS) -lncurses
65sdl: 65sdl.o sdl.o $(OBJS_SDL2) $(LIB)
	@echo "CC	65sdl"
	@$(CC) $^ -o $@ $(CFLAGS) $(SDL2_CFLAGS) $(LDFLAGS) $(SDL2_LDFLAGS)
lib: $(LIB)
$(LIB): $(OBJS)
	@echo "AR	$(LIB)"
	@$(AR) mc $(LIB) $(OBJS) 
test:
	@make -C test
%.o: %.c
	@echo "CC	$*.o"
	@$(CC) -c $^ $(CFLAGS) $(SDL2_CFLAGS) $(LDFLAGS) $(SDL2_LDFLAGS)
clean:
	@echo "RM	65 *.o *.nes $(LIB)"
	@$(RM) *.o 65 65sdl *.nes $(LIB)
	@echo "RM	test/*.nes"
	@$(RM) test/*.nes test/config
.PHONY: all clean test
