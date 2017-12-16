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
	void drawPlanet1();  // 配己
	void drawPlanet2();  // 秦空己
	void drawPlanet3();  // 格己
	void drawPlanet4();  // 陛己

	void updatePlanet();

	GLubyte* LoadDIBitmap(const char *filename, BITMAPINFO **info);
};