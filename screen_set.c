#include <ncurses.h>
#include <unistd.h>
#include "main.h"

int ScreenSet(void)
{
  int x, y;

  getmaxyx(stdscr, y, x);
  if ((SCR_X > x) || (SCR_Y > y))
  {
    endwin();
    printf("画面サイズを%d×%d以上にしてください。 \nx:%d y:%d\n", SCR_X, SCR_Y, x, y);

    return 1;
  }
  return 0;
}
