#include <stdio.h>
#include <stdlib.h>
#include "score.h"
#include "file_tools.h"

int read_from_file(char *filename, Score *buf) {
    FILE *fptr = fopen(filename, "rb");
    if (fptr == NULL) {
       return 1;
    }
    fread(buf, sizeof(Score),1,fptr);
    fclose(fptr);
    return 0; 
}

int write_to_file(char *filename, Score buf) {
    FILE *fptr = fopen(filename, "wb"); 
    if (fptr == NULL) {
        return 1;
    }
    fwrite(&buf,sizeof(Score),1,fptr);
    fclose(fptr);
    return 0;
}
