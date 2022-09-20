os-assignment:
	yasm -f elf64 -g dwarf2 -l os.lst os.asm
	gcc os.o -no-pie
	./a.out
