// Low level port I/O functions
// These functions are used by most hardware drivers in our kernel
#include "ports.h"

// Read a byte from the specified port
u8 port_byte_in(u16 port) {
  u8 result;
  __asm__("in %%dx, %%al" : "=a"(result) : "d"(port));
  return result;
}

// Write a byte into the specified port
void port_byte_out(u16 port, u8 data) {
  __asm__("out %%al, %%dx" : : "a"(data), "d"(port));
}

// Read a word from the specified port
u16 port_word_in(u16 port) {
  u16 result;
  __asm__("in %%dx, %%ax" : "=a"(result) : "d"(port));
  return result;
}

// Write a word into the specified port
void port_word_out(u16 port, u16 data) {
  __asm__("out %%ax, %%dx" : : "a"(data), "d"(port));
}
