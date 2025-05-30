#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <stdbool.h>
#include <stdint.h>

#define MAX_HS_ENTRIES 10
#define MAX_NAME_LEN   12

typedef struct {
  char name[MAX_NAME_LEN+1];
  int  score;
} hs_entry_t;

// Funções originais
void   highscore_init(void);
bool   highscore_try_add(int score); 
void   highscore_draw(void);

// Novas funções para integração com o sistema de drawing
void   highscore_show(void);
bool   highscore_is_active(void);
void   highscore_draw_screen(void);
void   highscore_handle_key(uint8_t scancode);

#endif // HIGHSCORE_H
