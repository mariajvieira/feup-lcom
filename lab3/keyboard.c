uint8_t scancode=0;
int kbd_hook_id =1;

int (kbd_subscribe_int)(uint8_t *bit_no) {
  if(bit_no==NULL) return 1;
  kbd_hook_id = *bit_no;
  if(sys_irqsetpolicy(KBD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &kbd_hook_id)!=0) return 1;
  return 0;
}

