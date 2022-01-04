// Implementation for Programmable Interval Timer
// http://wiki.osdev.org/Programmable_Interval_Timer

#include "timer.h"

#include "../debug.h"
#include "isr.h"
#include "ports.h"

u32 tick = 0;

// Callback for timer
// Triggers each time when hardware interrupt occurred
static void timer_callback(registers_t regs) {
  tick++;
  K_DEBUG_UNUSED(regs);
}

// Initialize PIC
// http://wiki.osdev.org/Programmable_Interval_Timer#PIT_Channel_0_Example_Code
void init_timer(u32 freq) {
  register_interrupt_handler(IRQ0, timer_callback);

  u32 divisor = 1193180 / freq;
  u8 low = (u8)(divisor & 0xFF);
  u8 high = (u8)((divisor >> 8) & 0xFF);

  port_byte_out(0x43, 0x36);
  port_byte_out(0x40, low);
  port_byte_out(0x40, high);
}
