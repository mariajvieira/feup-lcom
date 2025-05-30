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

        if (scancode == ENTER_KEY && len>0) break;
        else if (scancode == SPACE_KEY && len>0) {
          name[--len] = 0;
        }
        else {
          char c = scancode_to_char(scancode);
          if (c && len < MAX_NAME_LEN) name[len++] = c, name[len] = 0;
        }
    }
    strncpy(list[pos].name, name, MAX_NAME_LEN+1);
    list[pos].score = score;
    save_file();
    return true;
  }
  return false;
}

void highscore_draw(void) {
  while (true) {
    vg_draw_rectangle(0, 0,
                     mode_info.XResolution,
                     mode_info.YResolution,
                     0x000000);

    draw_text(80, 50, "HIGH SCORES", 0xFFFFFF);
    for (int i = 0; i < count; i++) {
      int y = 100 + i * 30;
      /* rank */
      draw_number(80, y, i+1,  0xFFFFFF);
      /* name */
      draw_text(110, y, list[i].name, 0xFFFFFF);
      /* score */
      draw_number(300, y, list[i].score, 0xFFFFFF);
    }

    draw_text(80,
              mode_info.YResolution - 40,
              "PRESS ESC TO RETURN",
              0xFFFFFF);

    if (scancode == ESC_BREAK_CODE)
      break;
  }
  menu_set_active(true);
}
