#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}


// if we use the address of a uint8_t variable, 
// the program may terminate abnormally, because it 
// accesses a memory position at an invalid address 
// (thus triggering a segmentation violation signal)
// for that reason, we use util_sys_inb
int (util_sys_inb)(int port, uint8_t *value) {
  if (value==NULL) return 1;   // 1 = erro
  uint32_t val;
  int ret = sys_inb(port, &val);

  return ret;
}
