#ifndef GAME_H
#define GAME_H
#include <lcom/lcf.h>
#include <stdint.h>
#include <stdbool.h>

void game_start(void);
void update_game(void);
void draw_game(void);
void handle_key(uint8_t scancode);
void draw_game_over(void);


#endif // GAME_H
