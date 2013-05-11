#ifndef CHC_OBJECT_H
#define CHC_OBJECT_H

#include <Windows.h>
#include <glut.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <glaux.h>
#include <iostream> 
#include <fstream>
#include <string>

#include "CHC_Constants.h"
#include "CHC_Vector3.h"
#include "CHC_ObjModel.h"

using namespace std;

class CHC_Object {
protected:
	static bool Loaded; // 是否已经加载输入并生成了显示列表
	static GLuint ViewList;
	static int TextureIndex;
	CHC_Vector3 Position, Normal;
	string ModelPath;
	//CHC_ObjModel ObjModel;
public:
	void Load();
	void Draw();
	void Draw(int x, int y, int dir);
	CHC_Object() {}
	CHC_Object(CHC_Vector3 _postion, CHC_Vector3 _normail, string _ModelPath);
};


#endif