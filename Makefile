all:
	@echo "$(OS)"
	@$(MAKE) -C src
	@mkdir -p bin test
	@echo "  CP	bin/65db bin/fes"
	@-cp -p src/65db src/fes bin
	@echo "  CP	test/*.nes"
	@-cp -p src/test/*.nes test
clean:
	@$(MAKE) -C src clean
	@echo "  RM	bin/65db bin/fes test/*.nes"
	@$(RM) bin/65db bin/fes test/*.nes
.PHONY: all clean
