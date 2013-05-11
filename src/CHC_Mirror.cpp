#include "CHC_Mirror.h"
#include <vector>

CHC_ObjModel CHC_Mirror::Models(0.0008);
extern vector <GLuint> FileTextures;

CHC_Mirror::CHC_Mirror() {
	Position = Grid(0, 0);
	Normal = Dir2Normal(2);
	type = 1;
}

CHC_Mirror::CHC_Mirror(int x, int y, int dir, int _type = 1) {
	Position = Grid(x, y);
	Normal = Dir2Normal(dir);
	type = _type;
}

CHC_Mirror::CHC_Mirror(CHC_Vector3 _Position, int dir, int _type = 1) {
	Position = _Position;
	Normal = Dir2Normal(dir);
	type = _type;
}

void CHC_Mirror::Set_Position(int x, int y) {
	Position = Grid(x, y);
}

void CHC_Mirror::Set_Direction(int dir) {
	Normal = Dir2Normal(dir);
}

void CHC_Mirror::Set_Type(int _type) {
	type = _type;
}

void CHC_Mirror::Load() {
	//CHC_ObjModel mdl(0.001);
	//mdl.SetZoomDegree(0.001);
	Models.ImportObj("Reflection\\data\\Mirror\\Porada Dodekagono mirror.obj");
	
	//Models.clear();
	//Models.push_back(mdl);
}

void CHC_Mirror::Draw() {
	if (!Loaded) {
		Load();
		Loaded = true;
	}
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
	glTranslatef(Position[0], Position[1] + 0.5, Position[2]);
	glRotatef(Normal[1] * 360, 0, 1, 0);
	Models.Draw();
	glPopMatrix();
	glPopAttrib();
}