#include "Background.h"

Background::Background()
{
	planet = new Planet();
	activeGrid = false;
	skyboxSize = 2048;

	GLubyte *pBytes;
	BITMAPINFO *info;

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
	glGenTextures(6, skyboxTexture);

	glBindTexture(GL_TEXTURE_2D, skyboxTexture[0]);
	pBytes = LoadDIBitmap("./Resource/SkyboxY-.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 2048, 2048, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, skyboxTexture[1]);
	pBytes = LoadDIBitmap("./Resource/SkyboxY+.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 2048, 2048, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, skyboxTexture[2]);
	pBytes = LoadDIBitmap("./Resource/SkyboxZ-.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 2048, 2048, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, skyboxTexture[3]);
	pBytes = LoadDIBitmap("./Resource/SkyboxZ+.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 2048, 2048, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, skyboxTexture[4]);
	pBytes = LoadDIBitmap("./Resource/SkyboxX+.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 2048, 2048, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, skyboxTexture[5]);
	pBytes = LoadDIBitmap("./Resource/SkyboxX-.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 2048, 2048, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
}

Background::~Background()
{
	delete planet;
}

void Background::drawBackground()
{
	drawSkybox();

	// Floor
	glPushMatrix();
	glTranslatef(0, 0, -60);
	for (int i = 0; i < 11; ++i) {
		glTranslatef(-60, 0, 10);
		for (int k = 0; k < 11; ++k) {
			glTranslatef(10, 0, 0);
			glColor3f(0.9, 0.9, 0.9);
			glBegin(GL_QUADS);
			glVertex3f(-5.0, 0.0, -5.0);
			glVertex3f(-5.0, 0.0, 5.0);
			glVertex3f(5.0, 0.0, 5.0);
			glVertex3f(5.0, 0.0, -5.0);
			glEnd();

			glTranslatef(0, 0.2, 0);
			glColor3f(0.2, 0.2, 0.2);
			glBegin(GL_LINE_LOOP);
			glVertex3f(-5.0, 0.0, -5.0);
			glVertex3f(-5.0, 0.0, 5.0);
			glVertex3f(5.0, 0.0, 5.0);
			glVertex3f(5.0, 0.0, -5.0);
			glEnd();
			glTranslatef(0, -0.2, 0);
		}
		glTranslatef(-50, 0, 0);
	}
	glPopMatrix();

	// Grid
	if (activeGrid)
	{
		glColor3f(0.8, 0.8, 0.8);

		for (int i = 1; i < 6; ++i) {
			glPushMatrix();
			if(i==1)
				glTranslatef(0, 110, 0);
			else if (i == 2) {
				glRotatef(90.0, 1.0f, 0.0f, 0.0f);
				glTranslatef(0, 55, -55);
			}
			else if (i == 3) {
				glRotatef(90.0, 1.0f, 0.0f, 0.0f);
				glTranslatef(0, -55, -55);
			}
			else if (i == 4) {
				glRotatef(90.0, 0.0f, 0.0f, 1.0f);
				glTranslatef(55, 55, 0);
			}
			else if (i == 5) {
				glRotatef(90.0, 0.0f, 0.0f, 1.0f);
				glTranslatef(55, -55, 0);
			}

			glTranslatef(0, 0, -60);
			for (int i = 0; i < 11; ++i) {
				glTranslatef(-60, 0, 10);
				for (int k = 0; k < 11; ++k) {
					glTranslatef(10, 0, 0);
					glBegin(GL_LINE_LOOP);
					glVertex3f(-5.0, 0.0, -5.0);
					glVertex3f(-5.0, 0.0, 5.0);
					glVertex3f(5.0, 0.0, 5.0);
					glVertex3f(5.0, 0.0, -5.0);
					glEnd();
				}
				glTranslatef(-50, 0, 0);
			}
			glPopMatrix();
		}
	}

	// Planet
	planet->drawPlanet();
}

void Background::updateBackground(float elapsedTime)
{
	planet->updatePlanet();
}

void Background::drawSkybox()
{
	GLfloat vec[8][3]{
		{ -skyboxSize, skyboxSize, skyboxSize },{ skyboxSize, skyboxSize, skyboxSize },
	{ skyboxSize, skyboxSize, -skyboxSize },{ -skyboxSize, skyboxSize, -skyboxSize },
	{ -skyboxSize, -skyboxSize, skyboxSize },{ -skyboxSize, -skyboxSize, -skyboxSize },
	{ skyboxSize, -skyboxSize, -skyboxSize },{ skyboxSize, -skyboxSize, skyboxSize }
	};

	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	// 위
	glBindTexture(GL_TEXTURE_2D, skyboxTexture[0]);
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

	// 아래
	glBindTexture(GL_TEXTURE_2D, skyboxTexture[1]);
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

	// 앞
	glBindTexture(GL_TEXTURE_2D, skyboxTexture[2]);
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

	// 뒤
	glBindTexture(GL_TEXTURE_2D, skyboxTexture[3]);
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

	// 왼
	glBindTexture(GL_TEXTURE_2D, skyboxTexture[4]);
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

	// 오
	glBindTexture(GL_TEXTURE_2D, skyboxTexture[5]);
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
	glDisable(GL_TEXTURE_2D);
}

GLubyte* Background::LoadDIBitmap(const char *filename, BITMAPINFO **info)
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