#include <windows.h>

#include "Dependencies/freeglut/freeglut.h"


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


float min = 0.0f;
float max = 1.0f;
float wll = 0.01f;

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
	glVertex3f(1.4f, -3.0f, 1.6f);
	glVertex3f(1.8f, -3.0f, 1.6f);

	//back
	glNormal3f(0.0f, 0.0f, -1.0f);

	glVertex3f(1.8f, -0.2f, 1.2f);
	glVertex3f(1.4f, -0.2f, 1.2f);
	glVertex3f(1.4f, -3.0f, 1.2f);
	glVertex3f(1.8f, -3.0f, 1.2f);

	//right
	glNormal3f(1.0f, 0.0f, 0.0f);

	glVertex3f(1.8f, -0.2f, 1.6f);
	glVertex3f(1.8f, -0.2f, 1.2f);
	glVertex3f(1.8f, -3.0f, 1.2f);
	glVertex3f(1.8f, -3.0f, 1.6f);

	//left
	glNormal3f(-1.0f, 0.0f, 0.0f);

	glVertex3f(1.4f, -0.2f, 1.6f);
	glVertex3f(1.4f, -0.2f, 1.2f);
	glVertex3f(1.4f, -3.0f, 1.2f);
	glVertex3f(1.4f, -3.0f, 1.6f);

	//back leg back
	//front
	glNormal3f(0.0f, 0.0f, -1.0f);

	glVertex3f(1.8f, -0.2f, -1.2f);
	glVertex3f(1.4f, -0.2f, -1.2f);
	glVertex3f(1.4f, -3.0f, -1.2f);
	glVertex3f(1.8f, -3.0f, -1.2f);

	//back
	glNormal3f(0.0f, 0.0f, -1.0f);

	glVertex3f(1.8f, -0.2f, -1.6f);
	glVertex3f(1.4f, -0.2f, -1.6f);
	glVertex3f(1.4f, -3.0f, -1.6f);
	glVertex3f(1.8f, -3.0f, -1.6f);

	//right
	glNormal3f(1.0f, 0.0f, 0.0f);

	glVertex3f(1.8f, -0.2f, -1.6f);
	glVertex3f(1.8f, -0.2f, -1.2f);
	glVertex3f(1.8f, -3.0f, -1.2f);
	glVertex3f(1.8f, -3.0f, -1.6f);

	//left
	glNormal3f(1.0f, 0.0f, 0.0f);

	glVertex3f(1.4f, -0.2f, -1.6f);
	glVertex3f(1.4f, -0.2f, -1.2f);
	glVertex3f(1.4f, -3.0f, -1.2f);
	glVertex3f(1.4f, -3.0f, -1.6f);

	//leg left front
	glNormal3f(0.0f, 0.0f, 1.0f);

	glVertex3f(-1.8f, -0.2f, 1.6f);
	glVertex3f(-1.4f, -0.2f, 1.6f);
	glVertex3f(-1.4f, -3.0f, 1.6f);
	glVertex3f(-1.8f, -3.0f, 1.6f);

	//back
	glNormal3f(0.0f, 0.0f, -1.0f);

	glVertex3f(-1.8f, -0.2f, 1.2f);
	glVertex3f(-1.4f, -0.2f, 1.2f);
	glVertex3f(-1.4f, -3.0f, 1.2f);
	glVertex3f(-1.8f, -3.0f, 1.2f);

	//right
	glNormal3f(1.0f, 0.0f, 0.0f);

	glVertex3f(-1.8f, -0.2f, 1.6f);
	glVertex3f(-1.8f, -0.2f, 1.2f);
	glVertex3f(-1.8f, -3.0f, 1.2f);
	glVertex3f(-1.8f, -3.0f, 1.6f);

	//left
	glNormal3f(-1.0f, 0.0f, 0.0f);

	glVertex3f(-1.4f, -0.2f, 1.6f);
	glVertex3f(-1.4f, -0.2f, 1.2f);
	glVertex3f(-1.4f, -3.0f, 1.2f);
	glVertex3f(-1.4f, -3.0f, 1.6f);

	//left leg back front

	//front
	glNormal3f(0.0f, 0.0f, -1.0f);

	glVertex3f(-1.8f, -0.2f, -1.2f);
	glVertex3f(-1.4f, -0.2f, -1.2f);
	glVertex3f(-1.4f, -3.0f, -1.2f);
	glVertex3f(-1.8f, -3.0f, -1.2f);

	//back
	glNormal3f(0.0f, 0.0f, -1.0f);

	glVertex3f(-1.8f, -0.2f, -1.6f);
	glVertex3f(-1.4f, -0.2f, -1.6f);
	glVertex3f(-1.4f, -3.0f, -1.6f);
	glVertex3f(-1.8f, -3.0f, -1.6f);

	//right
	glNormal3f(1.0f, 0.0f, 0.0f);

	glVertex3f(-1.8f, -0.2f, -1.6f);
	glVertex3f(-1.8f, -0.2f, -1.2f);
	glVertex3f(-1.8f, -3.0f, -1.2f);
	glVertex3f(-1.8f, -3.0f, -1.6f);

	//left
	glNormal3f(-1.0f, 0.0f, 0.0f);

	glVertex3f(-1.4f, -0.2f, -1.6f);
	glVertex3f(-1.4f, -0.2f, -1.2f);
	glVertex3f(-1.4f, -3.0f, -1.2f);
	glVertex3f(-1.4f, -3.0f, -1.6f);

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
	glVertex3f(1.4f, -3.0f, 1.6f);
	glVertex3f(1.8f, -3.0f, 1.6f);

	//back
	glNormal3f(0.0f, 0.0f, -1.0f);

	glVertex3f(1.8f, -0.2f, 1.2f);
	glVertex3f(1.4f, -0.2f, 1.2f);
	glVertex3f(1.4f, -3.0f, 1.2f);
	glVertex3f(1.8f, -3.0f, 1.2f);

	//right
	glNormal3f(1.0f, 0.0f, 0.0f);

	glVertex3f(1.8f, -0.2f, 1.6f);
	glVertex3f(1.8f, -0.2f, 1.2f);
	glVertex3f(1.8f, -3.0f, 1.2f);
	glVertex3f(1.8f, -3.0f, 1.6f);

	//left
	glNormal3f(-1.0f, 0.0f, 0.0f);

	glVertex3f(1.4f, -0.2f, 1.6f);
	glVertex3f(1.4f, -0.2f, 1.2f);
	glVertex3f(1.4f, -3.0f, 1.2f);
	glVertex3f(1.4f, -3.0f, 1.6f);

	//back leg back
	//front
	glNormal3f(0.0f, 0.0f, -1.0f);

	glVertex3f(1.8f, -0.2f, -1.2f);
	glVertex3f(1.4f, -0.2f, -1.2f);
	glVertex3f(1.4f, -3.0f, -1.2f);
	glVertex3f(1.8f, -3.0f, -1.2f);

	//back
	glNormal3f(0.0f, 0.0f, -1.0f);

	glVertex3f(1.8f, -0.2f, -1.6f);
	glVertex3f(1.4f, -0.2f, -1.6f);
	glVertex3f(1.4f, -3.0f, -1.6f);
	glVertex3f(1.8f, -3.0f, -1.6f);

	//right
	glNormal3f(1.0f, 0.0f, 0.0f);

	glVertex3f(1.8f, -0.2f, -1.6f);
	glVertex3f(1.8f, -0.2f, -1.2f);
	glVertex3f(1.8f, -3.0f, -1.2f);
	glVertex3f(1.8f, -3.0f, -1.6f);

	//left
	glNormal3f(1.0f, 0.0f, 0.0f);

	glVertex3f(1.4f, -0.2f, -1.6f);
	glVertex3f(1.4f, -0.2f, -1.2f);
	glVertex3f(1.4f, -3.0f, -1.2f);
	glVertex3f(1.4f, -3.0f, -1.6f);

	//leg left front
	glNormal3f(0.0f, 0.0f, 1.0f);

	glVertex3f(-1.8f, -0.2f, 1.6f);
	glVertex3f(-1.4f, -0.2f, 1.6f);
	glVertex3f(-1.4f, -3.0f, 1.6f);
	glVertex3f(-1.8f, -3.0f, 1.6f);

	//back
	glNormal3f(0.0f, 0.0f, -1.0f);

	glVertex3f(-1.8f, -0.2f, 1.2f);
	glVertex3f(-1.4f, -0.2f, 1.2f);
	glVertex3f(-1.4f, -3.0f, 1.2f);
	glVertex3f(-1.8f, -3.0f, 1.2f);

	//right
	glNormal3f(1.0f, 0.0f, 0.0f);

	glVertex3f(-1.8f, -0.2f, 1.6f);
	glVertex3f(-1.8f, -0.2f, 1.2f);
	glVertex3f(-1.8f, -3.0f, 1.2f);
	glVertex3f(-1.8f, -3.0f, 1.6f);

	//left
	glNormal3f(-1.0f, 0.0f, 0.0f);

	glVertex3f(-1.4f, -0.2f, 1.6f);
	glVertex3f(-1.4f, -0.2f, 1.2f);
	glVertex3f(-1.4f, -3.0f, 1.2f);
	glVertex3f(-1.4f, -3.0f, 1.6f);

	//left leg back front

	//front
	glNormal3f(0.0f, 0.0f, -1.0f);

	glVertex3f(-1.8f, -0.2f, -1.2f);
	glVertex3f(-1.4f, -0.2f, -1.2f);
	glVertex3f(-1.4f, -3.0f, -1.2f);
	glVertex3f(-1.8f, -3.0f, -1.2f);

	//back
	glNormal3f(0.0f, 0.0f, -1.0f);

	glVertex3f(-1.8f, -0.2f, -1.6f);
	glVertex3f(-1.4f, -0.2f, -1.6f);
	glVertex3f(-1.4f, -3.0f, -1.6f);
	glVertex3f(-1.8f, -3.0f, -1.6f);

	//right
	glNormal3f(1.0f, 0.0f, 0.0f);

	glVertex3f(-1.8f, -0.2f, -1.6f);
	glVertex3f(-1.8f, -0.2f, -1.2f);
	glVertex3f(-1.8f, -3.0f, -1.2f);
	glVertex3f(-1.8f, -3.0f, -1.6f);

	//left
	glNormal3f(-1.0f, 0.0f, 0.0f);

	glVertex3f(-1.4f, -0.2f, -1.6f);
	glVertex3f(-1.4f, -0.2f, -1.2f);
	glVertex3f(-1.4f, -3.0f, -1.2f);
	glVertex3f(-1.4f, -3.0f, -1.6f);

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
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //"czyszczenie" t³a okan i bufora g³êbokosci
	glEnable(GL_DEPTH_TEST); //w³¹cznie algorytmu zas³aniania
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80.0, 1.0, 0.1, 50.0); //bry³a widzenia perspektywicznego
	gluLookAt(eyex, eyey, eyez, 0.0, 0.0, -50.0, 0.0, 1.0, 0.0); //obserwator 1
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	drawWall();

	drawEntireTable();
	drawChairR();
	drawChairL();
	drawFloor();
	drawcCeiling();
	//drawChair(1.0, 1.0, 1.0);
	/*prostopadloscian(-12.0, 4.0, 2.0, 10.0, 2.0, -6.0);
	prostopadloscian(-4.0, -6.0, 2.0, 2.0, 12.0, -6.0);
	prostopadloscian(-8.0, -6.0, 2.0, 6.0, 2.0, -6.0);
	skos(-12.0, -6.0, 2.0, 4.0, 2.0, 4.0, -6.0);
	prostopadloscian(2.0, -6.0, 2.0, 2.0, 12.0, -6.0);
	skos(12.0, 0.0, 2.0, -6.0, -2.0, 6.0, -6.0);
	skos(12.0, 0.0, 2.0, -6.0, -2.0, -6.0, -6.0);
	*/

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
