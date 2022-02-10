#ifndef _KERNEL_ARCH_I386_CPU_IDT_H_
#define _KERNEL_ARCH_I386_CPU_IDT_H_

#include <kernel/libk/all.h>

// Address of kernel code segment
#define KERNEL_CS 0x08

// Entries count in Interrupt Descriptor Table
#define IDT_ENTRIES 256

// Structure for storing Gate entry
// http://wiki.osdev.org/Interrupt_Descriptor_Table#Location_and_Size
// 0..15 bits are Lo offset bits
// 16..31 bits is a code segment selector in GDT or LDT
// 32..39 bits are unused, set to 0
// 40..47 bits are type and attributes bits
// 48..63 bits are Hi offset bits
typedef struct {
  u16 low_offset;
  u16 sel;
  u8 always0;
  u8 flags;
  u16 high_offset;
} __attribute__((packed)) idt_gate_t;

// Structure for storing IDT location
// http://wiki.osdev.org/Interrupt_Descriptor_Table#Location_and_Size
// 0..15 bits defines the length of IDT
// 16..47 bits defines address where IDT starts
typedef struct {
  u16 limit;
  u32 base;
} __attribute__((packed)) idt_register_t;

// Declare array of IDT entries
extern idt_gate_t idt[IDT_ENTRIES];

// Declare structure with info about IDT location
extern idt_register_t idt_reg;

// Public API
void set_idt_gate(int n, u32 handler);
void set_idt();

#endif  //_KERNEL_ARCH_I386_CPU_IDT_H_
