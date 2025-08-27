#include <stdlib.h>
#include <stdio.h>
#include "globals.h"

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


