#ifndef GLOBALS_H
#define GLOBALS_H

extern char *filename;
extern FILE *fptr;
extern FILE *logfile;
extern char *log_filename;
extern int movex;  // movex and movey are used only inside move() functions to correct for text wrapping
extern int movey;
extern int x;
extern int y;
extern int j;      // looping var over all x in a line
extern int i;      // looping var over all lines in the file/y on screen
extern int xmax;
extern int ymax;
extern int ymin;   // ymin used to indicate top visible row; same indexing as lines[i][j] so ymin = 0 is the first writable line
extern int key;
extern int mode;
extern int linecap;
extern int linecharcap;
extern int linecount; // linecount++ and -- should be reserved for the edit_mode() and main() functions
extern char** lines;   // main array of lines which are arrays of each position
                       // lines[y-1][x] represents the character stored at position (y,x) (ncurses notation)
                       // y-1 because nothing needs to be stored on title line
                       // once again this implies the last line will be lines[ymax-1]



#endif
