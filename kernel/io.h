#ifndef _KERNEL_IO_H_
#define _KERNEL_IO_H_

#include <stdbool.h>

#include "types.h"

#define IO_COM1 0x3F8
#define IO_COM2 0x2F8
#define IO_COM3 0x3E8
#define IO_COM4 0x2E8

/* Read a 8/16/32-bit value at a given memory location using another segment
 than the default C data segment. Unfortunately there is no constraint for
 manipulating segment registers directly, so issuing the mov <reg>,
 <segmentreg> manually is required.
 From https://wiki.osdev.org/Inline_Assembly/Examples */
static inline u32 io_farpeekl(u16 sel, void* off) {
  u32 ret;
  __asm__ volatile(
      "push %%fs\n\t"
      "mov  %1, %%fs\n\t"
      "mov  %%fs:(%2), %0\n\t"
      "pop  %%fs"
      : "=r"(ret)
      : "g"(sel), "r"(off));
  return ret;
}

/* Write a 8/16/32-bit value to a segment:offset address too. Note that much
 like in farpeek, this version of farpoke saves and restore the segment
 register used for the access.
 From https://wiki.osdev.org/Inline_Assembly/Examples */
static inline void io_farpokeb(u16 sel, void* off, u8 v) {
  __asm__ volatile(
      "push %%fs\n\t"
      "mov  %0, %%fs\n\t"
      "movb %2, %%fs:(%1)\n\t"
      "pop %%fs"
      :
      : "g"(sel), "r"(off), "r"(v));
  /* TODO: Should "memory" be in the clobber list here? */
}

static inline void io_hlt(void) { __asm__ volatile("hlt" : :); }

static inline void io_cli() { __asm__ volatile("cli" ::); }

static inline void io_sti() { __asm__ volatile("sti" ::); }

static inline void io_stihlt() {
  __asm__ volatile(
      "sti\n\t"
      "hlt");
}

/* Receives a 8/16/32-bit value from an I/O location. Traditional names are inb,
inw and inl respectively. */
static inline u8 io_in8(u16 port) {
  u8 data;
  __asm__ volatile("inb %%dx,%%al" : "=a"(data) : "d"(port));
  return data;
}

static inline u16 io_in16(u16 port) {
  u16 data;
  __asm__ volatile("inb %%dx,%%al" : "=a"(data) : "d"(port));
  return data;
}

static inline u32 io_in32(u16 port) {
  u32 data;
  __asm__ volatile("inb %%dx,%%al" : "=a"(data) : "d"(port));
  return data;
}

/* Sends a 8/16/32-bit value on a I/O location. Traditional names are outb, outw
 and outl respectively. The a modifier enforces val to be placed in the eax
 register before the asm command is issued and Nd allows for one-byte constant
 values to be assembled as constants, freeing the edx register for other
 cases. */
static inline void io_out8(u16 port, u8 data) {
  __asm__ volatile("outb %%al,%%dx" : : "a"(data), "d"(port));
}

static inline void io_out16(u16 port, u16 data) {
  __asm__ volatile("outb %%al,%%dx" : : "a"(data), "d"(port));
}

static inline void io_out32(u16 port, u32 data) {
  __asm__ volatile("outb %%al,%%dx" : : "a"(data), "d"(port));
}

/* Wait a very small amount of time (1 to 4 microseconds, generally). Useful for
implementing a small delay for PIC remapping on old hardware or generally as a
simple but imprecise wait.

You can do an IO operation on any unused port: the Linux kernel by default uses
port 0x80, which is often used during POST to log information on the
motherboard's hex display but almost always unused after boot.
 From https://wiki.osdev.org/Inline_Assembly/Examples */
static inline void io_wait(void) { io_out8(0x80, 0); }

/* Returns a true boolean value if irq are enabled for the CPU.
From https://wiki.osdev.org/Inline_Assembly/Examples*/
static inline bool io_is_interrupts_enabled() {
  u32 flags;
  __asm__ volatile(
      "pushf\n\t"
      "pop %0"
      : "=g"(flags));
  return flags & (1 << 9);
}

/* Push/pop interrupt flag
 From https://wiki.osdev.org/Inline_Assembly/Examples */
static inline u32 io_save_irqdisable(void) {
  u32 flags;
  __asm__ volatile("pushf\n\tcli\n\tpop %0" : "=r"(flags) : : "memory");
  return flags;
}

/* Pop interrupt flag
 From https://wiki.osdev.org/Inline_Assembly/Examples */
static inline void io_irqrestore(u32 flags) {
  __asm__("push %0\n\tpopf" : : "rm"(flags) : "memory", "cc");
}

/* Define a new interrupt table.
 From https://wiki.osdev.org/Inline_Assembly/Examples */
static inline void io_lidt(void* base, u16 size) {
  // This function works in 32 and 64bit mode
  struct {
    u16 length;
    void* base;
  } __attribute__((packed)) IDTR = {size, base};
  __asm__ volatile("lidt %0"
                   :
                   : "m"(IDTR));  // let the compiler choose an addressing mode
}

/* Read the current value of the CPU's time-stamp counter and store into
EDX:EAX. The time-stamp counter contains the amount of clock ticks that have
elapsed since the last CPU reset. The value is stored in a 64-bit MSR and is
incremented after each clock cycle.
 From https://wiki.osdev.org/Inline_Assembly/Examples */
static inline u64 io_rdtsc() {
  u64 ret;
  __asm__ volatile("rdtsc" : "=A"(ret));
  return ret;
}

/* This can be used to find out how much time it takes to do certain functions,
very useful for testing/benchmarking /etc. Note: This is only an approximation.

On x86_64, the "A" constraint expects to write into the "rdx:rax" registers
instead of "edx:eax". So GCC can in fact optimize the above code by not setting
"rdx" at all. You instead need to do it manually with bitshifting:
 From https://wiki.osdev.org/Inline_Assembly/Examples */
static inline u64 io_rdtsc_x64(void) {
  u32 low, high;
  __asm__ volatile("rdtsc" : "=a"(low), "=d"(high));
  return ((u64)high << 32) | low;
}

/* Read the value in a control register. From
 https://wiki.osdev.org/Inline_Assembly/Examples */
static inline u32 io_read_cr0(void) {
  u32 val;
  __asm__ volatile("mov %%cr0, %0" : "=r"(val));
  return val;
}

/* Invalidates the TLB (Translation Lookaside Buffer) for one specific virtual
address. The next memory reference for the page will be forced to re-read PDE
and PTE from main memory. Must be issued every time you update one of those
tables. The m pointer points to a logical address, not a physical or virtual
one: an offset for your ds segment.
From https://wiki.osdev.org/Inline_Assembly/Examples */
static inline void io_invlpg(void* m) {
  /* Clobber memory to avoid optimizer re-ordering access before invlpg, which
   * may cause nasty bugs. */
  __asm__ volatile("invlpg (%0)" : : "b"(m) : "memory");
}

/* Write a 64-bit value to a MSR. The A constraint stands for concatenation of
registers EAX and EDX.
From https://wiki.osdev.org/Inline_Assembly/Examples */
static inline void io_wrmsr(u32 msr_id, u64 msr_value) {
  __asm__ volatile("wrmsr" : : "c"(msr_id), "A"(msr_value));
}

/* Write a 64-bit value to a MSR. The A constraint stands for concatenation of
registers EAX and EDX.
From https://wiki.osdev.org/Inline_Assembly/Examples */
// static inline void io_wrmsr_x64(u64 msr, u64 value) {
//   u32 low = value & 0xFFFFFFFF;
//   u32 high = value >> 32;
//   // FIXME:
//   //  __asm__ volatile("wrmsr" : : "c"(msr), "a"(low), "d"(high));
// }

/* Read a 64-bit value from a MSR. The A constraint stands for concatenation of
registers EAX and EDX.
From https://wiki.osdev.org/Inline_Assembly/Examples */
static inline u64 io_rdmsr(u32 msr_id) {
  u64 msr_value;
  __asm__ volatile("rdmsr" : "=A"(msr_value) : "c"(msr_id));
  return msr_value;
}

/* Read a 64-bit value from a MSR. The A constraint stands for concatenation of
registers EAX and EDX.
From https://wiki.osdev.org/Inline_Assembly/Examples */
// static inline u64 io_rdmsr_x64(u64 msr) {
//   u32 low, high;
//   // FIXME:
//   //  __asm__ volatile("rdmsr" : "=a"(low), "=d"(high) : "c"(msr));
//   return ((u64)high << 32) | low;
// }

// https://wiki.osdev.org/8259_PIC
// Common Definitions
#define PIC1 0x20 /* IO base address for master PIC */
#define PIC2 0xA0 /* IO base address for slave PIC */
#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1 + 1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA (PIC2 + 1)

// End of Interrupt
#define PIC_EOI 0x20 /* End-of-interrupt command code */
// void PIC_sendEOI(u8 irq) {
//   if (irq >= 8) io_out8(PIC2_COMMAND, PIC_EOI);
//   io_out8(PIC1_COMMAND, PIC_EOI);
// }

// Initialisation
/* reinitialize the PIC controllers, giving them specified vector offsets
   rather than 8h and 70h, as configured by default */
#define ICW1_ICW4 0x01       /* ICW4 (not) needed */
#define ICW1_SINGLE 0x02     /* Single (cascade) mode */
#define ICW1_INTERVAL4 0x04  /* Call address interval 4 (8) */
#define ICW1_LEVEL 0x08      /* Level triggered (edge) mode */
#define ICW1_INIT 0x10       /* Initialization - required! */
#define ICW4_8086 0x01       /* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO 0x02       /* Auto (normal) EOI */
#define ICW4_BUF_SLAVE 0x08  /* Buffered mode/slave */
#define ICW4_BUF_MASTER 0x0C /* Buffered mode/master */
#define ICW4_SFNM 0x10       /* Special fully nested (not) */

/*
arguments:
        offset1 - vector offset for master PIC
                vectors on the master become offset1..offset1+7
        offset2 - same for slave PIC: offset2..offset2+7
*/
// void PIC_remap(i32 offset1, i32 offset2) {
//   u8 a1, a2;
//
//   a1 = io_in8(PIC1_DATA);  // save masks
//   a2 = io_in8(PIC2_DATA);
//
//   io_out8(
//       PIC1_COMMAND,
//       ICW1_INIT |
//           ICW1_ICW4);  // starts the initialization sequence (in cascade
//           mode)
//   io_wait();
//   io_out8(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
//   io_wait();
//   io_out8(PIC1_DATA, offset1);  // ICW2: Master PIC vector offset
//   io_wait();
//   io_out8(PIC2_DATA, offset2);  // ICW2: Slave PIC vector offset
//   io_wait();
//   io_out8(PIC1_DATA, 4);  // ICW3: tell Master PIC that there is a slave PIC
//   at
//                           // IRQ2 (0000 0100)
//   io_wait();
//   io_out8(PIC2_DATA,
//           2);  // ICW3: tell Slave PIC its cascade identity (0000 0010)
//   io_wait();
//
//   io_out8(PIC1_DATA, ICW4_8086);
//   io_wait();
//   io_out8(PIC2_DATA, ICW4_8086);
//   io_wait();
//
//   io_out8(PIC1_DATA, a1);  // restore saved masks.
//   io_out8(PIC2_DATA, a2);
// }
//
//// Masking
// void IRQ_set_mask(unsigned char IRQline) {
//   u16 port;
//   u8 value;
//
//   if (IRQline < 8) {
//     port = PIC1_DATA;
//   } else {
//     port = PIC2_DATA;
//     IRQline -= 8;
//   }
//   value = io_in8(port) | (1 << IRQline);
//   io_out8(port, value);
// }
//
// void IRQ_clear_mask(unsigned char IRQline) {
//   u16 port;
//   u8 value;
//
//   if (IRQline < 8) {
//     port = PIC1_DATA;
//   } else {
//     port = PIC2_DATA;
//     IRQline -= 8;
//   }
//   value = io_in8(port) & ~(1 << IRQline);
//   io_out8(port, value);
// }

#endif  //_KERNEL_IO_H_
