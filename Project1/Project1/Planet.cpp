#include "Planet.h"

Planet::Planet()
{
	DayEarth = 0;
	DayMars = 0;
	Time = 0;

	GLubyte *pBytes;
	BITMAPINFO *info;

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
	glGenTextures(4, planetTexture);

	glBindTexture(GL_TEXTURE_2D, planetTexture[0]);
	pBytes = LoadDIBitmap("./Resource/planet1.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 304, 320, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, planetTexture[1]);
	pBytes = LoadDIBitmap("./Resource/planet2.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 300, 321, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, planetTexture[2]);
	pBytes = LoadDIBitmap("./Resource/planet3.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 332, 342, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, planetTexture[3]);
	pBytes = LoadDIBitmap("./Resource/planet4.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 300, 300, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, planetTexture[4]);
	pBytes = LoadDIBitmap("./Resource/planet5.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 300, 300, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
}

void Planet::drawPlanet()
{
	drawEarth();
	drawSun();
	drawPlanet1();
	drawPlanet2();
}

void Planet::drawEarth()
{
	glPushMatrix();
	glTranslatef(-70, 0, -60);

	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	glBindTexture(GL_TEXTURE_2D, planetTexture[0]);
	glRotatef((GLfloat)DayEarth, 0, 1, 0); 
	glTranslatef(30, 80, 0);     
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0); 
	glutSolidSphere(7, 15, 15); 

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, planetTexture[1]);
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
	glTranslatef(10, 0, 0);     
	glutSolidSphere(3, 15, 15); 
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void Planet::drawSun()
{
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	glBindTexture(GL_TEXTURE_2D, planetTexture[2]);
	glTranslatef(-70, 80, -60);
	glRotatef((GLfloat)Time, 1.0, 0.0, 0.0);
	glutSolidSphere(20, 30, 30);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void Planet::drawPlanet1()
{
	glPushMatrix();

	glTranslatef(30, 40, -150);        // 위치

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	glBindTexture(GL_TEXTURE_2D, planetTexture[3]);
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);  // 자전  y축회전
	glutSolidSphere(15, 30, 30);     // 행성

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);

	glColor3f(1.0f, 0.6f, 0.0f);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(2, 25, 10, 50); // 행성 토러스
	glutSolidTorus(1, 30, 10, 50);
	glPopMatrix();

	glPopMatrix();
}

void Planet::drawPlanet2()
{
	glPushMatrix();

	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	glBindTexture(GL_TEXTURE_2D, planetTexture[4]);
	glTranslatef(100, 80, -120);
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);

	glutSolidSphere(15, 30, 30);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void Planet::updatePlanet()
{
	DayEarth = (DayEarth + 10) % 360; // 공전
	Time = (Time + 5) % 360; // 자전
}

GLubyte* Planet::LoadDIBitmap(const char *filename, BITMAPINFO **info)
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