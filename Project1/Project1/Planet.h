#pragma once

#include <GL/glut.h>
#include <Windows.h>
#include <stdio.h>

class Planet
{
	int DayEarth, DayMars;
	int Time;
	float angle;
	GLuint planetTexture[7];
public:
	Planet();

	void drawPlanet();
	void drawEarth();
	void drawSun();
	void drawPlanet1();  // �伺
	void drawPlanet2();  // �ؿռ�
	void drawPlanet3();  // ��
	void drawPlanet4();  // �ݼ�

	void updatePlanet();

	GLubyte* LoadDIBitmap(const char *filename, BITMAPINFO **info);
};