#include "vgastr.h"

char *k_vgastr_offset_ptr = (char *)K_VGASTR_START;
uint32_t k_vgastr_offset_row = 0;
uint32_t k_vgastr_offset_column = 0;
uint8_t k_vgastr_color = K_VGASTR_COLOR_WHITE;

void
k_vgastr_reset (uint8_t color, char fill)
{
  char *ptr = (char *)K_VGASTR_START;
  for (int i = 0; i < K_VGASTR_ROWS; i++)
    {
      for (int j = 0; j < K_VGASTR_COLUMNS; j++)
        {
          *ptr = fill;
          ptr++;
          *ptr = color;
          ptr++;
        }
    }
  k_vgastr_offset_ptr = (char *)K_VGASTR_START;
}

inline void
k_vgastr_next_row ()
{
  k_vgastr_offset_row++;
  k_vgastr_offset_column = 0;
  k_vgastr_offset_ptr
      = (char *)(K_VGASTR_START
                 + K_VGASTR_OFFSET_PER_ROW * k_vgastr_offset_row);
}

inline void
k_vgastr_set_color (char c)
{
  k_vgastr_color = c;
}

inline void
k_vgastr_write (char c)
{
  *k_vgastr_offset_ptr = c;
  k_vgastr_offset_ptr++;
  *k_vgastr_offset_ptr = k_vgastr_color;
  k_vgastr_offset_ptr++;

  k_vgastr_offset_column++;

  // 80 columns per row
  if (k_vgastr_offset_column >= K_VGASTR_COLUMNS)
    {
      k_vgastr_next_row ();
    }
}

void
k_vgastr_write_string (char *s)
{
  while (*s)
    {
      // check newline
      if (*s == '\n')
        {
          k_vgastr_next_row ();
        }
      else
        {
          k_vgastr_write (*s);
        }
      s++;
    }
  return;
}
