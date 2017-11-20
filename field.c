#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include "main.h"
void field(void)
{
  int i, j;
  bkgd(COLOR_PAIR(2));
  refresh();

  attrset(COLOR_PAIR(3));
  for (i = 0; i < SCR_Y; i++)
  {
    for (j = 0; j < SCR_X; j += 2)
    {
      mvaddch(i, j, 'a');
      mvaddch(i, j + 1, 'a');
    }
  }

  attrset(COLOR_PAIR(2));
  /*tate*/
  mvvline(FLDS_Y - 1, FLDS_X - 2, 'a', SCR_Y - 2);
  mvvline(FLDS_Y - 1, FLDS_X - 1, 'a', SCR_Y - 2);
  mvvline(FLDS_Y - 1, FLD_X, 'a', FLD_Y);
  mvvline(FLDS_Y - 1, FLD_X + 1, 'a', FLD_Y);
  mvvline(FLDS_Y - 1, SCR_X - 4, 'a', SCR_Y - 2);
  mvvline(FLDS_Y - 1, SCR_X - 3, 'a', SCR_Y - 2);
  /*yoko*/
  mvhline(FLDS_Y - 1, FLDS_X - 2, 'a', SCR_X - 4);
  mvhline(FLD_Y, FLDS_X - 2, 'a', SCR_X - 4);
  mvhline(SCR_Y - 2, FLDS_X - 2, 'a', SCR_X - 4);
  mvhline(FLD_Y - 24, FLD_X, 'a', SCR_X - 4);
  mvhline(FLD_Y - 12, FLD_X, 'a', SCR_X - 4);
  /*huchi*/
  attrset(COLOR_PAIR(10));
  mvvline(0, 0, 'a', SCR_Y);
  mvvline(0, 1, 'a', SCR_Y);
  mvvline(0, SCR_X - 2, 'a', SCR_Y);
  mvvline(0, SCR_X - 1, 'a', SCR_Y);
  mvhline(0, 0, 'a', SCR_X);
  mvhline(SCR_Y - 1, 0, 'a', SCR_X);

  refresh();
  return;
}
