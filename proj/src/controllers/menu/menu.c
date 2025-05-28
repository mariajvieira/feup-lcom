#include "menu.h"
#include "../video/graphics.h"
#include "../keyboard/i8042.h"
#include <string.h>

static menu_state_t menu_state;


#define MENU_BG_COLOR     0x000080  
#define MENU_WINDOW_COLOR 0xC0C0C0 
#define MENU_BORDER_COLOR 0x000000  
#define MENU_TEXT_COLOR   0x2C3E50
#define MENU_SELECTED_COLOR 0xFF0000  
#define MENU_SELECTED_TEXT  0xFFFFFF

int menu_init() {
    menu_state.selected_item = MENU_START_GAME;
    menu_state.is_active = true;
    
    menu_state.window_w = mode_info.XResolution / 2;
    menu_state.window_h = mode_info.YResolution / 2;
    menu_state.window_x = (mode_info.XResolution - menu_state.window_w) / 2;
    menu_state.window_y = (mode_info.YResolution - menu_state.window_h) / 2;
    
    return 0;
}

static int draw_background() {
    return vg_draw_rectangle(0, 0, mode_info.XResolution, mode_info.YResolution, MENU_BG_COLOR);
}

static int draw_menu_window() {
    if (vg_draw_rectangle(menu_state.window_x + 5, menu_state.window_y + 5, 
                         menu_state.window_w, menu_state.window_h, MENU_BORDER_COLOR))
        return 1;
    
    if (vg_draw_rectangle(menu_state.window_x, menu_state.window_y, 
                         menu_state.window_w, menu_state.window_h, MENU_WINDOW_COLOR))
        return 1;
    
    if (vg_draw_rectangle(menu_state.window_x, menu_state.window_y, 
                         menu_state.window_w, 3, MENU_BORDER_COLOR))
        return 1;
    
    return 0;
}

static int draw_title() {
    uint16_t title_x = menu_state.window_x + 50;
    uint16_t title_y = menu_state.window_y + 30;
    
    return vg_draw_rectangle(title_x, title_y, menu_state.window_w - 100, 40, MENU_SELECTED_COLOR);
}

static int draw_menu_items() {
    uint16_t item_height = 50;
    uint16_t item_width = menu_state.window_w - 80;
    uint16_t start_x = menu_state.window_x + 40;
    uint16_t start_y = menu_state.window_y + 120;
    
    for (int i = 0; i < MENU_ITEMS_COUNT; i++) {
        uint16_t item_y = start_y + i * (item_height + 10);
        uint32_t bg_color = (i == menu_state.selected_item) ? MENU_SELECTED_COLOR : MENU_WINDOW_COLOR;
        uint32_t border_color = (i == menu_state.selected_item) ? MENU_SELECTED_TEXT : MENU_BORDER_COLOR;
        
        if (vg_draw_rectangle(start_x, item_y, item_width, item_height, bg_color))
            return 1;
        
        if (vg_draw_rectangle(start_x, item_y, item_width, 2, border_color))
            return 1;
        if (vg_draw_rectangle(start_x, item_y + item_height - 2, item_width, 2, border_color))
            return 1;
        
        if (i == menu_state.selected_item) {
            if (vg_draw_rectangle(start_x + 10, item_y + 20, 15, 10, MENU_SELECTED_TEXT))
                return 1;
        }
    }
    
    return 0;
}

static int draw_instructions() {
    uint16_t instr_y = menu_state.window_y + menu_state.window_h - 50;
    uint16_t instr_x = menu_state.window_x + 20;
    
    return vg_draw_rectangle(instr_x, instr_y, menu_state.window_w - 40, 20, MENU_BORDER_COLOR);
}

int menu_draw() {
    if (!menu_state.is_active)
        return 0;
    
    if (draw_background()) return 1;
    if (draw_menu_window()) return 1;
    if (draw_title()) return 1;
    if (draw_menu_items()) return 1;
    if (draw_instructions()) return 1;
    
    return 0;
}

void menu_handle_key(uint8_t scancode) {
    if (!menu_state.is_active)
        return;
    
    switch (scancode) {
        case W_KEY: 
        case ARROW_UP:
            if (menu_state.selected_item > 0)
                menu_state.selected_item--;
            else
                menu_state.selected_item = MENU_ITEMS_COUNT - 1;
            break;
            
        case S_KEY:   
        case ARROW_DOWN:
            if (menu_state.selected_item < MENU_ITEMS_COUNT - 1)
                menu_state.selected_item++;
            else
                menu_state.selected_item = 0;
            break;
            
        case ENTER_KEY:
        case SPACE_KEY:
            break;
    }
}

menu_item_t menu_get_selected() {
    return menu_state.selected_item;
}

bool menu_is_active() {
    return menu_state.is_active;
}

void menu_set_active(bool active) {
    menu_state.is_active = active;
}
