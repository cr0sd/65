all:
	@$(MAKE) -C src
	@mkdir -p bin
	@-cp -p src/65 src/65sdl bin
	@-cp -p src/test/*.nes test
clean:
	@$(MAKE) -C src clean
	@$(RM) bin/65 bin/65sdl test/*.nes
.PHONY: all clean
