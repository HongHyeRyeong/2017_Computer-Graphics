#include "Planet.h"

Planet::Planet()
{
	DayEarth = 0;
	DayMars = 0;
	Time = 0;
}

Planet::~Planet()
{
}

void Planet::drawPlanet()
{
	drawEarth();
	drawSun();
	drawPlanet1();
	drawPlanet2();
}

void Planet::drawEarth()
{
	glPushMatrix();

	glColor3f(0.0f, 0.0f, 1.0f);   // �Ķ�
	glRotatef((GLfloat)DayEarth, 0, 1, 0);
	glTranslatef(45, 0, 0);        // ���� ������
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
	glutSolidSphere(10, 15, 15);   // ����

	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);      // ���
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
	glTranslatef(20, 0, 0);        // �����κ��� ������ �Ÿ�
	glutSolidSphere(4, 15, 15);    // ��
	glPopMatrix();


	glPopMatrix();
}

void Planet::drawSun()
{
	glPushMatrix();
	glColor3f(1.0, 0.2, 0.2);
	glTranslatef(0, 0, 0);        // ���� ������
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
	glutSolidSphere(30, 30, 30);    // �¾�
	glPopMatrix();
}

void Planet::drawPlanet1()
{
	glPushMatrix();

	glRotatef(15, 1.0, 0.0, 0.0);    // ����
	glTranslatef(-100, 0, 0);        // ��ġ

	glPushMatrix();
	glColor3f(1.0, 0.7, 0.0);
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);  // ����
	glutSolidSphere(20, 30, 30);     // �༺

	glColor3f(1.0f, 0.6f, 0.0f);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(2, 30, 10, 50); // �༺ �䷯��
	glutSolidTorus(1, 35, 10, 50);
	glPopMatrix();

	glPopMatrix();
}

void Planet::drawPlanet2()
{
	glPushMatrix();

	glColor3f(0.0, 0.5, 1.0);       // �ϴû�
	glTranslatef(100, 0, 0);        // ��ġ
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);  // ����

	glutSolidSphere(15, 30, 30);    // �༺


	glPopMatrix();
}

void Planet::updatePlanet()
{
	DayEarth = (DayEarth + 10) % 360; // ����
	Time = (Time + 20) % 360; // ����
}