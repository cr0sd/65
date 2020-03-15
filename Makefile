all:
	@$(MAKE) -C src
	@mkdir -p bin test
	@echo "CP	bin/65db bin/65sdl"
	@-cp -p src/65db src/65sdl bin
	@echo "CP	test/*.nes"
	@-cp -p src/test/*.nes test
clean:
	@$(MAKE) -C src clean
	@echo "RM	bin/65db bin/65sdl test/*.nes"
	@$(RM) bin/65db bin/65sdl test/*.nes
.PHONY: all clean
