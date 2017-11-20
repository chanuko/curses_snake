#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include "main.h"

int Screen(void)
{
  int ch;
  int i, j;
  FILE *fp;
  char buf[256], tmp[256];

  field();

  chara(0, 't');
  chara(snake.size, 's');
  chara(snake.score, 'p');
  chara(snake.level, 'l');

  attrset(COLOR_PAIR(1));
  attron(A_BLINK);
  mvprintw(FLD_Y / 2 + 2, FLD_X / 2 - (strlen("1.Play Game") / 2), "1.Play Game");
  mvprintw(FLD_Y / 2 + 8, FLD_X / 2 - (strlen("0.Game Oveer") / 2), "0.Game Over");

  refresh();

  if ((fp = fopen("help.txt", "r")) == NULL)
  {
    attron(A_BOLD);
    mvprintw(SUBS_Y + 1, SUBS_X / 2 - (strlen("ファイルをオープンできません。") / 2 + 2), "☆エラー☆");
    mvprintw(SUBS_Y + 2, SUBS_X / 2 - (strlen("ファイルをオープンできません。") / 2), "ファイルをオープンできません。");
    refresh();
    sleep(3);
    return;
  }
  else
  {
    for (i = 0; fgets(buf, sizeof(buf), fp) != NULL; i++)
    {
      printf("\x1b[34;6H");
      for (j = 0; j < i; j++)
        printf("\x1b[1B");
      printf("%s", buf);
    }
    fclose(fp);
  }
  refresh();
  while (1)
  {
    ch = getch();
    if (ch == '0' || ch == '1' || ch == '2' || ch == '3')
      break;
  }

  return ch;
}
