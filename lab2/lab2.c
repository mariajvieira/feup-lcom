#include <lcom/lcf.h>
#include <lcom/lab2.h>

#include <stdbool.h>
#include <stdint.h>

extern int counter;
extern int hook_id;


int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab2/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab2/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(timer_test_read_config)(uint8_t timer, enum timer_status_field field) {
  
  uint8_t conf;
  // read the configuration of the timer
  if(timer_get_conf(timer, &conf)!=0) return 1;

  // display the configuration depending on the field
  if(timer_display_conf(timer, conf, field)!=0) return 1;
  
  return 0;
}

int(timer_test_time_base)(uint8_t timer, uint32_t freq) {
  if(timer_set_frequency(timer,freq)!=0) return 1;

  return 0;
}

int(timer_test_int)(uint8_t time) {
  
  uint8_t bit_no = 0;
  uint32_t irq_set = BIT(bit_no);

  if (timer_subscribe_int(&bit_no) != 0) return 1;
  if (timer_set_frequency(0, 60) != 0) return 1;  

  message m;
  int ipc_status;

  while (time > 0) {
    if (driver_receive(ANY, &m, &ipc_status) != 0) {
      printf("driver_receive failed\n");
      continue;
    }

    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(m.m_source)) {
        case HARDWARE:
          if (m.m_notify.interrupts & irq_set) {
            timer_int_handler();

            if (counter % 60 == 0) {
              timer_print_elapsed_time();
              time--;
            }
          }
          break;
        default:
          break;
      }
    }
  }

  if (timer_unsubscribe_int() != 0) return 1;

  return 0;
}
