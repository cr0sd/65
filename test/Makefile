AS65= xa
AS65FLAGS= -C

all: nes.nes
.a65.nes:
	$(AS65) $(AS65FLAGS) $*.a65 -o $*.nes
clean:
	$(RM) nes.nes
.SUFFIXES: .a65 .nes
