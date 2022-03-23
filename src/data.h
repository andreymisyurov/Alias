#ifndef SRC_DATA_H_
#define SRC_DATA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_search.h"

typedef struct record {
    unsigned char *eng_word, *transcription, *rus_word;
} Record;

Record *init_record();
void free_record(Record *record);
void skip_record(FILE *file);
Record *mem_record(FILE *file);
size_t count_records(FILE *file);
size_t count_all_records(char **file_names, const size_t files_count);
Record *read_record(FILE *file, size_t pos);

void show_files_contents(const char *folder);

#endif  // SRC_DATA_H_
