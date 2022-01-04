#include "debug.h"

#include "libk/libk.h"

void k_debug_assert(const char* _func, const char* _file, usize _line,
                    const char* msg, bool condition) {
  if (!condition) {
    K_DEBUG_KEEP_CURRENT_OUTPUT_STATUS(K_DEBUG_MESSAGE_K_DEBUG_COLOR, {
      K_DEBUG_FUNCTION_WRITE_FORMAT(
          "== ASSERT FAILURE: [%s]\n== AT %s(%s:%d)\n", msg, _func, _file,
          _line);
    })
  }
}

void k_debug_str(const char* _func, const char* _file, usize _line,
                 const char* prefix, const char* s) {
  K_DEBUG_KEEP_CURRENT_OUTPUT_STATUS(K_DEBUG_MESSAGE_K_DEBUG_COLOR, {
    K_DEBUG_FUNCTION_WRITE_FORMAT("== %s: %s\n== AT %s(%s:%d)\n", prefix, s,
                                  _func, _file, _line);
  })
}

void k_debug_error(const char* _func, const char* _file, usize _line,
                   const char* prefix, const char* s) {
  K_DEBUG_KEEP_CURRENT_OUTPUT_STATUS(K_DEBUG_MESSAGE_ERROR_COLOR, {
    K_DEBUG_FUNCTION_WRITE_FORMAT("== %s: %s\n== AT %s(%s:%d)\n", prefix, s,
                                  _func, _file, _line);
  })
}

void k_debug_int(const char* _func, const char* _file, usize _line,
                 const char* prefix, int n) {
  K_DEBUG_KEEP_CURRENT_OUTPUT_STATUS(K_DEBUG_MESSAGE_K_DEBUG_COLOR, {
    K_DEBUG_FUNCTION_WRITE_FORMAT("== %s: 0x%d\n== AT %s(%s:%d)\n", prefix, n,
                                  _func, _file, _line);
  })
}

void k_debug_dump_ptr(const char* _func, const char* _file, usize _line,
                      const void* ptr, usize n) {
  K_DEBUG_KEEP_CURRENT_OUTPUT_STATUS(K_DEBUG_MESSAGE_K_DEBUG_COLOR, {
    const usize bytes_per_line = 10;
    u8* p = (u8*)ptr;
    K_DEBUG_FUNCTION_WRITE_FORMAT(
        "== DUMP DATA FROM POINTER [0x%x]\n== AT %s(%s:%d)\n", p, _func, _file,
        _line);
    usize i = 0;
    for (; i < n; i++, p++) {
      K_DEBUG_FUNCTION_WRITE_FORMAT("0x%x ", *p);
      if (i > 0 && i % bytes_per_line == 0) {
        K_DEBUG_FUNCTION_WRITE_STR(" | ");
        for (u8* p2 = p - bytes_per_line; p2 < p; p2++) {
          K_DEBUG_FUNCTION_WRITE_CHAR(*p2);
        }
        K_DEBUG_FUNCTION_WRITE_CHAR('\n');
      }
    }
    K_DEBUG_FUNCTION_WRITE_STR(" | ");
    for (u8* p2 = p - i % bytes_per_line; p2 < p; p2++) {
      K_DEBUG_FUNCTION_WRITE_CHAR(*p2);
    }
    K_DEBUG_FUNCTION_WRITE_STR("\n== DUMP DATA END ==\n");
  })
}
