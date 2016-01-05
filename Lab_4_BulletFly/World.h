#pragma once
#include "Graphic.h"

class World
{
private:
	GLuint skyBox[6];
	GLuint floor;
	float skySize;
	float worldX, worldY, worldZ;
public:
	World(int _skySize);
	void drawWorld(float _worldX, float _worldY, float _worldZ);
	void drawSky();
	void drawFloor();
};