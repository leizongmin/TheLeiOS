#include "cpuid.h"

#include "debug.h"

i32 k_cpuid_str(i32 code, char buf[13]) {
  u32 eax, ebx, ecx, edx;
  __asm__("cpuid" : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx) : "a"(code));

  buf[0] = (char)((ebx & 0xFF000000) >> 24);
  buf[1] = (char)((ebx & 0xFF0000) >> 16);
  buf[2] = (char)((ebx & 0xFF00) >> 8);
  buf[3] = (char)(ebx & 0xFF);

  buf[4] = (char)((ecx & 0xFF000000) >> 24);
  buf[5] = (char)((ecx & 0xFF0000) >> 16);
  buf[6] = (char)((ecx & 0xFF00) >> 8);
  buf[7] = (char)(ecx & 0xFF);

  buf[8] = (char)((edx & 0xFF000000) >> 24);
  buf[9] = (char)((edx & 0xFF0000) >> 16);
  buf[10] = (char)((edx & 0xFF00) >> 8);
  buf[11] = (char)(edx & 0xFF);

  buf[12] = '\0';

  DEBUG_PRINTF("k_cpuid_str eax=0x%x ebx=0x%x ecx=0x%x edx=0x%x str=%s", eax,
               ebx, ecx, edx, buf)

  return (i32)eax;
}
