#ifndef _KERNEL_DEBUG_H_
#define _KERNEL_DEBUG_H_

#include "libk/libk.h"

#define DEBUG_UNUSED(x) (void)(x)

// if there are many debug output place,
// define the function and variable name here
#define DEBUG_OUTPUT_TO_COM1
#ifdef DEBUG_OUTPUT_TO_VGA

#include "vgastr.h"

#define DEBUG_FUNCTION_WRITE_CHAR(c) k_vgastr_write(c)
#define DEBUG_FUNCTION_WRITE_STR(s) k_vgastr_write_str(s)
#define DEBUG_FUNCTION_WRITE_FORMAT(fmt, ...) k_vgastr_printf(fmt, __VA_ARGS__)
#define DEBUG_FUNCTION_COLOR k_vgastr_color
#define DEBUG_FUNCTION_COLOR_SET(c) k_vgastr_set_color(c)
#define DEBUG_FUNCTION_OFFSET_COLUMN k_vgastr_offset_column

#else

#include "io.h"
#include "vgastr.h"

#define DEBUG_FUNCTION_WRITE_CHAR(c) io_out8(IO_COM1, c)
#define DEBUG_FUNCTION_WRITE_STR(s) \
  {                                 \
    u8* _p = (u8*)s;                \
    for (; *_p; _p++) {             \
      io_out8(IO_COM1, *_p);        \
    }                               \
  }
#define DEBUG_FUNCTION_WRITE_FORMAT(fmt, ...)    \
  {                                              \
    const usize _size = 1024;                    \
    char _buf[_size];                            \
    _buf[0] = '\0';                              \
    k_str_printf(_buf, _size, fmt, __VA_ARGS__); \
    DEBUG_FUNCTION_WRITE_STR(_buf);              \
  }
#define DEBUG_FUNCTION_COLOR 0
#define DEBUG_FUNCTION_COLOR_SET(c) (void)(0)
#define DEBUG_FUNCTION_OFFSET_COLUMN 1

#endif  // DEBUG_OUTPUT_TO_VGA

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
  (K_VGASTR_COLOR_BLACK + K_VGASTR_BGCOLOR_LIGHT_GREY)
#define DEBUG_MESSAGE_DEBUG_PREFIX "DEBUG"

#define DEBUG_MESSAGE_ERROR_COLOR \
  (K_VGASTR_COLOR_LIGHT_RED + K_VGASTR_BGCOLOR_DARK_GREY)
#define DEBUG_MESSAGE_ERROR_PREFIX "ERROR"

#define DEBUG_KEEP_CURRENT_OUTPUT_STATUS(c, x) \
  {                                            \
    u8 _color = DEBUG_FUNCTION_COLOR;          \
    DEBUG_UNUSED(_color);                      \
    DEBUG_FUNCTION_COLOR_SET(c);               \
    if (DEBUG_FUNCTION_OFFSET_COLUMN > 0) {    \
      DEBUG_FUNCTION_WRITE_CHAR('\n');         \
    }                                          \
    x;                                         \
    DEBUG_FUNCTION_COLOR_SET(_color);          \
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
#define DEBUG_PRINTF(fmt, ...)                                                 \
  DEBUG_KEEP_CURRENT_OUTPUT_STATUS(DEBUG_MESSAGE_DEBUG_COLOR, {                \
    DEBUG_FUNCTION_WRITE_FORMAT("== %s: ", DEBUG_MESSAGE_DEBUG_PREFIX);        \
    DEBUG_FUNCTION_WRITE_FORMAT(fmt, __VA_ARGS__);                             \
    DEBUG_FUNCTION_WRITE_FORMAT("\n== AT %s(%s:%d)\n", __FUNCTION__, __FILE__, \
                                __LINE__);                                     \
  })
#define DEBUG_DUMP_PTR(ptr, n) \
  k_debug_dump_ptr(__FUNCTION__, __FILE__, __LINE__, ptr, n)

#endif  // NDEBUG

#define DEBUG_ERROR(s) \
  k_debug_error(__FUNCTION__, __FILE__, __LINE__, DEBUG_MESSAGE_ERROR_PREFIX, s)
#define DEBUG_ERRORF(fmt, ...)                                                 \
  DEBUG_KEEP_CURRENT_OUTPUT_STATUS(DEBUG_MESSAGE_ERROR_COLOR, {                \
    DEBUG_FUNCTION_WRITE_FORMAT("== %s: ", DEBUG_MESSAGE_ERROR_PREFIX);        \
    DEBUG_FUNCTION_WRITE_FORMAT(fmt, __VA_ARGS__);                             \
    DEBUG_FUNCTION_WRITE_FORMAT("\n== AT %s(%s:%d)\n", __FUNCTION__, __FILE__, \
                                __LINE__);                                     \
  })

#endif  //_KERNEL_DEBUG_H_
