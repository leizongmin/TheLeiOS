#include "vgastr.h"

#include <stdarg.h>

#include "io.h"
#include "nostdlib.h"

volatile char *k_vgastr_offset_ptr = (char *)K_VGASTR_START;
volatile u16 k_vgastr_offset_row = 0;
volatile u16 k_vgastr_offset_column = 0;
volatile u8 k_vgastr_color = K_VGASTR_COLOR_WHITE;

void k_vgastr_clear(u8 color) { k_vgastr_fill(color, 0); }

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

void k_vgastr_set_color(u8 color) { k_vgastr_color = color; }

void k_vgastr_write(char c) {
  if (c == '\n') {
    // newline
    k_vgastr_next_row();
  } else if (c < 32) {
    // invisible
  } else {
    *k_vgastr_offset_ptr = c;
    k_vgastr_offset_ptr++;
    *k_vgastr_offset_ptr = (char)k_vgastr_color;
    k_vgastr_offset_ptr++;

    k_vgastr_offset_column++;

    // 80 columns per row
    if (k_vgastr_offset_column >= K_VGASTR_COLUMNS) {
      k_vgastr_next_row();
    }
  }
  k_vgastr_cursor_refresh();
}

void k_vgastr_write_str(const char *s) {
  while (*s) {
    k_vgastr_write(*s);
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

void k_vgastr_printf(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  const usize buf_size = 1024;
  char buf[buf_size];
  while (*fmt) {
    if (*fmt == '%') {
      switch (*(fmt + 1)) {
        case 'c':  // char
          k_vgastr_write((char)va_arg(args, int));
          break;
        case 's':  // string
          k_vgastr_write_str(va_arg(args, char *));
          break;
        case 'b':  // binary
          k_i32_to_str(buf, buf_size, va_arg(args, u32), 2);
          k_vgastr_write_str(buf);
          break;
        case 'o':  // octonary
          k_i32_to_str(buf, buf_size, va_arg(args, u32), 8);
          k_vgastr_write_str(buf);
          break;
        case 'd':  // decimal
          k_i32_to_str(buf, buf_size, va_arg(args, i32), 10);
          k_vgastr_write_str(buf);
          break;
        case 'x':  // hexadecimal
          k_i32_to_str(buf, buf_size, va_arg(args, u32), 16);
          k_vgastr_write_str(buf);
          break;
        case '%':  // %
          k_vgastr_write(*fmt);
          break;
        default:  // not support
          k_vgastr_write(*fmt);
          break;
      }
      fmt += 2;
    } else {
      k_vgastr_write(*fmt);
      fmt++;
    }
  }
  va_end(args);
}
