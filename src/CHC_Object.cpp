#include "CHC_Object.h"

bool CHC_Object::Loaded = false;
GLuint CHC_Object::ViewList = 0;
int CHC_Object::TextureIndex = 0;

CHC_Object::CHC_Object(CHC_Vector3 _Position, CHC_Vector3 _Normal, string _ModelPath) {
	Position = _Position;
	Normal = _Normal;
	ModelPath = _ModelPath;
}
 
void CHC_Object::Load() {
	ifstream Fin(ModelPath);
	CHC_Object::ViewList = glGenLists(1);
	glNewList(ViewList, GL_COMPILE);
		glBegin(GL_TRIANGLES);
			int n3;
			Fin >> n3;
			while (n3 --) {
				float x, y, z;
				for (int i = 0; i < 3; i++) {
					Fin >> x >> y >> z;
					glVertex3f(x, y, z);
				}
			}
		glEnd();
		glBegin(GL_QUADS);
			int n4;
			Fin >> n4;
			while (n4 --) {
				float x, y, z;
				for (int i = 0; i < 4; i++) {
					Fin >> x >> y >> z;
					glVertex3f(x, y, z);
				}
			}
		glEnd();
	glEndList();
}

void CHC_Object::Draw() {
	if (!Loaded) {
		Load(); 
		Loaded = true;
	}
	glPushMatrix();
	glTranslatef(Position[0], Position[1], Position[2]);
	glCallList(ViewList);
	glPopMatrix();
}

void CHC_Object::Draw(int x, int y, int dir) {
	if (!Loaded) {
		Load(); 
		Loaded = true;
	}
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(Grid(x, y)[0], 0, Grid(x, y)[2]);
	glCallList(ViewList);
	glPopMatrix();
}

