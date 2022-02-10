#ifndef _KERNEL_DRIVERS_VGATEXT_H
#define _KERNEL_DRIVERS_VGATEXT_H

/**
 * Framebuffer: https://en.wikipedia.org/wiki/Framebuffer
 * Double Buffering: https://wiki.osdev.org/Double_Buffering
 * ASCII Table: https://www.asciitable.com/
 */

#include <kernel/libk/all.h>

// Indexed registers for read\write from\in port
#define K_VGATEXT_REG_SCREEN_CTRL 0x3D4
#define K_VGATEXT_REG_SCREEN_DATA 0x3D5

#define K_VGATEXT_START 0xb8000
#define K_VGATEXT_END 0xb8fa0
#define K_VGATEXT_LAST_ROW_START 0xb8f00
#define K_VGATEXT_COLUMNS 80
#define K_VGATEXT_ROWS 25
#define K_VGATEXT_OFFSET_PER_ROW 160

#define K_VGATEXT_COLOR_BLACK 0
#define K_VGATEXT_COLOR_BLUE 1
#define K_VGATEXT_COLOR_GREEN 2
#define K_VGATEXT_COLOR_CYAN 3
#define K_VGATEXT_COLOR_RED 4
#define K_VGATEXT_COLOR_MAGENTA 5
#define K_VGATEXT_COLOR_BROWN 6
#define K_VGATEXT_COLOR_LIGHT_GREY 7
#define K_VGATEXT_COLOR_DARK_GREY 8
#define K_VGATEXT_COLOR_LIGHT_BLUE 9
#define K_VGATEXT_COLOR_LIGHT_GREEN 10
#define K_VGATEXT_COLOR_LIGHT_CYAN 11
#define K_VGATEXT_COLOR_LIGHT_RED 12
#define K_VGATEXT_COLOR_LIGHT_MAGENTA 13
#define K_VGATEXT_COLOR_LIGHT_BROWN 14
#define K_VGATEXT_COLOR_WHITE 15

#define K_VGATEXT_BGCOLOR_BLACK 0
#define K_VGATEXT_BGCOLOR_BLUE 16
#define K_VGATEXT_BGCOLOR_GREEN 32
#define K_VGATEXT_BGCOLOR_CYAN 48
#define K_VGATEXT_BGCOLOR_RED 64
#define K_VGATEXT_BGCOLOR_MAGENTA 80
#define K_VGATEXT_BGCOLOR_BROWN 96
#define K_VGATEXT_BGCOLOR_LIGHT_GREY 112
#define K_VGATEXT_BGCOLOR_DARK_GREY 128

extern volatile char *k_vgatext_offset_ptr;
extern volatile u16 k_vgatext_offset_row;
extern volatile u16 k_vgatext_offset_column;
extern volatile u8 k_vgatext_color;

void k_vgatext_fill(u8 color, char fill);
void k_vgatext_next_row();
static inline void k_vgatext_set_color(u8 color) { k_vgatext_color = color; }
void k_vgatext_write(char c);
void k_vgatext_write_str(const char *s);
void k_vgatext_printf(const char *fmt, ...);
void k_vgatext_backspace();

u16 k_vgatext_cursor_get(u16 *x, u16 *y);
void k_vgatext_cursor_set(u16 x, u16 y);
void k_vgatext_cursor_refresh();

static inline void k_vgatext_clear(u8 color) {
  k_vgatext_fill(color, 0);
  k_vgatext_offset_row = 0;
  k_vgatext_offset_column = 0;
  k_vgatext_cursor_refresh();
}

#endif  // _KERNEL_DRIVERS_VGATEXT_H
