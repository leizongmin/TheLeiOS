#ifndef _KERNEL_VGASTR_H
#define _KERNEL_VGASTR_H

/**
 * Framebuffer: https://en.wikipedia.org/wiki/Framebuffer
 * Double Buffering: https://wiki.osdev.org/Double_Buffering
 * ASCII Table: https://www.asciitable.com/
 */

#include <stdint.h>

#include "nostdlib.h"

#define K_VGASTR_START 0xb8000
#define K_VGASTR_END 0xb8fa0
#define K_VGASTR_LAST_ROW_START 0xb8f00
#define K_VGASTR_COLUMNS 80
#define K_VGASTR_ROWS 25
#define K_VGASTR_OFFSET_PER_ROW 160

#define K_VGASTR_COLOR_BLACK 0
#define K_VGASTR_COLOR_BLUE 1
#define K_VGASTR_COLOR_GREEN 2
#define K_VGASTR_COLOR_CYAN 3
#define K_VGASTR_COLOR_RED 4
#define K_VGASTR_COLOR_MAGENTA 5
#define K_VGASTR_COLOR_BROWN 6
#define K_VGASTR_COLOR_LIGHT_GREY 7
#define K_VGASTR_COLOR_DARK_GREY 8
#define K_VGASTR_COLOR_LIGHT_BLUE 9
#define K_VGASTR_COLOR_LIGHT_GREEN 10
#define K_VGASTR_COLOR_LIGHT_CYAN 11
#define K_VGASTR_COLOR_LIGHT_RED 12
#define K_VGASTR_COLOR_LIGHT_MAGENTA 13
#define K_VGASTR_COLOR_LIGHT_BROWN 14
#define K_VGASTR_COLOR_WHITE 15

extern volatile char *k_vgastr_offset_ptr;
extern volatile u16 k_vgastr_offset_row;
extern volatile u16 k_vgastr_offset_column;
extern volatile u8 k_vgastr_color;

void k_vgastr_clear();
void k_vgastr_fill(u8 color, char fill);
void k_vgastr_next_row();
void k_vgastr_set_color(char c);
void k_vgastr_write(char c);
void k_vgastr_write_string(char *s);

u16 k_vgastr_cursor_get();
void k_vgastr_cursor_set(u16 x, u16 y);
void k_vgastr_cursor_refresh();

#endif  // _KERNEL_VGASTR_H
