#include <windows.h>
#include <vector>
#include "vector"
#include "Dependencies/freeglut/freeglut.h"
#include <cmath>
#define M_PI 3.14159265358979323846

class Vector
{
public:
	Vector();
	void normalize(double* v);
	void vproduct(double* v, double a0, double a1, double a2, double b0, double b1, double b2);
	Vector(const Vector& orig);
	virtual ~Vector();
};

Vector::Vector()
{
}

void Vector::normalize(double* v)
{
	double d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	v[0] /= d;
	v[1] /= d;
	v[2] /= d;
}

void Vector::vproduct(double* v, double a0, double a1, double a2, double b0, double b1, double b2)
{
	v[0] = a1 * b2 - a2 * b1;
	v[1] = a2 * b0 - a0 * b2;
	v[2] = a0 * b1 - a1 * b0;
}

Vector::Vector(const Vector& orig)
{
}

Vector::~Vector()
{
}

using namespace std;
//wspolrzedne obserwatora

GLdouble eyex = 0.0;
GLdouble eyey = 0.0;
GLdouble eyez = 30.0;
float Rs = 15.0f; //size of room
float Tw = 2.0f; // width of table top from centre
float Tl = 3.0f; //length of table top from centre
float Th = 1.7f; //height of table top from centre
float Tt = 0.3f; //thickness of table top
float Ls = 0.3f; //size of table leg
float Rh = 10.0f; //height of room
float ChP = 2.5f;
float RED_LOW[] = { 0.8,0.7,0.0 };

float min = 0.0f;
float max = 1.0f;
float wll = 0.01f;
GLfloat scene_ambient[] = {1.0, 1.0, 1.0, 1.0};
//parametry zrodla swiatla nr 0
GLfloat light0_position[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light0_diffuse[] = {1.0, 1.0, 1.0, 1.0};

//parametry zrodla swiatla nr 1
GLfloat light1_position[] = {0.0, 0.0, 0.0, 1.0};
GLfloat light1_ambient[] = {0.0, 0.0, 0.0, 1.0};
GLfloat light1_diffuse[] = {1.0, 1.0, 0.1, 1.0};
GLfloat light1_specular[] = {0.2, 0.1, 0.0, 1.0};
GLfloat light1_spot_direction[] = {-5, -5, -10, 1.0};
GLint light1_spot_cutoff = 10;
GLint light1_spot_exponent = 20;

//parametry zrodla swiatla nr 2
GLfloat light2_position[] = {0.0, 0.0, 0.0, 0.0};
GLfloat light2_diffuse[] = {1.0, 1.0, 0.1, 1.0};
GLfloat light2_specular[] = {0.2, 0.1, 0.0, 1.0};

//specyfikacja materialu
GLfloat mat_ambient[] = {1.0, 1.0, 1.0, 1.0};
GLfloat mat_diffuse[] = {1.0, 1.0, 1.0, 1.0};
GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat mat_emmision[] = {0.0, 0.0, 0.0, 1.0};
GLfloat mat_shininess = 10.0;


void default_material_diffuse()
{
	mat_diffuse[0] = 0.0;
	mat_diffuse[1] = 8.0;
	mat_diffuse[2] = 0.0;

	mat_specular[0] = 0.0;
	mat_specular[1] = 8.0;
	mat_specular[2] = 0.0;

	mat_ambient[0] = 0.0;
	mat_ambient[1] = 8.0;
	mat_ambient[2] = 0.0;

	mat_shininess = 90.0;

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
}

void lampLight() {
	float position[] = { 0.0, 5.0f, 0.0, 1.0 };
	float direction[] = { 0.0, 0.0, -1.0 };
	float redlow[] = { 0.8,0.7,0.0 };
	GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
	GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, redlow);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0);
	glEnable(GL_COLOR_MATERIAL);
}



void lightDef2()
{
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	// Set lighting intensity and color
	// Somewhere in the initialization part of your program…


	// Create light components
	GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat diffuseLight[] = {0.8f, 0.8f, 0.8, 1.0f};
	GLfloat specularLight[] = {0.5f, 0.5f, 0.5f, 1.0f};
	GLfloat position[] = {-1.5f, 1.0f, -4.0f, 1.0f};

	// Assign created components to GL_LIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	// Set the light position
	GLfloat qaLightPosition[] = {0.0, 5.0f, 0.0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
}

void materialo()
{
	GLfloat qaBlack[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat qaGreen[] = {0.0, 1.0, 0.0, 1.0};
	GLfloat qaWhite[] = {1.0, 1.0, 1.0, 1.0};
	glMaterialfv(GL_FRONT, GL_AMBIENT, qaGreen);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, qaGreen);
	glMaterialfv(GL_FRONT, GL_SPECULAR, qaWhite);
	glMaterialf(GL_FRONT, GL_SHININESS, 60.0);
}

void drwatableTop()
{
	glPushMatrix(); // 1 set where to start the current object transformation
	glTranslatef(0.0f, -2.0f, 0.0f); // move downwards to lie on the floor

	glBegin(GL_QUADS);
	// bottom: normal pointing outwards
	//	glNormal3f(0, 1, 0);
	//glNormal3f(0, -1, 0);
	glTexCoord2f(min, min);
	glVertex3f(-Tw, Th, Tl);
	glTexCoord2f(max, min);
	glVertex3f(-Tw, Th, -Tl);
	glTexCoord2f(max, max);
	glVertex3f(Tw, Th, -Tl);
	glTexCoord2f(min, max);
	glVertex3f(Tw, Th, Tl);
	//Top:normal pointing outwards

	//front:normal pointing outwards
	//glNormal3f(0, 0, 1);
	glTexCoord2f(min, min);
	glVertex3f(-Tw, Th + Tt, Tl);
	glTexCoord2f(max, min);
	glVertex3f(-Tw, Th, Tl);
	glTexCoord2f(max, max);
	glVertex3f(Tw, Th, Tl);
	glTexCoord2f(min, max);
	glVertex3f(Tw, Th + Tt, Tl);
	//back:normal pointing outwards
	//glNormal3f(0, 0, -1);
	glTexCoord2f(min, min);
	glVertex3f(Tw, Th + Tt, -Tl);
	glTexCoord2f(max, min);
	glVertex3f(Tw, Th, -Tl);
	glTexCoord2f(max, max);
	glVertex3f(-Tw, Th, -Tl);
	glTexCoord2f(min, max);
	glVertex3f(-Tw, Th + Tt, -Tl);
	//right:normal pointing outwards
	//glNormal3f(1, 0, 0);
	glTexCoord2f(min, min);
	glVertex3f(Tw, Th + Tt, Tl);
	glTexCoord2f(max, min);
	glVertex3f(Tw, Th, Tl);
	glTexCoord2f(max, max);
	glVertex3f(Tw, Th, -Tl);
	glTexCoord2f(min, max);
	glVertex3f(Tw, Th + Tt, -Tl);
	//left:normal pointing outwards
	//glNormal3f(-1, 0, 0);
	glTexCoord2f(max, max);
	glVertex3f(-Tw, Th + Tt, Tl);
	glTexCoord2f(min, max);
	glVertex3f(-Tw, Th + Tt, -Tl);
	glTexCoord2f(min, min);
	glVertex3f(-Tw, Th, -Tl);
	glTexCoord2f(max, min);
	glVertex3f(-Tw, Th, Tl);

	//top
	//glNormal3f(0, 1, 0);
	glTexCoord2f(min, min);
	glVertex3f(-Tw, Th + Tt, Tl);
	glTexCoord2f(min, max);
	glVertex3f(Tw, Th + Tt, Tl);
	glTexCoord2f(max, max);
	glVertex3f(Tw, Th + Tt, -Tl);
	glTexCoord2f(max, min);
	glVertex3f(-Tw, Th + Tt, -Tl);
	glEnd();
	glPopMatrix();
}

void Firstleg()
{
	glPushMatrix(); // 1 set where to start the current object transformation
	glTranslatef(0.0f, -2.0f, 0.0f); // move downwards to lie on the floor

	glBegin(GL_QUADS);
	// front:normal pointing outwards
	glNormal3f(0, 0, 1);
	glTexCoord2f(min, min);
	glVertex3f(-Tw + Ls, Th, Tl - Ls);
	glTexCoord2f(max, min);
	glVertex3f(-Tw + Ls, 0.0f, Tl - Ls);
	glTexCoord2f(max, max);
	glVertex3f(-Tw + Ls + Ls, 0.0f, Tl - Ls);
	glTexCoord2f(min, max);
	glVertex3f(-Tw + Ls + Ls, Th, Tl - Ls);
	//back:normal pointing outwards
	glNormal3f(0, 0, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-Tw + Ls, Th, Tl - Ls - Ls);
	glTexCoord2f(0, 1);
	glVertex3f(-Tw + Ls + Ls, Th, Tl - Ls - Ls);
	glTexCoord2f(0, 0);
	glVertex3f(-Tw + Ls + Ls, 0.0f, Tl - Ls - Ls);
	glTexCoord2f(1, 0);
	glVertex3f(-Tw + Ls, 0.0f, Tl - Ls - Ls);
	//right: normal pointing outwards
	glNormal3f(1, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-Tw + Ls + Ls, Th, Tl - Ls);
	glTexCoord2f(0, 0);
	glVertex3f(-Tw + Ls + Ls, 0.0f, Tl - Ls);
	glTexCoord2f(1, 0);
	glVertex3f(-Tw + Ls + Ls, 0.0f, Tl - Ls - Ls);
	glTexCoord2f(1, 1);
	glVertex3f(-Tw + Ls + Ls, Th, Tl - Ls - Ls);
	//left:normal pointing outwards
	glNormal3f(-1, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-Tw + Ls, Th, Tl - Ls);
	glTexCoord2f(0, 1);
	glVertex3f(-Tw + Ls, Th, Tl - Ls - Ls);
	glTexCoord2f(0, 0);
	glVertex3f(-Tw + Ls, 0.0f, Tl - Ls - Ls);
	glTexCoord2f(1, 0);
	glVertex3f(-Tw + Ls, 0.0f, Tl - Ls);

	glEnd();
	glPopMatrix();
}

void secondleg()
{
	glPushMatrix(); // 1 set where to start the current object transformation
	glTranslatef(0.0f, -2.0f, 0.0f); // move downwards to lie on the floor

	glBegin(GL_QUADS);
	//front:Normals pointing outwards
	glNormal3f(0, 0, 1);
	glTexCoord2f(1, 1);
	glVertex3f(Tw - Ls, Th, Tl - Ls);
	glTexCoord2f(0, 1);
	glVertex3f(Tw - Ls - Ls, Th, Tl - Ls);
	glTexCoord2f(0, 0);
	glVertex3f(Tw - Ls - Ls, 0.0f, Tl - Ls);
	glTexCoord2f(1, 0);
	glVertex3f(Tw - Ls, 0.0f, Tl - Ls);

	//back:normals pointing outwards
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 1);
	glVertex3f(Tw - Ls, Th, Tl - Ls - Ls);
	glTexCoord2f(0, 0);
	glVertex3f(Tw - Ls, 0.0f, Tl - Ls - Ls);
	glTexCoord2f(1, 0);
	glVertex3f(Tw - Ls - Ls, 0.0f, Tl - Ls - Ls);
	glTexCoord2f(1, 1);
	glVertex3f(Tw - Ls - Ls, Th, Tl - Ls - Ls);
	//left:normal pointing outwards
	glNormal3f(-1, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(Tw - Ls - Ls, Th, Tl - Ls);
	glTexCoord2f(0, 1);
	glVertex3f(Tw - Ls - Ls, Th, Tl - Ls - Ls);
	glTexCoord2f(0, 0);
	glVertex3f(Tw - Ls - Ls, 0.0f, Tl - Ls - Ls);
	glTexCoord2f(1, 0);
	glVertex3f(Tw - Ls - Ls, 0.0f, Tl - Ls);
	//right:normal pointing outwards
	glNormal3f(1, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3f(Tw - Ls, Th, Tl - Ls);
	glTexCoord2f(0, 0);
	glVertex3f(Tw - Ls, 0.0f, Tl - Ls);
	glTexCoord2f(1, 0);
	glVertex3f(Tw - Ls, 0.0f, Tl - Ls - Ls);
	glTexCoord2f(1, 1);
	glVertex3f(Tw - Ls, Th, Tl - Ls - Ls);
	glEnd();
	glPopMatrix();
}

void thirdleg()
{
	glPushMatrix(); // 1 set where to start the current object transformation
	glTranslatef(0.0f, -2.0f, 0.0f); // move downwards to lie on the floor

	glBegin(GL_QUADS);
	//front:normal pointing outwards
	glNormal3f(0, 0, 1);
	glTexCoord2f(min, min);
	glVertex3f(-Tw + Ls, Th, -Tl + Ls);
	glTexCoord2f(max, min);
	glVertex3f(-Tw + Ls, 0.0f, -Tl + Ls);
	glTexCoord2f(max, max);
	glVertex3f(-Tw + Ls + Ls, 0.0f, -Tl + Ls);
	glTexCoord2f(min, max);
	glVertex3f(-Tw + Ls + Ls, Th, -Tl + Ls);
	//back:normal pointing outwards
	glNormal3f(0, 0, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-Tw + Ls, Th, -Tl + Ls + Ls);
	glTexCoord2f(0, 1);
	glVertex3f(-Tw + Ls + Ls, Th, -Tl + Ls + Ls);
	glTexCoord2f(0, 0);
	glVertex3f(-Tw + Ls + Ls, 0.0f, -Tl + Ls + Ls);
	glTexCoord2f(1, 0);
	glVertex3f(-Tw + Ls, 0.0f, -Tl + Ls + Ls);
	//right: normal pointing outwards
	glNormal3f(1, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-Tw + Ls + Ls, Th, -Tl + Ls);
	glTexCoord2f(0, 0);
	glVertex3f(-Tw + Ls + Ls, 0.0f, -Tl + Ls);
	glTexCoord2f(1, 0);
	glVertex3f(-Tw + Ls + Ls, 0.0f, -Tl + Ls + Ls);
	glTexCoord2f(1, 1);
	glVertex3f(-Tw + Ls + Ls, Th, -Tl + Ls + Ls);
	//left:normal pointing outwards
	glNormal3f(-1, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-Tw + Ls, Th, -Tl + Ls);
	glTexCoord2f(0, 1);
	glVertex3f(-Tw + Ls, Th, -Tl + Ls + Ls);
	glTexCoord2f(0, 0);
	glVertex3f(-Tw + Ls, 0.0f, -Tl + Ls + Ls);
	glTexCoord2f(1, 0);
	glVertex3f(-Tw + Ls, 0.0f, -Tl + Ls);
	glEnd();
	glPopMatrix();
}

void fourthleg()
{
	glPushMatrix(); // 1 set where to start the current object transformation
	glTranslatef(0.0f, -2.0f, 0.0f); // move downwards to lie on the floor

	glBegin(GL_QUADS);
	//front:Normals pointing outwards
	glNormal3f(0, 0, 1);
	glTexCoord2f(1, 1);
	glVertex3f(Tw - Ls, Th, -Tl + Ls);
	glTexCoord2f(0, 1);
	glVertex3f(Tw - Ls - Ls, Th, -Tl + Ls);
	glTexCoord2f(0, 0);
	glVertex3f(Tw - Ls - Ls, 0.0f, -Tl + Ls);
	glTexCoord2f(1, 0);
	glVertex3f(Tw - Ls, 0.0f, -Tl + Ls);
	//back:normals pointing outwards
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 1);
	glVertex3f(Tw - Ls, Th, -Tl + Ls + Ls);
	glTexCoord2f(0, 0);
	glVertex3f(Tw - Ls, 0.0f, -Tl + Ls + Ls);
	glTexCoord2f(1, 0);
	glVertex3f(Tw - Ls - Ls, 0.0f, -Tl + Ls + Ls);
	glTexCoord2f(1, 1);
	glVertex3f(Tw - Ls - Ls, Th, -Tl + Ls + Ls);
	//left:normal pointing outwards
	glNormal3f(-1, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(Tw - Ls - Ls, Th, -Tl + Ls);
	glTexCoord2f(0, 1);
	glVertex3f(Tw - Ls - Ls, Th, -Tl + Ls + Ls);
	glTexCoord2f(0, 0);
	glVertex3f(Tw - Ls - Ls, 0.0f, -Tl + Ls + Ls);
	glTexCoord2f(1, 0);
	glVertex3f(Tw - Ls - Ls, 0.0f, -Tl + Ls);
	//right:normal pointing outwards
	glNormal3f(1, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3f(Tw - Ls, Th, -Tl + Ls);
	glTexCoord2f(0, 0);
	glVertex3f(Tw - Ls, 0.0f, -Tl + Ls);
	glTexCoord2f(1, 0);
	glVertex3f(Tw - Ls, 0.0f, -Tl + Ls + Ls);
	glTexCoord2f(1, 1);
	glVertex3f(Tw - Ls, Th, -Tl + Ls + Ls);
	glEnd();
	glPopMatrix();
}

void drawChairR()
{
	glPushMatrix();
	//glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef(2.5f, -1.0f, 0.0f);
	glScalef(0.3f, 0.5f, 0.3f);
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);

	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);
	//Front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-2.0f, -0.2f, 2.0f);
	glVertex3f(2.0f, -0.2f, 2.0f);
	glVertex3f(2.0f, 0.2f, 2.0f);
	glVertex3f(-2.0f, 0.2f, 2.0f);

	//Right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(2.0f, -0.2f, -2.0f);
	glVertex3f(2.0f, 0.2f, -2.0f);
	glVertex3f(2.0f, 0.2f, 2.0f);
	glVertex3f(2.0f, -0.2f, 2.0f);

	//Back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-2.0f, -0.2f, -2.0f);
	glVertex3f(-2.0f, 0.2f, -2.0f);
	glVertex3f(2.0f, 0.2f, -2.0f);
	glVertex3f(2.0f, -0.2f, -2.0f);

	//Left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-2.0f, -0.2f, -2.0f);
	glVertex3f(-2.0f, -0.2f, 2.0f);
	glVertex3f(-2.0f, 0.2f, 2.0f);
	glVertex3f(-2.0f, 0.2f, -2.0f);

	//top
	glNormal3f(0.0f, 1.0f, 0.0f);

	glVertex3f(2.0f, 0.2f, 2.0f);
	glVertex3f(-2.0f, 0.2f, 2.0f);
	glVertex3f(-2.0f, 0.2f, -2.0f);
	glVertex3f(2.0f, 0.2f, -2.0f);

	//bottom
	glNormal3f(0.0f, -1.0f, 0.0f);

	glVertex3f(2.0f, -0.2f, 2.0f);
	glVertex3f(-2.0f, -0.2f, 2.0f);
	glVertex3f(-2.0f, -0.2f, -2.0f);
	glVertex3f(2.0f, -0.2f, -2.0f);

	//table front leg
	//front
	glNormal3f(0.0f, 0.0f, 1.0f);

	glVertex3f(1.8f, -0.2f, 1.6f);
	glVertex3f(1.4f, -0.2f, 1.6f);
	glVertex3f(1.4f, -2.0f, 1.6f);
	glVertex3f(1.8f, -2.0f, 1.6f);

	//back
	glNormal3f(0.0f, 0.0f, -1.0f);

	glVertex3f(1.8f, -0.2f, 1.2f);
	glVertex3f(1.4f, -0.2f, 1.2f);
	glVertex3f(1.4f, -2.0f, 1.2f);
	glVertex3f(1.8f, -2.0f, 1.2f);

	//right
	glNormal3f(1.0f, 0.0f, 0.0f);

	glVertex3f(1.8f, -0.2f, 1.6f);
	glVertex3f(1.8f, -0.2f, 1.2f);
	glVertex3f(1.8f, -2.0f, 1.2f);
	glVertex3f(1.8f, -2.0f, 1.6f);

	//left
	glNormal3f(-1.0f, 0.0f, 0.0f);

	glVertex3f(1.4f, -0.2f, 1.6f);
	glVertex3f(1.4f, -0.2f, 1.2f);
	glVertex3f(1.4f, -2.0f, 1.2f);
	glVertex3f(1.4f, -2.0f, 1.6f);

	//back leg back
	//front
	glNormal3f(0.0f, 0.0f, -1.0f);

	glVertex3f(1.8f, -0.2f, -1.2f);
	glVertex3f(1.4f, -0.2f, -1.2f);
	glVertex3f(1.4f, -2.0f, -1.2f);
	glVertex3f(1.8f, -2.0f, -1.2f);

	//back
	glNormal3f(0.0f, 0.0f, -1.0f);

	glVertex3f(1.8f, -0.2f, -1.6f);
	glVertex3f(1.4f, -0.2f, -1.6f);
	glVertex3f(1.4f, -2.0f, -1.6f);
	glVertex3f(1.8f, -2.0f, -1.6f);

	//right
	glNormal3f(1.0f, 0.0f, 0.0f);

	glVertex3f(1.8f, -0.2f, -1.6f);
	glVertex3f(1.8f, -0.2f, -1.2f);
	glVertex3f(1.8f, -2.0f, -1.2f);
	glVertex3f(1.8f, -2.0f, -1.6f);

	//left
	glNormal3f(1.0f, 0.0f, 0.0f);

	glVertex3f(1.4f, -0.2f, -1.6f);
	glVertex3f(1.4f, -0.2f, -1.2f);
	glVertex3f(1.4f, -2.0f, -1.2f);
	glVertex3f(1.4f, -2.0f, -1.6f);

	//leg left front
	glNormal3f(0.0f, 0.0f, 1.0f);

	glVertex3f(-1.8f, -0.2f, 1.6f);
	glVertex3f(-1.4f, -0.2f, 1.6f);
	glVertex3f(-1.4f, -2.0f, 1.6f);
	glVertex3f(-1.8f, -2.0f, 1.6f);

	//back
	glNormal3f(0.0f, 0.0f, -1.0f);

	glVertex3f(-1.8f, -0.2f, 1.2f);
	glVertex3f(-1.4f, -0.2f, 1.2f);
	glVertex3f(-1.4f, -2.0f, 1.2f);
	glVertex3f(-1.8f, -2.0f, 1.2f);

	//right
	glNormal3f(1.0f, 0.0f, 0.0f);

	glVertex3f(-1.8f, -0.2f, 1.6f);
	glVertex3f(-1.8f, -0.2f, 1.2f);
	glVertex3f(-1.8f, -2.0f, 1.2f);
	glVertex3f(-1.8f, -2.0f, 1.6f);

	//left
	glNormal3f(-1.0f, 0.0f, 0.0f);

	glVertex3f(-1.4f, -0.2f, 1.6f);
	glVertex3f(-1.4f, -0.2f, 1.2f);
	glVertex3f(-1.4f, -2.0f, 1.2f);
	glVertex3f(-1.4f, -2.0f, 1.6f);

	//left leg back front

	//front
	glNormal3f(0.0f, 0.0f, -1.0f);

	glVertex3f(-1.8f, -0.2f, -1.2f);
	glVertex3f(-1.4f, -0.2f, -1.2f);
	glVertex3f(-1.4f, -2.0f, -1.2f);
	glVertex3f(-1.8f, -2.0f, -1.2f);

	//back
	glNormal3f(0.0f, 0.0f, -1.0f);

	glVertex3f(-1.8f, -0.2f, -1.6f);
	glVertex3f(-1.4f, -0.2f, -1.6f);
	glVertex3f(-1.4f, -2.0f, -1.6f);
	glVertex3f(-1.8f, -2.0f, -1.6f);

	//right
	glNormal3f(1.0f, 0.0f, 0.0f);

	glVertex3f(-1.8f, -0.2f, -1.6f);
	glVertex3f(-1.8f, -0.2f, -1.2f);
	glVertex3f(-1.8f, -2.0f, -1.2f);
	glVertex3f(-1.8f, -2.0f, -1.6f);

	//left
	glNormal3f(-1.0f, 0.0f, 0.0f);

	glVertex3f(-1.4f, -0.2f, -1.6f);
	glVertex3f(-1.4f, -0.2f, -1.2f);
	glVertex3f(-1.4f, -2.0f, -1.2f);
	glVertex3f(-1.4f, -2.0f, -1.6f);

	//chair back
	//front
	glColor3f(0, 1, 0);
	//glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.8f, 0.2f, -1.8f);
	glVertex3f(1.8f, 0.2f, -1.8f);
	glVertex3f(1.8f, 3.5f, -1.8f);
	glVertex3f(-1.8f, 3.5f, -1.8f);

	//back
	//glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.8f, 0.2f, -2.0f);
	glVertex3f(1.8f, 0.2f, -2.0f);
	glVertex3f(1.8f, 3.5f, -2.0f);
	glVertex3f(-1.8f, 3.5f, -2.0f);


	//  glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.8f, 0.2f, -2.0f);
	glVertex3f(-1.8f, 3.5f, -2.0f);
	glVertex3f(-1.8f, 3.5f, -1.8f);
	glVertex3f(-1.8f, 0.2f, -1.8f);


	glVertex3f(1.8f, 0.2f, -2.0f);
	glVertex3f(1.8f, 3.5f, -2.0f);
	glVertex3f(1.8f, 3.5f, -1.8f);
	glVertex3f(1.8f, 0.2f, -1.8f);

	glVertex3f(-1.8f, 3.5f, -2.0f);
	glVertex3f(-1.8f, 3.5f, -1.8f);
	glVertex3f(1.8f, 3.5f, -1.8f);
	glVertex3f(1.8f, 3.5f, -2.0f);

	glEnd();
	glPopMatrix();
	glutSwapBuffers();
}

void drawChairL()
{
	glPushMatrix();
	//glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef(-2.5f, -1.0f, 0.0f);
	glScalef(0.3f, 0.5f, 0.3f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);
	//Front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-2.0f, -0.2f, 2.0f);
	glVertex3f(2.0f, -0.2f, 2.0f);
	glVertex3f(2.0f, 0.2f, 2.0f);
	glVertex3f(-2.0f, 0.2f, 2.0f);

	//Right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(2.0f, -0.2f, -2.0f);
	glVertex3f(2.0f, 0.2f, -2.0f);
	glVertex3f(2.0f, 0.2f, 2.0f);
	glVertex3f(2.0f, -0.2f, 2.0f);

	//Back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-2.0f, -0.2f, -2.0f);
	glVertex3f(-2.0f, 0.2f, -2.0f);
	glVertex3f(2.0f, 0.2f, -2.0f);
	glVertex3f(2.0f, -0.2f, -2.0f);

	//Left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-2.0f, -0.2f, -2.0f);
	glVertex3f(-2.0f, -0.2f, 2.0f);
	glVertex3f(-2.0f, 0.2f, 2.0f);
	glVertex3f(-2.0f, 0.2f, -2.0f);

	//top
	glNormal3f(0.0f, 1.0f, 0.0f);

	glVertex3f(2.0f, 0.2f, 2.0f);
	glVertex3f(-2.0f, 0.2f, 2.0f);
	glVertex3f(-2.0f, 0.2f, -2.0f);
	glVertex3f(2.0f, 0.2f, -2.0f);

	//bottom
	glNormal3f(0.0f, -1.0f, 0.0f);

	glVertex3f(2.0f, -0.2f, 2.0f);
	glVertex3f(-2.0f, -0.2f, 2.0f);
	glVertex3f(-2.0f, -0.2f, -2.0f);
	glVertex3f(2.0f, -0.2f, -2.0f);

	//table front leg
	//front
	glNormal3f(0.0f, 0.0f, 1.0f);

	glVertex3f(1.8f, -0.2f, 1.6f);
	glVertex3f(1.4f, -0.2f, 1.6f);
	glVertex3f(1.4f, -2.0f, 1.6f);
	glVertex3f(1.8f, -2.0f, 1.6f);

	//back
	glNormal3f(0.0f, 0.0f, -1.0f);

	glVertex3f(1.8f, -0.2f, 1.2f);
	glVertex3f(1.4f, -0.2f, 1.2f);
	glVertex3f(1.4f, -2.0f, 1.2f);
	glVertex3f(1.8f, -2.0f, 1.2f);

	//right
	glNormal3f(1.0f, 0.0f, 0.0f);

	glVertex3f(1.8f, -0.2f, 1.6f);
	glVertex3f(1.8f, -0.2f, 1.2f);
	glVertex3f(1.8f, -2.0f, 1.2f);
	glVertex3f(1.8f, -2.0f, 1.6f);

	//left
	glNormal3f(-1.0f, 0.0f, 0.0f);

	glVertex3f(1.4f, -0.2f, 1.6f);
	glVertex3f(1.4f, -0.2f, 1.2f);
	glVertex3f(1.4f, -2.0f, 1.2f);
	glVertex3f(1.4f, -2.0f, 1.6f);

	//back leg back
	//front
	glNormal3f(0.0f, 0.0f, -1.0f);

	glVertex3f(1.8f, -0.2f, -1.2f);
	glVertex3f(1.4f, -0.2f, -1.2f);
	glVertex3f(1.4f, -2.0f, -1.2f);
	glVertex3f(1.8f, -2.0f, -1.2f);

	//back
	glNormal3f(0.0f, 0.0f, -1.0f);

	glVertex3f(1.8f, -0.2f, -1.6f);
	glVertex3f(1.4f, -0.2f, -1.6f);
	glVertex3f(1.4f, -2.0f, -1.6f);
	glVertex3f(1.8f, -2.0f, -1.6f);

	//right
	glNormal3f(1.0f, 0.0f, 0.0f);

	glVertex3f(1.8f, -0.2f, -1.6f);
	glVertex3f(1.8f, -0.2f, -1.2f);
	glVertex3f(1.8f, -2.0f, -1.2f);
	glVertex3f(1.8f, -2.0f, -1.6f);

	//left
	glNormal3f(1.0f, 0.0f, 0.0f);

	glVertex3f(1.4f, -0.2f, -1.6f);
	glVertex3f(1.4f, -0.2f, -1.2f);
	glVertex3f(1.4f, -2.0f, -1.2f);
	glVertex3f(1.4f, -2.0f, -1.6f);

	//leg left front
	glNormal3f(0.0f, 0.0f, 1.0f);

	glVertex3f(-1.8f, -0.2f, 1.6f);
	glVertex3f(-1.4f, -0.2f, 1.6f);
	glVertex3f(-1.4f, -2.0f, 1.6f);
	glVertex3f(-1.8f, -2.0f, 1.6f);

	//back
	glNormal3f(0.0f, 0.0f, -1.0f);

	glVertex3f(-1.8f, -0.2f, 1.2f);
	glVertex3f(-1.4f, -0.2f, 1.2f);
	glVertex3f(-1.4f, -2.0f, 1.2f);
	glVertex3f(-1.8f, -2.0f, 1.2f);

	//right
	glNormal3f(1.0f, 0.0f, 0.0f);

	glVertex3f(-1.8f, -0.2f, 1.6f);
	glVertex3f(-1.8f, -0.2f, 1.2f);
	glVertex3f(-1.8f, -2.0f, 1.2f);
	glVertex3f(-1.8f, -2.0f, 1.6f);

	//left
	glNormal3f(-1.0f, 0.0f, 0.0f);

	glVertex3f(-1.4f, -0.2f, 1.6f);
	glVertex3f(-1.4f, -0.2f, 1.2f);
	glVertex3f(-1.4f, -2.0f, 1.2f);
	glVertex3f(-1.4f, -2.0f, 1.6f);

	//left leg back front

	//front
	glNormal3f(0.0f, 0.0f, -1.0f);

	glVertex3f(-1.8f, -0.2f, -1.2f);
	glVertex3f(-1.4f, -0.2f, -1.2f);
	glVertex3f(-1.4f, -2.0f, -1.2f);
	glVertex3f(-1.8f, -2.0f, -1.2f);

	//back
	glNormal3f(0.0f, 0.0f, -1.0f);

	glVertex3f(-1.8f, -0.2f, -1.6f);
	glVertex3f(-1.4f, -0.2f, -1.6f);
	glVertex3f(-1.4f, -2.0f, -1.6f);
	glVertex3f(-1.8f, -2.0f, -1.6f);

	//right
	glNormal3f(1.0f, 0.0f, 0.0f);

	glVertex3f(-1.8f, -0.2f, -1.6f);
	glVertex3f(-1.8f, -0.2f, -1.2f);
	glVertex3f(-1.8f, -2.0f, -1.2f);
	glVertex3f(-1.8f, -2.0f, -1.6f);

	//left
	glNormal3f(-1.0f, 0.0f, 0.0f);

	glVertex3f(-1.4f, -0.2f, -1.6f);
	glVertex3f(-1.4f, -0.2f, -1.2f);
	glVertex3f(-1.4f, -2.0f, -1.2f);
	glVertex3f(-1.4f, -2.0f, -1.6f);

	//chair back
	//front
	glColor3f(0, 1, 0);
	//glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.8f, 0.2f, -1.8f);
	glVertex3f(1.8f, 0.2f, -1.8f);
	glVertex3f(1.8f, 3.5f, -1.8f);
	glVertex3f(-1.8f, 3.5f, -1.8f);

	//back
	//glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.8f, 0.2f, -2.0f);
	glVertex3f(1.8f, 0.2f, -2.0f);
	glVertex3f(1.8f, 3.5f, -2.0f);
	glVertex3f(-1.8f, 3.5f, -2.0f);


	//  glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.8f, 0.2f, -2.0f);
	glVertex3f(-1.8f, 3.5f, -2.0f);
	glVertex3f(-1.8f, 3.5f, -1.8f);
	glVertex3f(-1.8f, 0.2f, -1.8f);


	glVertex3f(1.8f, 0.2f, -2.0f);
	glVertex3f(1.8f, 3.5f, -2.0f);
	glVertex3f(1.8f, 3.5f, -1.8f);
	glVertex3f(1.8f, 0.2f, -1.8f);

	glVertex3f(-1.8f, 3.5f, -2.0f);
	glVertex3f(-1.8f, 3.5f, -1.8f);
	glVertex3f(1.8f, 3.5f, -1.8f);
	glVertex3f(1.8f, 3.5f, -2.0f);


	glEnd();
	glPopMatrix();
	glutSwapBuffers();
}

void drawSphere(double r)
{
	glPushMatrix();
	glBegin(GL_QUADS);
	double phi;
	double rho;
	double v[] = {0.0, 0.0, 0.0};
	double deltaPhi;
	double deltaRho;
	Vector vector;
	deltaPhi = deltaRho = M_PI / 50;

	for (phi = 0; phi < M_PI; phi += deltaPhi)
	{
		for (rho = 0; rho < M_PI * 2; rho += deltaRho)
		{
			double x3 = r * sin(rho) * cos(phi);
			double y3 = r * sin(rho) * sin(phi);
			double z3 = r * cos(rho);

			double x4 = r * sin(rho + deltaRho) * cos(phi);
			double y4 = r * sin(rho + deltaRho) * sin(phi);
			double z4 = r * cos(rho + deltaRho);

			glVertex3f(x3, y3, z3);
			glVertex3f(x4, y4, z4);

			double x1 = r * sin(rho + deltaRho) * cos(phi + deltaPhi);
			double y1 = r * sin(rho + deltaRho) * sin(phi + deltaPhi);
			double z1 = r * cos(rho + deltaRho);

			double x2 = r * sin(rho) * cos(phi + deltaPhi);
			double y2 = r * sin(rho) * sin(phi + deltaPhi);
			double z2 = r * cos(rho);

			v[0] = x1;
			v[1] = y1;
			v[2] = z1;
			vector.normalize(v);
			glNormal3dv(v);

			glVertex3f(x1, y1, z1);
			glVertex3f(x2, y2, z2);
		}
	}
	glEnd();
	glPopMatrix();
	glutSwapBuffers();
}
void drawLamp()
{
	lampLight();
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 5.0f, 0.0f);
	glMaterialfv(GL_FRONT, GL_EMISSION, RED_LOW);
	drawSphere(1.0f);
	
	glPopMatrix();
	GLfloat black[4] = { 0,0,0,1 };
	//glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
	//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	//glutSwapBuffers();
}
void drawEntireTable()
{
	glColor3f(1.0, 0.0, 0.0);
	drwatableTop();
	Firstleg();
	secondleg();
	thirdleg();
	fourthleg();
}

void drawWall() //enclosing the walls of the room
{
	glColor3f(0.2, 0.1, 0.3);
	glBegin(GL_QUADS); //normals pointing outwards
	glNormal3f(0, 1, 0);
	float tl = 30.0f;
	////left
	glTexCoord2f(0, 0);
	glVertex3f(-Rs - wll, -2.0f, -Rs);
	glTexCoord2f(5, 0);
	glVertex3f(-Rs - wll, -2.0f, Rs);
	glTexCoord2f(5, 5);
	glVertex3f(-Rs - wll, Rh, Rs);
	glTexCoord2f(0, 5);
	glVertex3f(-Rs - wll, Rh, -Rs);
	////right
	glTexCoord2f(0, 0);
	glVertex3f(Rs + wll, -2.0f, Rs);
	glTexCoord2f(5, 0);
	glVertex3f(Rs + wll, -2.0f, -Rs);
	glTexCoord2f(5, 5);
	glVertex3f(Rs + wll, Rh, -Rs);
	glTexCoord2f(0, 5);
	glVertex3f(Rs + wll, Rh, Rs);
	////back
	glTexCoord2f(0, 0);
	glVertex3f(-Rs, -2.0f, Rs - tl);
	glTexCoord2f(5, 0);
	glVertex3f(Rs, -2.0f, Rs - tl);
	glTexCoord2f(5, 5);
	glVertex3f(Rs, Rh, Rs - tl);
	glTexCoord2f(0, 5);
	glVertex3f(-Rs, Rh, Rs - tl);

	glEnd();
	glDisable(GL_TEXTURE_2D);
}

static GLfloat floorVertices[4][3] = {
	{-Rs, -2.0f, Rs},
	{Rs, -2.0f, Rs},
	{Rs, -2.0f, -Rs},
	{-Rs, -2.0f, -Rs},
};

//////////////////////////

static void drawFloor(void)
{
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glColor3f(0.90f, 0.90f, 0.90f);
	glVertex3fv(floorVertices[0]);
	glVertex3fv(floorVertices[1]);
	glVertex3fv(floorVertices[2]);
	glVertex3fv(floorVertices[3]);
	glEnd();
	glPushMatrix();
}

static void drawcCeiling(void)
{
	glPushMatrix();
	glTranslatef(0.0f, Rh, 0.0f);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glColor3f(0.90f, 0.90f, 0.90f);
	glVertex3fv(floorVertices[0]);
	glVertex3fv(floorVertices[1]);
	glVertex3fv(floorVertices[2]);
	glVertex3fv(floorVertices[3]);
	glEnd();
	glPushMatrix();
}


void display()
{
	//glClearColor(1.0, 1.0, 1.0, 1.0);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //"czyszczenie" t³a okan i bufora g³êbokosci
	glEnable(GL_DEPTH_TEST); //w³¹cznie algorytmu zas³aniania
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80.0, 1.0, 0.1, 50.0); //bry³a widzenia perspektywicznego
	gluLookAt(eyex, eyey, eyez, 0.0, 0.0, -50.0, 0.0, 1.0, 0.0); //obserwator 1
	glMatrixMode(GL_MODELVIEW);
	
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glShadeModel(GL_SMOOTH);
	//glShadeModel(GL_FLAT);
	
	//glClearColor(0.0, 0.0, 0.0, 0.0);
	
	//lEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT1);
	
	glShadeModel(GL_SMOOTH);
	
	glLoadIdentity();
	//drawLamp();
	glLoadIdentity();
	//materialo();
	lightDef2();
	mat_ambient[0] = 1.0;
	mat_ambient[1] = 0.0;
	mat_ambient[2] = 0.0;

	mat_diffuse[0] = 1.0;
	mat_diffuse[1] = 0.0;
	mat_diffuse[2] = 0.0;

	mat_specular[0] = 10.0;
	mat_specular[1] = 0.1;
	mat_specular[2] = 0.1;

	mat_shininess = 40.0;

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	drawWall();
	default_material_diffuse();
	drawEntireTable();
	drawChairR();
	drawChairL();
	drawFloor();
	drawcCeiling();
	

	glFlush();
}

//odrysowywanie okna renderingu

void Redisplay(int width, int height)
{
	// obszar renderingu - ca³e okno
	glViewport(0, 0, width, height);

	// generowanie sceny 3D
	display();
}

void on_key(unsigned char c, int x, int y) {

	if (c == 'q') exit(0);
	if (c == 's') glShadeModel(GL_SMOOTH);
	if (c == 'f') glShadeModel(GL_FLAT);
	if (c == 'D') glEnable(GL_DEPTH_TEST);
	if (c == 'd') glDisable(GL_DEPTH_TEST);
	if (c == 'C') glEnable(GL_CULL_FACE);
	if (c == 'c') glDisable(GL_CULL_FACE);
	if (c == 'B') glCullFace(GL_BACK);
	if (c == 'b') glCullFace(GL_FRONT);
	if (c == '0') glEnable(GL_LIGHT0);
	if (c == '1') glEnable(GL_LIGHT1);
	if (c == '8') {
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
	}
}
//ruch obserwatora do przodu, do ty³u

void Klawiatura(unsigned char key, int x, int y)
{
	// klawisz +
	if (key == '+')
		eyez -= 1.0;
	else
		// klawisz -
		if (key == '-')
			eyez += 1.0;
	// odrysowanie okna
	Redisplay(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

//ruch obserwatora w poziomie i w pionie

void Strzalki(int key, int x, int y)
{
	switch (key)
	{
		// scena w lewo
	case GLUT_KEY_LEFT:
		eyex += 1.0;
		break;
		// scena w górê
	case GLUT_KEY_UP:
		eyey -= 1.0;
		break;
		// scena w prawo
	case GLUT_KEY_RIGHT:
		eyex -= 1.0;
		break;
		// scena w dó³
	case GLUT_KEY_DOWN:
		eyey += 1.0;
		break;
	}
	// odrysowanie okna
	Redisplay(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowSize(1024, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Test");
	glutDisplayFunc(display);

	// do³¹czenie funkcji wywo³ywanej przy zmianie rozmiaru okna
	glutReshapeFunc(Redisplay);
	
	// do³¹czenie funkcji obs³ugi klawiatury
	glutKeyboardFunc(Klawiatura);

	// do³¹czenie funkcji obs³ugi klawiszy strza³ek
	glutSpecialFunc(Strzalki);


	glutMainLoop();

	return 0;
}
