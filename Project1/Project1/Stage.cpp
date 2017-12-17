#include "Stage.h"

Stage::Stage()
{
}

Stage::Stage(int numStage) : numStage(numStage)
{
	for (int i = 0; i < 10; ++i)
		cube[i] = NULL;

	for (int y = 0; y < 11; ++y)
		for (int x = 0; x < 11; ++x)
			for (int z = 0; z < 11; ++z)
				map[y][x][z] = 0;

	stageType = 0;
	selectCube = 0;
	cubetotalnum = 0;

	clearUp = 0;
	clearY = 0;

	// bgm
	MCI_OPEN_PARMS m_mciOpenParms;
	MCI_PLAY_PARMS m_mciPlayParms;
	DWORD m_dwDeviceID;
	MCI_OPEN_PARMS mciOpen;
	MCI_PLAY_PARMS mciPlay;

	mciOpen.lpstrElementName = "./sound/bgm.wav";
	mciOpen.lpstrDeviceType = "waveaudio";
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);

	int dwID = mciOpen.wDeviceID;

	mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&m_mciPlayParms);

	// texture
	GLubyte *pBytes;
	BITMAPINFO *info;

	glDisable(GL_LIGHTING);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
	glGenTextures(4, mapTexture);

	glBindTexture(GL_TEXTURE_2D, mapTexture[0]);
	pBytes = LoadDIBitmap("./Resource/map.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 118, 118, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, mapTexture[1]);
	pBytes = LoadDIBitmap("./Resource/map3.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 118, 118, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, mapTexture[2]);
	pBytes = LoadDIBitmap("./Resource/gameover.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1000, 750, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, mapTexture[3]);
	pBytes = LoadDIBitmap("./Resource/gameclear.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1000, 750, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	if (numStage == 1)
		Stage1();
	else if (numStage == 2)
		Stage2();
	else if (numStage == 3)
		Stage3();
	else if (numStage == 4)
		Stage4();
	else if (numStage == 5)
		Stage5();
	else if (numStage == 6)
		Stage6();
	else if (numStage == 7)
		Stage7();
	else if (numStage == 8)
		Stage8();
}

Stage::~Stage()
{
	for (int i = 0; i < numCube; ++i)
		delete cube[i];

	delete[] cube;
}

void Stage::drawStage()
{
	if (stageType == 0 || stageType == 2)
		drawGamePlay();
	else if (stageType == 1)
		drawGameOver();
	else if (stageType == 2)
		drawGameClear();
}

void Stage::updateStage(float elapsedTime)
{
	if (stageType == 0) {
		int num = cubetotalnum;
		for (int y = 0; y < 11; ++y)
			for (int x = 0; x < 11; ++x)
				for (int z = 0; z < 11; ++z)
					if (map[y][x][z] == 3)
						num--;

		if (num == 0)
		{
			stageType = 2;
			PlaySound(TEXT(SOUND_FILE_NAME_CLEAR), NULL, SND_ASYNC | SND_ALIAS);
		}

		// 게임 시간
		if (timeStage <= 0) {
			timeStage = 0;
			stageType = 1;
			PlaySound(TEXT(SOUND_FILE_NAME_GAME_OVER), NULL, SND_ASYNC | SND_ALIAS);
		}
		else
			timeStage -= elapsedTime / 1000;
	}
	else if (stageType == 2) {
		if (clearY == 0) {
			if (clearUp >= 30)
				clearY = -1;
			else
				clearUp += 2;
		}
		else {
			if (clearUp >= 30)
				clearY = -1;
			else if (clearUp <= 20)
				clearY = 1;

			clearUp += clearY;
		}
	}
}

void Stage::Keyboard(unsigned char key)
{
	if (selectCube < numCube)
		if (cube[selectCube]->getType() == 0)
			cube[selectCube]->Keyboard(key);

	if (key == 'r') {
		int cnt[5]{ 0 };

		for (int y = 0; y < 11; ++y)
			for (int x = 0; x < 11; ++x)
				for (int z = 0; z < 11; ++z) {
					if (cube[selectCube]->getCube(y, x, z) == 1) {
						if (map[y][x][z] == 0)
							cnt[0]++;
						else if (map[y][x][z] == 1)
							cnt[1]++;
						else if (map[y][x][z] == 2)
							cnt[2]++;
						else if (map[y][x][z] == 3)
							cnt[3]++;
						else if (map[y][x][z] == 4)
							cnt[4]++;
					}
				}
	

		int sum{ 0 };
		for (int i = 0; i < 5; ++i)
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

void Stage::drawGamePlay()
{
	// 큐브 그리기 고정
	if (selectCube < numCube&&stageType == 0)
		cube[selectCube]->drawCube();

	// map 그리기
	glPushMatrix();
	glTranslatef(-50, 5 + clearUp, 50);

	for (int y = 0; y < 11; ++y) {
		for (int x = 0; x < 11; ++x) {
			for (int z = 0; z < 11; ++z) {
				if (map[y][x][z] == 1) {
					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glColor4f(0.8, 0.8, 0.8, 0.5);
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, mapTexture[0]);
					drawCube();
					glDisable(GL_TEXTURE_2D);
					glDisable(GL_BLEND);
				}
				else if (map[y][x][z] == 2) {
					glColor3f(1.0, 1.0, 1.0);
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, mapTexture[1]);
					drawCube();
					glDisable(GL_TEXTURE_2D);
				}
				else if (map[y][x][z] == 3) {
					glColor3f(1.0, 1.0, 1.0);
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, mapTexture[0]);
					drawCube();
					glDisable(GL_TEXTURE_2D);
				}
				else if (map[y][x][z] == 4) {
					glColor3f(0.6, 0.6, 0.6);
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, mapTexture[0]);
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
		glRasterPos2f(-110, 120);
		for (int i = 0; i < (int)strlen(string); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

void Stage::drawGameOver()
{
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mapTexture[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-135, -115, 0);
	glTexCoord2f(1, 0);
	glVertex3f(133, -115, 0);
	glTexCoord2f(1, 1);
	glVertex3f(133, 155, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-135, 155, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void Stage::drawGameClear()
{
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mapTexture[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-135, -115, 0);
	glTexCoord2f(1, 0);
	glVertex3f(133, -115, 0);
	glTexCoord2f(1, 1);
	glVertex3f(133, 155, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-135, 155, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
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

	numCube = 3;
	timeStage = 60 * 3;
	
	for (int y = 0; y < 11; ++y)
		for (int x = 0; x < 11; ++x)
			for (int z = 0; z < 11; ++z)
				if (map[y][x][z] == 1)
					cubetotalnum++;

	for (int i = 0; i < numCube; ++i)
		cube[i] = new Cube(1, i);
}

void Stage::Stage2()
{
	map[0][4][5] = 1;
	map[0][5][4] = 1;
	map[0][5][5] = 1;
	map[0][5][6] = 1;
	map[0][6][4] = 1;
	map[0][6][5] = 1;
	map[0][6][6] = 1;
	map[0][7][5] = 1;
	map[1][4][5] = 1;
	map[1][7][5] = 1;
	map[2][2][5] = 1;
	map[2][3][5] = 1;
	map[2][4][5] = 1;
	map[3][3][5] = 1;
	map[3][4][5] = 1;

	numCube = 4;
	timeStage = 60 * 3;

	for (int y = 0; y < 11; ++y)
		for (int x = 0; x < 11; ++x)
			for (int z = 0; z < 11; ++z)
				if (map[y][x][z] == 1)
					cubetotalnum++;

	for (int i = 0; i < numCube; ++i)
		cube[i] = new Cube(2, i);
}


void Stage::Stage3()
{
	map[0][4][4] = 1;
	map[0][4][5] = 1;
	map[1][4][5] = 1;
	map[2][4][5] = 1;
	map[0][5][5] = 1;
	map[0][5][6] = 1;
	map[0][5][6] = 1;
	map[1][5][6] = 1;
	map[0][4][6] = 1;

	numCube = 2;
	timeStage = 60 * 4;

	for (int y = 0; y < 11; ++y)
		for (int x = 0; x < 11; ++x)
			for (int z = 0; z < 11; ++z)
				if (map[y][x][z] == 1)
					cubetotalnum++;

	for (int i = 0; i < numCube; ++i)
		cube[i] = new Cube(3, i);
}

void Stage::Stage4()
{
	map[0][4][5] = 1;
	map[0][5][5] = 1;
	map[1][4][5] = 1;
	map[2][4][5] = 1;
	map[0][5][4] = 1;
	map[1][5][4] = 1;
	map[1][5][5] = 1;
	map[1][5][6] = 1;
	map[0][5][6] = 1;
	map[0][6][5] = 1;
	map[1][6][5] = 1;
	map[2][6][5] = 1;
	map[2][5][5] = 1;

	numCube = 3;
	timeStage = 60 * 4;

	for (int y = 0; y < 11; ++y)
		for (int x = 0; x < 11; ++x)
			for (int z = 0; z < 11; ++z)
				if (map[y][x][z] == 1)
					cubetotalnum++;

	for (int i = 0; i < numCube; ++i)
		cube[i] = new Cube(4, i);
}


void Stage::Stage5()
{
	map[0][4][3] = 1;
	map[0][5][3] = 1;
	map[0][6][3] = 1;
	map[0][7][3] = 1;
	map[0][7][4] = 1;
	map[0][7][5] = 1;
	map[0][7][6] = 1;
	map[0][6][6] = 1;
	map[0][5][6] = 1;
	map[0][4][4] = 1;
	map[0][4][5] = 1;
	map[0][5][4] = 1;
	map[0][3][4] = 1;
	map[1][3][4] = 1;
	map[1][4][4] = 1;
	map[1][5][4] = 1;

	numCube = 4;
	timeStage = 60 * 5;

	for (int y = 0; y < 11; ++y)
		for (int x = 0; x < 11; ++x)
			for (int z = 0; z < 11; ++z)
				if (map[y][x][z] == 1)
					cubetotalnum++;

	for (int i = 0; i < numCube; ++i)
		cube[i] = new Cube(5, i);
}


void Stage::Stage6()
{
	map[0][5][4] = 1;
	map[1][5][4] = 1;
	map[0][6][4] = 1;
	map[0][6][5] = 1;
	map[0][5][5] = 1;
	map[0][5][6] = 1;
	map[1][5][6] = 1;
	map[2][5][6] = 1;
	map[2][6][6] = 1;
	map[0][6][6] = 1;
	map[1][6][6] = 1;

	numCube = 3;
	timeStage = 60 * 5;

	for (int y = 0; y < 11; ++y)
		for (int x = 0; x < 11; ++x)
			for (int z = 0; z < 11; ++z)
				if (map[y][x][z] == 1)
					cubetotalnum++;

	for (int i = 0; i < numCube; ++i)
		cube[i] = new Cube(6, i);
}

void Stage::Stage7()
{
	map[0][3][5] = 4;
	map[0][4][4] = 1;
	map[0][4][5] = 1;
	map[0][5][4] = 1;
	map[0][5][5] = 1;
	map[0][5][6] = 1;
	map[0][6][6] = 4;
	map[1][5][6] = 1;

	numCube = 2;
	timeStage = 60 * 5;

	for (int y = 0; y < 11; ++y)
		for (int x = 0; x < 11; ++x)
			for (int z = 0; z < 11; ++z)
				if (map[y][x][z] == 1)
					cubetotalnum++;

	for (int i = 0; i < numCube; ++i)
		cube[i] = new Cube(7, i);
}

void Stage::Stage8()
{
	map[0][4][4] = 4;
	map[0][4][5] = 1;
	map[0][4][6] = 4;
	map[0][5][4] = 1;
	map[0][5][5] = 4;
	map[0][5][6] = 1;
	map[0][6][4] = 4;
	map[0][6][5] = 1;
	map[0][6][6] = 4;
	map[1][4][4] = 1;
	map[1][4][5] = 1;
	map[1][4][6] = 1;
	map[1][5][4] = 1;
	map[1][5][5] = 1;
	map[1][5][6] = 1;
	map[1][6][4] = 1;
	map[1][6][5] = 1;
	map[1][6][6] = 1;

	numCube = 4;
	timeStage = 60 * 5;

	for (int y = 0; y < 11; ++y)
		for (int x = 0; x < 11; ++x)
			for (int z = 0; z < 11; ++z)
				if (map[y][x][z] == 1)
					cubetotalnum++;

	for (int i = 0; i < numCube; ++i)
		cube[i] = new Cube(8, i);
}