#include "arch/i386/idt.h"
#include "arch/i386/isr.h"
#include "arch/i386/cpuid.h"
#include "drivers/vgatext.h"
#include "libk/debug.h"
#include "libk/libk.h"
#include "os.h"

extern "C" {
void k_main();
}

idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

void welcome() {
  k_vgatext_clear(K_VGATEXT_BGCOLOR_BLUE);
  k_vgatext_set_color(K_VGATEXT_COLOR_LIGHT_BROWN + K_VGATEXT_BGCOLOR_BLUE);
  k_vgatext_printf("Welcome to %s version %s!\n%s\n", K_OS_NAME, K_OS_VERSION,
                   K_OS_DESCRIPTION);
  k_vgatext_write_str("\n\n");

  k_vgatext_set_color(K_VGATEXT_COLOR_WHITE + K_VGATEXT_BGCOLOR_BLUE);
  {
    u16 x, y;
    u16 v = k_vgatext_cursor_get(&x, &y);
    k_vgatext_printf("current \r\bcursor=%d x=%d y=%d\n", v, x, y);
  }
  {
    char id[13];
    k_cpuid_str(K_CPUID_GETVENDORSTRING, id);
    k_vgatext_printf("detect cpuid: %s\n", id);
    K_DEBUG_DUMP_PTR(id, 12);
  }
}

void user_input(char *input) {
  if (k_str_cmp(input, "END") == 0) {
    k_vgatext_write_str("Stopping the CPU. Bye!\n");
    __asm__ __volatile__("hlt");
  }

  k_vgatext_write_str("You said: ");
  k_vgatext_write_str(input);
  k_vgatext_write_str("\n> ");
}

__attribute__((unused)) void k_main() {
  welcome();
  isr_install();
  irq_install();
}
