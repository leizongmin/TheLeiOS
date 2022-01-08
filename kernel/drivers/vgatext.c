#include "drivers/vgatext.h"

#include "io.h"
#include "libk/libk.h"

volatile char *k_vgatext_offset_ptr = (char *)K_VGATEXT_START;
volatile u16 k_vgatext_offset_row = 0;
volatile u16 k_vgatext_offset_column = 0;
volatile u8 k_vgatext_color = K_VGATEXT_COLOR_WHITE;

void k_vgatext_fill(u8 color, char fill) {
  char *ptr = (char *)K_VGATEXT_START;
  for (int i = 0; i < K_VGATEXT_ROWS; i++) {
    for (int j = 0; j < K_VGATEXT_COLUMNS; j++) {
      *ptr = fill;
      ptr++;
      *ptr = (char)color;
      ptr++;
    }
  }
  k_vgatext_offset_ptr = (char *)K_VGATEXT_START;
}

void k_vgatext_next_row() {
  k_vgatext_offset_row++;
  k_vgatext_offset_column = 0;

  // if hit the bottom, scroll one line
  if (k_vgatext_offset_row >= K_VGATEXT_ROWS) {
    k_mem_copy((void *)K_VGATEXT_START,
               (void *)K_VGATEXT_START + K_VGATEXT_OFFSET_PER_ROW,
               K_VGATEXT_LAST_ROW_START - K_VGATEXT_START);
    k_mem_set((void *)(K_VGATEXT_LAST_ROW_START), 0, K_VGATEXT_OFFSET_PER_ROW);
    k_vgatext_offset_row--;
  }

  k_vgatext_offset_ptr = (char *)(K_VGATEXT_START + K_VGATEXT_OFFSET_PER_ROW *
                                                        k_vgatext_offset_row);
}

void k_vgatext_write(char c) {
  if (c == '\n') {
    // newline
    k_vgatext_next_row();
  } else if (c < 32) {
    // invisible
  } else {
    *k_vgatext_offset_ptr = c;
    k_vgatext_offset_ptr++;
    *k_vgatext_offset_ptr = (char)k_vgatext_color;
    k_vgatext_offset_ptr++;

    k_vgatext_offset_column++;

    // 80 columns per row
    if (k_vgatext_offset_column >= K_VGATEXT_COLUMNS) {
      k_vgatext_next_row();
    }
  }
  k_vgatext_cursor_refresh();
}

void k_vgatext_write_str(const char *s) {
  while (*s) {
    k_vgatext_write(*s);
    s++;
  }
  k_vgatext_cursor_refresh();
}

// Get current cursor position
// Implementation based on low-level port I/O
// Write to CTRL register 14 (0xE) and read Hi byte
// Write to CTRL register 15 (0xF) and read Lo byte
// Adding these leads to current offset of cursor in memory
u16 k_vgatext_cursor_get(u16 *x, u16 *y) {
  io_out8(K_VGATEXT_REG_SCREEN_CTRL, 14);
  u8 cursor_pos_h = io_in8(K_VGATEXT_REG_SCREEN_DATA);
  io_out8(K_VGATEXT_REG_SCREEN_CTRL, 15);
  u8 cursor_pos_l = io_in8(K_VGATEXT_REG_SCREEN_DATA);
  u16 pos = (u16)((cursor_pos_h << 8) | cursor_pos_l);
  *x = pos % 80;
  *y = pos / 80;
  return pos;
}

// Set cursor position
// The same implementation as in get_cursor_offset()
// Write to CTRL register 14 (0xE) and write Hi byte to DATA register
// Write to CTRL register 15 (0xF) and write Lo byte to DATA register
void k_vgatext_cursor_set(u16 x, u16 y) {
  u16 cursor_pos = (u16)(y * 80 + x);
  io_out8(K_VGATEXT_REG_SCREEN_CTRL, 14);
  io_out8(K_VGATEXT_REG_SCREEN_DATA, (u8)((cursor_pos >> 8) & 0xff));
  io_out8(K_VGATEXT_REG_SCREEN_CTRL, 15);
  io_out8(K_VGATEXT_REG_SCREEN_DATA, (u8)(cursor_pos & 0xff));
}

void k_vgatext_cursor_refresh() {
  // update cursor position
  u16 y = k_vgatext_offset_row >= K_VGATEXT_ROWS ? K_VGATEXT_ROWS - 1
                                                 : k_vgatext_offset_row;
  k_vgatext_cursor_set(k_vgatext_offset_column, y);
  // update the color of next char, or else we cannot see the cursor,
  // and we need to keep the current background color
  u8 color = K_VGATEXT_COLOR_LIGHT_GREY + (k_vgatext_color & 0xF0);
  *(k_vgatext_offset_ptr + 1) = (char)color;
}

void k_vgatext_printf(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  const usize buf_size = 1024;
  char buf[buf_size];
  buf[0] = '\0';
  while (*fmt) {
    if (*fmt == '%') {
      switch (*(fmt + 1)) {
        case 'c':  // char
          k_vgatext_write((char)va_arg(args, int));
          break;
        case 's':  // string
          k_vgatext_write_str(va_arg(args, char *));
          break;
        case 'b':  // binary
          k_i32_to_str(buf, buf_size, va_arg(args, u32), 2);
          k_vgatext_write_str(buf);
          break;
        case 'o':  // octonary
          k_i32_to_str(buf, buf_size, va_arg(args, u32), 8);
          k_vgatext_write_str(buf);
          break;
        case 'd':  // decimal
          k_i32_to_str(buf, buf_size, va_arg(args, i32), 10);
          k_vgatext_write_str(buf);
          break;
        case 'x':  // hexadecimal
          k_i32_to_str(buf, buf_size, va_arg(args, u32), 16);
          k_vgatext_write_str(buf);
          break;
        case '%':  // %
          k_vgatext_write(*fmt);
          break;
        default:  // not support
          k_vgatext_write(*fmt);
          break;
      }
      fmt += 2;
    } else {
      k_vgatext_write(*fmt);
      fmt++;
    }
  }
  va_end(args);
}

void k_vgatext_backspace() {
  if (k_vgatext_offset_column == 0) {
    k_vgatext_offset_column = K_VGATEXT_COLUMNS - 1;
    if (k_vgatext_offset_row == 0) {
      k_vgatext_clear(k_vgatext_color);
      return;
    } else {
      k_vgatext_offset_row--;
    }
  } else {
    k_vgatext_offset_column--;
  }

  k_vgatext_offset_ptr -= 2;
  *k_vgatext_offset_ptr = ' ';
  *(k_vgatext_offset_ptr + 1) = (char)k_vgatext_color;
  k_vgatext_cursor_refresh();
}
