# ELF Shenanigans

This repo contains sample code for my two blog posts: [A Simple ELF](https://4zm.org/2024/12/25/a-simple-elf.html) and [ELF Shenanigans](https://4zm.org/2024/12/25/git-shenanigans.html) (for the XMAS Special).

## XMAS Special

Let's have some fun with linker scripts, ANSI codes, and emojis!

![objdump](xmas.gif)

The program works, and is loaded on address `Dec25`. And when you run `objdump` you get a fun surprise...

```
MEMORY {
  XMAS (rx) : ORIGIN = 0xDEC25000, LENGTH = 0x1000
}

SECTIONS
{
  "🎄 ^[[31;49m▓▒░^[[0m ^[[95;1;5m🌟^[[0m ^[[31m░▒▓^[[92;41;1mXMAS^[[31;49m▓▒░^[[0m ^[[95;1;5m🌟^[[0m ^[[31;49m░▒▓^[[0m 🎄" : {
    *(.text*)
  } > XMAS
}

ENTRY(xmas)
```

If you want to dig in to some more details about how all this works, my blog post "[A Simple ELF](https://4zm.org/2024/12/25/a-simple-elf.html)" might be helpful.

What other fun things can you come up with? Multi-line (ie. multi segment) ASCII art? Or hiding text using other ANSI codes? Let me know!

## A Simple ELF

These are a few examples of peeling away complexity from my blog post [A Simple ELF](https://4zm.org/2024/12/25/a-simple-elf.html):

```
$ make hello
$ make hello-nostd
$ make hello-nostd-nopie
$ make hello-data
```

In the end, we arrive at:

```
$ objdump -t -h ./build/hello-data

./build/hello-data:     file format elf64-x86-64

Sections:
Idx Name          Size      VMA               LMA               File off  Algn
  0 📜 .text    0000005c  00000000c0de0000  00000000c0de0000  00001000  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  1 📦 .data    00000008  00000000feed0000  00000000feed0000  00003000  2**3
                  CONTENTS, ALLOC, LOAD, DATA
  2 📁 .bss     00000008  00000000feed0008  00000000feed0008  00003008  2**3
                  ALLOC
  3 🧊 .rodata  00000013  00000000dead0000  00000000dead0000  00002000  2**4
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
SYMBOL TABLE:
0000000000000000 l    df *ABS*	0000000000000000 hello-data.c
00000000c0de002f g     F 📜 .text	000000000000002d startup
00000000feed0000 g     O 📦 .data	0000000000000008 length
00000000dead0000 g     O 🧊 .rodata	0000000000000013 message
00000000c0de0000 g     F 📜 .text	000000000000002f main
00000000feed0008 g     O 📁 .bss	0000000000000008 status
```
