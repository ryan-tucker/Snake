#ifndef SCORE_H
#define SCORE_H
#include <stdbool.h>
#define MAX_SCORES 5
#define MAX_NAME_LENGTH 20
typedef struct score {
    char names[MAX_SCORES][MAX_NAME_LENGTH];
    int scores[MAX_SCORES];
    int num_records;
} Score;

bool check_score(Score old_scores, int new_score);
void add_score(Score *old_scores, char *new_name, int new_score);
Score *init_dummy_score();
#endif
