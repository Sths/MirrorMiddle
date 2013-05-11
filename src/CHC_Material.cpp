#include "CHC_Material.h"

CHC_Material::CHC_Material(string _Name)
{
	Name = _Name;
	Ka[0] = Ka[1] = Ka[2] = 0.2;
	Kd[0] = Kd[1] = Kd[2] = 0.8;
	Ks[0] = Ks[1] = Ks[3] = 1.0;
	illum = 0;
	Ns = 0;
	texture = 0;
}

void CHC_Material::set()
{
	glColor3d(1, 1, 1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Ka);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Kd);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Ks);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, Ns);	
	if (texture != 0) {		
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);		
	}else {
		glDisable(GL_TEXTURE_2D);
	}
}

CHC_Material::~CHC_Material()
{
//	if (texture != 0)
//		glDeleteTextures(1, &texture);
}		