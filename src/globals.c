#include <stdio.h>
#include <stddef.h>

char *filename;
FILE *fptr;
FILE *logfile;
char *log_filename = ".noclogs";

int movex = 0;  // movex and movey are used only inside move() functions to correct for text wrapping
int movey = 1;

int x = 0;
int y = 1;


int j;      // looping var over all x in a line
int i;      // looping var over all lines in the file/y on screen

int xmax;
int ymax;
int ymin;   // ymin used to indicate top visible row; same indexing as lines[i][j] so ymin = 0 is the first writable line

int key;


int mode = 0;
/*  0 - read mode
 *  1 - edit mode
 *  2 - menu screen (same idea as just typing 'vim' instead of 'vim file')
 */

// ymax is used for rendering text on screen
// linecount is for total length of lines array


int linecap = 1024;
int linecharcap = 512;

int linecount = 0; // linecount++ and -- should be reserved for the edit_mode() and main() functions
                   // this is just for readability and code segmentation

char** lines = NULL;   // main array of lines which are arrays of each position
                       // lines[y-1][x] represents the character stored at position (y,x) (ncurses notation)
                       // y-1 because nothing needs to be stored on title line
                       // once again this implies the last line will be lines[ymax-1]

char** display_lines = NULL;
