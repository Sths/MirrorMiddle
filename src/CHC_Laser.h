#ifndef CHC_LASER_H
#define CHC_LASER_H

#include <Windows.h>
#include "glut.h"
#include "CHC_Vector3.h"
#include "CHC_Constants.h"
#include "CHC_Texture.h"
#include <vector>
#include <iostream>
using namespace std;

#define DefaultRadius 0.2

class CHC_Laser {
public:
	static int Loaded;
	static GLuint texture;
	CHC_Vector3 s, t;
	CHC_Vector3 color;
	GLfloat radius;
	GLfloat timer;
	vector<GLfloat> Points;
	CHC_Laser() {};
	CHC_Laser(int x0, int y0, int x1, int y1, int _color, GLfloat _radius);
	void set(int x0, int y0, int x1, int y1, int _color);
	void Draw();
};

#endif