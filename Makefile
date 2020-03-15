all:
	@$(MAKE) -C src
	@mkdir -p bin
	@echo "CP	src/65 src/65sdl"
	@-cp -p src/65 src/65sdl bin
	@echo "CP	src/test/*.nes"
	@-cp -p src/test/*.nes test
clean:
	@$(MAKE) -C src clean
	@echo "RM	bin/65 bin/65sdl test/*.nes"
	@$(RM) bin/65 bin/65sdl test/*.nes
.PHONY: all clean
