

#ifndef _KERNEL_ARCH_I386_MEMORY_H_
#define _KERNEL_ARCH_I386_MEMORY_H_

#include <kernel/libk/all.h>

namespace kernel::arch {
usize detectMemorySize();
}

#endif  // _KERNEL_ARCH_I386_MEMORY_H_
