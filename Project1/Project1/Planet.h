#pragma once

#include <GL/glut.h> 

class Planet
{
	int DayEarth, DayMars;
	int Time;
public:
	Planet();
	~Planet();

	void drawPlanet();
	void drawEarth();
	void drawSun();
	void drawPlanet1();
	void drawPlanet2();
	void updatePlanet();
};

