#include "memory.h"

#include "io.h"

namespace kernel::arch {

static usize detectMemorySizeFromCMOS() {
  usize total;
  u8 low, high;

  port_byte_out(0x70, 0x30);
  low = port_byte_in(0x71);
  port_byte_out(0x70, 0x31);
  high = port_byte_in(0x71);

  total = low | high << 8;
  return total;
}

usize detectMemorySize() { return detectMemorySizeFromCMOS(); }
}  // namespace kernel::arch
