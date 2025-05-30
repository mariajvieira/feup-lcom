#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <stdbool.h>

#define MAX_HS_ENTRIES 10
#define MAX_NAME_LEN   12

typedef struct {
  char name[MAX_NAME_LEN+1];
  int  score;
} hs_entry_t;

void   highscore_init(void);
bool   highscore_try_add(int score); 
void   highscore_draw(void);

#endif // HIGHSCORE_H
