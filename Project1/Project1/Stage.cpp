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

	if (numStage == 1) {
		numCube = 3;
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

	if (selectCube < numCube)
		cube[selectCube]->drawCube();

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

}


void Stage::updateStage()
{
	// 충돌체크 추가

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