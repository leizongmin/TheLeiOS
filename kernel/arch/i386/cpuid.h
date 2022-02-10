#ifndef _KERNEL_ARCH_I386_CPUID_H_
#define _KERNEL_ARCH_I386_CPUID_H_

#include <kernel/libk/all.h>

enum k_cpuid_requests {
  K_CPUID_GETVENDORSTRING,
  K_CPUID_GETFEATURES,
  K_CPUID_GETTLB,
  K_CPUID_GETSERIAL,

  K_CPUID_INTELEXTENDED = 0x80000000,
  K_CPUID_INTELFEATURES,
  K_CPUID_INTELBRANDSTRING,
  K_CPUID_INTELBRANDSTRINGMORE,
  K_CPUID_INTELBRANDSTRINGEND,
};

i32 k_cpuid_str(i32 code, char buf[13]);

#endif  //_KERNEL_ARCH_I386_CPUID_H_