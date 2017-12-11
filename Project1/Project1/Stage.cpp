#include "Stage.h"

Stage::Stage()
{
	for (int i = 0; i < 10; ++i)
		cube[i] = NULL;
}

Stage::Stage(int numStage) : numStage(numStage)
{
	for (int i = 0; i < 10; ++i)
		cube[i] = NULL;

	selectCube = 0;

	saveCube1 = 0;
	saveCube2 = 1;
	saveCube3 = 2;


	if (numStage == 1) {
		numCube = 3;
		timeStage = 60 * 5;	// 5분
		Stage1();
	}
}

Stage::~Stage()
{
	for (int i = 0; i < numCube; ++i)
		delete cube[i];

	delete[] cube;
}

void Stage::drawStage()
{
	// 큐브 그리기 고정
	if (selectCube < numCube)
		cube[selectCube]->drawCube();

	if (cube[saveCube1]->getsave1() == 1)
	{
		cube[saveCube1]->drawCube();
	}
	if (cube[saveCube2]->getsave2() == 1)
	{
		cube[saveCube2]->drawCube();
	}
	if (cube[saveCube3]->getsave3() == 1)
	{
		cube[saveCube3]->drawCube();
	}


	// map 그리기
	glPushMatrix();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.0, 0.5, 1.0, 0.5);
	glTranslatef(-30, 5, 20);

	for (int y = 0; y < 11; ++y) {
		for (int x = 0; x < 11; ++x) {
			for (int z = 0; z < 11; ++z) {
				if (map[y][x][z] == 1)
					glutSolidCube(10);

				glTranslatef(0, 0, -10);
			}
			glTranslatef(10, 0, 110);
		}
		glTranslatef(-110, 10, 0);
	}
	glPopMatrix();
	//
	// 게임 시간
	if (timeStage >= 0) {
		glLoadIdentity();
		int timeM{ (int)timeStage / 60 };
		int timeS{ (int)timeStage - timeM * 60 };
		char string[20];
		std::sprintf(string, "%d min %d second", timeM, timeS);

		glColor3f(1.0, 1.0, 1.0);
		glRasterPos2f(-125, 135);
		for (int i = 0; i < (int)strlen(string); i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
	}

}

void Stage::updateStage(float elapsedTime)
{
	// 충돌체크 추가
	if (cube[saveCube1]->getsave1() == 1)
	{

	}


	// 게임 시간
	if (timeStage <= 0) {
		timeStage = 0;
	}
	else
		timeStage -= elapsedTime / 1000;
}

void Stage::Keyboard(unsigned char key)
{
	if (selectCube < numCube)
		if (cube[selectCube]->getType() == 0)
			cube[selectCube]->Keyboard(key);
}

void Stage::Stage1()
{

	map[1][3][2] = 1;
	map[0][3][2] = 1;
	map[0][3][3] = 1;
	map[0][4][2] = 1;
	map[0][4][1] = 1;
	map[1][4][1] = 1;
	map[0][2][1] = 1;
	map[0][2][2] = 1;
	map[0][2][3] = 1;
	map[0][3][1] = 1;
	map[1][2][3] = 1;



	for (int i = 0; i < numCube; ++i)
		cube[i] = new Cube(1, i);
}