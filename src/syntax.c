#include <curses.h>

void tokenize(void) {
  const char delims[40] = "~`!@#$%^&*()-+={}[]:;,.<>?/'| ";
  for(i=0;i<ymax;i++) {
    char* token_buffer = lines[ymin + i];
    display_lines[i] = strtok(token_buffer, delims);
  }
  for(i=0;i<ymax;i++) {
    while(display_lines[i] != 0) {
      move(i, 0);
      printw("%s", display_lines[i]);
      display_lines[i] = strtok(NULL, delims);
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
