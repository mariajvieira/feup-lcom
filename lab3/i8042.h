#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

#ifndef BIT
#define BIT(n) (1 << (n)) 
#endif

#define STAT_REG          0x64
#define OUT_BUF           0x60

#define OBF               BIT(0)    // output buffer full
#define PAR_ERR           BIT(7)    // parity error
#define TO_ERR            BIT(6)    // timeout error

#define KBD_IRQ           1

#define TWO_BYTE_CODE     0xE0
#define ESC_BREAK_CODE    0x81
#define BREAK_MASK        BIT(7)

int kbd_subscribe_int(uint8_t *bit_no);
int kbd_unsubscribe(void);

#endif /*_LCOM_I8042_H_*/
