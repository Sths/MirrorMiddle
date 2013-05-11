#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#include "CHC_Vector3.h"
#include "CHC_Camera.h"
#include "CHC_Object.h"
#include "CHC_Mirror.h" 
#include "CHC_Constants.h"
#include "CHC_Skybox.h"
#include "CHC_Texture.h"
#include "CHC_Line.h"
#include "CHC_GameSystem.h"
#include "CHC_Laser.h"
#include <vector>

GLfloat LightGlobalAmbient[] = {0.3,0.3,0.3,1.0};

GLfloat Light0Ambient[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat Light0Diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat Light0Specular[] = { 0.8f, 0.8f, 0.8f, 1.0f};
GLfloat Light0Position[] = { 4.0f, 1.0f, 4.0f, 0.3f };

/*
GLfloat Light1Ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat Light1Diffuse[]  = { 0.2f, 0.8f, 0.1f, 1.0f };
GLfloat Light1Specular[] = { 0.0f, 0.5f, 0.0f, 1.0f};
GLfloat Light1Position[] = { 5.0f, 15.0f, 5.0f, 1.0f };
GLfloat Light1Direction[] = { 1.0f, -1.0f, 1.0f};
*/
HWND		hWnd = NULL;		
CHC_GameSystem GameSystem;		//Game System
CHC_Camera camera3P;			// 3rd person camera
CHC_Skybox SkyBox;

/* Texture */
GLuint floor_texture[10];
vector<GLuint> FileTextures;
GLuint WhiteTexture;
GLuint BlackTexture;

CHC_Mirror	DrawMirror;
CHC_Laser	DrawLaser;

extern void MakeLine(int x, int y, CHC_Line & LL);
extern void MakeLine(int x, int y);
extern void KeyOperations();
extern void keySpecialPressed(int, int, int);
extern void keySpecialUp(int, int, int);
extern void keyPressed(unsigned char, int, int);
extern void keyUp(unsigned char, int, int);
extern void Mouse(int, int, int, int);
extern void MouseMove(int, int);
extern void CHC_GetCursorPos(int & x, int & y);

extern bool keySpecialStates[KEY_NUM];
extern bool keyStates[KEY_NUM];
extern int	MouseState;
extern int	MouseLastX;
extern int  MouseLastY;
extern int  MousePickMirror;
extern int  PickMirrorState;

//positions of the cubes
const int maxnCube = 20;
struct gCube
{
	float x, y, z;
} Cp[maxnCube];

vector <CHC_Line> pick_L, PP;
CHC_Line	MouseIn;

/* Object */
vector <CHC_Laser>	Lasers;
vector <CHC_Mirror>	Mirrors;

void DrawVirtualMirror()
{
	if (MousePickMirror >= 0) {
		int lm_x, lm_y;
		CHC_GetCursorPos(lm_x, lm_y);
		MakeLine(lm_x, lm_y, MouseIn);
		CHC_Vector3 P;
		if (MouseIn.istYequal0(P)) {
			int x = floor(P[0] + MOUSEBIAS), y = floor(P[2] + MOUSEBIAS);
			if (PickMirrorState < 8) {
				if (GameSystem.InMap(x, y)) {
					DrawMirror.Set_Direction(PickMirrorState);
					DrawMirror.Set_Position(x, y);
					DrawMirror.Draw();
				}
				if (!GameSystem.InMap(x, y)) {
					DrawMirror.Set_Direction(PickMirrorState);
					DrawMirror.Set_Position(P[0] + MOUSEBIAS, P[2] + MOUSEBIAS);
					DrawMirror.Draw();
				}
			}
		}
	}
}

void DealClick()
{
	unsigned int num_L = pick_L.size();
	for (unsigned int i = 0; i != num_L; i++) {
		GameSystem.ClickMouse(pick_L[i]);
		PP.push_back(pick_L[i]);
	}
	if (num_L > 0) pick_L.clear();
}

void DrawLine()
{
	unsigned int num_L = PP.size();
	CHC_Vector3 P;
	for (unsigned int i = 0; i != num_L; i++) {
		if ( PP[i].istYequal0(P) ) {
			glPushMatrix();
				glTranslated(P[0], 0.025, P[2]);
				glColor3f(0.0, 0.0, 1.0);
				glutSolidCube(0.05);
			glPopMatrix();
		}
	}
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
	
	KeyOperations();
	
	if (GameSystem.Win()) {
		if (MessageBox(NULL, "Congratulations! Let us go to next level!", "You Win", MB_OKCANCEL) == IDOK) {
			GameSystem.NextLevel();
		} else {
			GameSystem.Restart();
			return;
		}
	}
	glLoadIdentity();

	camera3P.setLook();
	
	SkyBox.renderSkybox();

	/* Draw Board */
	glColor4f(1, 1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, floor_texture[1]);
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

	/* Draw Mirror toolbar */
	glColor4f(1, 1, 1, 0.2);
	glBindTexture(GL_TEXTURE_2D, floor_texture[1]);
	for (int i = MIRROR_TOOLBAR_X; i - MIRROR_TOOLBAR_X < MIRROR_TOOLBAR_LEN_X; i++) {
		for (int j = MIRROR_TOOLBAR_Y; j - MIRROR_TOOLBAR_Y < MIRROR_TOOLBAR_LEN_Y; j++) {
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f((i - 0.5) * Gridx, 0, (j - 0.5) * Gridy);
				glTexCoord2f(0.0f, 1.0f); glVertex3f((i - 0.5) * Gridx, 0, (j + 0.5) * Gridy);
				glTexCoord2f(1.0f, 1.0f); glVertex3f((i + 0.5) * Gridx, 0, (j + 0.5) * Gridy);
				glTexCoord2f(1.0f, 0.0f); glVertex3f((i + 0.5) * Gridx, 0, (j - 0.5) * Gridy);
			glEnd();
			glPopMatrix();
		}
	}


	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
		DealClick();
		GameSystem.Refresh();
		DrawVirtualMirror();
	glPopAttrib();
	glPopMatrix();

	/*
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_AMBIENT, Light0Ambient);            // Setup The Ambient Light
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Light0Diffuse);            // Setup The Diffuse Light
    glLightfv(GL_LIGHT0, GL_SPECULAR,Light0Specular);       // Setup The Specular Light
    glLightfv(GL_LIGHT0, GL_POSITION,Light0Position);   // Position The Light
    glEnable(GL_LIGHT0); 
	
    glLightfv(GL_LIGHT1, GL_AMBIENT, Light1Ambient);            // Setup The Ambient Light
    glLightfv(GL_LIGHT1, GL_DIFFUSE, Light1Diffuse);            // Setup The Diffuse Light
    glLightfv(GL_LIGHT1, GL_SPECULAR,Light1Specular);       // Setup The Specular Light
    glLightfv(GL_LIGHT1, GL_POSITION,Light1Position);   // Position The Light
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION,Light1Direction);    // Direction The Light
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF,10.0);
    glLighti(GL_LIGHT1, GL_SPOT_EXPONENT,64);
    glEnable(GL_LIGHT1);
	*/
	glutSwapBuffers(); 
}

// Sets timer for refresh the display
void Timer(int extra)
{
    glutPostRedisplay();
    glutTimerFunc(30,Timer,0);
}


void Reshape(GLsizei w,GLsizei h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (h == 0) h = 1;
	gluPerspective(P_FOVY, (GLfloat)w/(GLfloat)h, P_NEAR, P_FAR);
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
	for (int i = 0; i != maxnCube; i++) {
		Cp[i].x = rand() % 2 + 1;
		Cp[i].y = 0;
		Cp[i].z = rand() % 2 + 1;
	}
	Lasers.push_back(CHC_Laser(1, 1, 2, 2, 0x777700, 0.05));
	Lasers.push_back(CHC_Laser(3, 3, 7, 3, 0x007777, 0.05));
	Mirrors.push_back(CHC_Mirror(3, 3, 7));
	Mirrors.push_back(CHC_Mirror(2, 2, 1));
	Mirrors.push_back(CHC_Mirror(1, 1, 2));
	pick_L.clear();

	MousePickMirror = -1;
	MouseState = 0;
	GameSystem.setLevel(0);
}

void Init_GLUT(int argc, char** argv)
{
	glutInit(&argc, argv);		// Opnegl initial
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);		// set displaymode
	glutInitWindowSize(Window_W, Window_H);				//窗口大小
    glutInitWindowPosition(100, 100);					//窗口位置
    glutCreateWindow(GameWindowName);					//创建一个标题为hello的窗口
	hWnd = FindWindow(NULL,GameWindowName);
}

void Init_GL() 
{
	camera3P.set(-3, 12, -3, 9, 0, 9, 0, 1, 0);			//LoadGLTextures(texture, "face.bmp");
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);				// Black Background
	glClearDepth(1.0f);     							// Depth Buffer Setup

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	//glEnable(GL_LIGHTING);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	
	/*
	GLfloat LightAmbient[]= { 1.0f, 1.0f, 1.0f, 1.0f }; 
	GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lightPosition[] = {1.0f, 1.0f, 0.5f, 1.0f};
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);	
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);	
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	*/
	glEnable(GL_COLOR_MATERIAL);						// Enable Material Coloring
	
	LoadGLTextures(floor_texture[0], "Reflection\\data\\face.bmp");
	LoadGLTextures(floor_texture[1], "Reflection\\data\\ground.bmp"); 
	LoadGLTextures(WhiteTexture, "Reflection\\data\\WhiteT.bmp");
	LoadGLTextures(BlackTexture, "Reflection\\data\\BlackT.bmp");
	//LoadGLTextures(floor_texture[1], "Reflection\\data\\ABC.bmp");
	SkyBox.setSkyTexture();
	
	ifstream Fin("Reflection\\data\\LoadList.txt");
	int n;
	Fin >> n;
	cout << n << endl;
	//while (1) {}
	FileTextures.clear();
	for (int i = 0; i < n; i++) {
		GLuint j;
		string str;
		Fin >> str;
		LoadGLTextures(j, str.c_str());
		//cout << "Successfully Load " << str << endl;
		FileTextures.push_back(j);
	}
	//cout << FileTextures.size() << endl;

	gluPerspective(P_FOVY, (GLfloat)Window_W/(GLfloat)Window_H, P_NEAR, P_FAR);
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