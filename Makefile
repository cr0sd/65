all:
	@echo "$(OS)"
	@$(MAKE) -C src
	@mkdir -p bin test
	@echo "  CP	bin/65db bin/65da bin/fes"
	@-cp -p src/65db src/65da src/fes bin
	@echo "  CP	test/*.nes"
	@-cp -p src/test/*.nes test
65da 65db lib:
	@$(MAKE) -C src $@
clean:
	@$(MAKE) -C src clean
	@echo "  RM	bin/65db bin/65da bin/fes test/*.nes"
	@$(RM) bin/65db bin/65da bin/fes test/*.nes
.PHONY: all clean
