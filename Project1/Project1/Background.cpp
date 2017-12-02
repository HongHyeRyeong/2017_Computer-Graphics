#include "Background.h"

Background::Background()
{
	planet = new Planet();
	activeGrid = false;
}

Background::~Background()
{
	delete planet;
}

void Background::drawBackground()
{
	// Floor
	glPushMatrix();
	glTranslatef(0, 0, -60);
	for (int i = 0; i < 11; ++i) {
		glTranslatef(-60, 0, 10);
		for (int k = 0; k < 11; ++k) {
			glTranslatef(10, 0, 0);
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_QUADS);
			glVertex3f(-5.0, 0.0, -5.0);
			glVertex3f(-5.0, 0.0, 5.0);
			glVertex3f(5.0, 0.0, 5.0);
			glVertex3f(5.0, 0.0, -5.0);
			glEnd();

			glTranslatef(0, 0.2, 0);
			glColor3f(0.0, 0.0, 0.0);
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
	// 아래 주석 풀면 Planet이 그려짐
	//planet->drawPlanet();
}

void Background::updateBackground()
{
	planet->updatePlanet();
}