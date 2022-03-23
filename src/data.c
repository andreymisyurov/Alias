#include "data.h"

// Initialization of one record
Record *init_record() {
    Record *result = malloc(sizeof(Record));
    result->eng_word = NULL;
    result->transcription = NULL;
    result->rus_word = NULL;
    return result;
}

// Cleaning allocated memory
void free_record(Record *record) {
    if (record) {  // ! in case of uninitialized record
        if (record->eng_word)
            free(record->eng_word);
        if (record->transcription)
            free(record->transcription);
        if (record->rus_word)
            free(record->rus_word);
        free(record);
    }
}

// Reading records without memorising them
void skip_record(FILE *file) {
    unsigned char c = fgetc(file);
    while (c != '\n')
        c = fgetc(file);
}

// Reading record into memory
Record *mem_record(FILE *file) {
    unsigned char *str1 = NULL, c = fgetc(file);
    size_t size = 0;
    Record *result = init_record();
    while (c != '/') {
        unsigned char *tmp = str1;
        str1 = realloc(tmp, (++size + 1) * sizeof(unsigned char));
        str1[size - 1] = c;
        c = fgetc(file);
    }
    if (str1) {  // ! Theoretically it is possible that str1 will be NULL
        // in case of unwilling space after last eng word
        unsigned char *tmp = str1;
        str1 = realloc(tmp, size * sizeof(unsigned char));
        str1[size - 1] = '\0';
    }
    result->eng_word = str1;
    size = 0;
    unsigned char *str2 = NULL;
    c = fgetc(file);
    while (c != '/') {
        unsigned char *tmp = str2;
        str2 = realloc(tmp, (++size + 1) * sizeof(unsigned char));
        str2[size - 1] = c;
        c = fgetc(file);
    }
    if (str2) {  // ! Theoretically it is possible that str1 will be NULL
        // in case of unwilling space after last eng word
        unsigned char *tmp = str2;
        str2 = realloc(tmp, size * sizeof(unsigned char));
        str2[size - 1] = '\0';
    }
    result->transcription = str2;
    size = 0;
    unsigned char *str3 = NULL;
    c = fgetc(file);
    while (c != '\n') {
        unsigned char *tmp = str3;
        str3 = realloc(tmp, (++size + 1) * sizeof(char));
        str3[size - 1] = c;
        c = fgetc(file);
    }
    if (str3)  // ! Like str1 && str2^^
        str3[size] = '\0';
    result->rus_word = str3;
    return result;
}

// Counting records in one file
size_t count_records(FILE *file) {
    fseek(file, 0, SEEK_SET);
    size_t result = 0;
    unsigned char c = fgetc(file);
    c = fgetc(file);
    if (file) {  // ! In case if this file will not be opened
        while (!feof(file)) {
            if (c == '\n')
                result++;
            c = fgetc(file);
        }
    }
    return result;
}

// Counting all the records in all .txt files
size_t count_all_records(char **file_names, const size_t files_count) {
    size_t result = 0;
    for (size_t i = 0; i < files_count; i++) {
        FILE *file = fopen(file_names[i], "r");
        if (file) {
            result += count_records(file);
            fclose(file);
        }
    }
    return result;
}

// Input one record from 
Record *read_record(FILE *file, size_t pos) {
    fseek(file, 0, SEEK_SET);
    Record *record = NULL;
    for (size_t i = 1; i < pos; i++)
        skip_record(file);
    record = mem_record(file);
    return record;
}

/*
    Displaying all files contents from given folder
    on the screen (just debug information)
*/
void show_files_contents(const char *folder) {
    create_tmp_file_with_txt(folder);  // creating file with list of .txt files
    const size_t files_count = count_txt_files();
    char **files = read_tmp_file_with_txt(folder);
    remove_tmp_file_with_txt();
    printf("Total records: %lu in %lu files\n", count_all_records(files, files_count), files_count);
    for (size_t i = 0; i < files_count; i++) {
        FILE *file = fopen(files[i], "r");
        const size_t record_count = count_records(file);
        printf("----IN FILE %s - %lu RECORDS----\n", files[i], record_count);
        for (size_t j = 1; j <= record_count; j++) {
            Record *record = read_record(file, j);
            printf("%s [ %s ] - %s", record->eng_word, record->transcription, record->rus_word);
            free_record(record);
            if (j != record_count)
                printf("\n");
        }
        if (i != files_count - 1)
            printf("\n\n");
        if (file)
            fclose(file);
    }
    for (size_t i = 0; i < files_count; i++)
        free(files[i]);
    free(files);
}
