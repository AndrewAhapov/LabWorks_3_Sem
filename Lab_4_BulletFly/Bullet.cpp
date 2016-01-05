#include "Bullet.h"

#define GL_CLAMP_TO_EDGE 0x812F
#define G 9.81

GLuint LoadBulletTexture(String name)
{
	Image image;
	if (!image.loadFromFile(name))
		return EXIT_FAILURE;
	image.flipVertically();
	GLuint texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.getSize().x, image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return texture;
}



void Bullet::drawBullet() {
	glBindTexture(GL_TEXTURE_2D, sphereTexture);
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, 1);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotation, inFly, 0, collision);
	gluSphere(sphere, 20, 20, 20);
	glRotatef(-rotation, inFly, 0, collision);
	glTranslatef(-position.x, -position.y, -position.z);
}

void Bullet::applyPhysic(Gun &gun) {
	if(!collision && !gun.isShot()) {
		forces.y = gun.getPower()*sinf(-gun.getAngle() /180 * PI);
		forces.x = gun.getPower()*cosf(-gun.getAngle() / 180 * PI);
	}
	//check collision
	if (position.y < 0)
		collision = true;
	//before leave the gun
	if (way>190)
		forces.y -= G / 7;
	//while flying
	if (!collision && gun.isShot()) {
		way += sqrt(forces.x / 7 * forces.x / 7 + forces.y / 7 * forces.y / 7);
		position.x += forces.x / 7;
		position.y += forces.y / 7;
	}
	//after hitting ground
	else if (collision) {
		position.y = 0;
		gun.setShot(false);
		forces.x *= 0.99;
		rotation = (forces.x / 1.7) * 180 / PI;
		position.x += forces.x / 7;
		way += forces.x / 7;
	}
	//stop
	if (position.y == 0 && abs(forces.x)<0.5) {
		float power = sqrt(forces.x / 7 * forces.x / 7 + forces.y / 7 * forces.y / 7);
		forces.x = 0;
		forces.y = power*sinf(-gun.getAngle());
		forces.x = power*cosf(-gun.getAngle());
		way = 0;
		collision = false;
		gun.setShot(false);

	}
}

Bullet::Bullet(float _bulletX, float _bulletY, float _bulletZ)
{
	sphere = gluNewQuadric();
	sphereTexture = LoadBulletTexture("resources/gun1.jpg");
	position.x = _bulletX;
	position.y = _bulletY;
	position.z = _bulletZ;

	forces.x = 0.0;
	forces.y = 0.0;
	forces.z = 0.0;

	rotation = 0.0;
	way = 0.0;
	collision = false; 
	inFly = false;
}

