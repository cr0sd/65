AS65= xa
AS65FLAGS= -C

OBJS= nes.nes asciitest.nes asl.nes

all: $(OBJS)
.a65.nes:
	$(AS65) $(AS65FLAGS) $*.a65 -o $*.nes
	cp $*.nes ..
clean:
	$(RM) $(OBJS)
.SUFFIXES: .a65 .nes
