all:
	@make -C hal/emu uninstall clean all
	@make -C ds uninstall clean all

clean:
	@make -C ds $@
	@make -C hal/emu $@

uninstall: clean
	@make -C ds $@
	@make -C hal/emu $@

unittest: 
	@make -C test clean all

