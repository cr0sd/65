CC65		= cc65
CCAS65		= asmx
AS65		= xa
RM			= rm -f # for BSD
OBJS		= nes.nes asciitest.nes ctest.nes vram.nes

all: checks $(OBJS)
	@cp $(OBJS) ..
checks:
	@echo "Checking for $(CC65)..." `which $(CC65)`
	@echo "Checking for $(AS65)..." `which $(AS65)`
	@echo "Checking for $(CCAS65)..." `which $(CCAS65)`
.a65.nes:
	@echo "AS65	$*.nes"
	@$(AS65) -C $*.a65 -o $*.nes
.c65.nes:
	@echo "CC65	$*.nes"
	@$(CC65) $*.c65
	@-$(CCAS65) -C 6502 -b 8000-10000 -o $*.o65 $*.s
	@cat ines_header $*.o65 > $*.nes
	@$(RM) $*.o65 $*.s
.c65.a65:
	@echo "CC65	$*.a65"
	@$(CC65) $*.c65 -o $*.a65
clean:
	@echo "RM	$(OBJS)"
	@$(RM) $(OBJS)
	@$(RM) *.s *.o65
.SUFFIXES: .a65 .nes .c65
