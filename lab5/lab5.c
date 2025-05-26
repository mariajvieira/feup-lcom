// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/lab5.h>
#include <lcom/libxpm.h>

#include <stdint.h>
#include <stdio.h>
#include "graphics.h"  
#include "keyboard.h"

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int (video_test_init)(uint16_t mode, uint8_t delay) {
    if(vbe_get_mode_info(mode, &mode_info) != OK) return 1;
    
    if(map_vram(mode)) return 1;
    
    if(set_graphics_mode(mode)) return 1;
    
    sleep(delay);
    
    if(vg_exit()!=0)return 1;
    
    return 0;
}

int (video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {

    if(vbe_get_mode_info(mode, &mode_info) != OK) return 1;
    
    if(map_vram(mode)) return 1;

    if(set_graphics_mode(mode)) return 1;

    if(vg_draw_rectangle(x, y, width, height, color)) return 1;

    sleep(5);
    
    int ipc_status;
    message msg;
    uint8_t r_kbd;
    
    if (kbd_subscribe_int(&r_kbd) != OK) return 1;
    
    while(scancode != ESC_BREAK_CODE) { 
        if (driver_receive(ANY, &msg, &ipc_status) != 0) continue;
        if (is_ipc_notify(ipc_status)) {
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:
                    if (msg.m_notify.interrupts & BIT(r_kbd)) {
                        kbc_ih(); 
                    }
                    break;
                default:
                    break;
            }
        }
    }
    
    if (kbd_unsubscribe() != OK) return 1;
    if(vg_exit()!=0)return 1;
    
    return 0;
}


int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
    if (vbe_get_mode_info(mode, &mode_info) != OK) 
        return 1;
    if (map_vram(mode)) 
        return 1;
    if (set_graphics_mode(mode)) 
        return 1;

    uint16_t hres = mode_info.XResolution;
    uint16_t vres = mode_info.YResolution;
    uint16_t rect_w = hres / no_rectangles;
    uint16_t rect_h = vres / no_rectangles;
    bool direct = mode_info.BitsPerPixel > 8;

    for (uint8_t row = 0; row < no_rectangles; row++) {
        for (uint8_t col = 0; col < no_rectangles; col++) {
            uint32_t color;
            if (!direct) {   // Indexed mode 
                color = (first + (row * no_rectangles + col) * step) 
                        % (1u << mode_info.BitsPerPixel);
            }
            else { // Direct mode
                uint32_t R = (first >> mode_info.RedFieldPosition) 
                              & ((1u << mode_info.RedMaskSize) - 1);
                uint32_t G = (first >> mode_info.GreenFieldPosition) 
                              & ((1u << mode_info.GreenMaskSize) - 1);
                uint32_t B = (first >> mode_info.BlueFieldPosition) 
                              & ((1u << mode_info.BlueMaskSize) - 1);

                R = (R + col * step) % (1u << mode_info.RedMaskSize);
                G = (G + row * step) % (1u << mode_info.GreenMaskSize);
                B = (B + (col + row) * step) % (1u << mode_info.BlueMaskSize);

                color = (R << mode_info.RedFieldPosition)   |
                        (G << mode_info.GreenFieldPosition) |
                        (B << mode_info.BlueFieldPosition);
            }
            vg_draw_rectangle(col * rect_w,
                              row * rect_h,
                              rect_w,
                              rect_h,
                              color);
        }
    }

    sleep(5);

    uint8_t kbd_bit;
    if (kbd_subscribe_int(&kbd_bit) != OK) 
        return 1;
    int ipc_status;
    message msg;

    while (scancode != ESC_BREAK_CODE) {
        if (driver_receive(ANY, &msg, &ipc_status) != OK) 
            continue;
        if (is_ipc_notify(ipc_status) &&
            _ENDPOINT_P(msg.m_source) == HARDWARE &&
            (msg.m_notify.interrupts & BIT(kbd_bit)))
            kbc_ih();
    }
    if (kbd_unsubscribe() != OK) 
        return 1;

    if (vg_exit() != OK) 
        return 1;
    return 0;
}


int (video_test_xpm)(const char *xpm[], uint16_t x, uint16_t y) {
    uint16_t mode = 0x105;
    if (vbe_get_mode_info(mode, &mode_info) != OK) 
        return 1;
    if (map_vram(mode)) 
        return 1;
    if (set_graphics_mode(mode)) 
        return 1;

    if (print_xpm(xpm, x, y)!=0) return 1;

    uint8_t kbd_bit;
    if (kbd_subscribe_int(&kbd_bit) != OK) return 1;

    message msg;
    int ipc_status;
    while (scancode != ESC_BREAK_CODE) {
      if (driver_receive(ANY, &msg, &ipc_status) != OK) continue;
      if (is_ipc_notify(ipc_status) &&
          _ENDPOINT_P(msg.m_source) == HARDWARE &&
          (msg.m_notify.interrupts & BIT(kbd_bit)))
        kbc_ih();
    }
    if (kbd_unsubscribe() != OK) return 1;
    if (vg_exit() != OK)        return 1;

    return 0;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  /* To be completed */
  printf("%s(%8p, %u, %u, %u, %u, %d, %u): under construction\n",
         __func__, xpm, xi, yi, xf, yf, speed, fr_rate);

  return 1;
}

int(video_test_controller)() {
  /* This year you do not need to implement this */
  printf("%s(): under construction\n", __func__);

  return 1;
}
