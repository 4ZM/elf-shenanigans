const char message[] = "Hello Simplicity!\n"; // .rodata
unsigned long length = sizeof(message) - 1;   // .data
unsigned long status;                         // .bss

struct CppIsFun {
  explicit CppIsFun(unsigned long x);
  unsigned long member_var;
};

CppIsFun::CppIsFun(unsigned long x) : member_var(x) {}

CppIsFun a_global{42};

int main() {

  // write(1, message, length)
  asm volatile("mov $1, %%rax\n"           // write syscall number (0x01)
               "mov $1, %%rdi\n"           // Stdout file descriptor (0x01)
               "mov %0, %%rsi\n"           // Message buffer
               "mov %1, %%rdx\n"           // Buffer length
               "syscall"                   // Make the syscall
               :                           // No output operands
               : "r"(message), "r"(length) // Input operands
               : "rax", "rdi", "rsi", "rdx", "rcx", "r11",
                 "memory" // Clobbered registers
  );

  return a_global.member_var;
}

typedef void (*init_func)();
extern init_func _init_array_start;
extern init_func _init_array_end;
void run_init_array() {
  for (init_func *func = &_init_array_start; func != &_init_array_end; ++func) {
    (*func)();
  }
}

extern unsigned long _bss_start;
extern unsigned long _bss_end;
void zero_init_bss() {
  for (unsigned long *it = &_bss_start; it != &_bss_end; ++it)
    *it = 0;
}

extern "C" void startup() {

  zero_init_bss();

  run_init_array();

  status = main();

  // exit(status)
  asm volatile("mov $0x3c, %%rax\n" // exit syscall number (0x3c)
               "mov %0, %%rdi\n"    // exit status
               "syscall"            // Make the syscall
               :                    // No output operands
               : "r"(status)        // Input operands
               : "%rax", "%rdi"     // Clobbered registers
  );
}
