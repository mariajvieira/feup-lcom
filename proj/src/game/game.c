#include "game.h"
#include "digits.c"
#include "../controllers/video/graphics.h"
#include "../controllers/keyboard/i8042.h"
#include "../controllers/keyboard/keyboard.h"
#include "../controllers/timer/timer.c"
#include "../controllers/timer/i8254.h"
#include "../controllers/menu/menu.h"

#define CELL_SIZE       10
#define MAX_SNAKE_LEN   100
#define INIT_SNAKE_LEN  1
#define BORDER_WIDTH    20
#define GAME_AREA_WIDTH  400
#define GAME_AREA_HEIGHT 300

static int curr_game_area_width;
static int curr_game_area_height;
int update_tick_threshold;  
static int game_level = 2;

static uint16_t snake_x[MAX_SNAKE_LEN];
static uint16_t snake_y[MAX_SNAKE_LEN];
static int      snake_len;
static int      dir_x, dir_y;
static uint16_t food_x, food_y;
static int food_timer = 0; 
static int score = 0;

static uint16_t game_start_x;
static uint16_t game_start_y;
static uint16_t game_end_x;
static uint16_t game_end_y;

static bool game_running = true;
static bool score_updated = false;

void game_set_level(int level) {
  switch(level) {
    case 1:
      curr_game_area_width = 600;
      curr_game_area_height = 450;
      update_tick_threshold = 10; 
      break;
    case 2:
      curr_game_area_width = 400;
      curr_game_area_height = 300;
      update_tick_threshold = 6;  
      break;
    case 3:
      curr_game_area_width = 300;
      curr_game_area_height = 225;
      update_tick_threshold = 4; 
      break;
    default:
      curr_game_area_width = 400;
      curr_game_area_height = 300;
      update_tick_threshold = 6;
      break;
  }
}


static void init_game(void) {
    snake_len = INIT_SNAKE_LEN;
    dir_x = 1; dir_y = 0;
    
    game_start_x = (mode_info.XResolution - curr_game_area_width) / 2;
    game_start_y = (mode_info.YResolution - curr_game_area_height) / 2;
    game_end_x = game_start_x + curr_game_area_width;
    game_end_y = game_start_y + curr_game_area_height;
    
    uint16_t cols = curr_game_area_width / CELL_SIZE;
    uint16_t rows = curr_game_area_height / CELL_SIZE;
    uint16_t cx = game_start_x + (cols / 2) * CELL_SIZE;
    uint16_t cy = game_start_y + (rows / 2) * CELL_SIZE;
    
    for (int i = 0; i < snake_len; i++) {
        snake_x[i] = cx - i * CELL_SIZE;
        snake_y[i] = cy;
    }
    food_timer = 0;
    score = 0;
}

static void spawn_food(void) {
    uint16_t cols = curr_game_area_width / CELL_SIZE;
    uint16_t rows = curr_game_area_height / CELL_SIZE;
    
    food_x = game_start_x + (rand() % cols) * CELL_SIZE;
    food_y = game_start_y + (rand() % rows) * CELL_SIZE;
    food_timer = 0; 
}

void draw_game(void) {
    vg_draw_rectangle(0, 0, mode_info.XResolution, mode_info.YResolution, 0x333333);
    
    vg_draw_rectangle(game_start_x - BORDER_WIDTH, game_start_y - BORDER_WIDTH, 
                      curr_game_area_width + 2 * BORDER_WIDTH, BORDER_WIDTH, 0x666666);
    vg_draw_rectangle(game_start_x - BORDER_WIDTH, game_start_y + curr_game_area_height, 
                      curr_game_area_width + 2 * BORDER_WIDTH, BORDER_WIDTH, 0x666666);
    vg_draw_rectangle(game_start_x - BORDER_WIDTH, game_start_y, 
                      BORDER_WIDTH, curr_game_area_height, 0x666666);
    vg_draw_rectangle(game_start_x + curr_game_area_width, game_start_y, 
                      BORDER_WIDTH, curr_game_area_height, 0x666666);
    
    vg_draw_rectangle(game_start_x, game_start_y, curr_game_area_width, curr_game_area_height, 0xdddddd);
    
    int title_x = game_start_x + (curr_game_area_width / 2) - 60;
    int title_y = game_start_y - BORDER_WIDTH - 70;
    draw_text(title_x, title_y, "SNAKE GAME", 0xFFFFFF);
    
    draw_score();
    
    vg_draw_rectangle(food_x, food_y, CELL_SIZE, CELL_SIZE, 0xFFFA00);
    for (int i = 0; i < snake_len; i++)
        vg_draw_rectangle(snake_x[i], snake_y[i], CELL_SIZE, CELL_SIZE, 0x00FF00);
}


void update_game(void) {
    for (int i = snake_len - 1; i > 0; i--) {
        snake_x[i] = snake_x[i-1];
        snake_y[i] = snake_y[i-1];
    }
    snake_x[0] += dir_x * CELL_SIZE;
    snake_y[0] += dir_y * CELL_SIZE;
    
    if (snake_x[0] < game_start_x || snake_x[0] >= game_end_x ||
        snake_y[0] < game_start_y || snake_y[0] >= game_end_y) {
        draw_game_over();
        return;
    }
    
    for (int i = 1; i < snake_len; i++) {
        if (snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i]) {
            draw_game_over();
            return;
        }
    }
    
    if (snake_x[0] == food_x && snake_y[0] == food_y) {
        if (snake_len < MAX_SNAKE_LEN) snake_len++;
        spawn_food();
        score++;
        score_updated = true;
    }
}


void handle_key(uint8_t scancode) {
    switch (scancode) {
        case W_KEY: if (dir_y != 1) { dir_x = 0;  dir_y = -1; } break;
        case S_KEY: if (dir_y != -1){ dir_x = 0;  dir_y =  1; } break;
        case A_KEY: if (dir_x != 1) { dir_x = -1; dir_y =  0; } break;
        case D_KEY: if (dir_x != -1){ dir_x =  1; dir_y =  0; } break;
        case ESC_BREAK_CODE:
            game_exit(); 
            break;
        default:
            break;
    }
}

void draw_score(void) {
    int score_x = game_start_x + (curr_game_area_width / 2) - 50; 
    int score_y = game_start_y - BORDER_WIDTH - 30;
    draw_text(score_x, score_y, "SCORE", 0xFFFFFF);
    draw_number(score_x + 80, score_y, score, 0xFFFFFF);
}

void game_start(void) {

    init_game();
    spawn_food();
    score_updated = true;
    game_running = true;
}

void game_exit(void) {
    game_running = false;
}

bool game_is_running(void) {
    return game_running;
}

void draw_game_over(void) {
    vg_draw_rectangle(0, 0, mode_info.XResolution, mode_info.YResolution, 0x000000); 

    int x = mode_info.XResolution / 2 - 100;
    int y = mode_info.YResolution / 2 - 10;
    vg_draw_rectangle(x, y, 200, 20, 0xF65AA0); 
    draw_text(x + 50, y + 3, "GAME OVER", 0xFFFFFF); 
    
    int score_x = x + 60;
    int score_y = y + 30;
    draw_text(score_x, score_y, "SCORE", 0xFFFFFF);
    draw_number(score_x + 70, score_y, score, 0xFFFFFF);
    
    tickdelay(micros_to_ticks(2000000)); 

    menu_set_active(true);
}

void draw_score_static(void) {
    int score_x = game_start_x + (curr_game_area_width / 2) - 50; 
    int score_y = game_start_y - BORDER_WIDTH - 30;
    draw_text(score_x, score_y, "SCORE", 0xFFFFFF);
}

void draw_score_dynamic(void) {
    int score_x = game_start_x + (GAME_AREA_WIDTH / 2) - 50; 
    int score_y = game_start_y - BORDER_WIDTH - 30;
    
    int num_digits = 0;
    int temp = score;
    if (temp == 0) num_digits = 1;
    else {
        while (temp) {
            num_digits++;
            temp /= 10;
        }
    }
    
    int clear_width = num_digits * 12;
    vg_draw_rectangle(score_x + 80, score_y, clear_width, 20,0x333333);
    draw_number(score_x + 80, score_y, score, 0xFFFFFF);
}

void draw_game_static(void) {
    vg_draw_rectangle(0, 0, mode_info.XResolution, mode_info.YResolution, 0x333333); 
    vg_draw_rectangle(game_start_x - BORDER_WIDTH, game_start_y - BORDER_WIDTH,  
                      curr_game_area_width + 2 * BORDER_WIDTH, BORDER_WIDTH, 0x666666);
    vg_draw_rectangle(game_start_x - BORDER_WIDTH, game_start_y + curr_game_area_height, 
                      curr_game_area_width + 2 * BORDER_WIDTH, BORDER_WIDTH, 0x666666);
    vg_draw_rectangle(game_start_x - BORDER_WIDTH, game_start_y,  
                      BORDER_WIDTH, curr_game_area_height, 0x666666);
    vg_draw_rectangle(game_start_x + curr_game_area_width, game_start_y,  
                      BORDER_WIDTH, curr_game_area_height, 0x666666);
    
    vg_draw_rectangle(game_start_x, game_start_y, curr_game_area_width, curr_game_area_height, 0xdddddd);
    
    int title_x = game_start_x + (curr_game_area_width / 2) - 60;
    int title_y = game_start_y - BORDER_WIDTH - 70;
    draw_text(title_x, title_y, "SNAKE GAME", 0xFFFFFF);
    
    draw_score_static();
}

void draw_game_dynamic(void) {
    vg_draw_rectangle(game_start_x, game_start_y, curr_game_area_width, curr_game_area_height, 0xdddddd);
    if (score_updated) {
        draw_score_dynamic();
        score_updated = false;
    }
    
    vg_draw_rectangle(food_x, food_y, CELL_SIZE, CELL_SIZE, 0xFFFA00);
    
    for (int i = 0; i < snake_len; i++) {
        vg_draw_rectangle(snake_x[i], snake_y[i], CELL_SIZE, CELL_SIZE, 0x00FF00);
    }
}
