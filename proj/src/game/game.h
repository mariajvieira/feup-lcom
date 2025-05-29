#ifndef GAME_H
#define GAME_H
#include <lcom/lcf.h>

void game_start(void);
void update_game(void);
void draw_game(void);
void handle_key(uint8_t scancode);
void draw_game_over(void);

void draw_score(void);

#endif // GAME_H
