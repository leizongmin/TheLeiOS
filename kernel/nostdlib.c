#include "nostdlib.h"

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
