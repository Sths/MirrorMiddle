#ifndef CHC_CONSTANTS_H
#define CHC_CONSTANTS_H

#include <string>
using namespace std;

const double pi = 3.1415926;

#define KEY_NUM 256

#define MOUSE_OTHER_STATE	255

#define moveSensity 0.20		// 移动单位距离
#define RotateSensity 0.03		// 旋转单位角度
#define MouseSensity 500		// 鼠标密度，越大越慢

#define P_FOVY 45.0				// Perspective fory
#define P_NEAR 0.1
#define P_FAR  200.0

const string MirrorModelPath = "Reflection\\data\\Mirror.inf";
const string FloorModelPath = "Reflection\\data\\Floor.inf";
const string iFilename = "Reflection\\data\\init.inf";

#define Window_W 800			// Windows Width
#define Window_H 600			// Windows Height

const int Gridx = 1;
const int Gridy = 1;
const int Gridz = 1;

#define Grid(x, y) CHC_Vector3(Gridx * (x), 0, Gridy * (y))
#define Dir2Normal(dir) CHC_Vector3(0, (dir + 4) % 8 / 8.0, 0);
#define Color2Vector(color) CHC_Vector3((color >> 16) / 256.0, ((_color & 0xFF00) >> 8) / 256.0, (_color & 0xFF) / 256.0)
#define SEP(T) (T)[0], (T)[1], (T)[2]

/* Game System */
#define MAP_SIZE_WIDTH 17
#define MAP_SIZE_HEIGHT 17

#define MIRROR_TOOLBAR_X -2
#define MIRROR_TOOLBAR_Y 5
#define MIRROR_TOOLBAR_LEN_X 1
#define MIRROR_TOOLBAR_LEN_Y 5
#define START_MIRROR_STATE 2
#define NUM_MIRROR_STATE 8

static char GameWindowName[] = "Reflection";
#define MOUSEBIAS	0.5f

#endif CHC_CONSTANTS_H