#include <ncurses.h>
#include <unistd.h>
#include <locale.h>
#include "main.h"

int main(void)
{
  int x;
  int end = 0;
  setlocale(LC_ALL, "");
  initscr();
  if (ScreenSet() != 0)
  {
    return 0;
  }
  start_color();

  init_pair(1, COLOR_WHITE, COLOR_BLACK);   /*文字*/
  init_pair(2, COLOR_WHITE, COLOR_WHITE);   /*背景（全体）*/
  init_pair(3, COLOR_BLACK, COLOR_BLACK);   /*背景（フィールド）*/
  init_pair(4, COLOR_GREEN, COLOR_GREEN);   /*キャラクター（蛇）*/
  init_pair(5, COLOR_YELLOW, COLOR_YELLOW); /*キャラクター（えさ）*/
  init_pair(6, COLOR_BLACK, COLOR_WHITE);   /*文字（反転）*/
  init_pair(7, COLOR_BLUE, COLOR_BLUE);     /*スコア（背景）*/
  init_pair(8, COLOR_WHITE, COLOR_BLUE);    /*スコア（文字）*/
  init_pair(9, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(10, COLOR_RED, COLOR_RED);
  crmode();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);

  while (end != 1)
  {
    x = Screen();
    switch (x)
    {
    case '1':
      Game();
      break;
    case '0':
      end = 1;
      break;
    default:
      break;
    }
  }

  endwin();
  return 0;
}
