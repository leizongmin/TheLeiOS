#ifndef _KERNEL_IO_H_
#define _KERNEL_IO_H_

#include "types.h"

static inline void k_halt(void) { __asm__ volatile("hlt" : :); }

static inline u8 k_inb(u16 port) {
  u8 data;
  __asm__ volatile("inb %%dx,%%al" : "=a"(data) : "d"(port));
  return data;
}

static inline void k_outb(u16 port, u8 data) {
  __asm__ volatile("outb %%al,%%dx" : : "a"(data), "d"(port));
}

#endif  //_KERNEL_IO_H_
