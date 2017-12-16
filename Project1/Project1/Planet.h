#pragma once

#include <GL/glut.h>
#include <Windows.h>
#include <stdio.h>

class Planet
{
	int DayEarth, DayMars;
	int Time;
	GLuint planetTexture[5];
public:
	Planet();

	void drawPlanet();
	void drawEarth();
	void drawSun();
	void drawPlanet1();
	void drawPlanet2();
	void updatePlanet();

	GLubyte* LoadDIBitmap(const char *filename, BITMAPINFO **info);
};

