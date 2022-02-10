#ifndef _KERNEL_LIBK_TYPES_H_
#define _KERNEL_LIBK_TYPES_H_

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

#endif  // _KERNEL_LIBK_TYPES_H_
