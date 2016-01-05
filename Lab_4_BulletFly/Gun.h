#pragma once
#include "Graphic.h"

class Gun
{
private:
	struct Point {
		float x, y, z;
	} position;
	GLUquadric *gunBody;
	GLUquadric *gunTop;
	GLUquadric *gunWheels;
	GLuint gunTexture;
	GLuint wheelTexture;
	GLuint cylinderTexture;
	float gunAngle;
	float rollAngle;
	float power;
	bool shot;

public:
	Gun(float gunX, float gunY, float gunZ);
	void drawGun();
	void applyMovement();
	bool isShot();
	void setShot(bool _shot);
	float getPower();
	float getAngle();
};