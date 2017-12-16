#pragma once

#include <GL/glut.h>
#include <Windows.h>
#include <stdio.h>
#include <iostream>

class Cube
{
	int numStage, numCube;
	int type;				// 0: 움직, 1: 고정
	int cube[11][11][11];	// y, x, z순
	int centerCube[3];		// 회전 중심이 되는 큐브 위치
	GLuint cubeTexture;
public:
	Cube() {};
	Cube(int numStage, int numCube);

	void drawCube();
	void updateCube();
	void Keyboard(unsigned char key);
	void moveCube(unsigned char key);
	void rotateCube(unsigned char key);

	int getType() { return type; }
	void setType(int num) { type = num; }
	int getCube(int y, int x, int z) { return cube[y][x][z]; }

	void Stage1();
	void Stage2();
	void Stage3();
	void Stage4();
	void Stage5();
	void Stage6();
	void Stage7();
	void Stage8();
	
	GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);
};

