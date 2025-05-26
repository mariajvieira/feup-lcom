#include <lcom/lcf.h>
#include <lcom/lab3.h>

#include "i8042.h"

uint8_t scancode=0;
uint8_t r_kbd;
int kbd_hook_id=1; // Mantém-se como o ID do hook para a interrupção do teclado.

int (kbd_subscribe_int)(uint8_t *bit_no) {
  if(bit_no == NULL) return 1;

  *bit_no = kbd_hook_id; // Atribui o hook_id ao parâmetro de SAÍDA bit_no.
                         // Esta linha substitui a linha problemática.

  // Chama sys_irqsetpolicy com o kbd_hook_id correto.
  if(sys_irqsetpolicy(KBD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &kbd_hook_id) != OK) {
    return 1; // Falha ao definir a política de interrupção
  }
  
  return 0; // Sucesso
}

int (kbd_unsubscribe)() {
    return sys_irqrmpolicy(&kbd_hook_id);
}

void (kbc_ih)() {
    uint8_t status_reg;
    uint8_t output_data;

    // Attempt to read the status register
    // util_sys_inb is expected to be provided by LCF utils (e.g. utils.c)
    if (util_sys_inb(STAT_REG, &status_reg) != 0) {
        // Failed to read status, set scancode to 0 to indicate error/no data
        scancode = 0;
        return;
    }

    // Check if the output buffer is full (OBF flag is set)
    if (status_reg & OBF) {
        // Attempt to read the scancode from the output buffer
        if (util_sys_inb(OUT_BUF, &output_data) != 0) {
            // Failed to read scancode, set scancode to 0
            scancode = 0;
            return;
        }

        // Check for parity or timeout errors
        // If PAR_ERR or TO_ERR bits are set in status_reg, the data is invalid
        if ((status_reg & (PAR_ERR | TO_ERR)) == 0) {
            // No errors, update the global scancode
            scancode = output_data;
        } else {
            // Error detected (parity or timeout), data is invalid, set scancode to 0
            scancode = 0;
        }
    } else {
      // Output buffer not full. This might be unexpected if an interrupt was triggered.
      // Set scancode to 0 as no new valid data is available.
      scancode = 0;
    }
}


