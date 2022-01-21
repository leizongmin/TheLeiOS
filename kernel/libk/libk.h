#ifndef _KERNEL_LIBK_H_
#define _KERNEL_LIBK_H_

#include <stdarg.h>
#include <stdbool.h>
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

#define LOW_8(address) (uint8_t)((address)&0xFF)
#define HIGH_8(address) (uint8_t)(((address) >> 8) & 0xFF)

#define LOW_16(address) (uint16_t)((address)&0xFFFF)
#define HIGH_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

#define LOW_32(address) (uint32_t)((address)&0xFFFFFFFF)
#define HIGH_32(address) (uint32_t)(((address) >> 32) & 0xFFFFFFFF)

#define LOW_64(address) (uint64_t)((address)&0xFFFFFFFFFFFFFFFF)
#define HIGH_64(address) (uint64_t)(((address) >> 64) & 0xFFFFFFFFFFFFFFFF)

void *k_mem_copy(void *__restrict__ dest, const void *__restrict__ src,
                 usize count);
void *k_mem_set(void *dest, u8 ch, usize count);

int k_str_cmp(const char *__restrict__ s1, const char *__restrict__ s2);
void k_str_reverse(char *s);
usize k_str_len(const char *s);
void k_str_append(char *s, char n);
usize k_str_append_str(char *__restrict__ s, usize sz,
                       const char *__restrict__ s2);
usize k_str_append_str_at(char *__restrict__ s, usize sz,
                          const char *__restrict__ s2, usize offset);
void k_str_backspace(char *s);
usize k_str_printf(char *__restrict__ buffer, usize bufsz,
                   const char *__restrict__ format, ...);
usize k_i32_to_str(char *buf, usize buf_size, i32 num, i32 radix);

#endif  //_KERNEL_LIBK_H_
