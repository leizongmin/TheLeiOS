#include "vgastr.h"

#include "nostdlib.h"

char *k_vgastr_offset_ptr = (char *)K_VGASTR_START;
uint16_t k_vgastr_offset_row = 0;
uint16_t k_vgastr_offset_column = 0;
uint8_t k_vgastr_color = K_VGASTR_COLOR_WHITE;

void k_vgastr_clear() { k_memset((void *)K_VGASTR_START, 0, K_VGASTR_END - K_VGASTR_START); }

void k_vgastr_fill(uint8_t color, char fill) {
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
    k_memcpy((void *)K_VGASTR_START, (void *)K_VGASTR_START + K_VGASTR_OFFSET_PER_ROW,
             K_VGASTR_LAST_ROW_START - K_VGASTR_START);
    k_memset((void *)(K_VGASTR_LAST_ROW_START), 0, K_VGASTR_OFFSET_PER_ROW);
    k_vgastr_offset_row--;
  }

  k_vgastr_offset_ptr = (char *)(K_VGASTR_START + K_VGASTR_OFFSET_PER_ROW * k_vgastr_offset_row);
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

uint16_t k_vgastr_cursor_get() {
  k_outb(0x03d4, 14);
  uint8_t cursor_pos_h = k_inb(0x03d5);
  k_outb(0x03d4, 15);
  uint8_t cursor_pos_l = k_inb(0x03d5);
  return (uint16_t)((cursor_pos_h << 8) | cursor_pos_l);
}

void k_vgastr_cursor_set(uint16_t x, uint16_t y) {
  uint16_t cursor_pos = (uint16_t)(y * 80 + x);
  k_outb(0x03d4, 14);
  k_outb(0x03d5, (uint8_t)((cursor_pos >> 8) & 0xff));
  k_outb(0x03d4, 15);
  k_outb(0x03d5, (uint8_t)(cursor_pos & 0xff));
}

void k_vgastr_cursor_refresh() {
  // update cursor position
  uint16_t y = k_vgastr_offset_row >= K_VGASTR_ROWS ? K_VGASTR_ROWS - 1 : k_vgastr_offset_row;
  k_vgastr_cursor_set(k_vgastr_offset_column, y);
  // update the next char color, or else we can see the cursor
  *(k_vgastr_offset_ptr + 1) = K_VGASTR_COLOR_LIGHT_GREY;
}
