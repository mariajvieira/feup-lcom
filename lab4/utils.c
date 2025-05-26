#include <lcom/lcf.h>
#include "utils.h"

int util_sys_inb(int port, uint8_t *value) {
    uint32_t temp;
    if (sys_inb(port, &temp)) return 1;
    *value = (uint8_t) temp;
    return 0;
}