#ifndef _KERNEL_NOSTDLIB_H_
#define _KERNEL_NOSTDLIB_H_

#include <stddef.h>

static __attribute__((always_inline)) inline void *k_memcpy(void *dest, const void *src, size_t count) {
  char *d = dest;
  const char *s = src;
  while (count--) {
    *d++ = *s++;
  }
  return dest;
}

static __attribute__((always_inline)) inline void *k_memset(void *dest, char ch, size_t count) {
  char *d = dest;
  while (count--) {
    *d++ = ch;
  }
  return dest;
}

#endif  //_KERNEL_NOSTDLIB_H_
