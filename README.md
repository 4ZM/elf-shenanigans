# ELF Shenanigans

This repo contains sample code for my two blog posts: [A Simple ELF](https://4zm.org/2024/12/25/a-simple-elf.html) and [ELF Shenanigans](https://4zm.org/2024/12/25/git-shenanigans.html) (for the XMAS Special).

## XMAS Special

Let's have some fun with linker scripts, ANSI codes and emojis!

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

If you want to dig in to some more details about how all this works, my other article "[A Simple ELF](https://4zm.org/2024/12/25/a-simple-elf.html)" might be helpful.

What other fun things can you come up with? Multi-line (ie. multi segment) ASCII art? Or hiding text using other ANSI codes? Let me know!
