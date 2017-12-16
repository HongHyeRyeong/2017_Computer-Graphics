#pragma once

#include <GL/glut.h>
#include <Windows.h>
#include <stdio.h>
#include <iostream>

class Menu
{
	GLuint TitleTexture;
public:
	Menu();

	void drawMenu();
	void updateMenu(float elapsedTime);

	GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);
};

