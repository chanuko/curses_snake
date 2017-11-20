#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include "main.h"

void RecordMenu(void){

  int i=0,ch;
  FILE *fp;
  char buf[256];
  field();
  attrset(COLOR_PAIR(1));
  mvprintw(1, 5, "Help");


  if ((fp = fopen("record.txt", "r")) == NULL) {
    mvprintw(SCR_Y/2-1,SCR_X/2-(strlen("ファイルをオープンできません。")/2+2),"☆エラー☆");
    mvprintw(SCR_Y/2,SCR_X/2-(strlen("ファイルをオープンできません。")/2),"ファイルをオープンできません。");
    refresh();
    sleep(3);
    return;
  } else {
    for(i=0; fgets(buf, 256, fp)!=NULL;i++)  {
      mvprintw(i+3,1,"%s",buf);
    }
    fclose(fp);
  }

  mvprintw(SCR_Y-2, SCR_X-10, "0.Return");
  refresh();
  while(1){
    ch = getch();
    if(ch=='0') break;
  }
  
  return;
}
