#include "cpuid.h"
#include "debug.h"
#include "io.h"
#include "os.h"
#include "vgastr.h"

void welcome() {
  k_vgastr_clear(K_VGASTR_BGCOLOR_BLUE);
  k_vgastr_set_color(K_VGASTR_COLOR_LIGHT_BROWN + K_VGASTR_BGCOLOR_BLUE);
  k_vgastr_printf("Welcome to %s version %s!\n%s\n", K_OS_NAME, K_OS_VERSION,
                  K_OS_DESCRIPTION);
  k_vgastr_write_str("\n\n");

  k_vgastr_set_color(K_VGASTR_COLOR_WHITE + K_VGASTR_BGCOLOR_BLUE);
  //  {
  //    u16 x, y;
  //    u16 v = k_vgastr_cursor_get(&x, &y);
  //    k_vgastr_printf("current \r\bcursor=%d x=%d y=%d\n", v, x, y);
  //  }
  //  {
  //    char id[13];
  //    k_cpuid_str(K_CPUID_GETVENDORSTRING, id);
  //    k_vgastr_printf("detect cpuid: %s\n", id);
  //    DEBUG_DUMP_PTR(id, 12);
  //  }
  //  {
  //    io_out8(IO_COM1, 0x56);
  //    io_out16(IO_COM1, 0x1234);
  //    DEBUG_STR("read COM1");
  //    DEBUG_PRINTF("u8=%x", io_in8(IO_COM1));
  //  }
  //  {
  //    DEBUG_INT(io_in8(0x3C0));
  //    io_out8(0x3C0, 0x41);
  //    DEBUG_INT(io_in8(0x3C0));
  //
  //    u8* vram = (u8*)0xa0000;
  //    //    DEBUG_DUMP_PTR(vram, 256)
  //    for (u32 x = 0; x < 100; x++) {
  //      for (u32 y = 0; y < 200; y++) {
  //        vram[y * 320 + x] = 10;
  //      }
  //    }
  //    //    DEBUG_DUMP_PTR(vram, 256)
  //  }
  //  {
  //    DEBUG_ERROR("this is an error message");
  //    DEBUG_ERRORF("this is a formatted error message: %d", 123);
  //  }
  {
    const usize s = 128;
    char buf[s];
    buf[0] = '\0';
    k_str_printf(buf, s, "c=%c.s=%s.d=%d.x=%x.o=%o.b=%b\n", 'x', "world", 123,
                 123, 123, 123);
    k_vgastr_write_str(buf);

    DEBUG_PRINTF("c=%c.s=%s.d=%d.x=%x.o=%o.b=%b", 'x', "world", 123, 123, 123,
                 123);

    buf[0] = '\0';
    k_vgastr_write_str(buf);
    k_vgastr_write('\n');
    k_str_printf(buf, s, "c=%c.s=%s.d=%d.x=%x.o=%o.b=%b\n", 'x', "world", 123,
                 123, 123, 123);
    k_vgastr_write_str(buf);

    buf[0] = '\0';
    k_vgastr_write_str(buf);
    k_vgastr_write('\n');
    k_str_printf(buf, s, "c=%c.s=%s.d=%d.x=%x.o=%o.b=%b\n", 'x', "world", 123,
                 123, 123, 123);
    k_vgastr_write_str(buf);
  }
}

__attribute__((unused)) void k_main() { welcome(); }
