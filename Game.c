#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include <stdlib.h>
#include "main.h"


int kbhit(void){
  struct termios oldt, newt;
  int ch;
  int oldf;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
  ch = getch();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
  if(ch != EOF)
    {
      ungetch(ch);
    return 1;
    }
  return 0;
}

void draw_dot(void){
  int i,j;
  for(i=FLDS_Y; i<FLD_Y; i++){
    for(j=FLDS_X; j<FLD_X; j+=2){
      if(dot.field[j][i]==TRUE){
        attrset(COLOR_PAIR(5));
        mvaddch(i,j,'a');
        mvaddch(i,j+1,'a');
      }
    }
  }
}

void put_dot(void){
  int max_dot = 50;
  int x,y;
  srand((unsigned) time(NULL));
  while(max_dot>dot.num){
    x=((rand()%RANGE_X/2)*2)+FLDS_X;
    y=(rand()%RANGE_Y)+FLDS_Y;
    if(dot.field[x][y]!=TRUE){
      dot.field[x][y]=TRUE;
      dot.num++;
    }
  }
  draw_dot();
}



void draw_snake(void){
  int i,j;
  for(i=FLDS_Y; i<FLD_Y; i++){
    for(j=FLDS_X; j<FLD_X; j+=2){
      if(snake.point[j][i][0]==TRUE){
        if(snake.point[j][i][1]>0){
          attrset(COLOR_PAIR(4));
          mvaddch(i,j,'a');
          mvaddch(i,j+1,'a');
          snake.point[j][i][1]--;
        }else{
          snake.point[j][i][0]=FALSE;
          attrset(COLOR_PAIR(3));
          mvaddch(i,j,'a');
          mvaddch(i,j+1,'a');
        }
      }
    }
  }
  return;
}

void init_snake(void){
  snake.x=20;
  snake.y=20;
  snake.size=2;
  snake.point[snake.x][snake.y][0]=TRUE;
  snake.point[snake.x][snake.y][1]=snake.size;
  snake.dir=RIGHT;
  snake.level=1;
  snake.score=0;
return;
}
void init_field(void){
  int i,j;
  for(i=FLDS_Y; i<FLD_Y; i++){
    for(j=FLDS_X; j<FLD_X; j+=2){
      snake.point[j][i][0]=FALSE;
      dot.field[j][i]=FALSE;
    }
  }
  dot.num=0;
}
void subScr(int is, int ie, int js, int je, int c){
  int i,j;
  for(i=is; i<ie; i++){
    for(j=js; j<je;j++){
      attrset(COLOR_PAIR(c));
      mvaddch(i,j,'a');
    }
  }refresh();
}
void Game(void){
  int ch,x,y;
  int flag;
  int i,j;
  int count=0;
  int speed = 150000;
  field();
  noecho();
  init_field();
  init_snake();
  put_dot();
  flag=TRUE;
  while(flag==TRUE){



    chara(snake.size,'s');
    chara(snake.score,'p');
    chara(snake.level,'l');

    switch(ch){
    case KEY_UP:
      if(snake.dir==RIGHT || snake.dir==LEFT)
	snake.dir=UP;
      break;
    case KEY_DOWN:
      if(snake.dir==RIGHT || snake.dir==LEFT)
	snake.dir=DOWN;
      break;
    case KEY_LEFT:
      if(snake.dir==UP || snake.dir==DOWN)
	snake.dir=LEFT;
      break;
    case KEY_RIGHT:
      if(snake.dir==UP || snake.dir==DOWN)
	snake.dir=RIGHT;
      break;
    default: break;
    }
    switch(snake.dir){
    case UP:    snake.y--;  break;
    case DOWN:  snake.y++;  break;
    case LEFT:  snake.x-=2; break;
    case RIGHT: snake.x+=2; break;
    }
    count++;
    if(count%100==0){
      snake.level++;
      if(speed>=10000)
	speed=160000-snake.level*5000;
    }
    if(snake.point[snake.x][snake.y][0]==TRUE)
      flag=FALSE;
    else{
      snake.point[snake.x][snake.y][0]=TRUE;
      snake.point[snake.x][snake.y][1]=snake.size;
    }

    if(dot.field[snake.x][snake.y]==TRUE){
      dot.field[snake.x][snake.y]=FALSE;
      snake.size++;
      dot.num--;
    }

    if(count%10==0)
      put_dot();
    else
      draw_dot();

    if(snake.x<FLD_X && snake.x>=FLDS_X && snake.y<FLD_Y && snake.y>=FLDS_Y)
      snake.score = snake.score + snake.size *snake.level;
    else flag=FALSE;

    draw_snake();

    usleep(speed);
    refresh();

    if(kbhit())ch=getch();

  }

  subScr(FLD_Y/3, FLD_Y-FLD_Y/3, FLD_X/5, FLD_X-FLD_X/5, 7);

  attrset(COLOR_PAIR(8));
  attron(A_BOLD);
  mvprintw(FLD_Y/2, FLD_X/2-(strlen("Break!!")/2), "Break!!");
  refresh();
  sleep(1);
  mvprintw(FLD_Y/2, FLD_X/2-(strlen("Game Over")/2), "         ");
  mvprintw(FLD_Y/2-2, FLD_X/2-(strlen("Game Over")/2), "Game Over");
  mvprintw(FLD_Y/2+1, FLD_X/2-(strlen("Score :       ")/2), "Score : %6d",snake.score);
  refresh();
  sleep(5);
  return;
}

