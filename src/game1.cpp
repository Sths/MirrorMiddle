#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

#include "CHC_Vector3.h"
#include "CHC_Laser.h"
#include "CHC_Camera.h"
#include "CHC_Object.h"
#include "CHC_Mirror.h" 
#include "CHC_Texture.h"
#include "CHC_Constants.h"
#include "CHC_All.h"
#include <vector>

bool keyStates[256];		// key buffering, true - key is pressed
bool keySpecialStates[256]; // Same for special keys 

CHC_Camera camera3P;	// 3rd person camera
bool mouseViewMode;
GLuint floor_texture[20];
//vector<CHC_Mirror> CHC_mi;
CHC_all all;

//positions of the cubes
const int maxnCube = 20;
struct gCube
{
	float x, y, z;
} Cp[maxnCube];

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
	if (keyStates[27]) {   // Exit the program when hit the Esc
		exit(0);		
	}
}

CHC_Laser a(1, 1, 2, 2, 0x777700, 0.05), b(3, 3, 7, 2, 0x007777, 0.05);

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	KeyOperations();

	glLoadIdentity(); 
	
	camera3P.setLook();
	
	/*
	for (int i = 0; i != maxnCube; i++) {
		glPushMatrix();
		glTranslated(-Cp[i].x, 1, -Cp[i].z);
		glutSolidCube(2);
		glPopMatrix();
	}
	*/
	
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);

	glColor4f(1, 1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, floor_texture[3]);
	
	for (int i = 0; i < 17; i++)
		for (int j = 0; j < 17; j++) {
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f((i - 0.5) * Gridx, 0, (j - 0.5) * Gridy);
				glTexCoord2f(0.0f, 1.0f); glVertex3f((i - 0.5) * Gridx, 0, (j + 0.5) * Gridy);
				glTexCoord2f(1.0f, 1.0f); glVertex3f((i + 0.5) * Gridx, 0, (j + 0.5) * Gridy);
				glTexCoord2f(1.0f, 0.0f); glVertex3f((i + 0.5) * Gridx, 0, (j - 0.5) * Gridy);
			glEnd();
			glPopMatrix();
		}
	// all.print();
	
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	a.Draw(); b.Draw();
	glDepthMask(GL_TRUE);
	CHC_Mirror Mirror(3, 3, 7);
	Mirror.Draw();
	glutSwapBuffers(); 
}

// Sets timer for refresh the display
void Timer(int extra)
{
    glutPostRedisplay();
    glutTimerFunc(30,Timer,0);
}

void keyPressed(unsigned char key, int x, int y) {
	keyStates[key] = true;
}

void keyUp(unsigned char key, int x, int y) {
	keyStates[key] = false;
}

void keySpecialPressed(int key, int x, int y) {
	if (key >= 0 && key <= 255)
		keySpecialStates[key] = true;
}

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
}

void MouseMove(int x, int y)
{
	if (mouseViewMode) {
		camera3P.setViewByMouse(x, y, MouseSensity, MouseSensity);
	}
}

void Reshape(GLsizei w,GLsizei h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (h == 0) h = 1;
	gluPerspective(45.0f, (GLfloat)w/(GLfloat)h, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

void RegisterCallbacks()
{
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutSpecialFunc(keySpecialPressed);
	glutSpecialUpFunc(keySpecialUp);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutMouseFunc(Mouse);
    glutMotionFunc(MouseMove);
	glutTimerFunc(0,Timer,0);
}

void Init_Logic()
{
	memset(keyStates, 0, sizeof(keyStates));
	memset(keySpecialStates, 0, sizeof(keySpecialStates));
	/*
	for (int i = 0; i != maxnCube; i++) {
		Cp[i].x = rand() % 5 + 5;
		Cp[i].y = 0;
		Cp[i].z = rand() % 5 + 5;
	}
	*/
	all.load();
}

void Init_GLUT(int argc, char** argv)
{
	glutInit(&argc, argv);		// Opnegl initial
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);		// set displaymode
	glutInitWindowSize(Window_W, Window_H);				//窗口大小
    glutInitWindowPosition(100, 100);					//窗口位置
    glutCreateWindow("Hello World");					//创建一个标题为hello的窗口
}

void Init_GL() 
{
	camera3P.set(-3, 12, -3, 9, 0, 9, 0, 1, 0);			//LoadGLTextures(texture, "face.bmp");
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glEnable(GL_LIGHT0);								// Quick And Dirty Lighting (Assumes Light0 Is Set Up)
	//glEnable(GL_LIGHTING);								// Enable Lighting
	glEnable(GL_COLOR_MATERIAL);						// Enable Material Coloring
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
		
	LoadGLTextures(floor_texture[0], "Reflection\\data\\ch.bmp");
	LoadGLTextures(floor_texture[1], "Reflection\\data\\floor.bmp");
	LoadGLTextures(floor_texture[2], "Reflection\\data\\ch.bmp");
	LoadGLTextures(floor_texture[3], "Reflection\\data\\woodfloor.bmp");
}

int main(int argc, char** argv)
{
	Init_Logic();
	Init_GLUT(argc, argv);
	Init_GL();					// initial openGL option
	RegisterCallbacks();		// register Call Back
	glutMainLoop();				// Main Loop
	return 0;
}