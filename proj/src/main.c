#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>
#include "controllers/video/graphics.h"
#include "controllers/keyboard/keyboard.h"
#include "controllers/keyboard/i8042.h"
#include "controllers/menu/menu.h"
#include "game/game.h"

static uint8_t kbd_mask;
extern uint8_t scancode;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  lcf_trace_calls("/home/lcom/labs/proj/trace.txt");

  // enables to save the output of printf function calls on a file
  lcf_log_output("/home/lcom/labs/proj/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  lcf_cleanup();
  return 0;
}

int (proj_main_loop)(int argc, char *argv[]) {
    uint16_t mode = 0x117;  
    if(vbe_get_mode_info(mode, &mode_info) != OK) return 1;
    if(map_vram(mode)) return 1;
    if(set_graphics_mode(mode)) return 1;

    if(menu_init()) return 1;

    if (kbd_subscribe_int(&kbd_mask)) return 1;
    
    message msg;
    int ipc_status;
    bool running = true;
    
    while (running && scancode != ESC_BREAK_CODE) {
        if (menu_is_active()) {
            menu_draw();
        }
        
        if (driver_receive(ANY, &msg, &ipc_status) != OK) continue;
        
        if (is_ipc_notify(ipc_status) &&
            _ENDPOINT_P(msg.m_source) == HARDWARE &&
            (msg.m_notify.interrupts & BIT(kbd_mask))) {
            
            kbc_ih();
            
            if (!(scancode & 0x80)) {
                if (menu_is_active()) {
                    menu_handle_key(scancode);
                    
                    if (scancode == ENTER_KEY || scancode == SPACE_KEY) {
                        switch (menu_get_selected()) {
                            case MENU_START_GAME:
                                menu_set_active(false);
                                game_start();
                                printf("Starting Snake Game...\n");
                                break;
                                
                            case MENU_HIGH_SCORES:
                                printf("Showing High Scores...\n");
                                break;
                                
                            case MENU_OPTIONS:
                                printf("Showing Options...\n");
                                break;
                                
                            case MENU_EXIT:
                                running = false;
                                break;
                                
                            case MENU_ITEMS_COUNT:
                                break;
                        }
                    }
                }
            }
        }
    }
    
    kbd_unsubscribe();
    vg_exit();
    return 0;
}
