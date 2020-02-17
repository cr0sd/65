AS65= xa
AS65FLAGS= -C

OBJS= nes.nes asciitest.nes

all: $(OBJS)
.a65.nes:
	$(AS65) $(AS65FLAGS) $*.a65 -o $*.nes
clean:
	$(RM) $(OBJS)
.SUFFIXES: .a65 .nes
