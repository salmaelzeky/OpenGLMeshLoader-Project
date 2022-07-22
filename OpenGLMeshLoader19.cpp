#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"
#include <glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include<windows.h>  
#include <mmsystem.h>
#include <sstream>

#include <iostream>
#include <string.h>




float charx = 0;
float chary = 0;
float charz = 0;

int WIDTH = 1280;
int HEIGHT = 720;
int w;
double keyX = 2;
double keyY = 2;
double keyZ = -15;

int timerlevel2 = 0;



double goalkeeperX = 0;
double goalKeeperX2 = 4;


int ballMoveX = 0;
double ballMoveZ = -18;

double movepoohx = 0;
double movepoohy = 0;
double movepoohz = 0;

double movebeex = 0;
double movebeey = 0;
double movebeez = 0;

double movejarx = 0;
double movejary = 0;
double movejarz = 0;

double movebombx = 0;

double movebombz = 0;


bool collisionjarwithgoal = false;
bool collisionjarwithbee = false;
bool collisionjarwithpooh = false;

bool collisionbombwithpooh = false;
bool collisionbombwithbee = false;
bool move = false;
bool move2 = false;
GLuint tex;
int score = 0;
int scoregoal = 0;
int endgame = 0;

int scorepooh = 0;
int scorebee = 0;

char title[] = "3D Model Loader Sample";

// 3D Projection Options
GLdouble fovy = 60.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zFar = 100;

class Vector
{
public:
	GLdouble x, y, z;
	Vector() {}
	Vector(GLdouble _x, GLdouble _y, GLdouble _z) : x(_x), y(_y), z(_z) {}
	void operator +=(float value)
	{
		x += value;
		y += value;
		z += value;
	}
};

Vector Eye(0,10, 25);
Vector At(0, 0, 0);
Vector Up(0, 1, 0);

int cameraZoom = 10;

// Model Variables
Model_3DS model_house;
Model_3DS model_tree;
Model_3DS model_flowers;
Model_3DS model_player;
Model_3DS model_gate;
Model_3DS model_ball;
Model_3DS model_goalkeeper;
Model_3DS model_stadium;
Model_3DS model_policeBox;
Model_3DS model_ref;

// Textures
GLTexture tex_ground;
GLTexture tex_fence;
GLTexture tex_lane;


//=======================================================================
// Lighting Configuration Function
//=======================================================================
void InitLightSource()
{
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT0);



	GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };

	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);


	GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };
	GLfloat lightPosition[] = { 0.6f, 0.0f, 1.5f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightIntensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);}

//=======================================================================
// Material Configuration Function
//======================================================================
void InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);
	GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 50.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

//=======================================================================
// OpengGL Configuration Function
//=======================================================================
void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);
	//*******************************************************************************************//
	// fovy:			Angle between the bottom and top of the projectors, in degrees.			 //
	// aspectRatio:		Ratio of width to height of the clipping plane.							 //
	// zNear and zFar:	Specify the front and back clipping planes distances from camera.		 //
	//*******************************************************************************************//

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
	//*******************************************************************************************//
	// EYE (ex, ey, ez): defines the location of the camera.									 //
	// AT (ax, ay, az):	 denotes the direction where the camera is aiming at.					 //
	// UP (ux, uy, uz):  denotes the upward orientation of the camera.							 //
	//*******************************************************************************************//

	InitLightSource();

	InitMaterial();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
}



void print(int x, int y, char* string)
{
	int len, i;
	//glRasterPos2f(95, 783);
	//glRasterPos2f(x, y);
	glRasterPos2f(640, 360);

	//int WIDTH = 1280;
	//int HEIGHT = 720;

	len = (int)strlen(string);

	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
	}
}

//=======================================================================
// Render Ground Function
//=======================================================================

void drawCircle(float x, float y, float z, float r) {
	glPushMatrix();
	glTranslatef(x, y, z);
	GLUquadric* quadObj = gluNewQuadric();
	gluDisk(quadObj, 0, r, 50, 50);
	glPopMatrix();
}

void drawBee() {

	glPushMatrix();
	glScaled(10, 10, 10);
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(charx + 0.98, chary + 0.475, charz + 0.85);
	glRotated(90.0, 1, 0, 0);
	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	gluCylinder(qobj, 0.005, 0.005, 0.1, 80, 80);
	glPopMatrix();



	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(charx + 1.015, chary + 0.475, charz + 0.85);
	glRotated(90.0, 1, 0, 0);
	GLUquadricObj* qobj1;
	qobj1 = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	gluCylinder(qobj1, 0.005, 0.005, 0.1, 80, 80);
	glPopMatrix();



	glColor3f(0, 0, 0);  //eye1
	drawCircle(charx + 0.975, chary + 0.32, charz + 0.9, 0.015);

	glColor3f(0, 0, 0);  //eye1
	drawCircle(charx + 1.009, chary + 0.32, charz + 0.9, 0.015);

	glPushMatrix();   //spheredown
	glColor3f(1, 1, 0);
	glTranslated(charx + 1, chary + 0.32, charz + 0.8);
	glutSolidSphere(0.06, 15, 15);
	glPopMatrix();

	glPushMatrix();   //spheredown
	glColor3f(0, 0, 0);
	glTranslated(charx + 1, chary + 0.25, charz + 0.8);
	glutSolidSphere(0.07, 15, 15);
	glPopMatrix();

	glPushMatrix();   //spheredown
	glColor3f(1, 1, 0);
	glTranslated(charx + 1, chary + 0.2, charz + 0.8);
	glutSolidSphere(0.07, 15, 15);
	glPopMatrix();

	glPushMatrix();   //spheredown
	glColor3f(0, 0, 0);
	glTranslated(charx + 1, chary + 0.15, charz + 0.8);
	glutSolidSphere(0.06, 15, 15);
	glPopMatrix();

	glPushMatrix();   //spheredown
	glColor3f(0.6, 0.9, 1);
	glTranslated(charx + 0.95, chary + 0.31, charz + 0.8);
	glutSolidSphere(0.045, 15, 15);
	glPopMatrix();

	glPushMatrix();   //spheredown
	glColor3f(0.6, 0.9, 1);
	glTranslated(charx + 1.05, chary + 0.31, charz + 0.8);
	glutSolidSphere(0.045, 15, 15);
	glPopMatrix();

	glPopMatrix();


}


void drawPooh() {


	glPushMatrix();
	glScalef(10, 10, 10);
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(charx + 0.21, chary + 0.575, charz + 1);
	glVertex3f(charx + 0.24, chary + 0.585, charz + 1);
	glVertex3f(charx + 0.235, chary + 0.59, charz + 1);
	glVertex3f(charx + 0.215, chary + 0.58, charz + 1);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(charx + 0.29, chary + 0.585, charz + 1);
	glVertex3f(charx + 0.32, chary + 0.575, charz + 1);
	glVertex3f(charx + 0.325, chary + 0.58, charz + 1);
	glVertex3f(charx + 0.295, chary + 0.59, charz + 1);
	glEnd();

	glColor3f(0, 0, 0);  //mana5eer
	drawCircle(charx + 0.26, chary + 0.45, charz + 1, 0.02);

	glColor3f(0, 0, 0);  //eye1
	drawCircle(charx + 0.3, chary + 0.52, charz + 1, 0.015);

	glColor3f(0, 0, 0);  //eye2
	drawCircle(charx + 0.22, chary + 0.52, charz + 1, 0.015);


	glPushMatrix();     //ear 2
	glColor3f(1, 0.7, 0.2);
	glTranslated(charx + 0.3, chary + 0.65, charz + 0.9);
	glutSolidSphere(0.05, 15, 15);
	glPopMatrix();


	glPushMatrix();     //ear 1
	glColor3f(1, 0.7, 0.2);
	glTranslated(charx + 0.19, chary + 0.65, charz + 0.9);
	glutSolidSphere(0.05, 15, 15);
	glPopMatrix();


	glPushMatrix();     //sphereup
	glColor3f(1, 0.7, 0.2);
	glTranslated(charx + 0.22, chary + 0.55, charz + 0.83);
	glutSolidSphere(0.11, 15, 15);
	glPopMatrix();


	glPushMatrix();   //spheredown
	glColor3f(1, 0.7, 0.2);
	glTranslated(charx + 0.22, chary + 0.445, charz + 0.83);
	glutSolidSphere(0.125, 15, 15);
	glPopMatrix();


	glPushMatrix();
	glColor3f(1, 0.7, 0.2);
	glTranslated(charx + 0.17, chary, charz + 0.82);// cylinder at (0,0,1)
	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	glRotated(-90, 1, 0, 0);
	gluCylinder(qobj, 0.025, 0.01, 0.2, 80, 80);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0.7, 0.2);
	glTranslated(charx + 0.23, chary, charz + 0.82);// cylinder at (0,0,1)
	GLUquadricObj* qobjx;
	qobjx = gluNewQuadric();
	gluQuadricDrawStyle(qobjx, GLU_LINE);
	glRotated(-90, 1, 0, 0);
	gluCylinder(qobjx, 0.025, 0.01, 0.2, 80, 80);
	glPopMatrix();


	glPushMatrix();    //red box up
	glColor3f(1, 0, 0);
	glTranslated(charx + 0.22, chary + 0.37, charz + 0.83);
	glScaled(1.48, 0.4, 1);
	glutSolidCube(0.18);
	glPopMatrix();

	glPushMatrix();    //red box down
	glColor3f(1, 0, 0);
	glTranslated(charx + 0.22, chary + 0.275, charz + 0.83);
	glutSolidCube(0.18);
	glPopMatrix();

	glPushMatrix();    //yellow box left
	glColor3f(1, 0.7, 0.2);
	glTranslated(charx + 0.11, chary + 0.275, charz + 0.83);
	glScaled(0.25, 1, 1);
	glutSolidCube(0.18);
	glPopMatrix();

	glPushMatrix();    //yellow box riggt
	glColor3f(1, 0.7, 0.2);
	glTranslated(charx + 0.33, chary + 0.275, charz + 0.83);
	glScaled(0.25, 1, 1);
	glutSolidCube(0.18);
	glPopMatrix();


	glPushMatrix();
	glColor3f(1, 0.7, 0.2);
	glTranslated(charx + 0.2, chary + 0.2, charz + 0.80);
	glutSolidSphere(0.12, 15, 15);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

}

void drawhoneyjar() {
	glPushMatrix();
	glScaled(10, 10, 10);
	glPushMatrix();
	glColor3f(1, 0.7, 0);
	glTranslated(charx + 1.5, chary + 0.2, charz + 0.85);
	glRotated(90.0, 1, 0, 0);
	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	gluCylinder(qobj, 0.05, 0.05, 0.2, 80, 80);
	glPopMatrix();


	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(charx + 1.5, chary + 0.25, charz + 0.85);
	glRotated(90.0, 1, 0, 0);
	GLUquadricObj* qobj1;
	qobj1 = gluNewQuadric();
	gluQuadricDrawStyle(qobj1, GLU_LINE);
	gluCylinder(qobj1, 0.05, 0.05, 0.05, 80, 80);
	glPopMatrix();glPopMatrix();
}


void drawbomb() {
	glPushMatrix();
	glScaled(5, 5, 5);
	glColor3f(1, 0, 0);
	glTranslated(charx + 0, chary + 0.2, charz + 0.8);
	glutSolidSphere(0.12, 15, 15);
	glPopMatrix();
}

void RenderGround()
{
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-30, 0, -30);
	glTexCoord2f(5, 0);
	glVertex3f(30, 0, -30);
	glTexCoord2f(5, 5);
	glVertex3f(30, 0, 30);
	glTexCoord2f(0, 5);
	glVertex3f(-30, 0, 30);
	glEnd();
	glPopMatrix();



	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.


}




void renderLane() {

	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_lane.texture[0]);	// Bind the ground texture

	glPushMatrix();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-30, 0, 30);
	glTexCoord2f(5, 0);
	glVertex3f(30, 0, 30);
	glTexCoord2f(5, 5);
	glVertex3f(30, 0, 20);
	glTexCoord2f(0, 5);
	glVertex3f(-30, 0, 20);
	glEnd();
	glPopMatrix();



	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);


}




void RenderFence()
{
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_fence.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-20, 5, -20);
	glTexCoord2f(1, 0);
	glVertex3f(20, 5, -20);
	glTexCoord2f(1, 1);
	glVertex3f(20, 0, -20);
	glTexCoord2f(0, 1);
	glVertex3f(-20, 0, -20);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glTranslated(-20, -15, 0);
	glRotated(90, 0, 0, 1);
	
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(20, 0, -20);
	glTexCoord2f(1, 0);
	glVertex3f(20, 0, 20);
	glTexCoord2f(1, 1);
	glVertex3f(15, 0, 20);
	glTexCoord2f(0, 1);
	glVertex3f(15, 0, -20);
	glEnd();
	
	glPopMatrix();


	glPushMatrix();
	glTranslated(20, -15, 0);
	glRotated(90, 0, 0, 1);

	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(20, 0, -20);
	glTexCoord2f(1, 0);
	glVertex3f(20, 0, 20);
	glTexCoord2f(1, 1);
	glVertex3f(15, 0, 20);
	glTexCoord2f(0, 1);
	glVertex3f(15, 0, -20);
	glEnd();

	glPopMatrix();


	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.








}



void drawFence(double thickness) {

	glPushMatrix();
	//glColor3f(backGreen, backRed, backBlue);
	glTranslated(0.5, 0.5 * thickness, 0.5);
	glScaled(1.0, thickness, 1.0);
	glutSolidCube(1);
	glPopMatrix();


}
void drawFences() {
	//Fence 1
	glPushMatrix();
	glTranslated(20,0,-20);
	glRotated(90, 0, 0, 1.0);
	glScaled(5, 25, 40);
	drawFence(0.02);
	glPopMatrix();

	//Fence 2
	glPushMatrix();
	glTranslated(-20, 0, -20);
	glRotated(90, 0, 0, 1.0);
	glScaled(5, 25, 40);
	drawFence(0.02);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-20, 0, -20);
	glRotated(-90, 1.0, 0.0, 0.0);
	glScaled(40, 25, 5);
	drawFence(0.02);
	glPopMatrix();

}


void Soccer_Field()
{
	float x, y, ang, radius = 0.05;     // Not sure what the radius of the center circle should be?

	static float RAD_DEG = 57.296;

	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 1.0);
	
	glVertex3f(-15,0.2, -10); glVertex3f(15,0.2, -10);  // Inner White Quad - Right
	
	glVertex3f(5, 0.2, -10); glVertex3f(5, 0.2, -2);
	glVertex3f(-5, 0.2, -10); glVertex3f(-5, 0.2, -2);
	glVertex3f(-5, 0.2, -2); glVertex3f(5, 0.2, -2);

	glVertex3f(-15, 0.2, 10); glVertex3f(15, 0.2, 10); // center

	glVertex3f(15, 0.2, -10); glVertex3f(15, 0.2, 20);

	glVertex3f(-15, 0.2, -10); glVertex3f(-15, 0.2, 20);




	glEnd();
}

void drawLane() {

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex3f(-30, 0, 30);
	glVertex3f(30, 0, 30);
	glVertex3f(30, 0, 20);
	glVertex3f(-30, 0, 20);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1,1,1);
	glVertex3f(-30, 0, 28);
	glVertex3f(30, 0, 28);
	glVertex3f(30, 0, 26);
	glVertex3f(-30, 0, 26);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3f(-30, 0, 24);
	glVertex3f(30, 0, 24);
	glVertex3f(30, 0, 22);
	glVertex3f(-30, 0, 22);
	glEnd();


}




//=======================================================================
// Display Function
//=======================================================================

using namespace std;
void drawBitmapText(string caption, int score, float r, float g, float b,
	float x, float y, float z) {
	glColor3f(r, g, b);
	glRasterPos3f(x, y, z);
	stringstream strm;
	strm << caption << score;
	string text = strm.str();
	for (string::iterator it = text.begin(); it != text.end(); ++it) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *it);
	}
}

std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat lightIntensity[] = { 0.7, 0.7, 0.7, 1.0f };
	GLfloat lightPosition[] = { 0.6f, 0.0f, 1.5f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);

	if (endgame > 2000 || scorepooh ==3  || scorebee==3 ) {


		
		drawBitmapText("END GAME ", 2, 0, 0, 1, -10, 10, 0);
		


		drawBitmapText("LEVEL ", 1, 0, 0, 1, -20,5, 0);
		drawBitmapText("SCORE  ", score, 0, 0, 1, -20, 0, 0);

		drawBitmapText("LEVEL ", 2, 0, 0, 1, 0, 5, 0);
		drawBitmapText("SCORE POOH  ", scorepooh, 0, 0, 1, 0, 0, 0);
		drawBitmapText("SCORE BEE ", scorebee, 0, 0, 1, 0, -5, 0);
		/*
		glPushMatrix();
		//glColor3d(0.1, 1, 0.3);
		glColor3d(0, 2, 0);
		glutSolidCube(30);
		glPopMatrix();
		*/
	
		


		char* p0s[100];
		glColor3d(1, 1, 1);//the background color is changed in the timer function after 1 sec by changing these parameters.
		sprintf((char*)p0s, "YOU WIN !!!!!! %d", 1);
		print(10, 10, (char*)p0s);
	}





	else {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GLfloat lightIntensity[] = { 0.7, 0.7, 0.7, 1.0f };
		GLfloat lightPosition[] = { 0.6f, 0.0f, 1.5f, 0.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);

		if (timerlevel2 == 1) {
			



			//sky box
			glPushMatrix();

			GLUquadricObj* qobj;
			qobj = gluNewQuadric();
			glTranslated(40, 0, 0);
			glRotated(90, 1, 0, 1);
			glBindTexture(GL_TEXTURE_2D, tex);
			gluQuadricTexture(qobj, true);
			gluQuadricNormals(qobj, GL_SMOOTH);
			gluSphere(qobj, 60, 80, 80);
			gluDeleteQuadric(qobj);
			glPopMatrix();

			RenderGround();

			glPushMatrix();
			glTranslatef(0, 0.2, -27);
			glScalef(0.055, 0.05, 0.05);
			glRotated(-90, 0.0, 1.0, 0.0);
			model_gate.Draw();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(movepoohx, movepoohy, movepoohz);

			glTranslatef(0, 0.2, -27);
			drawPooh();
			glPopMatrix();







			glPushMatrix();
			glTranslatef(movebeex, movebeey, movebeez);

			glTranslatef(-8, 0.2, 0);
			drawBee();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(movejarx, movejary, movejarz);
			glTranslatef(-15, 0.2, -17);
			drawhoneyjar();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(movebombx, 0, movebombz);
			glTranslatef(2, 1, -20);
			drawbomb();
			glPopMatrix();

			drawBitmapText("LEVEL ", 2, 0.9, 1, 1, -17, 10, 0);
			drawBitmapText("SCORE BEE ", scorebee, 0.9, 1, 1, -15, 10, 0);
			drawBitmapText("SCORE POOH ", scorepooh, 0.9, 1, 1, -10, 10, 0);
			




		}
		else {
			drawBitmapText("LEVEL ", 1, 0, 0, 1, -20, 10, 0);
			drawBitmapText("SCORE ", score, 0, 0, 1, -15, 10, 0);
			//drawLane();
			renderLane();

			// Draw Ground
			RenderGround();

			// Draw Tree Model
			/*glPushMatrix();
			glTranslatef(10, 0, 0);
			glScalef(0.7, 0.7, 0.7);
			model_tree.Draw();
			glPopMatrix();*/




			glPushMatrix();
			glTranslatef(ballMoveX, 0, ballMoveZ);
			glScalef(0.007, 0.007, 0.007);
			glRotatef(360.f, 0, 1, 0);
			model_ball.Draw();
			glPopMatrix();



			glPushMatrix();
			glTranslatef(goalkeeperX, 0, -25);
			glScalef(0.04, 0.04, 0.04);
			glRotatef(360.f, 0, 1, 0);
			model_goalkeeper.Draw();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(keyX, 0, keyZ);
			glScalef(2, 2, 2);
			glRotatef(360.f, 0, 1, 0);
			model_player.Draw();
			glPopMatrix();

			std::cout << "keyX = ";
			std::cout << keyX;
			std::cout << "keyZ = ";
			std::cout << keyZ;



			glPushMatrix();
			glTranslatef(-4, 4, -6);
			glScalef(0.035, 0.035, 0.035);
			glRotatef(90.f, 0, 1, 0);
			model_ref.Draw();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0, 0.2, -27);
			glScalef(0.035, 0.03, 0.03);
			glRotated(-90, 0.0, 1.0, 0.0);
			model_gate.Draw();
			glPopMatrix();


			glPushMatrix();
			glTranslatef(0, 0, -12);
			glScalef(6, 2, 5);
			glRotated(-90, 0.0, 1.0, 0.0);
			model_stadium.Draw();
			glPopMatrix();




			glPushMatrix();
			glTranslatef(20, 10, 15);
			glScalef(60, 20, 50);
			//glRotated(-90, 0.0, 1.0, 0.0);
			model_policeBox.Draw();
			glPopMatrix();




			//sky box
			glPushMatrix();

			GLUquadricObj* qobj;
			qobj = gluNewQuadric();
			glTranslated(40, 0, 0);
			glRotated(90, 1, 0, 1);
			glBindTexture(GL_TEXTURE_2D, tex);
			gluQuadricTexture(qobj, true);
			gluQuadricNormals(qobj, GL_SMOOTH);
			gluSphere(qobj, 80, 80, 80);
			gluDeleteQuadric(qobj);


			glPopMatrix();



		}
	}

	glutSwapBuffers();
}

void movement() {
	glBegin(GL_LINE_LOOP);                                     // Circle at center of field
	for (goalkeeperX = -4; goalkeeperX <= 5; goalkeeperX += 1) {
		glTranslatef(goalkeeperX, 0, -10);
	}
	glEnd();
}

void Timer(int value) {

	glutTimerFunc(7000, Timer, 0);
	if (score >= 1) {
		 keyX = 2;
		 keyY = 2;
		 keyZ = -15;

		 goalkeeperX = 0;
		 goalKeeperX2 = 4;
		 //move = false;
		 move2 = false;
		 ballMoveX = 0;
		 ballMoveZ = -18;
	}
	//timerlevel2++; 
	endgame++;
	glutPostRedisplay();
}

void time(int val)//timer animation function, allows the user to pass an integer valu to the timer function.
{
	if (move2 == true) {
		
		if (goalkeeperX <= 4) {
			goalkeeperX++;
		}
		else{
		if (goalkeeperX >= 4) {
			goalKeeperX2--;
			goalkeeperX = goalKeeperX2;
		
			if (goalKeeperX2 == -4) {
				goalKeeperX2;
			}
		}
		}
	
	}

	glutPostRedisplay();						// redraw 		

	glutTimerFunc(1000, time, 0);//recall the time function after 1000 ms and pass a zero value as an input to the time func.
	
}


//=======================================================================
// Keyboard Function
//=======================================================================
void myKeyboard(unsigned char button, int x, int y)
{
	switch (button)
	{
	case 'w':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'r':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 27:
		exit(0);
		break;
	case 'g':
		move2 = true;
		break;
	case 'p':       //pooh move right
		if (movepoohx < 5) {
			movepoohx += 1;
			if (movepoohx == -2 && movejarz == -5 && movepoohz == 0) {
				collisionjarwithpooh = true;

			}
			if (movepoohx == 0 && movepoohz == 3) {
				collisionbombwithpooh = true;
				movebombz = 20;
				if (movebeex == 0) {
					collisionbombwithbee = true;
				}
			}
		}
			break;

	case 'o':         //pooh move up
		if (movepoohz > -2) {
			movepoohz -= 1;
			if (movepoohx == -2 && movejarz == -5 && movepoohz == 0) {
				collisionjarwithpooh = true;
			}
			if (movepoohx == 0 && movepoohz == 3) {
				collisionbombwithpooh = true;
				movebombz = 20;
				if (movebeex == 0) {
					collisionbombwithbee = true;
				}
				
			}

		}
		break;

	case 'i':        //pooh move left 
		if (movepoohx > -10) {
			movepoohx -= 1;
			if (movepoohx == -2 && movejarz == -5 && movepoohz == 0) {
				collisionjarwithpooh = true;
			}
			if (movepoohx == 0 && movepoohz == 3) {
				collisionbombwithpooh = true;
				movebombz = 20;
				if (movebeex == 0) {
					collisionbombwithbee = true;
				}
			}

		}
			break;

	case 'l':         //pooh move down
		if (movepoohz < 5) {
			movepoohz += 1;
			if (movepoohx == -2 && movejarz == -5 && movepoohz==0) {
				collisionjarwithpooh = true;
			}
			if (movepoohx == 0 && movepoohz == 3) {
				collisionbombwithpooh = true;
				movebombz = 20;
				if (movebeex == 0) {
					collisionbombwithbee = true;
				}
				
			}
			
		}
			break;





	

	default:
		break;
	
		

	}

	if (collisionbombwithpooh == true && collisionbombwithbee==true) {
		
			
			PlaySound(TEXT("goal"), NULL, SND_ASYNC);
			scorepooh++;
			movebeex = 0;
			movebombz = 0;
			movepoohx = 0;
			movepoohz = 0;
			collisionbombwithpooh = false;
			collisionbombwithbee = false ;


		
	}

	if (collisionbombwithpooh == true && collisionbombwithbee == false) {
		movebeex = 0;
		movebombz = 0;
		movepoohx = 0;
		movepoohz = 0;
		collisionbombwithpooh = false;
		collisionbombwithbee = false;

	}



	glutPostRedisplay();
}



void Special(int key, int x, int Y) {

	if (timerlevel2 == 1) {
		int d = 1;

		if (key == GLUT_KEY_RIGHT) {
			srand(16);
			if (movebeex<4) {
				movebeex+=1;
				if (movebeex == -2 && movebeez == -12) {
					collisionjarwithbee = true;
					movejarz -= 5;
				}

				/*
				if (keyX == ballMoveX && keyZ <= -16) {

					ballMoveX = (int)((int)(rand()) % 4) + 1;
					if (goalkeeperX != ballMoveX) {
						ballMoveZ = -27;
						PlaySound(TEXT("goal"), NULL, SND_ASYNC);
						score++;
						glColor3f(1, 0, 0);
						char* p0s[20];
						sprintf((char*)p0s, "Score: %d", score);
						print(0, 19, (char*)p0s);
						glutPostRedisplay();

					}
				}
				*/
			}
		}

		if (key == GLUT_KEY_LEFT) {
			srand(16);
			if (movebeex > -8) {
				movebeex -=1;
				if (movebeex == -2 && movebeez == -12) {
					collisionjarwithbee = true;
					movejarz -= 5;
				}
				/*
				if (keyX > -8) {
					keyX -= 1;
					if (keyX == ballMoveX && keyZ <= -16) {

						ballMoveX = (int)((int)(rand()) % -4) - 4;
						if (goalkeeperX != ballMoveX) {
							ballMoveZ = -27;
							PlaySound(TEXT("goal"), NULL, SND_ASYNC);
							score++;
						}
					}
				}
				*/
			}
		}



		//keyX = 2 keyZ = -15

		if (key == GLUT_KEY_UP) {
			if (movebeez > -20) {
				movebeez -= 1;
				if (movebeex == -2 && movebeez == -12) {
					collisionjarwithbee = true;
					movejarz -= 5;
				}

			}
		}
		if (key == GLUT_KEY_DOWN) {
			if (movebeez < 5) {
				movebeez += 1;
				if (movebeex == -2 && movebeez == -12) {
					collisionjarwithbee = true;
					movejarz -= 5;
				}
			}

		}

		if (movepoohx == -2 && movejarz == -5 && movepoohz == 0) {
			collisionjarwithpooh = true;
		}

		if (collisionjarwithbee == true && collisionjarwithpooh == false) {
			PlaySound(TEXT("goal"), NULL, SND_ASYNC);
			scorebee++;
			movebeex = 0;
			movebeez = 0;
			movejarz = 0;
			movepoohx = 0;
			movepoohz = 0;
			collisionjarwithbee = false;
			collisionjarwithpooh = false;
		}

		if (collisionjarwithbee == true && collisionjarwithpooh == true) {
			

			movebeex = 0;
			movebeez = 0;
			movejarz = 0;
			movepoohx = 0;
			movepoohz = 0;
			collisionjarwithbee = false;
			collisionjarwithpooh = false;
		}


	}

	else {

		if (key == GLUT_KEY_RIGHT) {
			srand(16);
			if (keyX < 9) {
				keyX += 1;
				if (keyX == ballMoveX && keyZ <= -16) {

					ballMoveX = (int)((int)(rand()) % 4) + 1;
					if (goalkeeperX != ballMoveX) {
						ballMoveZ = -27;
						PlaySound(TEXT("goal"), NULL, SND_ASYNC);
						score++;

						glColor3f(1, 0, 0);
						char* p0s[20];
						sprintf((char*)p0s, "Score: %d", score);
						print(0, 19, (char*)p0s);
						glutPostRedisplay();
						if (score == 3) {
							timerlevel2 = 1;
						}

					}
				}
			}
		}

		if (key == GLUT_KEY_LEFT) {
			srand(16);
			if (keyX != -4) {
				if (keyX > -8) {
					keyX -= 1;
					if (keyX == ballMoveX && keyZ <= -16) {

						ballMoveX = (int)((int)(rand()) % -4) - 4;
						if (goalkeeperX != ballMoveX) {
							ballMoveZ = -27;
							PlaySound(TEXT("goal"), NULL, SND_ASYNC);
							score++;
							if (score == 3) {
								timerlevel2 = 1;
							}
						}
					}
				}
			}
		}



		//keyX = 2 keyZ = -15

		if (key == GLUT_KEY_UP) {
			if (keyZ > -24) {
				keyZ -= 1;

			}
		}
		if (key == GLUT_KEY_DOWN) {
			if (keyZ < 2) {
				keyZ += 1;
			}

		}
	}
	
	glutPostRedisplay();
}





//=======================================================================
// Motion Function
//=======================================================================
void myMotion(int x, int y)
{ 

	
	
	y = HEIGHT - y;

	if (cameraZoom - y > 0)
	{
		Eye.x += -0.1;
		Eye.z += -0.1;
	}
	else
	{
		Eye.x += 0.1;
		Eye.z += 0.1;
	}

	cameraZoom = y;

	glLoadIdentity();	//Clear Model_View Matrix

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);	//Setup Camera with modified paramters

	GLfloat light_position[] = { 0.2f, 0.1f, 1.2f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glutPostRedisplay();	//Re-draw scene 
	
}

//=======================================================================
// Mouse Function
//=======================================================================
void myMouse(int button, int state, int x, int y)
{
	
	y = HEIGHT - y;

	if (state == GLUT_DOWN)
	{
		cameraZoom = y;
	}

	
}

//=======================================================================
// Reshape Function
//=======================================================================
void myReshape(int w, int h)
{
	if (h == 0) {
		h = 1;
	}

	WIDTH = w;
	HEIGHT = h;

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)WIDTH / (GLdouble)HEIGHT, zNear, zFar);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
}

//=======================================================================
// Assets Loading Function
//=======================================================================
void LoadAssets()
{
	// Loading Model files
	model_house.Load("Models/house/house.3DS");
	model_tree.Load("Models/tree/Tree1.3ds");
	model_flowers.Load("Models/flowers/Flowers.3ds");
	model_player.Load("Models/player/Man.3ds");
	model_gate.Load("Models/Gates/Gate.3ds");
	model_ball.Load("Models/balls/Ball.3DS");
	model_goalkeeper.Load("Models/goalkeeper/Man.3DS");
	model_policeBox.Load("Models/policeBox/Police.3ds");
	model_stadium.Load("Models/stadium/stadium.3DS");
	model_ref.Load("Models/ref/Man.3DS");


	// Loading texture files
	tex_ground.Load("textures/grass.bmp");
	tex_lane.Load("textures/black.bmp");
	tex_fence.Load("textures/bricks.bmp");
	loadBMP(&tex, "Textures/blu-sky-3.bmp", true);
}

//=======================================================================
// Main Function
//=======================================================================
void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitWindowPosition(150, 50);

	glutCreateWindow(title);

	glutDisplayFunc(myDisplay);

	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(Special);
	glutMotionFunc(myMotion);

	glutMouseFunc(myMouse);
	glutTimerFunc(0, Timer, 0);
	glutTimerFunc(0, time, 0);
	
	glutReshapeFunc(myReshape);

	myInit();

	LoadAssets();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}