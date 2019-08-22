#include <string.h>
#include <stdbool.h>
#include "score.h"
#include "file_tools.h"
#include <stdlib.h>
#include <stdio.h>

static bool check_score(Score *old_scores, int new_score);
void add_score(Score *old_scores, char *new_name, int new_score);
static int find_index_for_score(Score *old_scores, int new_score);
static void shift_scores(Score *old_scores, int new_index);

void add_score(Score *old_scores, char *new_name, int new_score) {
    int num_records, new_index;
    if (!check_score(old_scores, new_score)) return;
    num_records = old_scores->num_records;
    new_index = find_index_for_score(old_scores, new_score);
    shift_scores(old_scores, new_index);
    strcpy(old_scores->names[new_index], new_name);
    old_scores->scores[new_index] = new_score;
    write_to_file("highscores.bin", *old_scores);
}
static bool check_score(Score *old_scores, int new_score) {
    if (old_scores->num_records < MAX_SCORES && new_score > 0) {
        old_scores->num_records ++;
        return true;
    } else {
        return old_scores->scores[MAX_SCORES-1] < new_score;
    }
}

static int find_index_for_score(Score *old_scores, int new_score) {
    int index = old_scores->num_records;
    while (index > 0 && old_scores->scores[index - 1] < new_score) {
        index --;
    }
    return index;
}

static void shift_scores(Score *old_scores, int new_index) {
    if (new_index == old_scores->num_records-1) {
        return;
    } else {
        int cur_index = MAX_SCORES - 2;
        while (cur_index >= new_index) {
            old_scores->scores[cur_index+1] = old_scores->scores[cur_index];
            strcpy(old_scores->names[cur_index+1], old_scores->names[cur_index]);
            cur_index--;
        }
    }
}
