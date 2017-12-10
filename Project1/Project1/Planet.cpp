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

	glColor3f(0.0f, 0.0f, 1.0f);   // 파랑
	glRotatef((GLfloat)DayEarth, 0, 1, 0);
	glTranslatef(45, 0, 0);        // 도는 반지름
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
	glutSolidSphere(10, 15, 15);   // 지구

	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);      // 노랑
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
	glTranslatef(20, 0, 0);        // 지구로부터 떨어진 거리
	glutSolidSphere(4, 15, 15);    // 달
	glPopMatrix();


	glPopMatrix();
}

void Planet::drawSun()
{
	glPushMatrix();
	glColor3f(1.0, 0.2, 0.2);
	glTranslatef(0, 0, 0);        // 도는 반지름
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
	glutSolidSphere(30, 30, 30);    // 태양
	glPopMatrix();
}

void Planet::drawPlanet1()
{
	glPushMatrix();

	glRotatef(15, 1.0, 0.0, 0.0);    // 기울기
	glTranslatef(-100, 0, 0);        // 위치

	glPushMatrix();
	glColor3f(1.0, 0.7, 0.0);
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);  // 자전
	glutSolidSphere(20, 30, 30);     // 행성

	glColor3f(1.0f, 0.6f, 0.0f);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(2, 30, 10, 50); // 행성 토러스
	glutSolidTorus(1, 35, 10, 50);
	glPopMatrix();

	glPopMatrix();
}

void Planet::drawPlanet2()
{
	glPushMatrix();

	glColor3f(0.0, 0.5, 1.0);       // 하늘색
	glTranslatef(100, 0, 0);        // 위치
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);  // 자전

	glutSolidSphere(15, 30, 30);    // 행성


	glPopMatrix();
}

void Planet::updatePlanet()
{
	DayEarth = (DayEarth + 10) % 360; // 공전
	Time = (Time + 20) % 360; // 자전
}