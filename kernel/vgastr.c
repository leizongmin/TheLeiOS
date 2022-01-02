#include "vgastr.h"

#include "nostdlib.h"

volatile char *k_vgastr_offset_ptr = (char *)K_VGASTR_START;
volatile u16 k_vgastr_offset_row = 0;
volatile u16 k_vgastr_offset_column = 0;
volatile u8 k_vgastr_color = K_VGASTR_COLOR_WHITE;

void k_vgastr_clear() {
  k_memset((void *)K_VGASTR_START, 0, K_VGASTR_END - K_VGASTR_START);
}

void k_vgastr_fill(u8 color, char fill) {
  char *ptr = (char *)K_VGASTR_START;
  for (int i = 0; i < K_VGASTR_ROWS; i++) {
    for (int j = 0; j < K_VGASTR_COLUMNS; j++) {
      *ptr = fill;
      ptr++;
      *ptr = (char)color;
      ptr++;
    }
  }
  k_vgastr_offset_ptr = (char *)K_VGASTR_START;
}

void k_vgastr_next_row() {
  k_vgastr_offset_row++;
  k_vgastr_offset_column = 0;

  // if hit the bottom, scroll one line
  if (k_vgastr_offset_row >= K_VGASTR_ROWS) {
    k_memcpy((void *)K_VGASTR_START,
             (void *)K_VGASTR_START + K_VGASTR_OFFSET_PER_ROW,
             K_VGASTR_LAST_ROW_START - K_VGASTR_START);
    k_memset((void *)(K_VGASTR_LAST_ROW_START), 0, K_VGASTR_OFFSET_PER_ROW);
    k_vgastr_offset_row--;
  }

  k_vgastr_offset_ptr =
      (char *)(K_VGASTR_START + K_VGASTR_OFFSET_PER_ROW * k_vgastr_offset_row);
}

void k_vgastr_set_color(char c) { k_vgastr_color = c; }

void k_vgastr_write(char c) {
  *k_vgastr_offset_ptr = c;
  k_vgastr_offset_ptr++;
  *k_vgastr_offset_ptr = (char)k_vgastr_color;
  k_vgastr_offset_ptr++;

  k_vgastr_offset_column++;

  // 80 columns per row
  if (k_vgastr_offset_column >= K_VGASTR_COLUMNS) {
    k_vgastr_next_row();
  }

  k_vgastr_cursor_refresh();
}

void k_vgastr_write_string(char *s) {
  while (*s) {
    // check newline
    if (*s == '\n') {
      k_vgastr_next_row();
    } else {
      k_vgastr_write(*s);
    }
    s++;
  }
  k_vgastr_cursor_refresh();
}

u16 k_vgastr_cursor_get() {
  k_outb(0x03d4, 14);
  u8 cursor_pos_h = k_inb(0x03d5);
  k_outb(0x03d4, 15);
  u8 cursor_pos_l = k_inb(0x03d5);
  return (u16)((cursor_pos_h << 8) | cursor_pos_l);
}

void k_vgastr_cursor_set(u16 x, u16 y) {
  u16 cursor_pos = (u16)(y * 80 + x);
  k_outb(0x03d4, 14);
  k_outb(0x03d5, (u8)((cursor_pos >> 8) & 0xff));
  k_outb(0x03d4, 15);
  k_outb(0x03d5, (u8)(cursor_pos & 0xff));
}

void k_vgastr_cursor_refresh() {
  // update cursor position
  u16 y = k_vgastr_offset_row >= K_VGASTR_ROWS ? K_VGASTR_ROWS - 1
                                               : k_vgastr_offset_row;
  k_vgastr_cursor_set(k_vgastr_offset_column, y);
  // update the color of next char, or else we cannot see the cursor
  *(k_vgastr_offset_ptr + 1) = K_VGASTR_COLOR_LIGHT_GREY;
}
