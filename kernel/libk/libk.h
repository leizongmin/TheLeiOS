#ifndef _KERNEL_LIBK_LIBK_H_
#define _KERNEL_LIBK_LIBK_H_

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

#include "types.h"

void *k_mem_copy(void *__restrict__ dest, const void *__restrict__ src,
                 usize count);
void *k_mem_set(void *dest, u8 ch, usize count);

int k_str_cmp(const char *__restrict__ s1, const char *__restrict__ s2);
void k_str_reverse(char *s);
usize k_str_len(const char *s);
void k_str_append(char *s, char n);
usize k_str_append_str(char *__restrict__ s, usize sz,
                       const char *__restrict__ s2);
usize k_str_append_str_at(char *__restrict__ s, usize sz,
                          const char *__restrict__ s2, usize offset);
void k_str_backspace(char *s);
usize k_str_printf(char *__restrict__ buffer, usize bufsz,
                   const char *__restrict__ format, ...);
usize k_i32_to_str(char *buf, usize buf_size, i32 num, i32 radix);

#endif  //_KERNEL_LIBK_LIBK_H_
