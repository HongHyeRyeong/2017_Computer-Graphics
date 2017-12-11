#pragma once

#include <GL/glut.h>
#include <Windows.h>
#include <stdio.h>
#include <iostream>

class Cube
{
	int numStage, numCube;
	int type;				// 0: ����, 1: ����
	int cube[11][11][11];	// y, x, z��
	int centerCube[3];		// ȸ�� �߽��� �Ǵ� ť�� ��ġ
	GLuint cubeTexture;
public:
	Cube() {};
	Cube(int numStage, int numCube);

	void drawCube();
	void updateCube();
	void Keyboard(unsigned char key);
	void moveCube(unsigned char key);
	void rotateCube(unsigned char key);

	void Stage1();

	int getType() { return type; }
	void setType(int num) { type = num; }
	GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);
};

