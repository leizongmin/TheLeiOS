#ifndef _KERNEL_DEBUG_H_
#define _KERNEL_DEBUG_H_

#include <stdbool.h>

#include "vgastr.h"

#ifdef NDEBUG

#define DEBUG_ASSERT(msg, condition) ((void)0);
#define DEBUG_PRINTF(fmt, ...) ((void)0);
#define DEBUG_STR(s) ((void)0);
#define DEBUG_DUMP_PTR(ptr, n) ((void)0);

#else

#define DEBUG_ASSERT(msg, condition)                                          \
  {                                                                           \
    if (condition) {                                                          \
    } else {                                                                  \
      u8 color = k_vgastr_color;                                              \
      k_vgastr_set_color(K_VGASTR_COLOR_LIGHT_BROWN + K_VGASTR_BGCOLOR_CYAN); \
      k_vgastr_printf("\n== ASSERT FAILURE: [%s] AT %s(%s:%d) ==\n", msg,     \
                      __FUNCTION__, __FILE__, __LINE__);                      \
      k_vgastr_set_color(color);                                              \
    }                                                                         \
  }

#define DEBUG_STR(s)                                                         \
  {                                                                          \
    u8 color = k_vgastr_color;                                               \
    k_vgastr_set_color(K_VGASTR_COLOR_LIGHT_BROWN + K_VGASTR_BGCOLOR_CYAN);  \
    k_vgastr_write_str("\n== DEBUG: ");                                      \
    k_vgastr_write_str(s);                                                   \
    k_vgastr_printf(" AT %s(%s:%d) ==\n", __FUNCTION__, __FILE__, __LINE__); \
    k_vgastr_set_color(color);                                               \
  }

#define DEBUG_PRINTF(fmt, ...)                                               \
  {                                                                          \
    u8 color = k_vgastr_color;                                               \
    k_vgastr_set_color(K_VGASTR_COLOR_LIGHT_BROWN + K_VGASTR_BGCOLOR_CYAN);  \
    k_vgastr_write_str("\n== DEBUG: ");                                      \
    k_vgastr_printf(fmt, __VA_ARGS__);                                       \
    k_vgastr_printf(" AT %s(%s:%d) ==\n", __FUNCTION__, __FILE__, __LINE__); \
    k_vgastr_set_color(color);                                               \
  }

#define DEBUG_DUMP_PTR(ptr, n)                                              \
  {                                                                         \
    u8* p = (u8*)ptr;                                                       \
    u8 color = k_vgastr_color;                                              \
    k_vgastr_set_color(K_VGASTR_COLOR_LIGHT_BROWN + K_VGASTR_BGCOLOR_CYAN); \
    k_vgastr_printf("\n== DUMP DATA FROM POINTER [0x%x] AT %s(%s:%d) ==\n", \
                    __FUNCTION__, __FILE__, __LINE__, p);                   \
    for (int i = 0; i < n; i++) {                                           \
      k_vgastr_printf("0x%x", *p++);                                        \
      if (i > 0 && i % 16 == 0) {                                           \
        k_vgastr_write('\n');                                               \
      } else {                                                              \
        k_vgastr_write(' ');                                                \
      }                                                                     \
    }                                                                       \
    k_vgastr_write_str("\n== DUMP DATA END ==\n");                          \
    k_vgastr_set_color(color);                                              \
  }

#endif  // NDEBUG

#endif  //_KERNEL_DEBUG_H_
