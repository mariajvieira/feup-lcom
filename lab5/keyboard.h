#ifndef LAB5_KEYBOARD_H
#define LAB5_KEYBOARD_H

#include <stdint.h>

#include "i8042.h"


extern uint8_t scancode;

void     (kbc_ih)();
int      kbd_subscribe_int(uint8_t *bit_no);
int      kbd_unsubscribe();

#endif /* LAB5_KEYBOARD_H */


