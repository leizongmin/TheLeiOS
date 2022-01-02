#include "nostdlib.h"

int k_strcmp(const char *s1, const char *s2) {
  const char *l = s1, *r = s2;
  while (*l && (*l == *r)) {
    l++;
    r++;
  }
  return *l - *r;
}
