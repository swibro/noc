#include <curses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


/**********************************OVERVIEW****************************************
 *
 * noc 
 *
 * This is a text editor that takes in a filename as an argument and either opens
 * and allows editing of the file or creates a new one and allows editing of that
 * if it does not exist.
 *
 * The main memory is the pointer array 'lines' which points to array pointers
 * 'lines[i]'. Characters are stored at 'lines[i][j]', which would be the j-th
 * character in row i.
 *
 * text wrapping may not be the best as I had to use two variables so when moving
 * better to just use movex++ and x++ or movey++ and y++ unless dealing specifically
 * with text wrapping
 * 
 *
 *
 *
 **********************************LICENSE*****************************************
 *
 * BSD 2-Clause License
 *
 * Copyright (c) 2025, Spencer Brown <gamelover750 at yahoo dot com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 *
 *
 *
 ******************************INDEXING NOTES*****************************************
 *
 * For memory purposes unbeknownst to me use lines[0] to represent y=1
 * or the first line of typing.
 * 
 * When referring to current line use lines[y-1]
 * 
 * By the same token, lines[ymax-1] is the lowest line, do not print 
 * lines[ymax-1] or you get an artifact in the bottom right corner.
 * 
 * ymax use the same numbering system as y therefore the final line will be lines[ymax-1]
 *
 *
 *
 *
 ********************************LOCAL/TEMP VARS***********************************
 * 
 *  -line
 *  -val
 *  -pmsg
 *
 *
 *
 *
 **********************************BUGS*******************************************
 *
 * not really a bug but unistd.h which provides access functions
 * for checking file existence/permissions doesnt work on windows
 *
 *
 *
 *
 *********************************************************************************/




/************************************************GLOBALS*************************************/

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





/**************************************************LOGGING********************************/

int init_logs(void)
{
  logfile = fopen(log_filename, "w");
  if(logfile==NULL)
  {
    return 1;
  }
  else
  {
    fclose(logfile);
    return 0;
  }
}

void log_message(char *pmsg)
{
  logfile = fopen(log_filename, "a");
  fprintf(logfile, "%s\n", pmsg);
  fclose(logfile);
}


/************************************************UTILS********************************/

int is_char(int val)
{
  if((val >= 31 && val <= 126) || val == 9){return 1;} // 9 is tab
  else{return 0;}
}



int end_window(void)    // only use after initializing lines  ;  before that use endwin()
{
  for(i=0;i<linecount;i++)
  {
    if(lines[i])
    {
      free(lines[i]);
    }
    else
    {
      char tempstr[40];
      snprintf(tempstr, 40, "lines[%d] tried to be freed but was NULL", i);
      log_message(tempstr);
    }
  }
  if(lines)
  {
    free(lines);
    log_message("lines successfully freed");
  }
  else
  {
    log_message("lines tried to be freed but was NULL");
  }
  endwin();
  return 0;
}
  

/**************************************************MEMORY********************************************/


char* init_line(void)
{                     // im looking at this line below and this cannot be the best way to do this
  char *line = (char *)malloc(linecharcap);
  if(line == NULL)
  {
    log_message("Error allocating memory for new line");
    exit(1);
  }
  else
  {
    for(j=0;j<linecharcap;j++)
    {
      line[j] = '\0';
    }
    return line;
  }
}

void del_line(void)
{
  for(i=ymin+y-1;i<linecount-1;i++)
  {
    memmove(lines[i], lines[i+1], linecharcap);
  }
  free(lines[linecount-1]);
  linecount--;
}


void shift_lines(void)
{
  for(i=linecount;i>y+ymin;i--)
  {
    memmove(lines[i], lines[i-1], linecharcap);
  }
  for(j=x;j<linecharcap;j++)
  {
    lines[y][j-x] = lines[y-1][j];
    lines[y-1][j] = '\0';
  }
}

void shift_chars(void)
{
  for(j=linecharcap;j>x;j--)
  {
    lines[y-1][j] = lines[y-1][j-1];
  }
}

/*****************************************************EDITING FUNCTIONS********************************/

void backspace(void)
{
  if(x > 0)
  {
    movex--;
    x--;
    lines[ymin+y-1][x] = '\0';
    for(j=x;j<linecharcap;j++)
    {
      lines[ymin+y-1][j] = lines[ymin+y-1][j+1];
    }
    lines[ymin+y-1][linecharcap] = '\0';
  }
  else if(x == 0 && y + ymin > 1)
  {
    for(j=0;j<linecharcap;j++)
    {
      if(is_char(lines[ymin+y-2][j]))
      {
        x=j+1;
      }
    }
    movex = x % xmax;
    for(j=x;j<linecharcap;j++)
    {
      lines[ymin+y-2][j] = lines[ymin+y-1][j-x];
    }
    del_line();
    movey--;
    y--;
  }
}

void new_line(void)
{
  lines[linecount] = init_line();
  shift_lines();
  linecount++;
  lines[y-1][x] = (char)10;
  if(y<ymax)
  {
    movey++;
    y++;
  }
  else
  {
    ymin++;
  }
  movex=0;
  x=0;
}
void space_tab(int tab_spaces)
{
  for(i=0;i<tab_spaces;i++)
  {
    shift_chars();
    lines[y-1][x] = (char)32;
    movex++;
    x++;
  }
  if(movex > xmax)
  {
    movex = 1;
    movey++;
  }
}

/**************************************************MOVEMENT**************************************/

void move_down(void)
{
  if(ymin+y<linecount && y+1<ymax)
  {
    movey++;
    y++;
  }
  else if(ymin+y<linecount)
  {
    ymin++;
  }
  for(j=x;j>0;j--)
  {
    if(is_char(lines[y-1][j-1]))
    {
      movex=j;
      x=j;
      break;
    }
    else
    {
      movex=0;
      x=0;
    }
  }
}

int move_up(void)
{
  if(y == 1 && ymin > 0)
  {
    ymin--;
    return 0;
  }
  else if(y == 1)
  {
    return 0;
  }
  else
  {
    movey--;
    y--;
    for(j=x;j>0;j--)
    {
      if(is_char(lines[y-1][j-1]))
      {
        movex=j;
        x=j;
        break;
      }
      else
      {
        movex=0;
        x=0;
      }
    }
    return 0;
  }
}

void move_right(void)
{
  if(movex != xmax)
  {
    if(is_char(lines[y-1][x]))
    {
      movex++;
      x++;
    }
  }
  else
  {
    if(is_char(lines[y-1][x]))
    {
      movex = 0;
      movey++;
      x++;
    }
  }
}

void move_left(void)
{
  if(movex == 0 && x != 0)
  {
    movex = xmax;
    movey--;
    x--;
  }
  else if(x > 0)
  {
    movex--;
    x--;
  }
}

/***************************************************DISPLAY****************************/



void write_header(char *pmsg)
{
  move(0,xmax/2);
  printw("%s", pmsg);
  move(movey,movex);
}

void write_footer(char *pmsg)
{
  move(ymax-1,0);
  for(j=0;j<xmax;j++)
  {
    printw("%c", 32);
  }
  move(ymax-1,0);
  printw("%s", pmsg);
  move(movey,movex);
}


void write_title(void)
{
  move(0,0);
  if(mode==0){printw("q - quit               e - edit mode");}
  else if(mode==1){printw("EDIT MODE                     esc - quit");}
  else{printw("Error writing title");}
  move(movey,movex);
}

void write_chrcs(void)
{
  clear();
  write_title();
  int wrap_buff = 1;
  for(i=0;i<ymax-1;i++)
  {
    if(i<linecount)
    {
      for(j=0;j<linecharcap;j++)
      {
        if(j > (wrap_buff*xmax) + 1 && is_char(lines[i+ymin][j]))
        {
          wrap_buff++;
        }
        move((i+1) + (wrap_buff-1), j);
        printw("%c", lines[i+ymin][j]);
      }
    }
    else
    {
      break;
    }
  }
  move(movey,movex);
  refresh();
}



/*********************************************FILE MANAGEMENT*********************************/

int init_file(void)
{
  if(access(filename, F_OK) == 0)
  {
    log_message("File found");
    fptr = fopen(filename, "r");
    if(fptr == NULL)
    {
      log_message("Error opening edit file");
      return 1;
    }
    i=0;
    while(fgets(lines[i], linecharcap, fptr))
    {
      i++;
      lines[linecount] = init_line();
      linecount++;
    }
    fclose(fptr);
    return 0;
  }
  else
  {
    log_message("File not found");
    return 0;
  }
}

void save_file(void)
{
  fptr = fopen(filename, "w");
  if(fptr == NULL)
  {
    log_message("Error opening file to save");
  }
  for(i=0;i<linecount;i++)
  {
    fprintf(fptr, "%s", lines[i]);
  }
  fclose(fptr);
}




/******************************PUT IT ALL IN THE POT***********************/

void edit_mode(void)
{
  mode = 1;
	while(key != 27) // ESC
	{
    write_chrcs();
		key = getch();
		switch(key)
		{
			case KEY_LEFT:
        move_left();
        break;

			case KEY_RIGHT:
        move_right();
        break;
			  
			case KEY_UP:
        move_up();
        break;

			case KEY_DOWN:
        move_down();
        break;

      case 127: // BCKSPC (MacOS)
        backspace();
        break;

			case KEY_BACKSPACE:
        backspace();
        break;

      case 330: // DEL
        del_line();
        movex=0;
        x=0;
        break;

			case 10: // ENTER
        new_line();
        break;

      case 9: // 2 SPACE TAB (value can be safely edited or disabled by commenting out case which puts regular tabs back)
        space_tab(2);
        break;

			default:
        if(is_char(key))
        {
          shift_chars();
          lines[y-1][x] = (char)key;
          movex++;
          x++;
        }
        if(movex > xmax)
        {
          movex = 1;
          movey++;
        }
        break;
		}
	}
	mode = 0;
}



int main(int argc, char **argv)
{
	use_env(TRUE); initscr(); keypad(stdscr, TRUE); noecho();
	xmax = COLS; ymax = LINES; ESCDELAY = 10;

// Initialization and error handling

  // logs

  if(init_logs())
  {
    endwin();
    printf("Error initializing log file\nCheck if %s is read protected\n", log_filename);
    exit(1);
  }
  log_message("Logs initialized");
  
  // lines

  lines = malloc(linecap * sizeof(char *));
  if(lines == NULL)
  {
    log_message("Error allocating space for lines");
    endwin();
    exit(1);
  }                                                       // Past here use end_window();
  log_message("lines memory successfully allocated");

  lines[linecount] = init_line();
  linecount++;
  log_message("lines[0] allocated and initialized");

  // file

  if(argc == 1)
  {
    end_window();
    printf("Too few arguments; need file name to edit or create\n");
    exit(1);
  }

  if(argc > 2)
  {
    end_window();
    printf("Too many arguments\n");
    exit(1);
  }

  filename = argv[1];
  log_message("filename read");
  if(strcmp(filename, ".noclogs") == 0)
  {
    end_window();
    printf("Cannot edit noc log file with noc\n");
    printf("Please use another text editor or change the log filename\n");
    exit(1);
  }
  if(init_file())
  {
    end_window();
    printf("Error initializing chosen file (check file permissions)\n");
    exit(1);
  }
  else
  {
    log_message("file initialized");
  }

// Main Loop

	while(key != 'q')
	{
    write_chrcs();
    log_message("chrcs written");
		key = getch();
		switch(key)
		{
			case KEY_LEFT:
        move_left();
        break;

			case KEY_RIGHT:
        move_right();
        break;

      case KEY_UP:
        move_up();
        break;

			case KEY_DOWN:
        move_down();
        break;

      case 'e':
		  	edit_mode();
        break;

      case 'S':
        if(argc == 2)
        {
          save_file();
          write_footer("file saved - press any key to continue");
          getch();
        }
        break;

      /* dev */ /*
      case 'p':
        write_footer("Press a key");
        write_footer("");
        move(ymax-1,xmax/2);
        int tempkey = getch();
        printw("%d",tempkey);
        move(movey,movex);
        getch();
      */
		}
	}
  log_message("switch exited");
  end_window();
  log_message("program terminated");
	return 0;
}
