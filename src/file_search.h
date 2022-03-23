#ifndef SRC_FILE_SEARCH_H_
#define SRC_FILE_SEARCH_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define TMP_FILE_WITH_TXT "data_files_names"

char *str_finput(FILE *file);
int is_file_txt(const char *file);

void create_tmp_file_with_txt(const char *folder);
void remove_tmp_file_with_txt();
char **read_tmp_file_with_txt(const char *folder);
char *add_path_to_file(char *file, const char *folder);
size_t count_txt_files();

#endif  // SRC_FILE_SEARCH_H_
