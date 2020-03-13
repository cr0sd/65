CC65		= cc65
CCAS65		= asmx
AS65		= xa
RM			= rm -f # for BSD
OBJS		= nes.nes asciitest.nes ctest.nes vram.nes pi.nes div.nes

all: config $(OBJS)
	@#cp $(OBJS) ..
config:
	@echo "Checking for $(CC65)..."; echo "`which $(CC65)`" > config
	@echo "Checking for $(AS65)..."; echo "`which $(AS65)`" >> config
	@echo "Checking for $(CCAS65)..."; echo "`which $(CCAS65)`" >> config
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
	@$(RM) *.s *.o65 config
.SUFFIXES: .a65 .nes .c65
