#include "game.h"
#include "../controllers/video/graphics.h"
#include "../controllers/keyboard/i8042.h"
#include "../controllers/keyboard/keyboard.h"
#include "../controllers/timer/timer.c"
#include "../controllers/timer/i8254.h"
#include "../controllers/menu/menu.h"

#define CELL_SIZE       10
#define MAX_SNAKE_LEN   100
#define INIT_SNAKE_LEN  1

static uint16_t snake_x[MAX_SNAKE_LEN];
static uint16_t snake_y[MAX_SNAKE_LEN];
static int      snake_len;
static int      dir_x, dir_y;
static uint16_t food_x, food_y;
static bool     running;
static int food_timer = 0; 
static int score = 0;  // Add the score variable

static void init_game(void) {
    snake_len = INIT_SNAKE_LEN;
    dir_x = 1; dir_y = 0;
    uint16_t cols = mode_info.XResolution / CELL_SIZE;
    uint16_t rows = mode_info.YResolution / CELL_SIZE;
    uint16_t cx = cols  / 2 * CELL_SIZE;
    uint16_t cy = rows  / 2 * CELL_SIZE;
    
    for (int i = 0; i < snake_len; i++) {
        snake_x[i] = cx - i * CELL_SIZE;
        snake_y[i] = cy;
    }
    food_timer = 0;
    score = 0;  // Reset score when game starts
}

static void spawn_food(void) {

    food_x = (rand() % (mode_info.XResolution / CELL_SIZE)) * CELL_SIZE;
    food_y = (rand() % (mode_info.YResolution / CELL_SIZE)) * CELL_SIZE;
    food_timer = 0; 
}

void draw_game(void) {
    vg_draw_rectangle(0,0, mode_info.XResolution, mode_info.YResolution, 0xdddddA); 
    vg_draw_rectangle(0, 0, mode_info.XResolution, mode_info.YResolution, 0x000000); 

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

    if (snake_x[0] < 0 || snake_x[0] >= mode_info.XResolution ||
        snake_y[0] < 0 || snake_y[0] >= mode_info.YResolution) {
        running = false;
        draw_game_over();
        return;
    }

    for (int i = 1; i < snake_len; i++) {
        if (snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i]) {
            running = false;
            draw_game_over();
            return;
        }
    }

    if (snake_x[0] == food_x && snake_y[0] == food_y) {
        if (snake_len < MAX_SNAKE_LEN) snake_len++;
        spawn_food();
        score++;  // Increment score when food is eaten
    }
}


void handle_key(uint8_t scancode) {
    switch (scancode) {
        case W_KEY: if (dir_y != 1) { dir_x = 0;  dir_y = -1; } break;
        case S_KEY: if (dir_y != -1){ dir_x = 0;  dir_y =  1; } break;
        case A_KEY: if (dir_x != 1) { dir_x = -1; dir_y =  0; } break;
        case D_KEY: if (dir_x != -1){ dir_x =  1; dir_y =  0; } break;
        case ESC_BREAK_CODE:
            running = false;
            break;
        default:
            break;
    }
}

void draw_score(void) {
    //vg_draw_rectangle(10, 10, 50, 10, 0xFFFFFF);
    vg_draw_rectangle(60, 10, score * 5, 10, 0xFFFFFF);
}


void game_start(void) {

    init_game();
    spawn_food();
    running = true;
}


void draw_game_over(void) {
    vg_draw_rectangle(0, 0, mode_info.XResolution, mode_info.YResolution, 0x000000); 

    int x = mode_info.XResolution / 2 - 100;
    int y = mode_info.YResolution / 2 - 10;
    vg_draw_rectangle(x, y, 200, 20, 0xF65AA0); 
    // vg_draw_text(x, y, "GAME OVER", 0xFFFFFF); 

    tickdelay(micros_to_ticks(1000000)); 


    menu_set_active(true);

    // handle_key(0); 
    // update_game();
    // draw_game();


    // ---------------------- //

    // message msg;
    // int ipc_status;
    // extern int hook_id;
    // extern int kbd_hook_id; 
    

    // while (running) {
    //     if (driver_receive(ANY, &msg, &ipc_status) != 0)
    //         continue;
    //     if (is_ipc_notify(ipc_status)) {
    //         switch (_ENDPOINT_P(msg.m_source)) {
    //             case HARDWARE:
    //                 if (msg.m_notify.interrupts & hook_id) {
    //                     update_game();
    //                     draw_game();
    //                 }
    //                 if (msg.m_notify.interrupts & kbd_hook_id) {
    //                     kbc_ih();
    //                     handle_key(scancode);
    //                 }
    //                 break;
    //             default:
    //                 break;
    //         }
    //     }
    // }

    // -------------------//


    // sleep(5);
    // vg_exit();
    // menu_set_active(true);
    printf("START GAME SELECTED\n");
}
