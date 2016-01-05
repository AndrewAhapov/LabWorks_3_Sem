#pragma once
#include "Graphic.h"
#include "Gun.h"

class Bullet
{
private:
	struct Point {
		float x, y, z;
	} position, forces;
	GLuint sphereTexture;
	GLUquadric *sphere;
	float rotation, way; 
	bool inFly, collision;
public:
	Bullet(float _bulletX, float _bulletY, float _bulletZ);
	void drawBullet();
	void applyPhysic(Gun &gun);
};