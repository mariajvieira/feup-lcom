// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>
#include "graphics.h"  // Changed from graphics.c to .h

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
    
    struct reg86 r;
    memset(&r, 0, sizeof(r));
    r.ax = 0x0003;
    r.bx = 0x0000;
    r.intno = 0x10;
    if(sys_int86(&r) != OK) return 1;
    
    return 0;
}

int (video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {
    if(vbe_get_mode_info(mode, &mode_info) != OK) return 1;
    
    if(map_vram(mode)) return 1;

    struct reg86 r;
    memset(&r, 0, sizeof(r));
    r.ax = 0x4F02;
    r.bx = mode | BIT(14);  
    r.intno = 0x10;
    if(sys_int86(&r) != OK) return 1;

    for(uint16_t i = x; i < x + width; i++) {
        for(uint16_t j = y; j < y + height; j++) {
            draw_pixel(i, j, color);
        }
    }
    
    uint8_t scancode = 0;
    int ipc_status;
    message msg;
    int r_kbd;
    
    if (kbd_subscribe_int(&r_kbd) != OK) return 1;
    
    while(scancode != 0x81) {
        if (driver_receive(ANY, &msg, &ipc_status) != 0) continue;
        if (is_ipc_notify(ipc_status)) {
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:
                    if (msg.m_notify.interrupts & BIT(r_kbd)) {
                        kbc_ih();
                        scancode = get_scancode();
                    }
                    break;
                default:
                    break;
            }
        }
    }
    
    if (kbd_unsubscribe_int() != OK) return 1;
    
    memset(&r, 0, sizeof(r));
    r.ax = 0x0003;
    r.intno = 0x10;
    if(sys_int86(&r) != OK) return 1;
    
    return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
    if(vbe_get_mode_info(mode, &mode_info) != OK) return 1;
    
    if(map_vram(mode)) return 1;
    
    if(set_graphics_mode(mode)) return 1;
    
    uint16_t x_res = mode_info.XResolution;
    uint16_t y_res = mode_info.YResolution;
    uint16_t rect_width = x_res / no_rectangles;
    uint16_t rect_height = y_res / no_rectangles;
    
    uint32_t color = first;
    for(uint8_t i = 0; i < no_rectangles; i++) {
        for(uint8_t j = 0; j < no_rectangles; j++) {
            uint16_t x = i * rect_width;
            uint16_t y = j * rect_height;
            
            for(uint16_t xi = x; xi < x + rect_width; xi++) {
                for(uint16_t yi = y; yi < y + rect_height; yi++) {
                    draw_pixel(xi, yi, color);
                }
            }
            
            color += step;
        }
    }
    
    sleep(5); 
    
    struct reg86 r;
    memset(&r, 0, sizeof(r));
    r.ax = 0x0003;
    r.bx = 0x0000;
    r.intno = 0x10;
    if(sys_int86(&r) != OK) return 1;
    
    return 0;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  /* To be completed */
  printf("%s(%8p, %u, %u): under construction\n", __func__, xpm, x, y);

  return 1;
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
