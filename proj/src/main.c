#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>
#include "controllers/video/graphics.h"
#include "controllers/keyboard/keyboard.h"

static uint8_t kbd_mask;

static void draw_background() {
  vg_draw_rectangle(0, 0, mode_info.XResolution, mode_info.YResolution, 0x001144);
}

static void draw_menu_window() {
  uint16_t w = mode_info.XResolution / 2;
  uint16_t h = mode_info.YResolution / 2;
  uint16_t x = (mode_info.XResolution - w) / 2;
  uint16_t y = (mode_info.YResolution - h) / 2;
  vg_draw_rectangle(x+5, y+5, w, h, 0x000000);
  vg_draw_rectangle(x, y, w, h, 0xCCCCCC);
}

static void draw_menu_items() {
  //const char *labels[3] = { "Start Game", "Options", "Exit" };
  uint16_t w = mode_info.XResolution / 2 - 40;
  uint16_t h = 40;
  uint16_t x = (mode_info.XResolution - (mode_info.XResolution/2)) / 2 + 20;
  uint16_t y0 = (mode_info.YResolution - (mode_info.YResolution/2)) / 2 + 20;

  for (int i = 0; i < 3; i++) {
    uint16_t y = y0 + i*(h + 20);
    vg_draw_rectangle(x, y, w, h, 0x888888);

  }
}

int main(int argc, char *argv[]) {
  lcf_set_language("EN-US");

  const uint16_t mode = 0x105;  
  if (set_graphics_mode(mode))        return 1;
  if (map_vram(mode))                 return 1;

  draw_background();
  draw_menu_window();
  draw_menu_items();

//   // espera ESC
//   if (kbd_subscribe_int(&kbd_mask))   return 1;
//   message msg;
//   int ipc_status;
//   while (scancode != ESC_BREAK_CODE) {
//     if (driver_receive(ANY, &msg, &ipc_status) != OK) continue;
//     if (is_ipc_notify(ipc_status) &&
//         _ENDPOINT_P(msg.m_source) == HARDWARE &&
//         (msg.m_notify.interrupts & BIT(kbd_mask)))
//       kbc_ih();
//   }
  kbd_unsubscribe();

  vg_exit();
  return 0;
}
