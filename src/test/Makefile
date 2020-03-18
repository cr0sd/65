AS65		= xa
OBJS		= nes.nes asciitest.nes vram.nes pi.nes div.nes
RM			= rm -f # for BSD

all: $(OBJS)
%.nes: %.a65
	@echo "  AS65	$*.nes"
	@$(AS65) -C $*.a65 -o $*.nes
clean:
	@echo "  RM	$(OBJS)"
	@$(RM) $(OBJS)
	@$(RM) *.s *.o6
