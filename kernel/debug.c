#include "debug.h"

#include "libk.h"

void k_debug_assert(const char* _func, const char* _file, usize _line,
                    const char* msg, bool condition) {
  if (!condition) {
    DEBUG_KEEP_VGASTR_STATUS(DEBUG_MESSAGE_DEBUG_COLOR, {
      k_vgastr_printf("== ASSERT FAILURE: [%s] AT %s(%s:%d) ==\n", msg, _func,
                      _file, _line);
    })
  }
}

void k_debug_str(const char* _func, const char* _file, usize _line,
                 const char* prefix, const char* s) {
  DEBUG_KEEP_VGASTR_STATUS(DEBUG_MESSAGE_DEBUG_COLOR, {
    k_vgastr_printf("== %s: %s AT %s(%s:%d) ==\n", prefix, s, _func, _file,
                    _line);
  })
}

void k_debug_error(const char* _func, const char* _file, usize _line,
                   const char* prefix, const char* s) {
  DEBUG_KEEP_VGASTR_STATUS(DEBUG_MESSAGE_ERROR_COLOR, {
    k_vgastr_printf("== %s: %s AT %s(%s:%d) ==\n", prefix, s, _func, _file,
                    _line);
  })
}

void k_debug_int(const char* _func, const char* _file, usize _line,
                 const char* prefix, int n) {
  DEBUG_KEEP_VGASTR_STATUS(DEBUG_MESSAGE_DEBUG_COLOR, {
    k_vgastr_printf("== %s: 0x%d AT %s(%s:%d) ==\n", prefix, n, _func, _file,
                    _line);
  })
}

void k_debug_dump_ptr(const char* _func, const char* _file, usize _line,
                      const void* ptr, usize n) {
  DEBUG_KEEP_VGASTR_STATUS(DEBUG_MESSAGE_DEBUG_COLOR, {
    u8* p = (u8*)ptr;
    k_vgastr_printf("== DUMP DATA FROM POINTER [0x%x] AT %s(%s:%d) ==\n", _func,
                    _file, _line, p);
    for (usize i = 0; i < n; i++) {
      k_vgastr_printf("0x%x", *p++);
      if (i > 0 && i % 16 == 0) {
        k_vgastr_write('\n');
      } else {
        k_vgastr_write(' ');
      }
    }
    k_vgastr_write_str("\n== DUMP DATA END ==\n");
  })
}
