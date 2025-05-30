#include "digits.h"
#include "../controllers/video/graphics.h"

static const uint8_t digit_patterns[10][7] = {
    // 0
    {0x0E, 0x11, 0x11,0x11,0x11,0x11,0x0E},
    // 1
    {0x04,0x0C,0x04,0x04,0x04,0x04,0x0E},
    // 2
    {0x0E,0x11,0x01,0x02,0x04,0x08,0x1F},
    // 3
    {0x0E,0x11,0x01,0x06,0x01,0x11,0x0E},
    // 4
    {0x02,0x06,0x0A,0x12,0x1F,0x02,0x02},
    // 5
    {0x1F,0x10,0x10,0x1E,0x01,0x11,0x0E},
    // 6
    {0x0E,0x11,0x10,0x1E,0x11,0x11,0x0E},
    // 7
    {0x1F, 0x01, 0x02,0x04,0x08,0x08,0x08},
    // 8
    {0x0E,0x11,0x11,0x0E,0x11,0x11,0x0E},
    // 9
    {0x0E,0x11,0x11,0x0F,0x01,0x11,0x0E}
};

void draw_digit(int x, int y, int digit, uint32_t color) {
    if (digit < 0 || digit > 9) return;
    
    for (int row = 0; row < 7; row++) {
        uint8_t pattern = digit_patterns[digit][row];
        for (int col = 0; col < 5; col++) {
            if (pattern & (1 << (4 - col))) {
                vg_draw_rectangle(x + col * 2, y + row * 2, 2, 2, color);
            }
        }
    }
}

void draw_number(int x, int y, int number, uint32_t color) {
    if (number == 0) {
        draw_digit(x, y, 0, color);
        return;
    }
    
    int temp = number;
    int digit_count = 0;
    while (temp > 0) {
        digit_count++;
        temp /= 10;
    }
    
    int current_x = x + (digit_count - 1) * 12;
    while (number > 0) {
        int digit = number % 10;
        draw_digit(current_x, y, digit, color);
        number /= 10;
        current_x -= 12;
    }
}
