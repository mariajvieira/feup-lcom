#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  if(timer < 0 || timer > 2) return 1;
  if(freq < 19 || freq > TIMER_FREQ) return 1;

  uint8_t control_word;
  if(timer_get_conf(timer,&control_word)!=0) return 1;

  control_word = (control_word & 0x0F) | TIMER_LSB_MSB;

  uint32_t init_val = TIMER_FREQ/freq;

  uint8_t msb=0, lsb =0;
  util_get_MSB(init_val,&msb);
  util_get_LSB(init_val,&lsb);

  uint8_t timer_address;
  switch(timer) {
    case 0: 
      control_word = control_word | TIMER_SEL0;
      timer_address = TIMER_0;
      break;
    case 1:
      control_word = control_word | TIMER_SEL1;
      timer_address = TIMER_1;
      break;
    case 2:
      control_word = control_word | TIMER_SEL2;
      timer_address = TIMER_2;
      break;
    default:
      return 1;
  }

  if(sys_outb(TIMER_CTRL,control_word)!=0) return 1;
  if(sys_outb(timer_address,lsb)!=0) return 1;
  if(sys_outb(timer_address,msb)!=0) return 1;

  return 0;


}

int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

void (timer_int_handler)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  if(st==NULL) return 1;
  if(timer < 0 || timer > 2) return 1;
  uint8_t readback = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);
  if(sys_outb(TIMER_CTRL, readback) != 0) return 1;
  if(util_sys_inb(TIMER_0 + timer, st) != 0) return 1;
  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {

  union timer_status_field_val field_data;

  switch (field) {
    case tsf_all:
      field_data.byte = st;
      break;
    case tsf_initial:
      st = (st >> 4) & 0x03;
      if (st == 1) field_data.in_mode = LSB_only;
      else if (st == 2) field_data.in_mode = MSB_only;
      else if (st==3) field_data.in_mode = MSB_after_LSB;
      else field_data.in_mode = INVAL_val;
      break;
    case tsf_mode:
      st = (st >> 1) & 0x07;
      if (st == 6) field_data.count_mode = 2;
      else if (st == 7) field_data.count_mode = 3;
      else field_data.count_mode = st;
      break;
    case tsf_base:
      field_data.bcd = st & TIMER_BCD;
      break;
    default:
    return 1;
  }

  if (timer_print_config(timer, field, field_data)!=0) return 1;
  
  return 0;
}
