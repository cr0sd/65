# Makefile for lib65 + 65 simulator/debugger/disassembler
# Use `make help` to see targets

include include.mk

CFLAGS			+= -Wfatal-errors
LDFLAGS			+= -pthread -lpthread -lportaudio
LIB				= lib65.a
OBJS			= cpu.o ram.o rom.o joy.o ppu.o

all: 65db 65da fes test
help:
	@echo "usage: make [65db|65da|fes|lib|test|clean]"
65db: 65db.o 65db_disasm.o $(LIB)
	@echo "  CC	$@"
	@$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)
65da: 65da.o 65da_disasm.o $(LIB)
	@echo "  CC	$@"
	@$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)
fes: fes.o ppu.o sdl.o $(LIB)
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
	@echo "  RM	65db 65da fes *.o *.nes $(LIB)"
	@$(RM) *.o 65db 65da fes *.nes $(LIB)
	@echo "  RM	test/*.nes"
	@$(RM) test/*.nes
.PHONY: all clean test
