MEMORY {
  XMAS (rx) : ORIGIN = 0xDEC25000, LENGTH = 0x1000
}

SECTIONS
{
  "[95;1;5m🌟[0m [92;41;1m XMAS [0m [95;1;5m🌟[0m" : {
    *(.text*)
  } > XMAS
}

ENTRY(xmas)
