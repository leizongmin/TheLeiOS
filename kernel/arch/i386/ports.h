#ifndef _KERNEL_ARCH_I386_CPU_PORTS_H_
#define _KERNEL_ARCH_I386_CPU_PORTS_H_

#include "libk/libk.h"

u8 port_byte_in(u16 port);
void port_byte_out(u16 port, u8 data);
u16 port_word_in(u16 port);
void port_word_out(u16 port, u16 data);

#endif  //_KERNEL_ARCH_I386_CPU_PORTS_H_
