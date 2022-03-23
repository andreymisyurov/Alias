#include "file_search.h"

// Reading one stroke from file
char *str_finput(FILE *file) {
    char *str = NULL, c;
    size_t size = 0;
    if (file) {
        c = fgetc(file);
        if (c != EOF) {
            while (c != '\n') {
                char *tmp = str;
                str = realloc(tmp, (++size + 1) * sizeof(char));
                str[size - 1] = c;
                c = fgetc(file);
            }
            if (str)
            str[size] = '\0';
        }
    }
    return str;
}

// Detecting if file has .txt extension
int is_file_txt(const char *file) {
    int result = 0;
    const char extension[] = ".txt\0";
    const char *last_occur = strstr(file, extension), *last_occur_tmp = last_occur;
    while (last_occur_tmp) {
        last_occur = last_occur_tmp;
        last_occur_tmp++;
        last_occur_tmp = strstr(last_occur_tmp, extension);
    }
    if (last_occur) {
        if (*(last_occur + strlen(extension)) == '\0')
            result = 1;
    }
    return result;
}

// Creating temporary file with list of all .txt files in "folder"
void create_tmp_file_with_txt(const char *folder) {
    // Creating string with command and foolder path
    const size_t tmp_size = strlen(TMP_FILE_WITH_TXT);
    const char cmd_part_1[] = "ls ", cmd_part_3[] = " | grep .txt > ";
    const size_t size_1 = strlen(cmd_part_1), size_2 = strlen(folder), size_3 = strlen(cmd_part_3);
    char *command = calloc(size_1 + size_2 + size_3 + tmp_size + 1, sizeof(char));
    command = strcat(command, cmd_part_1);
    command = strcat(command, folder);
    command = strcat(command, cmd_part_3);
    command = strcat(command, TMP_FILE_WITH_TXT);
    // ! THIS WORKS ONLY ON UNIX-OS DEVICES
    system(command);
    free(command);
}

// Removal of tmp file with .txt's
void remove_tmp_file_with_txt() {
    const char cmd_1[] = "rm -rf ";
    const size_t size_1 = strlen(cmd_1), size_2 = strlen(TMP_FILE_WITH_TXT);
    char *command = calloc(size_1 + size_2 + 1, sizeof(char));
    command = strcat(command, cmd_1);
    command = strcat(command, TMP_FILE_WITH_TXT);
    system(command);
    free(command);
}

// Adding path to folder to readed filenames
char *add_path_to_file(char *file, const char *folder) {
    char *str = calloc(strlen(file) + strlen(folder) + 1, sizeof(char));
    str = strcat(str, folder);
    str = strcat(str, file);
    free(file);
    return str;
}

/*
    Reading temporary file with list of all .txt files and
    transfering it to char** object
*/
char **read_tmp_file_with_txt(const char *folder) {
    FILE *file = fopen(TMP_FILE_WITH_TXT, "r");
    char **files = NULL;
    size_t files_size = 0;
    while (!feof(file)) {
        char *str = str_finput(file);
        if (str) {
            if (is_file_txt(str)) {
                str = add_path_to_file(str, folder);
                char **tmp_files = files;
                files = realloc(tmp_files, ++files_size * sizeof(char*));
                files[files_size - 1] = str;
            } else {
                free(str);
            }
            char c = fgetc(file);
            if (c != EOF) {
                fseek(file, -1, SEEK_CUR);
            } else if (c == '\n') {
                c = fgetc(file);
            }
        } else {
            break;
        }
    }
    if (file)
        fclose(file);
    return files;
}

// Counting all .txt files in "folder"
size_t count_txt_files() {
    size_t result = 0;
    FILE *file = fopen(TMP_FILE_WITH_TXT, "r");
    char c;
    if (file) {
        c = fgetc(file);
        while (!feof(file)) {
            if (c == '\n')
                result++;
            c = fgetc(file);
        }
        if (file)
            fclose(file);
    }
    return result;
}
