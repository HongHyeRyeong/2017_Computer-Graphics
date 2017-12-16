#pragma once

#include <GL/glut.h>
#include <Windows.h>
#include <stdio.h>
#include "Planet.h"

class Background
{
	Planet* planet; 
	bool activeGrid;

	GLuint skyboxTexture[6];
	int skyboxSize;
public:
	Background();
	~Background();

	void drawBackground();
	void drawSkybox();
	void updateBackground(float elapsedTime);

	void setGrid(bool b) { activeGrid = b; }
	GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);
};

