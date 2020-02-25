AS65= xa
AS65FLAGS= -C

OBJS= nes.nes asciitest.nes asl.nes

all: $(OBJS)
	@cp $(OBJS) ..
.a65.nes:
	@echo "AS65	$*.nes"
	@$(AS65) $(AS65FLAGS) $*.a65 -o $*.nes
clean:
	@echo "RM	$(OBJS)"
	@$(RM) $(OBJS)
.SUFFIXES: .a65 .nes
