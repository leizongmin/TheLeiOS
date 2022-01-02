#ifndef _KERNEL_NOSTDLIB_H_
#define _KERNEL_NOSTDLIB_H_

#include <stddef.h>
#include <stdint.h>

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define u64 uint64_t
#define i8 int8_t
#define i16 int16_t
#define i32 int32_t
#define i64 int64_t
#define f32 float
#define f64 double
#define usize size_t

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

static inline void k_halt(void) { __asm__ volatile("hlt" : :); }

static inline u8 k_inb(u16 port) {
  u8 data;
  __asm__ volatile("inb %%dx,%%al" : "=a"(data) : "d"(port));
  return data;
}

static inline void k_outb(u16 port, u8 data) {
  __asm__ volatile("outb %%al,%%dx" : : "a"(data), "d"(port));
}

int k_strcmp(const char *s1, const char *s2);

usize k_i32_to_str(char *buf, usize buf_size, i32 num, i32 radix);

#endif  //_KERNEL_NOSTDLIB_H_
