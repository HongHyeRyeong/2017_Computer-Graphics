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
	int map[11][11][11];	// 0일때 empty, 1일때 기본 제한, 2일때 틀 아닌 곳 고정, 3일때 틀 인곳 고정

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

