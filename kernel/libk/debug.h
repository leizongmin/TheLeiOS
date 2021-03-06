#ifndef _KERNEL_LIBK_DEBUG_H_
#define _KERNEL_LIBK_DEBUG_H_

#include "libk.h"

#define K_DEBUG_UNUSED(x) (void)(x)

// if there are many debug output place,
// define the function and variable name here
#define K_DEBUG_OUTPUT_TO_COM1
#ifdef K_DEBUG_OUTPUT_TO_VGA

#include "vgastr.h"

#define K_DEBUG_FUNCTION_WRITE_CHAR(c) k_vgatext_write(c)
#define K_DEBUG_FUNCTION_WRITE_STR(s) k_vgatext_write_str(s)
#define K_DEBUG_FUNCTION_WRITE_FORMAT(fmt, ...) \
  k_vgatext_printf(fmt, __VA_ARGS__)
#define K_DEBUG_FUNCTION_COLOR k_vgatext_color
#define K_DEBUG_FUNCTION_COLOR_SET(c) k_vgatext_set_color(c)
#define K_DEBUG_FUNCTION_OFFSET_COLUMN k_vgatext_offset_column

#else

#include <kernel/arch/i386/all.h>
#include <kernel/drivers/all.h>

#define K_DEBUG_FUNCTION_WRITE_CHAR(c) io_out8(IO_COM1, c)
#define K_DEBUG_FUNCTION_WRITE_STR(s) \
  {                                   \
    u8* _p = (u8*)s;                  \
    for (; *_p; _p++) {               \
      io_out8(IO_COM1, *_p);          \
    }                                 \
  }
#define K_DEBUG_FUNCTION_WRITE_FORMAT(fmt, ...)  \
  {                                              \
    const usize _size = 1024;                    \
    char _buf[_size];                            \
    _buf[0] = '\0';                              \
    k_str_printf(_buf, _size, fmt, __VA_ARGS__); \
    K_DEBUG_FUNCTION_WRITE_STR(_buf);            \
  }
#define K_DEBUG_FUNCTION_COLOR 0
#define K_DEBUG_FUNCTION_COLOR_SET(c) (void)(0)
#define K_DEBUG_FUNCTION_OFFSET_COLUMN 1

#endif  // K_DEBUG_OUTPUT_TO_VGA

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

#define K_DEBUG_MESSAGE_K_DEBUG_COLOR \
  (K_VGATEXT_COLOR_BLACK + K_VGATEXT_BGCOLOR_LIGHT_GREY)
#define K_DEBUG_MESSAGE_K_DEBUG_PREFIX "DEBUG"

#define K_DEBUG_MESSAGE_ERROR_COLOR \
  (K_VGATEXT_COLOR_LIGHT_RED + K_VGATEXT_BGCOLOR_DARK_GREY)
#define K_DEBUG_MESSAGE_ERROR_PREFIX "ERROR"

#define K_DEBUG_KEEP_CURRENT_OUTPUT_STATUS(c, x) \
  {                                              \
    u8 _color = K_DEBUG_FUNCTION_COLOR;          \
    K_DEBUG_UNUSED(_color);                      \
    K_DEBUG_FUNCTION_COLOR_SET(c);               \
    if (K_DEBUG_FUNCTION_OFFSET_COLUMN > 0) {    \
      K_DEBUG_FUNCTION_WRITE_CHAR('\n');         \
    }                                            \
    x;                                           \
    K_DEBUG_FUNCTION_COLOR_SET(_color);          \
  }

#ifdef NDEBUG

#define K_DEBUG_ASSERT(msg, condition) ((void)0)
#define K_DEBUG_PRINTF(fmt, ...) ((void)0)
#define K_DEBUG_STR(s) ((void)0)
#define K_DEBUG_INT(n) ((void)0)
#define K_DEBUG_DUMP_PTR(ptr, n) ((void)0)

#else

#define K_DEBUG_ASSERT(msg, condition) \
  k_debug_assert(__FUNCTION__, __FILE__, __LINE__, msg, condition)
#define K_DEBUG_STR(s)                          \
  k_debug_str(__FUNCTION__, __FILE__, __LINE__, \
              K_DEBUG_MESSAGE_K_DEBUG_PREFIX, s)
#define K_DEBUG_INT(n)                          \
  k_debug_int(__FUNCTION__, __FILE__, __LINE__, \
              K_DEBUG_MESSAGE_K_DEBUG_PREFIX, n)
#define K_DEBUG_PRINTF(fmt, ...)                                              \
  K_DEBUG_KEEP_CURRENT_OUTPUT_STATUS(K_DEBUG_MESSAGE_K_DEBUG_COLOR, {         \
    K_DEBUG_FUNCTION_WRITE_FORMAT("== %s: ", K_DEBUG_MESSAGE_K_DEBUG_PREFIX); \
    K_DEBUG_FUNCTION_WRITE_FORMAT(fmt, __VA_ARGS__);                          \
    K_DEBUG_FUNCTION_WRITE_FORMAT("\n== AT %s(%s:%d)\n", __FUNCTION__,        \
                                  __FILE__, __LINE__);                        \
  })
#define K_DEBUG_DUMP_PTR(ptr, n) \
  k_debug_dump_ptr(__FUNCTION__, __FILE__, __LINE__, ptr, n)

#endif  // NDEBUG

#define K_DEBUG_ERROR(s)                          \
  k_debug_error(__FUNCTION__, __FILE__, __LINE__, \
                K_DEBUG_MESSAGE_ERROR_PREFIX, s)
#define K_DEBUG_ERRORF(fmt, ...)                                            \
  K_DEBUG_KEEP_CURRENT_OUTPUT_STATUS(K_DEBUG_MESSAGE_ERROR_COLOR, {         \
    K_DEBUG_FUNCTION_WRITE_FORMAT("== %s: ", K_DEBUG_MESSAGE_ERROR_PREFIX); \
    K_DEBUG_FUNCTION_WRITE_FORMAT(fmt, __VA_ARGS__);                        \
    K_DEBUG_FUNCTION_WRITE_FORMAT("\n== AT %s(%s:%d)\n", __FUNCTION__,      \
                                  __FILE__, __LINE__);                      \
  })

#endif  //_KERNEL_LIBK_DEBUG_H_
