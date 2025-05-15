#include <lcom/lcf.h>
#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>

#include "i8042.h"

extern uint8_t scancode;
extern uint32_t sys_inb_cnt;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (kbd_test_scan)() {
  uint8_t bit_no = kbd_hook_id;
  if (kbd_subscribe_int(&bit_no) != 0)
    return 1;
  uint32_t irq_set = BIT(bit_no);

  message msg;
  int ipc_status;
  uint8_t bytes[2];
  uint8_t size = 0;
  bool two_byte = false;

  while (true) {
    if (driver_receive(ANY, &msg, &ipc_status) != 0)
      continue;
    if (is_ipc_notify(ipc_status) &&
        _ENDPOINT_P(msg.m_source) == HARDWARE &&
        (msg.m_notify.interrupts & irq_set)) {

      kbc_ih();
      uint8_t code = scancode;

      if (code == TWO_BYTE_CODE && !two_byte) {
        two_byte = true;
        bytes[0] = code;
        size = 1;
      }
      else {
        bytes[size++] = code;
        bool make = !(bytes[size - 1] & BREAK_MASK);
        kbd_print_scancode(make, size, bytes);
        if (!make && bytes[0] == ESC_BREAK_CODE)
          break;
        two_byte = false;
        size = 0;
      }
    }
  }

  if (kbd_unsubscribe() != 0)
    return 1;
  kbd_print_no_sysinb(sys_inb_cnt);
  return 0;
}

int(kbd_test_poll)() {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int(kbd_test_timed_scan)(uint8_t n) {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}
