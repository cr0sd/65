default:
	@$(MAKE) -C src
	@mkdir -p bin
	@cp -p src/65 bin
all:
	@$(MAKE) -C src all
	@mkdir -p bin
	@cp -p src/65 src/65v src/65sdl bin
test:
	@$(MAKE) -C src test
	@mkdir -p test
	@cp -p src/test/*.nes test
clean:
	@$(MAKE) -C src clean
	@$(RM) bin/65 bin/65v bin/65sdl
