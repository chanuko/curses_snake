#define SCR_X 140
#define SCR_Y 50

#define RANGE_X 92
#define RANGE_Y 37

#define FLDS_X 4
#define FLDS_Y 2
#define FLD_X (RANGE_X + FLDS_X)
#define FLD_Y (RANGE_Y + FLDS_Y)

#define SUBS_X FLDS_X
#define SUBS_Y (FLD_Y+1)
#define SUBE_X FLD_X
#define SUBE_Y (SCR_Y-2)


#define FALSE 0
#define TRUE 1

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

typedef struct{
  int x;
  int y;
  int size;
  int dir;
  int point[FLD_X][FLD_Y][2];
  int level;
  int score;

}SNAKE;
SNAKE snake;
typedef struct{
  bool field[FLD_X][FLD_Y];
  int num;
}DOT;
DOT dot;


int main(void);
int ScreenSet(void);
int Screen(void);
void ScreenHelp(void);
void RecordMenu(void);
void Game(void);
void field(void);
void chara(int,char);
