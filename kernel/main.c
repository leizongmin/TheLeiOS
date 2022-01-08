#include "cpu/idt.h"
#include "cpu/isr.h"
#include "cpuid.h"
#include "io.h"
#include "libk/debug.h"
#include "libk/libk.h"
#include "os.h"
#include "vgastr.h"

idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

void welcome() {
  k_vgastr_clear(K_VGASTR_BGCOLOR_BLUE);
  k_vgastr_set_color(K_VGASTR_COLOR_LIGHT_BROWN + K_VGASTR_BGCOLOR_BLUE);
  k_vgastr_printf("Welcome to %s version %s!\n%s\n", K_OS_NAME, K_OS_VERSION,
                  K_OS_DESCRIPTION);
  k_vgastr_write_str("\n\n");

  k_vgastr_set_color(K_VGASTR_COLOR_WHITE + K_VGASTR_BGCOLOR_BLUE);
  {
    u16 x, y;
    u16 v = k_vgastr_cursor_get(&x, &y);
    k_vgastr_printf("current \r\bcursor=%d x=%d y=%d\n", v, x, y);
  }
  {
    char id[13];
    k_cpuid_str(K_CPUID_GETVENDORSTRING, id);
    k_vgastr_printf("detect cpuid: %s\n", id);
    K_DEBUG_DUMP_PTR(id, 12);
  }
}

void user_input(char *input) {
  if (k_str_cmp(input, "END") == 0) {
    k_vgastr_write_str("Stopping the CPU. Bye!\n");
    __asm__ __volatile__("hlt");
  }

  k_vgastr_write_str("You said: ");
  k_vgastr_write_str(input);
  k_vgastr_write_str("\n> ");
}

__attribute__((unused)) void k_main() {
  welcome();
  isr_install();
  irq_install();
}
