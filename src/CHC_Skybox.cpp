#include "CHC_Skybox.h"

void CHC_Skybox::setSkyTexture() {
	BuildTexture_new(_skybox[0], "Reflection\\data\\ft.jpg");
	BuildTexture_new(_skybox[1], "Reflection\\data\\lf.jpg");
	BuildTexture_new(_skybox[2], "Reflection\\data\\bk.jpg");
	BuildTexture_new(_skybox[3], "Reflection\\data\\rt.jpg");
	BuildTexture_new(_skybox[4], "Reflection\\data\\up.jpg");
	BuildTexture_new(_skybox[5], "Reflection\\data\\dn.jpg");
}

void CHC_Skybox::loadSkybox(GLuint *_sky, int num)
{
	for (int i = 0; i != num; i++)
		_skybox[i] = _sky[i];
}

void CHC_Skybox::renderSkybox()
{
	glPushMatrix();
	glPushAttrib(GL_ENABLE_BIT);
	
	glEnable(GL_TEXTURE_2D);
	
	glDisable(GL_LIGHTING);
	
	glColor4f(1, 1, 1, 1);
	
	// Render the front quad
	glBindTexture(GL_TEXTURE_2D, _skybox[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);   
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(  SkyBoxSize, -SkyBoxSize, -SkyBoxSize );
        glTexCoord2f(1, 0); glVertex3f( -SkyBoxSize, -SkyBoxSize, -SkyBoxSize );
        glTexCoord2f(1, 1); glVertex3f( -SkyBoxSize,  SkyBoxSize, -SkyBoxSize );
        glTexCoord2f(0, 1); glVertex3f(  SkyBoxSize,  SkyBoxSize, -SkyBoxSize );
    glEnd();
 
    // Render the left quad
    glBindTexture(GL_TEXTURE_2D, _skybox[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(  SkyBoxSize, -SkyBoxSize,  SkyBoxSize );
        glTexCoord2f(1, 0); glVertex3f(  SkyBoxSize, -SkyBoxSize, -SkyBoxSize );
        glTexCoord2f(1, 1); glVertex3f(  SkyBoxSize,  SkyBoxSize, -SkyBoxSize );
        glTexCoord2f(0, 1); glVertex3f(  SkyBoxSize,  SkyBoxSize,  SkyBoxSize );
    glEnd();
 
    // Render the back quad
    glBindTexture(GL_TEXTURE_2D, _skybox[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f( -SkyBoxSize, -SkyBoxSize,  SkyBoxSize );
        glTexCoord2f(1, 0); glVertex3f(  SkyBoxSize, -SkyBoxSize,  SkyBoxSize );
        glTexCoord2f(1, 1); glVertex3f(  SkyBoxSize,  SkyBoxSize,  SkyBoxSize );
        glTexCoord2f(0, 1); glVertex3f( -SkyBoxSize,  SkyBoxSize,  SkyBoxSize );
 
    glEnd();
 
    // Render the right quad
    glBindTexture(GL_TEXTURE_2D, _skybox[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f( -SkyBoxSize, -SkyBoxSize, -SkyBoxSize );
        glTexCoord2f(1, 0); glVertex3f( -SkyBoxSize, -SkyBoxSize,  SkyBoxSize );
        glTexCoord2f(1, 1); glVertex3f( -SkyBoxSize,  SkyBoxSize,  SkyBoxSize );
        glTexCoord2f(0, 1); glVertex3f( -SkyBoxSize,  SkyBoxSize, -SkyBoxSize );
    glEnd();
 
    // Render the top quad
    glBindTexture(GL_TEXTURE_2D, _skybox[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex3f( -SkyBoxSize,  SkyBoxSize, -SkyBoxSize );
        glTexCoord2f(0, 0); glVertex3f( -SkyBoxSize,  SkyBoxSize,  SkyBoxSize );
        glTexCoord2f(1, 0); glVertex3f(  SkyBoxSize,  SkyBoxSize,  SkyBoxSize );
        glTexCoord2f(1, 1); glVertex3f(  SkyBoxSize,  SkyBoxSize, -SkyBoxSize );
    glEnd();
 
    // Render the bottom quad
    glBindTexture(GL_TEXTURE_2D, _skybox[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glBegin(GL_QUADS);
        glTexCoord2f(1, 0); glVertex3f( -SkyBoxSize, -SkyBoxSize, -SkyBoxSize );
        glTexCoord2f(0, 0); glVertex3f( -SkyBoxSize, -SkyBoxSize,  SkyBoxSize );
        glTexCoord2f(0, 1); glVertex3f(  SkyBoxSize, -SkyBoxSize,  SkyBoxSize );
        glTexCoord2f(1, 1); glVertex3f(  SkyBoxSize, -SkyBoxSize, -SkyBoxSize );
    glEnd();

	glEnable(GL_LIGHTING);
	glPopAttrib();
	glPopMatrix();
}