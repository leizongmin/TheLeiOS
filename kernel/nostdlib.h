#ifndef _KERNEL_NOSTDLIB_H_
#define _KERNEL_NOSTDLIB_H_

#include <stddef.h>

#include "types.h"

static inline void *k_memcpy(void *dest, const void *src, size_t count) {
  u8 *d = dest;
  const u8 *s = src;
  while (count--) {
    *d++ = *s++;
  }
  return dest;
}

static inline void *k_memset(void *dest, u8 ch, size_t count) {
  u8 *d = dest;
  while (count--) {
    *d++ = ch;
  }
  return dest;
}

int k_strcmp(const char *s1, const char *s2);

usize k_i32_to_str(char *buf, usize buf_size, i32 num, i32 radix);

#endif  //_KERNEL_NOSTDLIB_H_
