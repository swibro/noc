#include <curses.h>
#include <ctype.h>

// add to everything to header file when done


struct statement_list {
  
}

int is_statement(char* tempstr) {

}

void tokenize(void) {
  for(i=0;i<ymax;i++) {
    for(j=0;j<linecharcap;j++) {
      if(isalpha(lines[ymin + i][j])) {

      }
      else if(isdigit(lines[ymin + i][j])) {

      }
      else if(ispunct(lines[ymin + i][j])) {
        if(lines[ymin + i][j] == '.' && isdigit(lines[ymin + i][j - 1])) {
          continue;
        }

      }
    }
}

void init_colors(void) {
  start_color();
  use_default_colors();

  init_pair(1, -1, -1);
  init_pair(2, COLOR_WHITE, -1)
  init_pair(3, COLOR_CYAN, -1)
  init_pair(4, COLOR_GREEN, -1)
  init_pair(5, COLOR_YELLOW, -1)
  init_pair(6, COLOR_MAGENTA, -1)
}
