void xmas() {
  volatile const char message[] = "🎄 Happy Holidays!\n";
  volatile const unsigned long length = sizeof(message) - 1;

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

  // exit(status)
  asm volatile("mov $0x3c, %%rax\n" // exit syscall number (exit = 0x3c)
               "mov $0x00, %%rdi\n" // exit status (0x00)
               "syscall"            // Make the syscall
               :                    // No output operands
               :                    // No input operands
               : "%rax", "%rdi"     // Clobbered registers
  );
}
