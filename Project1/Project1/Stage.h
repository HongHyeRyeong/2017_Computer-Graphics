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
	int stageType;
	int numStage, numCube, cubetotalnum;
	int selectCube;
	int map[11][11][11];	// 0일때 empty, 1일때 기본 제한, 2일때 틀 아닌 곳 고정, 3일때 틀 인곳 고정

	Cube* cube[10];
	float timeStage;
	GLuint mapTexture[4];
public:
	Stage();
	Stage(int numStage);
	~Stage();

	void drawStage();
	void drawGamePlay();
	void drawGameOver();
	void drawGameClear();
	void drawCube();
	void updateStage(float elapsedTime);
	void Keyboard(unsigned char key);

	int getNumCube() { return numCube; }
	int getStageType() { return stageType; }
	void setSelectCube(int num) { selectCube = num; }
	void setCubeType(int num) { cube[selectCube]->setType(num); }

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

