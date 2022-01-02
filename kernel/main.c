#include "nostdlib.h"
#include "vgastr.h"

void welcome() {
  k_vgastr_fill(K_VGASTR_COLOR_DARK_GREY, (char)178);
  k_vgastr_clear();
  k_vgastr_set_color(K_VGASTR_COLOR_LIGHT_RED);
  k_vgastr_write_string("    Welcome to the LeiOS!\n\n");

  k_vgastr_set_color(K_VGASTR_COLOR_LIGHT_BROWN);
  for (int i = 0; i < 400; i++) {
    k_vgastr_write('+');
  }

  k_vgastr_set_color(K_VGASTR_COLOR_LIGHT_GREEN);
  k_vgastr_write_string("    Welcome to the LeiOS!\n\n");
  k_vgastr_set_color(K_VGASTR_COLOR_LIGHT_CYAN);
  k_vgastr_write_string(
      "    Homepage: https://github.com/leizongmin/TheLeiOS\n\n");

  k_vgastr_set_color(K_VGASTR_COLOR_LIGHT_BROWN);
  for (int i = 0; i < 400; i++) {
    k_vgastr_write('+');
  }

  k_vgastr_write_string(" line 1\n");
  k_vgastr_write_string(" line 2\n");
  k_vgastr_write_string(" line 3\n");
  k_vgastr_write_string(" line 4\n");
  k_vgastr_write_string(" line 5\n");
  k_vgastr_write_string(" line 6\n");
  k_vgastr_write_string(" line 7\n");
  k_vgastr_write_string(" line 8\n");
  k_vgastr_write_string(" line 9\n");
  k_vgastr_write_string(" line 10\n");
  k_vgastr_write_string(" line 11---------\n");
  k_vgastr_write_string(" line 12-------/\n");
  k_vgastr_write_string(" line 13------+\n");
  k_vgastr_write_string(" line 14\n");
  k_vgastr_write_string(" line 15\n");

  if (k_strcmp("aa", "aa") == 0) {
    k_vgastr_write_string("aa == aa");
  }

  k_vgastr_printf(
      "++hello %% char=%c string=%s bin=%b oct=%o dec=%d hex=%x end", 'x',
      "world", k_vgastr_offset_ptr, k_vgastr_offset_ptr, k_vgastr_offset_ptr,
      k_vgastr_offset_ptr);
}

__attribute__((unused)) void k_main() { welcome(); }
