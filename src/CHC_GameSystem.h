#ifndef CHC_GAMESYSTEM_H
#define CHC_GAMESYSTEM_H

#include "CHC_Constants.h"
#include "CHC_Vector3.h"
#include "CHC_Line.h"
#include "CHC_Color.h"
#include "CHC_Mirror.h"
#include "CHC_Laser.h"

#define MAP_WIDTH	16
#define MAP_HEIGHT	16
#define BLANK_ID	0
#define MIRROR_ID	1
#define SENDER_ID	2
#define RECEIVER_ID	3
#define NUM_MIRROR_SORT	MIRROR_TOOLBAR_LEN_Y

static const int dx[4] = {0, 1, 0, -1};
static const int dy[4] = {1, 0, -1, 0};

static const int DirChange[1][4][8] = 
{ { {-1, -1, -1, 2, 4 ,6 , -1, -1},
	{-1, -1, -1, -1, -1, 4, 6, 0},
	{0, 2, -1, -1, -1, -1, -1, 6},
	{-1, 0, 2, 4, -1, -1, -1, -1}
	}
};

/* Mirror */
/* Mirror */
static const float  GetNormal[4][3]=
{{1,0,0},
{0.5,0,0.5},
 {0,0,1},
 {-0.5,0,0.5}};

/*static const float PoChange[4][4][3] =
{{{0.5,0,0},{0.5,0,1},{0.5,1,1},{0.5,1,0}},
{{1,0,0},{0,0,1},{0,1,1},{1,1,0}},
{{1,0,0.5},{0,0,0.5},{0,1,0.5},{1,1,0.5}},
{{1,0,1},{0,0,0},{0,1,0},{1,1,1}}
};*/
static const float PoChange[4][4][3] =
{{{0,0,-0.5},{0,0,0.5},{0,1,0.5},{0,1,-0.5}},
{{0.5,0,-0.5},{-0.5,0,0.5},{-0.5,1,0.5},{0.5,1,-0.5}},
{{0.5,0,0},{-0.5,0,0},{-0.5,1,0},{0.5,1,0}},
{{0.5,0,0.5},{-0.5,0,-0.5},{-0.5,1,-0.5},{0.5,1,0.5}}
};

class CHC_Mir_Info
{
public :
	CHC_Vector3 x[4],n;
	CHC_Mir_Info(){};
	CHC_Mir_Info(int dir,int x_,int y_){
		for (int i = 0 ; i < 4 ; i++){
			x[i] = CHC_Vector3(PoChange[dir % 4][i][0] + x_, PoChange[dir % 4][i][1],PoChange[dir % 4][i][2] + y_);
		}
		n = CHC_Vector3(GetNormal[dir % 4][0],GetNormal[dir % 4][1],GetNormal[dir % 4][2]);
	}
};


class CHC_Map_Info
{
public:
	int obj;					// object id
	int mirror_s;				// mirror sort
	int dir;					// direction
	CHC_Color col[4];				// need when obj is Sender or Receive 

	void operator=(const CHC_Map_Info & m) {
		obj = m.obj;
		dir = m.dir;
		for (int i = 0; i != 4; i++)
			col[i] = m.col[i];
	}
	void setBlank() {
		obj = BLANK_ID;
		for (int i = 0; i != 4; i++)
			col[i].setColor(0, 0, 0);
	}
	bool isMirror() {
		return obj == MIRROR_ID;
	}
	bool isBlank() {
		return obj == BLANK_ID;
	}
	bool isSender() {
		return obj == SENDER_ID;
	}
	bool isReceive() {
		return obj == RECEIVER_ID;
	}
	void getnearest(CHC_Line L , CHC_Vector3 & p) ;
};

class CHC_GameSystem
{
public:
	CHC_Map_Info ori_map[MAP_WIDTH][MAP_HEIGHT];
	CHC_Map_Info now_map[MAP_WIDTH][MAP_HEIGHT];

	bool LoadMap(char *filename);								// Load Map
	
	/* Draw the board situation */
	void DrawMirrorToolbar();									// Draw Mirror Toolbar
	void GameDraw();											// Draw Game

	/* game simulation */
	void RefreshBackTrace(int x, int y, int d, CHC_Color & col);
	int  InToolBar(int x, int y);								// check in toolbar, if in return the mirror sort, otherwise return -1
	bool InMap(int x, int y);									// check (x,y) is in Board
	int Reflection(int inDir, int mDir, int mirrorType = 0);	// Game simulate when reflection
	void Refresh();												// Fresh simulate
	bool Win();													// check whether win
	
	/* Game operation */
	void Restart();												// restart the game
	bool Insert_mirror(int x, int y, int s, int d);					// Insert_mirror in (x,y), direction is d
	bool Delete_mirror(int x, int y);							// Delete_mirror in (x,y)
	
	/* Interation */
	void xyToBoardxy(float fx, float fy, int & x, int &y);		// (fx, fy) change to board (x, y)
	void ClickMouse(CHC_Line & L);					// Click Mouse
	void KeyBoardDelete();
	void KeyBoardChangeState(int dx);
	void ClickMouseUp(CHC_Line & L);

	/* */
	void getnearest(CHC_Line & L ,CHC_Vector3 & p);
	
	void setLevel(int Lv);
	void NextLevel();

	static void CHC_GameSystem::RefreshBackTrace();
private:
	bool win_flag;
	int map_w, map_h;					// map width, height
	int num_mirror[NUM_MIRROR_SORT], now_nm[NUM_MIRROR_SORT];				// number of mirror
	int num_sender, num_receiver;		// number of sender & receiver
	int SelectX, SelectY;
	int nowLevel;
};


#endif