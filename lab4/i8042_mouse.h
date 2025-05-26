#ifndef _I8042_MOUSE_H_
#define _I8042_MOUSE_H_

#define MOUSE_IRQ 12


#define MOUSE_ENABLE_DATA 0xF4
#define MOUSE_DISABLE_DATA 0xF5
#define MOUSE_SET_STREAM_MODE 0xEA

// KBC
#define KBC_STATUS_REG 0x64
#define KBC_OUT_BUF 0x60

// status register
#define KBC_OBF BIT(0)
#define KBC_PAR_ERR BIT(7)
#define KBC_TO_ERR BIT(6)

#endif