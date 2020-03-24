include ../include.mk

#AS65		= xa
OBJS		= asciitest.nes vram.nes div.nes int2ascii.nes

all: $(OBJS)
%.nes: %.a65
	@echo "  AS65	$*.nes"
	@$(AS65) -C $*.a65 -o $*.nes
clean:
	@echo "  RM	$(OBJS)"
	@$(RM) $(OBJS)
	@$(RM) *.s *.o6
