#ifndef CHC_MATERIAL_H
#define CHC_MATERIAL_H

#include <string>
#include "CHC_Texture.h"

using namespace std;

class CHC_Material {
public:
	string Name;
	float Ka[4], Kd[4], Ks[4];
	float illum, Ns;
	GLuint texture;
	CHC_Material(string _Name);
	~CHC_Material();
	void set();
};

#endif