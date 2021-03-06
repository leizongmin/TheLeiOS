#include "keyboard.h"

#include <kernel/arch/i386/all.h>
#include <kernel/libk/all.h>

#include "vgatext.h"

#define BACKSPACE 0x0E
#define ENTER 0x1C

static char key_buffer[256];

#define SC_MAX 57

const char *sc_name[] = {
    "ERROR",     "Esc",     "1", "2", "3", "4",      "5",
    "6",         "7",       "8", "9", "0", "-",      "=",
    "Backspace", "Tab",     "Q", "W", "E", "R",      "T",
    "Y",         "U",       "I", "O", "P", "[",      "]",
    "Enter",     "Lctrl",   "A", "S", "D", "F",      "G",
    "H",         "J",       "K", "L", ";", "'",      "`",
    "LShift",    "\\",      "Z", "X", "C", "V",      "B",
    "N",         "M",       ",", ".", "/", "RShift", "Keypad *",
    "LAlt",      "Spacebar"};

const char sc_ascii[] = {
    '?', '?', '1', '2', '3', '4', '5', '6', '7', '8', '9',  '0', '-', '=',  '?',
    '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',  '[', ']', '?',  '?',
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z',
    'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/', '?', '?',  '?', ' '};

// Calls each time when key is pressed
static void keyboard_callback(registers_t regs) {
  // The PIC leaves us the scancode in port 0x60
  uint8_t scancode = port_byte_in(0x60);

  if (scancode > SC_MAX) return;
  if (scancode == BACKSPACE) {
    k_str_backspace(key_buffer);
    k_vgatext_backspace();
  } else if (scancode == ENTER) {
    k_vgatext_write_str("\n");
    user_input(key_buffer);
    key_buffer[0] = '\0';
  } else {
    char letter = sc_ascii[(int)scancode];
    char str[2] = {letter, '\0'};
    k_str_append(key_buffer, letter);
    k_vgatext_write_str(str);
  }

  K_DEBUG_UNUSED(regs);
}

// Maps keyboard_callback() to IRQ1 interrupt
void init_keyboard() { register_interrupt_handler(IRQ1, keyboard_callback); }
