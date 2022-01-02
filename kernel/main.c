#include "nostdlib.h"
#include "vgastr.h"

void welcome() {
  k_vgastr_clear(K_VGASTR_BGCOLOR_DARK_GREY);
  k_vgastr_set_color(K_VGASTR_COLOR_LIGHT_RED);
  k_vgastr_write_str("    Welcome to the LeiOS!\n\n");

  k_vgastr_set_color(K_VGASTR_COLOR_LIGHT_BROWN);
  for (int i = 0; i < 160; i++) {
    k_vgastr_write('+');
  }

  k_vgastr_set_color(K_VGASTR_COLOR_LIGHT_GREEN);
  k_vgastr_write_str("    Welcome to the LeiOS!\n\n");
  k_vgastr_set_color(K_VGASTR_COLOR_LIGHT_CYAN);
  k_vgastr_write_str(
      "    Homepage: https://github.com/leizongmin/TheLeiOS\n\n");

  k_vgastr_set_color(K_VGASTR_COLOR_LIGHT_BROWN);
  for (int i = 0; i < 160; i++) {
    k_vgastr_write('+');
  }

  k_vgastr_write_str(" line 1\n");
  k_vgastr_write_str(" line 2\n");
  k_vgastr_write_str(" line 3\n");
  k_vgastr_write_str(" line 4\n");
  k_vgastr_write_str(" line 5\n");
  k_vgastr_write_str(" line 6\n");
  k_vgastr_write_str(" line 7\n");
  k_vgastr_write_str(" line 8\n");
  k_vgastr_write_str(" line 9\n");
  k_vgastr_write_str(" line 10\n");
  k_vgastr_write_str(" line 11---------\n");
  k_vgastr_write_str(" line 12-------/\n");
  k_vgastr_write_str(" line 13------+\n");
  k_vgastr_write_str(" line 14\n");
  k_vgastr_write_str(" line 15\n");

  if (k_strcmp("aa", "aa") == 0) {
    k_vgastr_write_str("aa == aa\n");
  }

  k_vgastr_set_color(K_VGASTR_COLOR_LIGHT_RED + K_VGASTR_BGCOLOR_BLUE);
  k_vgastr_printf(
      "++hello %% char=%c string=%s bin=%b oct=%o dec=%d hex=%x end\n", 'x',
      "world", k_vgastr_offset_ptr, k_vgastr_offset_ptr, k_vgastr_offset_ptr,
      k_vgastr_offset_ptr);
  k_vgastr_printf("current \r\bcursor=%d", k_vgastr_cursor_get());
}

__attribute__((unused)) void k_main() { welcome(); }
