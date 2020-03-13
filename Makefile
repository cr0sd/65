default:
	@$(MAKE) -C src
	@mkdir bin
	@cp src/65 src/65v src/65sdl bin
all:
	@$(MAKE) -C src all
	@mkdir bin
	@cp src/65 src/65v src/65sdl bin
clean:
	@$(MAKE) -C src clean
	@$(RM) bin/65 bin/65v bin/65sdl
