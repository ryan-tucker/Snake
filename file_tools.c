#include <stdio.h>
#include <stdlib.h>
#include "score.h"

int read_from_file(char *filename, score *buf) {
    FILE *fptr = fopen(filename, "rb");
    score to_return;
    if (fptr == NULL) {
       return 1;
    }
    fread(buf, sizeof(score),1,fptr);
    fclose(fptr);
    return 0; 
}

int write_to_file(char *filename, score buf) {
    FILE *fptr = fopen(filename, "wb"); 
    if (fptr == NULL) {
        return 1;
    }
    fwrite(&buf,sizeof(score),1,fptr);
    fclose(fptr);
    return 0;
}
