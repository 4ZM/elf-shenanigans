MEMORY {
  IRAM (rx) : ORIGIN = 0xC0DE0000, LENGTH = 0x1000
  RAM  (rw) : ORIGIN = 0xFEED0000, LENGTH = 0x1000
  ROM  (r)  : ORIGIN = 0xDEAD0000, LENGTH = 0x1000
}

SECTIONS
{
  "📜 .text" : {
    *(.text) *(.text.*)
  } > IRAM

  "📜 .init_array" : {
    _init_array_start = .;
    *(.init_array*)
    _init_array_end = .;
  } > IRAM

  "📦 .data" : {
    *(.data*)
  } > RAM

  "📁 .bss" : {
    _bss_start = .;
    *(.bss*)
    _bss_end = .;
  } > RAM

  "🧊 .rodata" : {
    *(.rodata*)
  }  > ROM

  /DISCARD/ : { *(.comment) }
}

ENTRY(startup)
