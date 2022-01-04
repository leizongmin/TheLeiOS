#include "libk.h"

#include "debug.h"

void *k_mem_copy(void *restrict dest, const void *restrict src, usize count) {
  u8 *d = dest;
  const u8 *s = src;
  while (count--) {
    *d++ = *s++;
  }
  return dest;
}

void *k_mem_set(void *dest, u8 ch, usize count) {
  u8 *d = dest;
  while (count--) {
    *d++ = ch;
  }
  return dest;
}

int k_str_cmp(const char *restrict s1, const char *restrict s2) {
  const char *l = s1, *r = s2;
  while (*l && (*l == *r)) {
    l++;
    r++;
  }
  return *l - *r;
}

void k_str_reverse(char *s) {
  char c;
  usize i, j;
  for (i = 0, j = k_str_len(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

usize k_str_len(const char *s) {
  int i = 0;
  while (s[i] != '\0') ++i;
  return i;
}

void k_str_append(char *s, char n) {
  usize len = k_str_len(s);
  s[len] = n;
  s[len + 1] = '\0';
}

void k_str_backspace(char *s) {
  usize len = k_str_len(s);
  s[len - 1] = '\0';
}

usize k_str_append_str(char *restrict s, usize sz, const char *restrict s2) {
  usize len = k_str_len(s);
  return k_str_append_str_at(s, sz, s2, len);
}

usize k_str_append_str_at(char *restrict s, usize sz, const char *restrict s2,
                          usize offset) {
  usize i = offset;
  for (; i < sz && *s2; i++) {
    *(s + i) = *s2++;
  }
  if (i >= sz) {
    *(s + sz - 1) = '\0';
  } else {
    *(s + i) = '\0';
  }
  return i - offset;
}

usize k_str_printf(char *restrict buffer, usize bufsz,
                   const char *restrict format, ...) {
  va_list args;
  va_start(args, format);

  const usize value_buf_size = 1024;
  char value_buf[value_buf_size];
  usize buffer_index = 0;

  while (*format && buffer_index < bufsz) {
    if (*format == '%') {
      switch (*(format + 1)) {
        case 'c':  // char
          buffer[buffer_index++] = (char)va_arg(args, int);
          break;
        case 's':  // string
          buffer_index += k_str_append_str_at(
              buffer, bufsz, va_arg(args, char *), buffer_index);
          break;
        case 'b':  // binary
          k_i32_to_str(value_buf, value_buf_size, va_arg(args, u32), 2);
          buffer_index +=
              k_str_append_str_at(buffer, bufsz, value_buf, buffer_index);
          break;
        case 'o':  // octonary
          k_i32_to_str(value_buf, value_buf_size, va_arg(args, u32), 8);
          buffer_index +=
              k_str_append_str_at(buffer, bufsz, value_buf, buffer_index);
          break;
        case 'd':  // decimal
          k_i32_to_str(value_buf, value_buf_size, va_arg(args, i32), 10);
          // K_DEBUG_DUMP_PTR(value_buf, 32);
          buffer_index +=
              k_str_append_str_at(buffer, bufsz, value_buf, buffer_index);
          break;
        case 'x':  // hexadecimal
          k_i32_to_str(value_buf, value_buf_size, va_arg(args, u32), 16);
          buffer_index +=
              k_str_append_str_at(buffer, bufsz, value_buf, buffer_index);
          break;
        case '%':  // %
          buffer[buffer_index++] = *format;
          break;
        default:  // not support
          buffer[buffer_index++] = *format;
          break;
      }
      format += 2;
    } else {
      buffer[buffer_index++] = *format;
      format++;
    }
  }

  va_end(args);

  if (buffer_index < bufsz) {
    buffer[buffer_index] = '\0';
  } else {
    buffer[bufsz - 1] = '\0';
  }

  return buffer_index;
}

// radix must be between 2 and 36
usize k_i32_to_str(char *buf, usize buf_size, i32 num, i32 radix) {
  char tmp[buf_size];
  char num_str[37] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  i32 i = 0;
  i32 len = 0;
  i32 rem;
  char sign = '+';

  // reverse write to tmp
  tmp[i++] = '\0';
  if (num < 0) {
    sign = '-';
    num = 0 - num;
  } else if (num == 0) {
    tmp[i++] = '0';
  }

  // number to string
  while (num > 0) {
    rem = num % radix;
    tmp[i++] = num_str[rem];
    num = num / radix;
  }
  // number sign
  if (sign == '-') {
    tmp[i++] = sign;
  }
  len = i;

  // copy tmp chars to buf
  for (i = len - 1; i >= 0; i--) {
    *buf++ = tmp[i];
  }

  return len;
}
