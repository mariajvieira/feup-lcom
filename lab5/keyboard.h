#ifndef LAB3_KEYBOARD_H
#define LAB3_KEYBOARD_H

#include <stdint.h>

#include "i8042.h"
#include "keyboard.c"
#ifdef kbc_ih
#  undef kbc_ih
#endif

void     kbc_ih(void);
int      kbd_subscribe_int(uint8_t *bit_no);
int      kbd_unsubscribe();

#endif /* LAB3_KEYBOARD_H */
