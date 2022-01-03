#include "cpuid.h"
#include "debug.h"
#include "io.h"
#include "nostdlib.h"
#include "os.h"
#include "vgastr.h"

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
    DEBUG_DUMP_PTR((u8*)id, 12)
  }
  {
    io_out8(IO_COM1, 0x56);
    io_out16(IO_COM1, 0x1234);
    DEBUG_STR("read COM1")
    DEBUG_PRINTF("u8=%x", io_in8(IO_COM1))
  }
}

__attribute__((unused)) void k_main() { welcome(); }
