#include "highscore.h"
#include <stdio.h>
#include <string.h>
#include "../controllers/video/graphics.h"
#include "../controllers/keyboard/i8042.h"
#include "../controllers/keyboard/keyboard.h" 
#include "../controllers/menu/menu.h"
#include "digits.h"

static hs_entry_t list[MAX_HS_ENTRIES];
static int        count = 0;
extern uint8_t scancode; 

static char scancode_to_char(uint8_t scancode) {
    switch (scancode) {
        case 0x1E: return 'A';
        case 0x30: return 'B';
        case 0x2E: return 'C';
        case 0x20: return 'D';
        case 0x12: return 'E';
        case 0x21: return 'F';
        case 0x22: return 'G';
        case 0x23: return 'H';
        case 0x17: return 'I';
        case 0x24: return 'J';
        case 0x25: return 'K';
        case 0x26: return 'L';
        case 0x32: return 'M';
        case 0x31: return 'N';
        case 0x18: return 'O';
        case 0x19: return 'P';
        case 0x10: return 'Q';
        case 0x13: return 'R';
        case 0x1F: return 'S';
        case 0x14: return 'T';
        case 0x16: return 'U';
        case 0x2F: return 'V';
        case 0x11: return 'W';
        case 0x2D: return 'X';
        case 0x15: return 'Y';
        case 0x2C: return 'Z';
        
        case 0x02: return '1';
        case 0x03: return '2';
        case 0x04: return '3';
        case 0x05: return '4';
        case 0x06: return '5';
        case 0x07: return '6';
        case 0x08: return '7';
        case 0x09: return '8';
        case 0x0A: return '9';
        case 0x0B: return '0';
        
        case 0x39: return ' ';
        
        case 0x0C: return '-';
        case 0x0D: return '=';
        case 0x1A: return '[';
        case 0x1B: return ']';
        case 0x27: return ';';
        case 0x28: return '\'';
        case 0x29: return '`';
        case 0x2B: return '\\';
        case 0x33: return ',';
        case 0x34: return '.';
        case 0x35: return '/';
        
        default:
            return 0; 
    }
}

void highscore_init(void) {
  FILE *f = fopen("highscores.dat","rb");
  if (!f) return;
  fread(&count, sizeof(count), 1, f);
  if (count > MAX_HS_ENTRIES) count = MAX_HS_ENTRIES;
  fread(list, sizeof(hs_entry_t), count, f);
  fclose(f);
}

static void save_file(void) {
  FILE *f = fopen("highscores.dat","wb");
  if (!f) return;
  fwrite(&count, sizeof(count), 1, f);
  fwrite(list, sizeof(hs_entry_t), count, f);
  fclose(f);
}

bool highscore_try_add(int score) {
  if (count == 0 || score > list[count-1].score || count < MAX_HS_ENTRIES) {
    int pos = 0;
    while (pos < count && list[pos].score >= score) pos++;
    if (count < MAX_HS_ENTRIES) count++;
    for (int i = count - 1; i > pos; i--) list[i] = list[i-1];

    char name[MAX_NAME_LEN+1] = {0};
    int  len = 0;

    while (true) {
      vg_draw_rectangle(0, 0, mode_info.XResolution, mode_info.YResolution, 0x000000);
      draw_text(100,100,"NEW HIGH SCORE!",0xFFFFFF);
      draw_text(100,140,"ENTER YOUR NAME:",0xFFFFFF);
      draw_text(100,180,name,0xFFFFFF);
      
      message msg;
      int ipc_status;
      if (driver_receive(ANY, &msg, &ipc_status) == OK) {
        if (is_ipc_notify(ipc_status) && _ENDPOINT_P(msg.m_source) == HARDWARE) {
          if (msg.m_notify.interrupts & BIT(1)) { 
            kbc_ih();
            if (!(scancode & 0x80)) { /
              if (scancode == ENTER_KEY && len > 0) {
                break;
              }
              else if (scancode == SPACE_KEY && len > 0) {
                name[--len] = 0;
              }
              else {
                char c = scancode_to_char(scancode);
                if (c && len < MAX_NAME_LEN) {
                  name[len++] = c;
                  name[len] = 0;
                }
              }
            }
          }
        }
      }
    }
    
    strncpy(list[pos].name, name, MAX_NAME_LEN+1);
    list[pos].score = score;
    save_file();
    return true;
  }
  return false;
}

static bool highscore_active = false;

void highscore_show(void) {
    highscore_active = true;
}

bool highscore_is_active(void) {
    return highscore_active;
}

void highscore_draw_screen(void) {
    vg_draw_rectangle(0, 0,
                     mode_info.XResolution,
                     mode_info.YResolution,
                     0x000000);

    draw_text(80, 50, "HIGH SCORES", 0xFFFFFF);
    for (int i = 0; i < count; i++) {
        int y = 100 + i * 30;
        draw_number(80, y, i+1,  0xFFFFFF);
        draw_text(110, y, list[i].name, 0xFFFFFF);
        draw_number(300, y, list[i].score, 0xFFFFFF);
    }

    draw_text(80,
              mode_info.YResolution - 40,
              "PRESS ESC TO RETURN",
              0xFFFFFF);
}

void highscore_handle_key(uint8_t scancode) {
    if (scancode == ESC_BREAK_CODE) {
        highscore_active = false;
        menu_set_active(true);
    }
}
