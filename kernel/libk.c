#include "libk.h"

void *k_mem_copy(void *dest, const void *src, size_t count) {
  u8 *d = dest;
  const u8 *s = src;
  while (count--) {
    *d++ = *s++;
  }
  return dest;
}

void *k_mem_set(void *dest, u8 ch, size_t count) {
  u8 *d = dest;
  while (count--) {
    *d++ = ch;
  }
  return dest;
}

int k_str_cmp(const char *s1, const char *s2) {
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
