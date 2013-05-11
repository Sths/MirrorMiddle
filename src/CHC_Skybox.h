#ifndef CHC_SKYBOX_H
#define CHC_SKYBOX_H

#include <Windows.h>
#include <glut.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <glaux.h>
#include "CHC_Texture.h"

#define SkyBoxSize 30.0

class CHC_Skybox
{
public:
	void loadSkybox(GLuint *_sky, int num);
	void renderSkybox();
	void setSkyTexture();
private:
	GLuint _skybox[6];
};

#endif