#include <lcom/lcf.h>
#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>

#include "i8042.h"

extern uint8_t scancode;
extern int kbd_hook_id; 
extern uint32_t sys_inb_cnt;

int main(int argc, char *argv[]) {
  lcf_set_language("EN-US");
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");
  lcf_log_output("/home/lcom/labs/lab3/output.txt");
  if (lcf_start(argc, argv))
    return 1;

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
  uint8_t bytes[2];
  uint8_t size = 0;
  bool two_byte = false;
  
  while(1) {
    uint8_t status;
    util_sys_inb(STAT_REG, &status);
    
    if (status & (PAR_ERR | TO_ERR)) {
      uint8_t dummy;
      util_sys_inb(OUT_BUF, &dummy);
      size = 0;
      two_byte = false;
      continue;
    }
      
    if (status & OBF) {
      util_sys_inb(OUT_BUF, &bytes[size]);
      uint8_t code = bytes[size];
      size++;

      if (code == TWO_BYTE_CODE && !two_byte) {
        two_byte = true;
        size = 1;
        continue;
      }

      bool make = !(bytes[size-1] & BREAK_MASK);
      kbd_print_scancode(make, size, bytes);
      
      if (!make && (two_byte ? bytes[0] == TWO_BYTE_CODE && bytes[1] == (ESC_BREAK_CODE & ~BREAK_MASK) 
                             : bytes[0] == ESC_BREAK_CODE)) {
        break;
      }
      
      two_byte = false;
      size = 0;
    }
  }
  
  uint8_t cmd_byte;
  sys_outb(STAT_REG, 0x20); 
  util_sys_inb(OUT_BUF, &cmd_byte);
  cmd_byte |= 0x01;               // Habilitar bit de interrupção do teclado
  sys_outb(STAT_REG, 0x60);       // Comando para escrever command byte
  sys_outb(OUT_BUF, cmd_byte);
  
  kbd_print_no_sysinb(sys_inb_cnt);
  return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {
  uint8_t kbd_bit_no = 1, timer_bit_no = 0;
  uint32_t kbd_irq = BIT(kbd_bit_no);
  uint32_t timer_irq = BIT(timer_bit_no);
  int ipc_status;
  message msg;
  
  if(kbd_subscribe_int(&kbd_bit_no) || timer_subscribe_int(&timer_bit_no))
    return 1;

  uint8_t bytes[2] = {0};
  uint8_t size = 0;
  bool two_byte = false;
  int timer_counter = 0;
  bool exit = false;

  while(!exit) {
    if(driver_receive(ANY, &msg, &ipc_status)) continue;
    
    if(is_ipc_notify(ipc_status)) {
      if(_ENDPOINT_P(msg.m_source) == HARDWARE) {
        if(msg.m_notify.interrupts & kbd_irq) {
          kbc_ih();
          uint8_t code = scancode;

          if(code == TWO_BYTE_CODE && !two_byte) {
            two_byte = true;
            bytes[0] = code;
            size = 1;
          } else {
            bytes[size++] = code;
            bool make = !(bytes[size-1] & BREAK_MASK);
            kbd_print_scancode(make, size, bytes);
            
            if(!make && bytes[0] == ESC_BREAK_CODE) exit = true;
            
            two_byte = false;
            size = 0;
            timer_counter = 0;
          }
        }
        
        if(msg.m_notify.interrupts & timer_irq) {
          timer_counter++;
          if(timer_counter >= n * 60) exit = true;
        }
      }
    }
  }

  if(kbd_unsubscribe() || timer_unsubscribe_int()) return 1;
  
  kbd_print_no_sysinb(sys_inb_cnt);
  return 0;
}
