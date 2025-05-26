// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (mouse_test_packet)(uint32_t cnt) {
    /* To be completed */
    printf("%s(%u): under construction\n", __func__, cnt);
    return 1;
}

int (mouse_test_async)(uint8_t idle_time) {
    uint8_t mouse_bit, timer_bit;
    int ipc_status;
    message msg;
    uint32_t irq_set = BIT(mouse_bit) | BIT(timer_bit);
    uint32_t last_active = 0;

    if(mouse_subscribe_int(&mouse_bit) || timer_subscribe_int(&timer_bit)) 
        return 1;

    while (elapsed_time < idle_time * 60) { // 60 ticks por segundo
        int r = driver_receive(ANY, &msg, &ipc_status);
        if (r != 0 || !(ipc_status & 0x20)) continue;

        if (msg.m_notify.interrupts & BIT(mouse_bit)) {
            mouse_ih();
            last_active = get_ticks();
            if (packet_index == 2) { // Pacote completo
                struct packet pp;
                mouse_parse_packet(&pp);
                mouse_print_packet(&pp);
                packet_index = 0;
            }
        }

        if (msg.m_notify.interrupts & BIT(timer_bit)) {
            elapsed_time = (get_ticks() - last_active) / 60;
        }
    }

    mouse_unsubscribe_int();
    timer_unsubscribe_int();
    return 0;
}

int (mouse_test_gesture)() {
    uint8_t bit_no;
    struct packet pp;
    enum gesture_states { START, LEFT_PRESSED, MOVING_RIGHT, RELEASED };
    static enum gesture_states state = START;

    if(mouse_subscribe_int(&bit_no)) return 1;

    while (state != RELEASED) {
        // Implementar máquina de estados aqui
        /* Esperar interrupção do mouse */
        int ipc_status;
        message msg;
        int r = driver_receive(ANY, &msg, &ipc_status);
        
        if(r != 0 || !(ipc_status & 0x20)) continue;
        
        if(msg.m_notify.interrupts & BIT(bit_no)) {
            mouse_ih();
            if(packet_index == 0 && (packet[0] & BIT(3))) { // Pacote completo
                struct packet pp;
                mouse_parse_packet(&pp);
                mouse_print_packet(&pp);
                cnt--;
            }
        }
        
        // Exemplo de transição de estado
        if (pp.lb && !pp.rb && !pp.mb) {
            if (state == START) state = LEFT_PRESSED;
        }
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;
        
        if (state == START) state = LEFT_PRESSED;