const char message[] = "Hello Simplicity!\n";   // .rodata
unsigned long length = sizeof(message) - 1;     // .data
unsigned long status;                           // .bss

int main() {
  // write(1, message, length)
  asm volatile("mov $1, %%rax\n"                // write syscall number (0x01)
               "mov $1, %%rdi\n"                // Stdout file descriptor (0x01)
               "mov %0, %%rsi\n"                // Message buffer
               "mov %1, %%rdx\n"                // Buffer length
               "syscall"                        // Make the syscall
               :                                // No output operands
               : "r"(message), "r"(length)      // Input operands
               : "%rax", "%rdi", "%rsi", "%rdx" // Clobbered registers
  );

  return 0;
}

void startup() {
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
