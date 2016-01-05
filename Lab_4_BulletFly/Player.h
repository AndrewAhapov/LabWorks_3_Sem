#pragma once
#include "Graphic.h"
class Player
{
private:
	struct Point {
		float x, y, z;
	} playerPosition, viewPoint, viewAngle;
	float speed;
	float angleX, angleY;
public:
	Player(float playerX, float playerY, float playerZ);
	void setPosition(float posDx, float posDy, float posDz);
	void setViewPoint();
	void show();
	void applyShift();
	void applyRotate(RenderWindow &window);
	float* getPosition();
};

