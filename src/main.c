#include "main.h"

int main(void) {
  FILE *fp = fopen("data/words.txt", "rt");
  if (fp == NULL) {
    printf("\t[ERROR] File does not exist\n");
    return EXIT_FAILURE;
  }

  size_t count_line = 0u;
  while (!feof(fp)) {
    fscanf(fp, "%*[^\n]%*c");
    count_line++;
  }
  rewind(fp);

  int number_commands = 0;
  printf("Input number of comands (0 > n <= %d): ", MAX_NUM_COM);
  while (scanf("%d", &number_commands) != 1 || number_commands <= 0 || number_commands > MAX_NUM_COM) {
    fscanf(stdin, "%*[^\n]%*c");
    printf("\t[ERROR] Do not correct data\n");
  }

  size_t *scope = (size_t *)calloc(number_commands, sizeof(size_t));
  char **name_com = (char **)malloc(number_commands * sizeof(char *));

  for (size_t i = 0; i < (size_t)number_commands; ++i) {
    name_com[i] = (char *)malloc(20 * sizeof(char));
    printf("Name of %lu team: ", i + 1);
    scanf("%20s", name_com[i]);
  }

  char *line = (char *)malloc(256 * sizeof(char));
  int menu_option = 0;
  while (menu_option != -1) {
    for (int i = 0; i < number_commands; i++) {
      printf("Team %d: %10s are you ready?\n", i + 1, name_com[i]);
      int ch = 0;
      if ((scanf("%d", &ch) && ch == 1)) {
        time_t endwait;
        int seconds = 120;
        endwait = time(NULL) + seconds;
        srand(time(NULL));
        while (time(NULL) < endwait) {
          int tr_ln = rand() % count_line;
          int cnt_l = 0;
          while (cnt_l < tr_ln) {
            fscanf(fp, "%*[^\n]%*c");
            cnt_l++;
          }
          fgets(line, 256, fp);
          puts(line);
          rewind(fp);
          printf("Press 2 to skip or 3 to go next world.\n");
          scanf("%d", &menu_option);
          if (menu_option == 2) {
            scope[i]--;
          } else if (menu_option == 3) {
            scope[i]++;
          }
        }
      }
    }
    for (int i = 0; i < number_commands; ++i) {
      printf("%2d:%20s | Scope: %3lu\n", i + 1, name_com[i], scope[i]);
    }
    printf("Press -1 to exit or any number for continue\n");
    scanf("%d", &menu_option);
    fscanf(stdin, "%*[^\n]%*c");
  }
  free(line);
  fclose(fp);
  return EXIT_SUCCESS;
}
