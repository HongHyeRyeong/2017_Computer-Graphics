#pragma once

#include <GL/glut.h>
#include "Planet.h"

class Background
{
	Planet* planet;
	bool activeGrid;
public:
	Background();
	~Background();

	void drawBackground();
	void updateBackground(float elapsedTime);

	void setGrid(bool b) { activeGrid = b; }
};

