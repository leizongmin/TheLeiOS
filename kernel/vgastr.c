#include "vgastr.h"

char *k_vga_offset = (char *)K_VGA_START;
int k_vga_offset_line = 0;
int k_vga_offset_column = 0;
char k_vga_color = 0xf;

inline void
k_vgastr_next_line ()
{
  k_vga_offset_line++;
  k_vga_offset_column = 0;
  k_vga_offset
      = (char *)K_VGA_START + K_VGA_OFFSET_PER_LINE * k_vga_offset_line;
}

inline void
k_vgastr_set_color (char color)
{
  k_vga_color = color;
}

void
k_vgastr_write (char *s)
{
  while (*s)
    {
      // check newline
      if (*s == '\n')
        {
          k_vgastr_next_line ();
          s++;
          continue;
        }

      // write char
      *k_vga_offset = *s;
      s++;
      k_vga_offset++;
      // 80 columns per line
      k_vga_offset_column++;
      if (k_vga_offset_column >= K_VGA_COLUMNS)
        {
          k_vgastr_next_line ();
        }
      // set color
      *k_vga_offset = k_vga_color;
      k_vga_offset++;
    }
  return;
}
