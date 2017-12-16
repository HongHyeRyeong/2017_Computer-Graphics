#include "Stage.h"

Stage::Stage()
{
	for (int i = 0; i < 10; ++i)
		cube[i] = NULL;

	for (int y = 0; y < 11; ++y)
		for (int x = 0; x < 11; ++x)
			for (int z = 0; z < 11; ++z)
				map[y][x][z] = 0;

	GLubyte *pBytes;
	BITMAPINFO *info;

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
	glGenTextures(3, cubeTexture);

	glBindTexture(GL_TEXTURE_2D, cubeTexture[0]);
	pBytes = LoadDIBitmap("./Resource/map.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 118, 118, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, cubeTexture[1]);
	pBytes = LoadDIBitmap("./Resource/cube.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 118, 118, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, cubeTexture[2]);
	pBytes = LoadDIBitmap("./Resource/map2.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 118, 118, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
}

Stage::Stage(int numStage) : numStage(numStage)
{
	for (int i = 0; i < 10; ++i)
		cube[i] = NULL;
	for (int y = 0; y < 11; ++y)
		for (int x = 0; x < 11; ++x)
			for (int z = 0; z < 11; ++z)
				map[y][x][z] = 0;
	
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
	if (selectCube < numCube&&cube[selectCube]->getType() == 0)
		cube[selectCube]->drawCube();

	// map 그리기
	glPushMatrix();
	glTranslatef(-50, 5, 50);

	for (int y = 0; y < 11; ++y) {
		for (int x = 0; x < 11; ++x) {
			for (int z = 0; z < 11; ++z) {
				if (map[y][x][z] == 1) {
					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glColor4f(1.0, 1.0, 1.0, 0.5);
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, cubeTexture[0]);
					drawCube();
					glDisable(GL_TEXTURE_2D);
					glDisable(GL_BLEND);
				}
				else if (map[y][x][z] == 2) {
					glColor3f(1.0, 1.0, 1.0);
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, cubeTexture[1]);
					drawCube();
					glDisable(GL_TEXTURE_2D);
				}
				else if (map[y][x][z] == 3) {
					glColor3f(1.0, 1.0, 1.0);
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, cubeTexture[2]);
					drawCube();
					glDisable(GL_TEXTURE_2D);
				}

				glTranslatef(0, 0, -10);
			}
			glTranslatef(10, 0, 110);
		}
		glTranslatef(-110, 10, 0);
	}
	glPopMatrix();

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
	int num = cubetotalnum;
	for (int y = 0; y < 11; ++y) {
		for (int x = 0; x < 11; ++x) {
			for (int z = 0; z < 11; ++z) {

				if (map[y][x][z] == 3) // 제한 된 틀에 큐브가 있을 때
				{
					//PlaySound(TEXT(SOUND_FILE_NAME_CLEAR), NULL, SND_SYNC); // 일단 소리로 클리어 처리
					num--;
				}
			}
	
		}
	}
	if (num == 0 )
	{
		std::cout << " ok ";
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

	if (key == 'r') {
		int cnt[4]{ 0 };

		for (int y = 0; y < 11; ++y)
			for (int x = 0; x < 11; ++x)
				for (int z = 0; z < 11; ++z)
					if (cube[selectCube]->getCube(y, x, z) == 1) {
						if (map[y][x][z] == 0)
							cnt[0]++;
						else if (map[y][x][z] == 1)
							cnt[1]++;
						else if (map[y][x][z] == 2)
							cnt[2]++;
						else if (map[y][x][z] == 3)
							cnt[3]++;
					}

		int sum{ 0 };
		for (int i = 0; i < 4; ++i)
			sum += cnt[i];

		if (sum == cnt[0]) {
			setCubeType(1);

			for (int y = 0; y < 11; ++y)
				for (int x = 0; x < 11; ++x)
					for (int z = 0; z < 11; ++z)
						if (cube[selectCube]->getCube(y, x, z) == 1) {
							if (map[y][x][z] == 0)
								map[y][x][z] = 2;
						}
		}
		else if (sum == cnt[1]) {
			setCubeType(1);

			for (int y = 0; y < 11; ++y)
				for (int x = 0; x < 11; ++x)
					for (int z = 0; z < 11; ++z)
						if (cube[selectCube]->getCube(y, x, z) == 1) {
							if (map[y][x][z] == 1)
								map[y][x][z] = 3;
						}
		}
	}
	else if (key == 't') {
		setCubeType(0);

		for (int y = 0; y < 11; ++y)
			for (int x = 0; x < 11; ++x)
				for (int z = 0; z < 11; ++z)
					if (cube[selectCube]->getCube(y, x, z) == 1) {
						if (map[y][x][z] == 2)
							map[y][x][z] = 0;
						else if (map[y][x][z] == 3)
							map[y][x][z] = 1;
					}
	}
}

void Stage::Stage1()
{
	map[1][5][5] = 1;
	map[0][5][5] = 1;
	map[0][5][6] = 1;
	map[0][6][5] = 1;
	map[0][6][4] = 1;
	map[1][6][4] = 1;
	map[0][4][4] = 1;
	map[0][4][5] = 1;
	map[0][4][6] = 1;
	map[0][5][4] = 1;
	map[1][4][6] = 1;

	cubetotalnum = 11;

	for (int i = 0; i < numCube; ++i)
		cube[i] = new Cube(1, i);
}

void  Stage::drawCube()
{
	GLfloat vec[8][3]{
		{ -5, 5, 5 },{ 5, 5, 5 },{ 5, 5, -5 },{ -5, 5, -5 },
	{ -5, -5, 5 },{ -5, -5, -5 },{ 5, -5, -5 },{ 5, -5, 5 }
	};

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3fv(vec[2]);
	glTexCoord2f(1, 0);
	glVertex3fv(vec[3]);
	glTexCoord2f(1, 1);
	glVertex3fv(vec[0]);
	glTexCoord2f(0, 1);
	glVertex3fv(vec[1]);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3fv(vec[4]);
	glTexCoord2f(1, 0);
	glVertex3fv(vec[7]);
	glTexCoord2f(1, 1);
	glVertex3fv(vec[6]);
	glTexCoord2f(0, 1);
	glVertex3fv(vec[5]);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3fv(vec[5]);
	glTexCoord2f(1, 0);
	glVertex3fv(vec[6]);
	glTexCoord2f(1, 1);
	glVertex3fv(vec[2]);
	glTexCoord2f(0, 1);
	glVertex3fv(vec[3]);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3fv(vec[7]);
	glTexCoord2f(1, 0);
	glVertex3fv(vec[4]);
	glTexCoord2f(1, 1);
	glVertex3fv(vec[0]);
	glTexCoord2f(0, 1);
	glVertex3fv(vec[1]);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3fv(vec[4]);
	glTexCoord2f(1, 0);
	glVertex3fv(vec[5]);
	glTexCoord2f(1, 1);
	glVertex3fv(vec[3]);
	glTexCoord2f(0, 1);
	glVertex3fv(vec[0]);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3fv(vec[6]);
	glTexCoord2f(1, 0);
	glVertex3fv(vec[7]);
	glTexCoord2f(1, 1);
	glVertex3fv(vec[1]);
	glTexCoord2f(0, 1);
	glVertex3fv(vec[2]);
	glEnd();
}

GLubyte* Stage::LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;

	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;

	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}

	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}

	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);

	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}

	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
		(*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);

	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}