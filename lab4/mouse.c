#include <lcom/lcf.h>
#include "i8042_mouse.h"
#include "utils.h"

static uint8_t packet[3];
static int packet_index = 0;

int mouse_subscribe_int(uint8_t *bit_no) {
    *bit_no = MOUSE_IRQ;
    return sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id);
}

int mouse_unsubscribe_int() {
    return sys_irqrmpolicy(&hook_id);
}

void mouse_ih() {
    uint8_t status;
    util_sys_inb(KBC_STATUS_REG, &status);
    
    if (status & KBC_OBF) {
        util_sys_inb(KBC_OUT_BUF, &packet[packet_index]);
        packet_index = (packet_index + 1) % 3;
    }
}

int mouse_parse_packet(struct packet *pp) {
    pp->bytes[0] = packet[0];
    pp->bytes[1] = packet[1];
    pp->bytes[2] = packet[2];
    
    // Parse dos botões
    pp->lb = (packet[0] & BIT(0)) ? 1 : 0;
    pp->rb = (packet[0] & BIT(1)) ? 1 : 0;
    pp->mb = (packet[0] & BIT(2)) ? 1 : 0;
    
    // Parse dos overflow flags
    pp->x_ov = (packet[0] & BIT(6)) ? 1 : 0;
    pp->y_ov = (packet[0] & BIT(7)) ? 1 : 0;
    
    // Parse do movimento X (complemento para 2)
    pp->delta_x = (packet[0] & BIT(4)) ? 
        (0xFF00 | packet[1]) : packet[1];
        
    // Parse do movimento Y (complemento para 2)
    pp->delta_y = (packet[0] & BIT(5)) ? 
        (0xFF00 | packet[2]) : packet[2];

    return 0;
}