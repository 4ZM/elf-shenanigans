xmas: xmas.c xmas.ld Makefile
	gcc -T xmas.ld -fno-asynchronous-unwind-tables -fno-unwind-tables -nostdlib -no-pie -o $@ $<
