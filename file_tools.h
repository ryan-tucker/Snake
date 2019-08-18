#ifndef FILE_TOOLS_H
#define FILE_TOOLS_H
#include "score.h"

int read_from_file(char *filename, score *buf);
int write_to_file(char *filename, score buf);
#endif
