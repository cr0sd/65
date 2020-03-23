# Makefile for lib65 + 65 simulator/debugger/disassembler
# Use `make help` to see targets

include include.mk

CFLAGS			+= -Wfatal-errors
LDFLAGS			+= -pthread -lpthread
LIB				= lib65.a
OBJS			= cpu.o ram.o rom.o joy.o
RM				= rm -f # for BSDmake

all: 65db 65sdl test
help:
	@echo "usage: make [65db|65sdl|lib|test|clean]"
65db: 65db.o 65db_disasm.o $(LIB)
	@echo "  CC	$@"
	@$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)
65sdl: 65sdl.o sdl.o $(LIB)
	@echo "  CC	$@"
	@$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)
lib: $(LIB)
$(LIB): $(OBJS)
	@echo "  AR	$(LIB)"
	@$(AR) $(ARFLAGS) $(LIB) $(OBJS) 
test:
	@$(MAKE) -C test
%.o: %.c
	@echo "  CC	$*.o"
	@$(CC) -c $^ $(CFLAGS) $(LDFLAGS)
clean:
	@echo "  RM	65db *.o *.nes $(LIB)"
	@$(RM) *.o 65db 65sdl *.nes $(LIB)
	@echo "  RM	test/*.nes"
	@$(RM) test/*.nes
.PHONY: all clean test
