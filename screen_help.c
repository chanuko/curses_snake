#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include "main.h"

void ScreenHelp(void)
{
  int i;
  FILE *fp;
  char buf[256];
  field();
  attrset(COLOR_PAIR(1));
  mvprintw(1, 5, "Help");

  if ((fp = fopen("help.txt", "r")) == NULL)
  {
    attron(A_BOLD);
    mvprintw(SCR_Y / 2 - 1, SCR_X / 2 - (strlen("ファイルをオープンできません。") / 2 + 2), "☆エラー☆");
    mvprintw(SCR_Y / 2, SCR_X / 2 - (strlen("ファイルをオープンできません。") / 2), "ファイルをオープンできません。");
    refresh();
    sleep(3);
    return;
  }
  else
  {
    for (i = 0; fgets(buf, sizeof(buf), fp) != NULL; i++)
    {
      attron(A_BOLD);
      attrset(COLOR_PAIR(6));
      if (buf[0] != '\n')
        mvprintw(i + 3, 1, "%s", buf);
    }
    fclose(fp);
  }

  mvprintw(SCR_Y - 2, SCR_X - 10, "0.Return");
  refresh();
  while (getch() != '0')
    ;

  return;
}
