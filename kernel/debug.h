#ifndef _KERNEL_DEBUG_H_
#define _KERNEL_DEBUG_H_

#include <stdbool.h>

#include "vgastr.h"

void k_debug_assert(const char* _func, const char* _file, usize line,
                    const char* msg, bool condition);
void k_debug_str(const char* _func, const char* _file, usize line,
                 const char* prefix, const char* s);
void k_debug_int(const char* _func, const char* _file, usize line,
                 const char* prefix, int n);
void k_debug_dump_ptr(const char* _func, const char* _file, usize line,
                      const void* ptr, usize n);
void k_debug_error(const char* _func, const char* _file, usize _line,
                   const char* prefix, const char* s);

#define DEBUG_MESSAGE_DEBUG_COLOR \
  (K_VGASTR_COLOR_LIGHT_BROWN + K_VGASTR_BGCOLOR_CYAN)
#define DEBUG_MESSAGE_DEBUG_PREFIX "DEBUG"

#define DEBUG_MESSAGE_ERROR_COLOR \
  (K_VGASTR_COLOR_LIGHT_RED + K_VGASTR_BGCOLOR_DARK_GREY)
#define DEBUG_MESSAGE_ERROR_PREFIX "ERROR"

#define DEBUG_KEEP_VGASTR_STATUS(c, x) \
  {                                    \
    u8 color = k_vgastr_color;         \
    k_vgastr_set_color(c);             \
    if (k_vgastr_offset_column > 0) {  \
      k_vgastr_write('\n');            \
    }                                  \
    x;                                 \
    k_vgastr_set_color(color);         \
  }

#ifdef NDEBUG

#define DEBUG_ASSERT(msg, condition) ((void)0)
#define DEBUG_PRINTF(fmt, ...) ((void)0)
#define DEBUG_STR(s) ((void)0)
#define DEBUG_INT(n) ((void)0)
#define DEBUG_DUMP_PTR(ptr, n) ((void)0)

#else

#define DEBUG_ASSERT(msg, condition) \
  k_debug_assert(__FUNCTION__, __FILE__, __LINE__, msg, condition)
#define DEBUG_STR(s) \
  k_debug_str(__FUNCTION__, __FILE__, __LINE__, DEBUG_MESSAGE_DEBUG_PREFIX, s)
#define DEBUG_INT(n) \
  k_debug_int(__FUNCTION__, __FILE__, __LINE__, DEBUG_MESSAGE_DEBUG_PREFIX, n)
#define DEBUG_PRINTF(fmt, ...)                                               \
  DEBUG_KEEP_VGASTR_STATUS(DEBUG_MESSAGE_DEBUG_COLOR, {                      \
    k_vgastr_printf("== %s ", DEBUG_MESSAGE_DEBUG_PREFIX);                   \
    k_vgastr_printf(fmt, __VA_ARGS__);                                       \
    k_vgastr_printf(" AT %s(%s:%d) ==\n", __FUNCTION__, __FILE__, __LINE__); \
  })
#define DEBUG_DUMP_PTR(ptr, n) \
  k_debug_dump_ptr(__FUNCTION__, __FILE__, __LINE__, ptr, n)

#endif  // NDEBUG

#define DEBUG_UNUSED(x) (void)(x)
#define DEBUG_ERROR(s) \
  k_debug_error(__FUNCTION__, __FILE__, __LINE__, DEBUG_MESSAGE_ERROR_PREFIX, s)
#define DEBUG_ERRORF(fmt, ...)                                               \
  DEBUG_KEEP_VGASTR_STATUS(DEBUG_MESSAGE_ERROR_COLOR, {                      \
    k_vgastr_printf("== %s ", DEBUG_MESSAGE_ERROR_PREFIX);                   \
    k_vgastr_printf(fmt, __VA_ARGS__);                                       \
    k_vgastr_printf(" AT %s(%s:%d) ==\n", __FUNCTION__, __FILE__, __LINE__); \
  })

#endif  //_KERNEL_DEBUG_H_
