#ifndef _KERNEL_VGASTR_H
#define _KERNEL_VGASTR_H

void _strwrite (char *string);
void _strwrite_color (char color, char *string);
void printf (char *fmt, ...);
void printf_color (char color, char *fmt, ...);

#endif
