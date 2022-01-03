#ifndef _KERNEL_LIBK_H_
#define _KERNEL_LIBK_H_

#include <stddef.h>
#include <stdint.h>

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define u64 uint64_t
#define i8 int8_t
#define i16 int16_t
#define i32 int32_t
#define i64 int64_t
#define f32 float
#define f64 double
#define usize size_t

void *k_mem_copy(void *dest, const void *src, size_t count);
void *k_mem_set(void *dest, u8 ch, size_t count);

int k_str_cmp(const char *s1, const char *s2);
void k_str_reverse(char *s);
usize k_str_len(const char *s);
void k_str_append(char *s, char n);
void k_str_backspace(char *s);

usize k_i32_to_str(char *buf, usize buf_size, i32 num, i32 radix);

#endif  //_KERNEL_LIBK_H_
