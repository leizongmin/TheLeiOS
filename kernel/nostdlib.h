#ifndef _KERNEL_NOSTDLIB_H_
#define _KERNEL_NOSTDLIB_H_

#include <stddef.h>
#include <stdint.h>

static inline void *k_memcpy(void *dest, const void *src, size_t count) {
  uint8_t *d = dest;
  const uint8_t *s = src;
  while (count--) {
    *d++ = *s++;
  }
  return dest;
}

static inline void *k_memset(void *dest, uint8_t ch, size_t count) {
  uint8_t *d = dest;
  while (count--) {
    *d++ = ch;
  }
  return dest;
}

static inline void k_halt(void) { __asm__ volatile("hlt" : :); }

static inline uint8_t k_inb(uint16_t port) {
  uint8_t data;
  __asm__ volatile("inb %%dx,%%al" : "=a"(data) : "d"(port));
  return data;
}

static inline void k_outb(uint16_t port, uint8_t data) {
  __asm__ volatile("outb %%al,%%dx" : : "a"(data), "d"(port));
}

int k_strcmp(const char *s1, const char *s2);

#endif  //_KERNEL_NOSTDLIB_H_
