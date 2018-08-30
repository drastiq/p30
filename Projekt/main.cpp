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
float Lamp_Glow[] = {1, 1, 0.0};

float min = 0.0f;
float max = 1.0f;
float wll = 0.01f;
float no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
float mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
float mat_ambient_color[] = {0.8f, 0.8f, 0.2f, 1.0f};
float mat_diffuse[] = {0.1f, 0.5f, 0.8f, 1.0f};
float mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
float no_shininess = 0.0f;
float low_shininess = 5.0f;
float high_shininess = 100.0f;
float mat_emission[] = {0.3f, 0.2f, 0.2f, 0.0f};


void lampLight()
{
	float position[] = {0.0, 6.0f, 0.0, 1.0};
	//float direction[] = { 0.0, 0.0, -1.0 };
	float redlow[] = {0.8, 0.7, 0.0};
	GLfloat diffuseLight[] = {0.8f, 0.8f, 0.8, 1.0f};
	GLfloat specularLight[] = {1.0f, 0.5f, 0.5f, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, redlow);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0);
	////glEnable(GL_COLOR_MATERIAL);
}


void lightDef2()
{
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_COLOR_MATERIAL);
	// Set lighting intensity and color
	// Somewhere in the initialization part of your program…


	// Create light components
	GLfloat ambientLight[] = {0.4f, 0.4f, 0.4f, 1.0f};

	GLfloat diffuseLight[] = {1.0f, 1.0f, 1.0f, 1.0f};

	GLfloat specularLight[] = {1.0f, 1.0f, 1.0f, 1.0f};


	// Assign created components to GL_LIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	// Set the light position
	GLfloat qaLightPosition[] = {0.0, 6.0f, 0.0, 1.0};
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

	//glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glBegin(GL_QUADS);
	// bottom: normal pointing outwards
	glNormal3f(0, -1, 0);

	glVertex3f(-Tw, Th, Tl);

	glVertex3f(-Tw, Th, -Tl);

	glVertex3f(Tw, Th, -Tl);

	glVertex3f(Tw, Th, Tl);
	//Top:normal pointing outwards

	//front:normal pointing outwards
	glNormal3f(0, 0, 1);
	glVertex3f(-Tw, Th + Tt, Tl);

	glVertex3f(-Tw, Th, Tl);

	glVertex3f(Tw, Th, Tl);

	glVertex3f(Tw, Th + Tt, Tl);
	//back:normal pointing outwards
	glNormal3f(0, 0, -1);
	glVertex3f(Tw, Th + Tt, -Tl);

	glVertex3f(Tw, Th, -Tl);

	glVertex3f(-Tw, Th, -Tl);

	glVertex3f(-Tw, Th + Tt, -Tl);
	//right:normal pointing outwards
	glNormal3f(1, 0, 0);
	glVertex3f(Tw, Th + Tt, Tl);

	glVertex3f(Tw, Th, Tl);

	glVertex3f(Tw, Th, -Tl);

	glVertex3f(Tw, Th + Tt, -Tl);
	//left:normal pointing outwards
	glNormal3f(-1, 0, 0);

	glVertex3f(-Tw, Th + Tt, Tl);

	glVertex3f(-Tw, Th + Tt, -Tl);
	glVertex3f(-Tw, Th, -Tl);

	glVertex3f(-Tw, Th, Tl);

	//top
	glNormal3f(0, 1, 0);
	glVertex3f(-Tw, Th + Tt, Tl);

	glVertex3f(Tw, Th + Tt, Tl);

	glVertex3f(Tw, Th + Tt, -Tl);

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
	glVertex3f(-Tw + Ls, Th, Tl - Ls);

	glVertex3f(-Tw + Ls, 0.0f, Tl - Ls);

	glVertex3f(-Tw + Ls + Ls, 0.0f, Tl - Ls);

	glVertex3f(-Tw + Ls + Ls, Th, Tl - Ls);
	//back:normal pointing outwards
	glNormal3f(0, 0, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-Tw + Ls, Th, Tl - Ls - Ls);
	glTexCoord2f(0, 1);
	glVertex3f(-Tw + Ls + Ls, Th, Tl - Ls - Ls);

	glVertex3f(-Tw + Ls + Ls, 0.0f, Tl - Ls - Ls);
	glTexCoord2f(1, 0);
	glVertex3f(-Tw + Ls, 0.0f, Tl - Ls - Ls);
	//right: normal pointing outwards
	glNormal3f(1, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-Tw + Ls + Ls, Th, Tl - Ls);

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

	glVertex3f(Tw - Ls - Ls, 0.0f, Tl - Ls);
	glTexCoord2f(1, 0);
	glVertex3f(Tw - Ls, 0.0f, Tl - Ls);

	//back:normals pointing outwards
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 1);
	glVertex3f(Tw - Ls, Th, Tl - Ls - Ls);

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

	glVertex3f(Tw - Ls - Ls, 0.0f, Tl - Ls - Ls);
	glTexCoord2f(1, 0);
	glVertex3f(Tw - Ls - Ls, 0.0f, Tl - Ls);
	//right:normal pointing outwards
	glNormal3f(1, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3f(Tw - Ls, Th, Tl - Ls);

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
	glVertex3f(-Tw + Ls, Th, -Tl + Ls);

	glVertex3f(-Tw + Ls, 0.0f, -Tl + Ls);

	glVertex3f(-Tw + Ls + Ls, 0.0f, -Tl + Ls);

	glVertex3f(-Tw + Ls + Ls, Th, -Tl + Ls);
	//back:normal pointing outwards
	glNormal3f(0, 0, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-Tw + Ls, Th, -Tl + Ls + Ls);
	glTexCoord2f(0, 1);
	glVertex3f(-Tw + Ls + Ls, Th, -Tl + Ls + Ls);

	glVertex3f(-Tw + Ls + Ls, 0.0f, -Tl + Ls + Ls);
	glTexCoord2f(1, 0);
	glVertex3f(-Tw + Ls, 0.0f, -Tl + Ls + Ls);
	//right: normal pointing outwards
	glNormal3f(1, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-Tw + Ls + Ls, Th, -Tl + Ls);

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

	glVertex3f(Tw - Ls - Ls, 0.0f, -Tl + Ls);
	glTexCoord2f(1, 0);
	glVertex3f(Tw - Ls, 0.0f, -Tl + Ls);
	//back:normals pointing outwards
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 1);
	glVertex3f(Tw - Ls, Th, -Tl + Ls + Ls);

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

	glVertex3f(Tw - Ls - Ls, 0.0f, -Tl + Ls + Ls);
	glTexCoord2f(1, 0);
	glVertex3f(Tw - Ls - Ls, 0.0f, -Tl + Ls);
	//right:normal pointing outwards
	glNormal3f(1, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3f(Tw - Ls, Th, -Tl + Ls);

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
	//glColor3f(0.0f, 1.0f, 0.0f);
	GLfloat amb[] = { 0.0f,0.57f,0.0f,1.0f };
	GLfloat diff[] = { 0.4f,1.0f,0.4f,1.0f };
	GLfloat spec[] = { 0.04f,1.0f,0.04f,1.0f };
	GLfloat shine = 18.0f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
	//glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glTranslatef(2.0f, -1.0f, 0.0f);
	glScalef(0.3f, 0.5f, 0.3f);
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);

	glBegin(GL_QUADS);

	//Front
	glNormal3f(0, -1, 0);
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
	glNormal3f(0.0f, -1.0f, 0.0f);

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
	glNormal3f(0, 0, -1);

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
	glNormal3f(0, -1, 0);

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
	glNormal3f(0.0f, -1.0f, -1.0f);

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
	glNormal3f(-1.0f, 0.0f, 0.0f);

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
	////glColor3f(0, 1, 0);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1.8f, 0.2f, -1.8f);
	glVertex3f(1.8f, 0.2f, -1.8f);
	glVertex3f(1.8f, 3.5f, -1.8f);
	glVertex3f(-1.8f, 3.5f, -1.8f);

	//back
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.8f, 0.2f, -2.0f);
	glVertex3f(1.8f, 0.2f, -2.0f);
	glVertex3f(1.8f, 3.5f, -2.0f);
	glVertex3f(-1.8f, 3.5f, -2.0f);


	glNormal3f(-1.0f, 0.0f, 0.0f);
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
	//glutSwapBuffers();
}

void drawChairL()
{
	glPushMatrix();
	////glColor3f(1.0f, 1.0f, 0.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);
	GLfloat amb[] = { 0.0f,0.57f,0.0f,1.0f };
	GLfloat diff[] = { 0.4f,1.0f,0.4f,1.0f };
	GLfloat spec[] = { 0.04f,1.0f,0.04f,1.0f };
	GLfloat shine = 18.0f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
	glTranslatef(-2.0f, -1.0f, 0.0f);
	glScalef(0.3f, 0.5f, 0.3f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);

	//Front
	glNormal3f(0, -1, 0);
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
	glNormal3f(0.0f, -1.0f, 0.0f);

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
	glNormal3f(0, 0, -1);

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
	glNormal3f(0, -1, 0);

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
	glNormal3f(0.0f, -1.0f, -1.0f);

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
	glNormal3f(-1.0f, 0.0f, 0.0f);

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
	////glColor3f(0, 1, 0);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1.8f, 0.2f, -1.8f);
	glVertex3f(1.8f, 0.2f, -1.8f);
	glVertex3f(1.8f, 3.5f, -1.8f);
	glVertex3f(-1.8f, 3.5f, -1.8f);

	//back
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.8f, 0.2f, -2.0f);
	glVertex3f(1.8f, 0.2f, -2.0f);
	glVertex3f(1.8f, 3.5f, -2.0f);
	glVertex3f(-1.8f, 3.5f, -2.0f);


	glNormal3f(-1.0f, 0.0f, 0.0f);
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
void lampHook()
{
	glPushMatrix();
	GLfloat amb[] = { 0.0f,0.0f,0.0f,1.0f };
	GLfloat diff[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat spec[] = { 0.8f,0.79f,0.8f,1.0f };
	GLfloat shine = 100.1f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
	glBegin(GL_QUADS);
	glNormal3f(0,-1,0);
	glVertex3f(0.5f, 10.0f, 0);
	glVertex3f(0, 6.0f, 0);
	glVertex3f(0, 6.0f, 0);
	glVertex3f(-0.5f, 10.0f, 0);
	glEnd();
	glPopMatrix();
}
void drawLamp()
{
	lampHook();
	//lampLight();
	lightDef2();
	glPushMatrix();

	//glColor3f(1.0f, 1.0f, 0.0f);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glTranslatef(0.0f, 6.0f, 0.0f);
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, Lamp_Glow);
	//glDisable(GL_CULL_FACE);
	drawSphere(1.0f);
	GLfloat black[4] = {0, 0, 0, 1}; //reset to default
	glMaterialfv(GL_FRONT, GL_EMISSION, black);
	glPopMatrix();

	glutSwapBuffers();
}

void mate()
{
	GLfloat no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
	//glPushMatrix();
	//glTranslatef(1.25f, 0.0f, 0.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 5.0f);
	//glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	//glPopMatrix();
}

void drawEntireTable()
{
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	GLfloat amb[] = {0.05f, 0.0f, 0.0f, 1.0f};
	GLfloat diff[] = {1.0f, 0.4f, 0.4f, 1.0f};
	GLfloat spec[] = {0.7f, 0.04f, 0.04f, 1.0f};
	GLfloat shine = 5.0f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
	glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
	////glColor3f(1.0, 0.0, 0.0);
	drwatableTop();
	Firstleg();

	secondleg();

	thirdleg();

	fourthleg();
	//glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();
}

void drawWall() //enclosing the walls of the room
{
	glDisable(GL_COLOR_MATERIAL);
	GLfloat amb[] = {0.0f, 0.22f, 0.88f, 1.0f};
	GLfloat diff[] = {0.54f, 0.89f, 0.49f, 1.0f};
	GLfloat spec[] = {0.316228f, 0.32f, 0.316228f, 1.0f};
	GLfloat shine = 90.0f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);

	glBegin(GL_QUADS); //normals pointing outwards
	glNormal3f(0, 1, 0);
	float tl = 30.0f;
	////left

	glVertex3f(-Rs - wll, -2.0f, -Rs);

	glVertex3f(-Rs - wll, -2.0f, Rs);

	glVertex3f(-Rs - wll, Rh, Rs);

	glVertex3f(-Rs - wll, Rh, -Rs);
	////right

	glVertex3f(Rs + wll, -2.0f, Rs);

	glVertex3f(Rs + wll, -2.0f, -Rs);

	glVertex3f(Rs + wll, Rh, -Rs);

	glVertex3f(Rs + wll, Rh, Rs);
	////back

	glVertex3f(-Rs, -2.0f, -Rs);

	glVertex3f(Rs, -2.0f, -Rs);

	glVertex3f(Rs, Rh, -Rs);

	glVertex3f(-Rs, Rh, -Rs);

	glEnd();
	//glEnable(GL_COLOR_MATERIAL);
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
	glDisable(GL_COLOR_MATERIAL);
	float mat_ambient[] = {0.25f, 0.25f, 0.25f, 1.0f};
	float mat_diffuse[] = {0.4f, 0.4f, 0.4f, 1.0f};
	float mat_specular[] = {0.774597f, 0.774597f, 0.774597f, 1.0f};
	float shine = 76.8f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);

	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	////glColor3f(0.40f, 0.40f, 0.10f);
	glVertex3fv(floorVertices[0]);
	glVertex3fv(floorVertices[1]);
	glVertex3fv(floorVertices[2]);
	glVertex3fv(floorVertices[3]);

	glEnd();
	glPushMatrix();
	//glEnable(GL_COLOR_MATERIAL);
}

static void drawcCeiling(void)
{
	glPushMatrix();
	glTranslatef(0.0f, Rh + 2.0f, 0.0f);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, -1);
	GLfloat amb[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat diff[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat spec[] = { 0.8f,0.8f,0.8f,1.0f };
	GLfloat shine = 51.2f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
	//glColor3f(1, 1, 1);
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

	//glShadeModel(GL_SMOOTH);
	//glShadeModel(GL_FLAT);

	//glClearColor(0.0, 0.0, 0.0, 0.0);

	glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT1);

	glShadeModel(GL_SMOOTH);

	glLoadIdentity();
	//mate();
	drawLamp();
	//glLoadIdentity();
	//materialo();
	//lightDef2();


	//default_material_diffuse();

	drawEntireTable();
	drawWall();
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

void on_key(unsigned char c, int x, int y)
{
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
	if (c == '8')
	{
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
	}
}

//ruch obserwatora do przodu, do ty³u

void Klawiatura(unsigned char key, int x, int y)
{
	if (key == '1')
	{
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
	}
	if (key == '0')
	{
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
	}
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
		eyex -= 1.0;
		break;
		// scena w górê
	case GLUT_KEY_UP:
		eyey += 1.0;
		break;
		// scena w prawo
	case GLUT_KEY_RIGHT:
		eyex += 1.0;
		break;
		// scena w dó³
	case GLUT_KEY_DOWN:
		eyey -= 1.0;
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
