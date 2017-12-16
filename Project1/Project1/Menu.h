#pragma once

#include <GL/glut.h>
#include <Windows.h>
#include <stdio.h>
#include <iostream>

class Menu
{
	int totalStage;
	int selectStage;
	GLuint TitleTexture;
public:
	Menu();

	void drawMenu();
	void updateMenu(float elapsedTime);

	GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);
};

