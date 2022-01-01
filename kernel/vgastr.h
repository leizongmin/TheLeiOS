#ifndef _KERNEL_VGASTR_H
#define _KERNEL_VGASTR_H

#define K_VGA_START 0xb8000
#define K_VGA_COLUMNS 80
#define K_VGA_OFFSET_PER_LINE 160

extern char *k_vga_offset;
extern int k_vga_offset_line;
extern int k_vga_offset_column;
extern char k_vga_color;

void k_vgastr_next_line ();
void k_vgastr_set_color (char color);
void k_vgastr_write (char *string);

#endif
