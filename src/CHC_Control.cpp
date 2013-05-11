#include "CHC_Vector3.h"
#include "CHC_Camera.h"
#include "CHC_Constants.h"
#include "CHC_Line.h"
#include "CHC_GameSystem.h"
#include <vector>

#define GLUT_KEY_DELETE 127

bool keyStates[KEY_NUM];			// key buffering, true - key is pressed
bool keySpecialStates[KEY_NUM];		// Same for special keys 
bool mouseViewMode;					// mouseViewMode is true mean Camera is controled by mouse
int	 MouseState;
int  MouseLastX, MouseLastY;
int  ClickLeft_X, ClickLeft_Y;		// last Click Left Mouse(X, Y)
int	 MousePickMirror;
bool MouseLeftDown;

extern CHC_GameSystem GameSystem;
extern CHC_Camera camera3P;	// 3rd person camera in game.cpp
extern vector<CHC_Line> pick_L;
extern HWND	hWnd;

void CHC_GetCursorPos(int & x, int & y)
{
	static POINT lastMouse = {0,0};
	GetCursorPos(&lastMouse);
	ScreenToClient(hWnd, &lastMouse);
	x = lastMouse.x, y = lastMouse.y;
}

/* Mouse Click (x, y), return the line between Click Point & Camera Point */
void MakeLine(int x, int y, CHC_Line & LL)
{
		/* Get Camera */
	CHC_Vector3 pV = camera3P.m_pV;
	CHC_Vector3 P = camera3P.m_P;
	CHC_Vector3 U = camera3P.m_U;

	/* View Vector */
	CHC_Vector3 view = pV - P;
	view.normalize();

	/* Strafe Vector */
	CHC_Vector3 h_v = view.cross(U);
	h_v.normalize();

	/* Up Vector */
	CHC_Vector3 v_v = view.cross(h_v);
	v_v.normalize();

	float midX = glutGet(GLUT_WINDOW_WIDTH) >> 1; 
    float midY = glutGet(GLUT_WINDOW_HEIGHT) >> 1;
	float aspect = midX / midY;
	float rad = P_FOVY * pi / 180;
	float vL = tan(rad / 2) * P_NEAR;
	float hL = vL * aspect;

	v_v *= vL;
	h_v *= hL;

	float fx = x;
	fx -= midX;
	fx /= midX;
	float fy = y;
	fy -= midY;
	fy /= midY;

	CHC_Vector3 pos = P + view * P_NEAR + h_v * fx + v_v * fy;
	CHC_Vector3 vTemp = pos - camera3P.m_P;
	vTemp.normalize();

	vTemp *= 10.0;
	pos = camera3P.m_P + vTemp;
	
	LL = CHC_Line(camera3P.m_P, pos);
}

void MakeLine(int x, int y)
{
	CHC_Line LTemp;
	MakeLine(x, y, LTemp);
	pick_L.push_back(LTemp);
}

void KeyOperations()
{
	if (keyStates['w']) {
		camera3P.moveStraight(moveSensity);
	}
	if (keyStates['s']) {
		camera3P.moveStraight(-moveSensity);
	}
	if (keyStates['a']) {
		camera3P.strafe(-moveSensity);
	}
	if (keyStates['d']) {
		camera3P.strafe(moveSensity);
	}
	if (keySpecialStates[GLUT_KEY_LEFT]) {
		camera3P.yaw(RotateSensity);
	}
	if (keySpecialStates[GLUT_KEY_RIGHT]) {
		camera3P.yaw(-RotateSensity);
	}
	if (keySpecialStates[GLUT_KEY_UP]) {
		camera3P.pitch(RotateSensity);
	}
	if (keySpecialStates[GLUT_KEY_DOWN]) {
		camera3P.pitch(-RotateSensity);
	}
	if (keyStates['r']) {
		camera3P.worldUp(moveSensity);
	}
	if (keyStates['f']) {
		camera3P.worldUp(-moveSensity);
	}
	if (keySpecialStates[GLUT_KEY_F5]) {
		MouseState = 0;
		GameSystem.Restart();
		pick_L.clear();
	}
	if (keyStates[27]) {   // Exit the program when hit the Esc
		exit(0);		
	}
}

/* Key Pressed */
void keyPressed(unsigned char key, int x, int y) {
	keyStates[key] = true;
	if (key == GLUT_KEY_DELETE) {
		GameSystem.KeyBoardDelete();
	}
}

/* Key Up */
void keyUp(unsigned char key, int x, int y) {
	keyStates[key] = false;
	if (key == 'c') {
		GameSystem.KeyBoardChangeState(1);
	}
	if (key == 'x') {
		GameSystem.KeyBoardChangeState(-1);
	}
}

/* Key SpecialPressed */
void keySpecialPressed(int key, int x, int y) {
	if (key >= 0 && key <= 255)
		keySpecialStates[key] = true;
}

/* Key SpecialUp */
void keySpecialUp(int key, int x, int y) {
	if (key >= 0 && key <= 255)
		keySpecialStates[key] = false;
}

void Mouse(int button, int state, int x, int y) {
	if (button == GLUT_RIGHT_BUTTON) {
		if (state == GLUT_DOWN) {
			int midX = glutGet(GLUT_WINDOW_WIDTH) >> 1;
			int midY = glutGet(GLUT_WINDOW_HEIGHT) >> 1;
			glutWarpPointer(midX, midY);
			glutSetCursor(GLUT_CURSOR_NONE);
			mouseViewMode = true;
		} else if (state == GLUT_UP) {
			glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
			mouseViewMode = false;
		}
	}
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			ClickLeft_X = x, ClickLeft_Y = y;
			MakeLine(x, y);
			MouseLeftDown = true;
		} else 
		if (state == GLUT_UP) {
			MouseLeftDown = false;
			if (MousePickMirror >= 0) {
				int x, y;
				CHC_GetCursorPos(x, y);
				CHC_Line LTemp;
				MakeLine(x, y, LTemp);
				GameSystem.ClickMouseUp(LTemp);
			}
			MousePickMirror = -1;
		}
	}
}

void MouseMove(int x, int y)
{
	if (mouseViewMode) {
		camera3P.setViewByMouse(x, y, MouseSensity, MouseSensity);
	}
}
