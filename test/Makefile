CC65		= cc65
CCAS65		= asmx -C 6502 -b 8000-10000
AS65		= xa -C
RM			= rm -f # for BSD
OBJS		= nes.nes asciitest.nes asl.nes ctest.nes

all: $(OBJS)
	@cp $(OBJS) ..
.a65.nes:
	@echo "AS65	$*.nes"
	@$(AS65) $(AS65FLAGS) $*.a65 -o $*.nes
.c65.nes:
	@echo "CC65	$*.nes"
	@$(CC65) $*.c65
	@-$(CCAS65) -b 0-10000 -o $*.o65 $*.s
	@cat ines_header $*.o65 > $*.nes
	@$(RM) $*.o65 $*.s
clean:
	@echo "RM	$(OBJS)"
	@$(RM) $(OBJS)
	@$(RM) *.s *.o65
.SUFFIXES: .a65 .nes .c65
