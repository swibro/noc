#include <curses.h>
#include <string.h>
#include <ctype.h>
#include "uthash.h"
#include "keywords.h"
#include "globals.h"

// add to everything to header file when done
const char *delims = ""
int pos_buff = 0;


int colorize(int token_id, int pos_char) {
  switch(token_id) {
    case 1:
      move(movey, pos_char);
      attron(COLOR_PAIR(4));
      printw("void");
      attroff(COLOR_PAIR(4));
      move(movey, movex);
  }
}


int tokenize(char *line) {
  char *linebuff = malloc(strlen(line) + 1);
  strcpy(linebuff, line);
  char * tok;
  tok = strtok(linebuff, delims);
  struct keyword *found;
  while(tok != NULL) {
    HASH_FIND_STR(kw_table, tok, found);
    if(found != NULL) {
      pos_buff = tok - linebuff
      if(found->id < 16) {
        colorize(found->id, pos_buff);
      }
      else {
        // keyword
      }
    }
    tok = strtok(NULL, delims);
  }
  free(linebuff);
}

/*

void tokenize(void) {
  for(i=0;i<ymax;i++) {
    for(j=0;j<linecharcap;j++) {
      if(isalpha(lines[ymin + i][j])) {

      }
      else if(isdigit(lines[ymin + i][j])) {
        if(isalpha(lines[ymin + i][j - 1]) || lines[ymin + i][j - 1] == '.') {
          continue;
        }
        else if(isalpha(lines[ymin + i][j + 1])) {
          continue;
        }
      }
      else if(ispunct(lines[ymin + i][j])) {
        if(lines[ymin + i][j] == '.' && isdigit(lines[ymin + i][j - 1])) {
          continue;
        }

      }
    }
}

*/

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
