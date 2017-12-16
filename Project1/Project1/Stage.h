#pragma once
#pragma comment(lib,"winmm")

#include <GL/glut.h>
#include <iostream>
#include "Cube.h"
#include<mmsystem.h>

#define SOUND_FILE_NAME_BGM    "    "
#define SOUND_FILE_NAME_CUBE   "./sound/cube.wav "
#define SOUND_FILE_NAME_CLEAR   "./sound/clear.wav"
#define SOUND_FILE_NAME_GAME_OVER   "./sound/gameover.wav"

class Stage
{
	int numStage, numCube;
	int selectCube;
	int saveCube1,saveCube2,saveCube3;
	int map[11][11][11];	// 0�϶� empty, 1�϶� �⺻ ����, 2�϶� Ʋ �ƴ� �� ����, 3�϶� Ʋ �ΰ� ����

	int cubetotalnum;
	int next;
	int title;

	Cube* cube[10];
	float timeStage;
	GLuint mapTexture[2];
public:
	Stage();
	Stage(int numStage);
	~Stage();

	void drawStage();
	void drawCube();
	void updateStage(float elapsedTime);
	void Keyboard(unsigned char key);

	void Stage1();

	int getNumCube() { return numCube; }
	void setSelectCube(int num) { selectCube = num; }
	void setCubeType(int num) { cube[selectCube]->setType(num); }

	GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);
};

