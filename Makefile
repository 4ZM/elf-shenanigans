xmas: xmas.c xmas.ld Makefile
	gcc -T xmas.ld -fno-asynchronous-unwind-tables -fno-unwind-tables -nostdlib -no-pie -o build/$@ $<

hello: hello.c Makefile
	gcc -o build/$@ $<

hello-nostd: hello-syscall.c Makefile
	gcc -Wl,-entry=startup -nostdlib -o build/$@ $<

hello-nostd-nopie: hello-syscall.c Makefile
	gcc -no-pie -nostdlib -Wl,-e,startup -Wl,--build-id=none -fcf-protection=none -fno-stack-protector -fno-asynchronous-unwind-tables -fno-unwind-tables -o build/$@ $<

hello-data: hello-data.c Makefile
	gcc -T hello.ld -no-pie -nostdlib -Wl,-e,startup -Wl,--build-id=none -fcf-protection=none -fno-stack-protector -fno-asynchronous-unwind-tables -fno-unwind-tables -o build/$@ $<
