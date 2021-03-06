#ifndef _KERNEL_DRIVERS_KEYBOARD_H
#define _KERNEL_DRIVERS_KEYBOARD_H

#define KB_ESC 0x1B
#define KB_ENTER 0x0A
#define KB_TAB 0x09
#define KB_BACK 0x08
#define KB_SPACE 0x20

#define KB_F1 (0X100 | 59)
#define KB_F2 (0X100 | 60)
#define KB_F3 (0X100 | 61)
#define KB_F4 (0X100 | 62)
#define KB_F5 (0X100 | 63)
#define KB_F6 (0X100 | 64)
#define KB_F7 (0X100 | 65)
#define KB_F8 (0X100 | 66)
#define KB_F9 (0X100 | 67)
#define KB_F10 (0X100 | 68)
#define KB_F11 (0X100 | 133)
#define KB_F12 (0X100 | 134)

#define KB_SHIFT_F1 (0X100 | 84)
#define KB_SHIFT_F2 (0X100 | 85)
#define KB_SHIFT_F3 (0X100 | 86)
#define KB_SHIFT_F4 (0X100 | 87)
#define KB_SHIFT_F5 (0X100 | 88)
#define KB_SHIFT_F6 (0X100 | 89)
#define KB_SHIFT_F7 (0X100 | 90)
#define KB_SHIFT_F8 (0X100 | 91)
#define KB_SHIFT_F9 (0X100 | 92)
#define KB_SHIFT_F10 (0X100 | 93)
#define KB_SHIFT_F11 (0X100 | 135)
#define KB_SHIFT_F12 (0X100 | 136)

#define KB_CTRL_F1 (0X100 | 94)
#define KB_CTRL_F2 (0X100 | 95)
#define KB_CTRL_F3 (0X100 | 96)
#define KB_CTRL_F4 (0X100 | 97)
#define KB_CTRL_F5 (0X100 | 98)
#define KB_CTRL_F6 (0X100 | 99)
#define KB_CTRL_F7 (0X100 | 100)
#define KB_CTRL_F8 (0X100 | 101)
#define KB_CTRL_F9 (0X100 | 102)
#define KB_CTRL_F10 (0X100 | 103)
#define KB_CTRL_F11 (0X100 | 137)
#define KB_CTRL_F12 (0X100 | 138)

#define KB_ALT_F1 (0X100 | 104)
#define KB_ALT_F2 (0X100 | 105)
#define KB_ALT_F3 (0X100 | 106)
#define KB_ALT_F4 (0X100 | 107)
#define KB_ALT_F5 (0X100 | 108)
#define KB_ALT_F6 (0X100 | 109)
#define KB_ALT_F7 (0X100 | 110)
#define KB_ALT_F8 (0X100 | 111)
#define KB_ALT_F9 (0X100 | 112)
#define KB_ALT_F10 (0X100 | 113)
#define KB_ALT_F11 (0X100 | 139)
#define KB_ALT_F12 (0X100 | 140)

#define KB_UP (0X100 | 72)
#define KB_LEFT (0X100 | 75)
#define KB_RIGHT (0X100 | 77)
#define KB_DOWN (0X100 | 80)
#define KB_HOME (0X100 | 71)
#define KB_END (0X100 | 79)
#define KB_PGUP (0X100 | 73)
#define KB_PGDN (0X100 | 81)
#define KB_INSERT (0X100 | 82)
#define KB_DELETE (0X100 | 83)

#define KB_CTRL_UP (0X100 | 132)
#define KB_CTRL_LEFT (0X100 | 115)
#define KB_CTRL_RIGHT (0X100 | 116)
#define KB_CTRL_DOWN (0X100 | 145)
#define KB_CTRL_HOME (0X100 | 119)
#define KB_CTRL_END (0X100 | 117)
#define KB_CTRL_PGUP (0X100 | 132)
#define KB_CTRL_PGDN (0X100 | 118)
#define KB_CTRL_INSERT (0X100 | 146)
#define KB_CTRL_DELETE (0X100 | 147)

#define KB_ALT_UP (0X100 | 152)
#define KB_ALT_LEFT (0X100 | 155)
#define KB_ALT_RIGHT (0X100 | 157)
#define KB_ALT_DOWN (0X100 | 154)
#define KB_ALT_HOME (0X100 | 151)
#define KB_ALT_END (0X100 | 159)
#define KB_ALT_PGUP (0X100 | 153)
#define KB_ALT_PGDN (0X100 | 161)
#define KB_ALT_INSERT (0X100 | 162)
#define KB_ALT_DELETE (0X100 | 163)

void init_keyboard();
void user_input(char *input);

#endif  //_KERNEL_DRIVERS_KEYBOARD_H
