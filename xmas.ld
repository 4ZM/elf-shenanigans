MEMORY {
  XMAS (rx) : ORIGIN = 0xDEC25000, LENGTH = 0x1000
}

SECTIONS
{
  "🎄 [31;49m▓▒░[0m [95;1;5m🌟[0m [31m░▒▓[92;41;1mXMAS[31;49m▓▒░[0m [95;1;5m🌟[0m [31;49m░▒▓[0m 🎄" : {
    *(.text*)
  } > XMAS
}

ENTRY(xmas)
