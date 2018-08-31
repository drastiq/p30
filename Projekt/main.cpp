#include <windows.h>
#include <vector>
#include "vector"
#include "Dependencies/freeglut/freeglut.h"
#include <cmath>
#define M_PI 3.14159265358979323846
//clasa wektora dla ulatwienia normalizacji sfery
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
GLdouble eyey = 4.0;
GLdouble eyez = 25.0;
GLfloat Rs = 15.0f; //size of room
GLfloat Tw = 2.0f; // width of table top from centre
GLfloat Tl = 3.0f; //length of table top from centre
GLfloat Th = 1.7f; //height of table top from centre
GLfloat Tt = 0.3f; //thickness of table top
GLfloat Ls = 0.3f; //size of table leg
GLfloat Rh = 10.0f; //height of room
GLfloat ChP = 2.5f;
GLfloat Lamp_Glow[] = {1, 1, 0.0};
bool lightLamp = false;
bool lightLampSpot = false;
GLfloat min = 0.0f;
GLfloat max = 1.0f;
GLfloat wll = 0.01f;

//metoda pomocnicza dla prostopodlascianu
void prostopadloscian(GLfloat x, GLfloat y, GLfloat z, GLfloat dx, GLfloat dy, GLfloat dz)
{
	glBegin(GL_QUADS);

	//gora,
	glVertex3f(x, y + dy, z);
	glVertex3f(x + dx, y + dy, z);
	glVertex3f(x + dx, y + dy, z + dz);
	glVertex3f(x, y + dy, z + dz);

	//dol,
	glVertex3f(x, y, z);
	glVertex3f(x + dx, y, z);
	glVertex3f(x + dx, y, z + dz);
	glVertex3f(x, y, z + dz);

	//prawa,
	glVertex3f(x + dx, y, z);
	glVertex3f(x + dx, y, z + dz);
	glVertex3f(x + dx, y + dy, z + dz);
	glVertex3f(x + dx, y + dy, z);

	//lewa, 
	glVertex3f(x, y, z);
	glVertex3f(x, y, z + dz);
	glVertex3f(x, y + dy, z + dz);
	glVertex3f(x, y + dy, z);

	//przod, 
	glVertex3f(x, y, z);
	glVertex3f(x + dx, y, z);
	glVertex3f(x + dx, y + dy, z);
	glVertex3f(x, y + dy, z);

	//tyl,
	glVertex3f(x, y, z + dz);
	glVertex3f(x + dx, y, z + dz);
	glVertex3f(x + dx, y + dy, z + dz);
	glVertex3f(x, y + dy, z + dz);

	glEnd();
}

//swiatlo spot na inicjaly
void lampLight()
{
	if (lightLampSpot)
	{
		GLfloat position[] = {0.0, 6.0f, 0.0, 1.0};
		GLfloat direction[] = {0.0, 0.0, -3.0};
		GLfloat redlow[] = {0.8, 0.7, 0.0};
		glLightfv(GL_LIGHT1, GL_DIFFUSE, redlow);
		glLightfv(GL_LIGHT1, GL_POSITION, position);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
	}
}

//swiatlo lampy z ambient
void lightDef2()
{
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);


	GLfloat ambientLight[] = {0.55f, 0.5f, 0.3f, 1.0f};

	GLfloat diffuseLight[] = {0.55f, 0.5f, 0.3f, 1.0f};

	GLfloat specularLight[] = {0.8f, 0.8f, 0.5f, 1.0f};


	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	GLfloat qaLightPosition[] = {0.0, 6.0f, 0.0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
}

//rysowanie blatu stolu
void drwatableTop()
{
	glPushMatrix(); // 1 set where to start the current object transformation

	glTranslatef(0.0f, -2.0f, 0.0f); // move downwards to lie on the floor


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
//pierwsza noga stó³
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

	glVertex3f(-Tw + Ls, Th, Tl - Ls - Ls);

	glVertex3f(-Tw + Ls + Ls, Th, Tl - Ls - Ls);

	glVertex3f(-Tw + Ls + Ls, 0.0f, Tl - Ls - Ls);

	glVertex3f(-Tw + Ls, 0.0f, Tl - Ls - Ls);
	//right: normal pointing outwards
	glNormal3f(1, 0, 0);

	glVertex3f(-Tw + Ls + Ls, Th, Tl - Ls);

	glVertex3f(-Tw + Ls + Ls, 0.0f, Tl - Ls);

	glVertex3f(-Tw + Ls + Ls, 0.0f, Tl - Ls - Ls);

	glVertex3f(-Tw + Ls + Ls, Th, Tl - Ls - Ls);
	//left:normal pointing outwards
	glNormal3f(-1, 0, 0);

	glVertex3f(-Tw + Ls, Th, Tl - Ls);

	glVertex3f(-Tw + Ls, Th, Tl - Ls - Ls);

	glVertex3f(-Tw + Ls, 0.0f, Tl - Ls - Ls);

	glVertex3f(-Tw + Ls, 0.0f, Tl - Ls);

	glEnd();
	glPopMatrix();
}
//drug noga stó³
void secondleg()
{
	glPushMatrix(); // 1 set where to start the current object transformation
	glTranslatef(0.0f, -2.0f, 0.0f); // move downwards to lie on the floor

	glBegin(GL_QUADS);
	//front:Normals pointing outwards
	glNormal3f(0, 0, 1);

	glVertex3f(Tw - Ls, Th, Tl - Ls);

	glVertex3f(Tw - Ls - Ls, Th, Tl - Ls);

	glVertex3f(Tw - Ls - Ls, 0.0f, Tl - Ls);

	glVertex3f(Tw - Ls, 0.0f, Tl - Ls);

	//back:normals pointing outwards
	glNormal3f(0, 0, -1);

	glVertex3f(Tw - Ls, Th, Tl - Ls - Ls);

	glVertex3f(Tw - Ls, 0.0f, Tl - Ls - Ls);

	glVertex3f(Tw - Ls - Ls, 0.0f, Tl - Ls - Ls);

	glVertex3f(Tw - Ls - Ls, Th, Tl - Ls - Ls);
	//left:normal pointing outwards
	glNormal3f(-1, 0, 0);

	glVertex3f(Tw - Ls - Ls, Th, Tl - Ls);

	glVertex3f(Tw - Ls - Ls, Th, Tl - Ls - Ls);

	glVertex3f(Tw - Ls - Ls, 0.0f, Tl - Ls - Ls);

	glVertex3f(Tw - Ls - Ls, 0.0f, Tl - Ls);
	//right:normal pointing outwards
	glNormal3f(1, 0, 0);

	glVertex3f(Tw - Ls, Th, Tl - Ls);

	glVertex3f(Tw - Ls, 0.0f, Tl - Ls);

	glVertex3f(Tw - Ls, 0.0f, Tl - Ls - Ls);

	glVertex3f(Tw - Ls, Th, Tl - Ls - Ls);
	glEnd();
	glPopMatrix();
}
//trzecia noga stó³
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

	glVertex3f(-Tw + Ls, Th, -Tl + Ls + Ls);

	glVertex3f(-Tw + Ls + Ls, Th, -Tl + Ls + Ls);

	glVertex3f(-Tw + Ls + Ls, 0.0f, -Tl + Ls + Ls);

	glVertex3f(-Tw + Ls, 0.0f, -Tl + Ls + Ls);
	//right: normal pointing outwards
	glNormal3f(1, 0, 0);

	glVertex3f(-Tw + Ls + Ls, Th, -Tl + Ls);

	glVertex3f(-Tw + Ls + Ls, 0.0f, -Tl + Ls);

	glVertex3f(-Tw + Ls + Ls, 0.0f, -Tl + Ls + Ls);

	glVertex3f(-Tw + Ls + Ls, Th, -Tl + Ls + Ls);
	//left:normal pointing outwards
	glNormal3f(-1, 0, 0);

	glVertex3f(-Tw + Ls, Th, -Tl + Ls);

	glVertex3f(-Tw + Ls, Th, -Tl + Ls + Ls);

	glVertex3f(-Tw + Ls, 0.0f, -Tl + Ls + Ls);

	glVertex3f(-Tw + Ls, 0.0f, -Tl + Ls);
	glEnd();
	glPopMatrix();
}
//czwarta noga stó³
void fourthleg()
{
	glPushMatrix(); // 1 set where to start the current object transformation
	glTranslatef(0.0f, -2.0f, 0.0f); // move downwards to lie on the floor

	glBegin(GL_QUADS);
	//front:Normals pointing outwards
	glNormal3f(0, 0, 1);

	glVertex3f(Tw - Ls, Th, -Tl + Ls);

	glVertex3f(Tw - Ls - Ls, Th, -Tl + Ls);

	glVertex3f(Tw - Ls - Ls, 0.0f, -Tl + Ls);

	glVertex3f(Tw - Ls, 0.0f, -Tl + Ls);
	//back:normals pointing outwards
	glNormal3f(0, 0, -1);

	glVertex3f(Tw - Ls, Th, -Tl + Ls + Ls);

	glVertex3f(Tw - Ls, 0.0f, -Tl + Ls + Ls);

	glVertex3f(Tw - Ls - Ls, 0.0f, -Tl + Ls + Ls);

	glVertex3f(Tw - Ls - Ls, Th, -Tl + Ls + Ls);
	//left:normal pointing outwards
	glNormal3f(-1, 0, 0);

	glVertex3f(Tw - Ls - Ls, Th, -Tl + Ls);

	glVertex3f(Tw - Ls - Ls, Th, -Tl + Ls + Ls);

	glVertex3f(Tw - Ls - Ls, 0.0f, -Tl + Ls + Ls);

	glVertex3f(Tw - Ls - Ls, 0.0f, -Tl + Ls);
	//right:normal pointing outwards
	glNormal3f(1, 0, 0);

	glVertex3f(Tw - Ls, Th, -Tl + Ls);

	glVertex3f(Tw - Ls, 0.0f, -Tl + Ls);

	glVertex3f(Tw - Ls, 0.0f, -Tl + Ls + Ls);

	glVertex3f(Tw - Ls, Th, -Tl + Ls + Ls);
	glEnd();
	glPopMatrix();
}
//krzeslo prawe
void drawChairR()
{
	glPushMatrix();
	//glColor3f(0.0f, 1.0f, 0.0f);
	GLfloat amb[] = {0.0f, 0.57f, 0.0f, 1.0f};
	GLfloat diff[] = {0.4f, 1.0f, 0.4f, 1.0f};
	GLfloat spec[] = {0.04f, 1.0f, 0.04f, 1.0f};
	GLfloat shine = 18.0f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);

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
//krzeslo lewe
void drawChairL()
{
	glPushMatrix();
	GLfloat amb[] = {0.0f, 0.57f, 0.0f, 1.0f};
	GLfloat diff[] = {0.4f, 1.0f, 0.4f, 1.0f};
	GLfloat spec[] = {0.04f, 1.0f, 0.04f, 1.0f};
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
//rysowanie sfery
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
//rysowanie zaczep lampy
void lampHook()
{
	glPushMatrix();
	GLfloat amb[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat diff[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat spec[] = {0.8f, 0.79f, 0.8f, 1.0f};
	GLfloat shine = 100.1f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	glVertex3f(0.5f, 10.0f, 0);
	glVertex3f(0, 6.0f, 0);
	glVertex3f(0, 6.0f, 0);
	glVertex3f(-0.5f, 10.0f, 0);
	glEnd();
	glPopMatrix();
}
//rysowanie lampa+zaczep+swiatlo
void drawLamp()
{
	lampHook();
	if (lightLamp)
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Lamp_Glow);
		lightDef2();
	}
	else
	{
		GLfloat black[4] = {0, 0, 0, 1};
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
	}
	lightDef2();
	glPushMatrix();
	glTranslatef(0.0f, 6.0f, 0.0f);
	drawSphere(1.0f);
	GLfloat black[4] = {0, 0, 0, 1};
	glMaterialfv(GL_FRONT, GL_EMISSION, black);
	glPopMatrix();
	glutSwapBuffers();
}
//rysowanie ca³y stó³
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
	drwatableTop();
	Firstleg();
	secondleg();
	thirdleg();
	fourthleg();
	glPopMatrix();
}
//rysowanie scian
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
	GLfloat tl = 30.0f;
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
//rysowanie okrêgu
void drawCircle
(float angle, float length, float radius, float width, unsigned int samples )
{
	if (samples < 3) samples = 3;
	const float outer = radius + width;
	glPushMatrix();
	glBegin(GL_QUAD_STRIP);
	for (unsigned int i = 0; i <= samples; ++i)
	{
		float a = angle + (i / (float)samples) * length;
		glVertex3f(radius * cos(a), radius * sin(a), 0);
		glVertex3f(outer * cos(a), outer * sin(a), 0);
	}

	glEnd();
	glPopMatrix();
}
//wieszcho³ki podlogi
static GLfloat floorVertices[4][3] = {
	{-Rs, -2.0f, Rs},
	{Rs, -2.0f, Rs},
	{Rs, -2.0f, -Rs},
	{-Rs, -2.0f, -Rs},
};
//rysowanie podlgi
static void drawFloor(void)
{
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	GLfloat mat_ambient[] = {0.25f, 0.25f, 0.25f, 1.0f};
	GLfloat mat_diffuse[] = {0.4f, 0.4f, 0.4f, 1.0f};
	GLfloat mat_specular[] = {0.774597f, 0.774597f, 0.774597f, 1.0f};
	GLfloat shine = 76.8f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);

	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3fv(floorVertices[0]);
	glVertex3fv(floorVertices[1]);
	glVertex3fv(floorVertices[2]);
	glVertex3fv(floorVertices[3]);

	glEnd();
	glPushMatrix();
}
//rysowanie sufitu(podloga+translate y)
static void drawcCeiling(void)
{
	glPushMatrix();
	glTranslatef(0.0f, Rh + 2.0f, 0.0f);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, -1);
	GLfloat amb[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat diff[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat spec[] = {0.8f, 0.8f, 0.8f, 1.0f};
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

//rysowanie litery S (dwie po³ówki okrêgu +translate na y)
void drawS()
{
	glPushMatrix();

	drawCircle(1.5707963268, M_PI, 2, 1, 30);
	glTranslatef(0, -5, 0);

	drawCircle(-1.5707963268, M_PI, 2, 1, 30);

	glPopMatrix();
}
//rysowanie  litery P (po³owa okrêgu + prosta)
void drawP()
{
	glPushMatrix();
	glTranslatef(-6, 0, 0);
	drawCircle(-1.5707963268, M_PI, 2, 1, 30);
	prostopadloscian(0, -6, 0, 0.8f, 8, 0);
	glPopMatrix();
	glEnd();
}
//rysowanie ramki z inicja³ami 
void drawPS()
{
	glPushMatrix();
	GLfloat amb0[] = {0.8f, 0.8f, 0.8f, 1.0f};
	GLfloat diff0[] = {0.8f, 0.8f, 0.8f, 1.0f};
	GLfloat spec0[] = {0.8f, 0.8f, 0.8f, 1.0f};
	GLfloat shine0 = 100.2f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec0);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine0);
	glNormal3f(0, 0, 1);
	prostopadloscian(-4, 0.1, -Rs + 0.1f, 6.0, 4.5, -Rs + 0.1f);
	glTranslatef(0.0f, 2.0f, -Rs + 0.2f);
	glScalef(0.2f, 0.3f, 0.0f);

	GLfloat amb[] = {0.1745f, 0.01175f, 0.01175f, 1.0f};
	GLfloat diff[] = {0.61424f, 0.04136f, 0.04136f, 1.0f};
	GLfloat spec[] = {0.727811f, 0.626959f, 0.626959f, 1.0f};

	GLfloat shine = 25.0f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
	glNormal3f(0, 0, 1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-20.0f, 0.0f, 0.0f, 1.0f);
	glTranslatef(-0.6f, 3.2f, -Rs + 0.2f);
	glScalef(0.4, 0.38, 1);
	drawS();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5f, 3.0f, -Rs + 0.2f);
	glScalef(0.5, 0.45, 1);
	drawP();


	//glEnd();
	glPopMatrix();
}
//funkcja wyœwietlania
void display()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //"czyszczenie" t³a okan i bufora g³êbokosci
	glEnable(GL_DEPTH_TEST); //w³¹cznie algorytmu zas³aniania
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 0.1, 50.0); //bry³a widzenia perspektywicznego
	gluLookAt(eyex, eyey, eyez, 0.0, 0.0, -50.0, 0.0, 1.0, 0.0); //obserwator 1
	glMatrixMode(GL_MODELVIEW);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glLoadIdentity();
	lampLight();
	drawLamp();
	drawPS();
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
//funkcja klawiatury (1-w³acz swiat³o lampy,0 wy³acz œwiat³o,2-w³acz œwiat³o spotlight na inicja³y,3-wy³acz swiat³o spotlight)
void Klawiatura(unsigned char key, int x, int y)
{
	if (key == '1')
	{
		lightLamp = true;
		glEnable(GL_LIGHT0);
	}
	if (key == '0')
	{
		lightLamp = false;
		glDisable(GL_LIGHT0);
	}
	if (key == '2')
	{
		lightLampSpot = true;

		glEnable(GL_LIGHT1);
	}
	if (key == '3')
	{
		lightLampSpot = false;

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
		eyex -= 0.5;
		break;
		// scena w górê
	case GLUT_KEY_UP:
		eyey += 0.5;
		break;
		// scena w prawo
	case GLUT_KEY_RIGHT:
		eyex += 0.3;
		break;
		// scena w dó³
	case GLUT_KEY_DOWN:
		eyey -= 0.3;
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
	glutCreateWindow("Projekt");
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
