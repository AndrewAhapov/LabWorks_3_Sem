#include "Gun.h"
#define GL_CLAMP_TO_EDGE 0x812F

GLuint LoadGunTexture(String name)
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

void Gun::drawGun() {
	glTranslatef(position.x, position.y, position.z);
	glRotatef(90, 0.0f, 1.0f, 0.0f);
	//gun's wheels
	glBindTexture(GL_TEXTURE_2D, wheelTexture);
	gluQuadricDrawStyle(gunWheels, GLU_FILL);
	gluQuadricTexture(gunWheels, 1);
	gluQuadricNormals(gunWheels, GLU_SMOOTH);
	glRotatef(rollAngle, 1.0f, 0.0f, 0.0f);
	glTranslatef(25, 0, 0);
	glRotatef(90, 0.0f, 1.0f, 0.0f);
	glTranslatef(0, 0, 10);
	gluDisk(gunWheels, 20, 60, 20, 20);
	glTranslatef(0, 0, -10);
	gluCylinder(gunWheels, 60, 60, 10, 20, 3);
	glRotatef(-90, 0.0f, 1.0f, 0.0f);
	glTranslatef(-25, 0, 0);
	//
	glTranslatef(-35, 0, 0);
	glRotatef(90, 0.0f, 1.0f, 0.0f);
	gluCylinder(gunWheels, 60, 60, 10, 20, 3);
	gluDisk(gunWheels, 20, 60, 20, 20);
	glRotatef(-90, 0.0f, 1.0f, 0.0f);
	glTranslatef(35, 0, 0);
	glRotatef(-rollAngle, 1.0f, 0.0f, 0.0f);
	//gun's body
	glBindTexture(GL_TEXTURE_2D, cylinderTexture);
	gluQuadricDrawStyle(gunTop, GLU_FILL);
	gluQuadricTexture(gunTop, 1);
	gluQuadricNormals(gunTop, GLU_SMOOTH);
	glRotatef(gunAngle, 1.0f, 0.0f, 0.0f);
	glTranslatef(40, 0, 0);
	gluCylinder(gunWheels, 1.5, 1.5, power + 20, 5, 2);
	glTranslatef(0, 0, power + 20);
	gluCylinder(gunWheels, 3, 0, 5, 5, 2);
	glTranslatef(0, 0, -power - 20);
	glTranslatef(-40, 0, 0);
	glTranslatef(-40, 0, 0);
	gluCylinder(gunWheels, 1.5, 1.5, power + 20, 5, 2);
	glTranslatef(0, 0, power + 20);
	gluCylinder(gunWheels, 3, 0, 5, 5, 2);
	glTranslatef(0, 0, -power - 20);
	glTranslatef(40, 0, 0);
	glBindTexture(GL_TEXTURE_2D, gunTexture);
	gluSphere(gunBody, 30, 20, 20);
	gluQuadricDrawStyle(gunBody, GLU_FILL);
	gluQuadricTexture(gunBody, 1);
	gluQuadricNormals(gunBody, GLU_SMOOTH);
	gluCylinder(gunBody, 29, 21, 190, 20, 3);
	glRotatef(-gunAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(-position.x, -position.y, -position.z);
}

void Gun::applyMovement() {
	//change power
	if (Keyboard::isKeyPressed(Keyboard::Add)) {
		power += 3;
	}
	if (Keyboard::isKeyPressed(Keyboard::Subtract)) {
		power -= 3;
	}
	//change angle
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		gunAngle -= 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		gunAngle += 1;
	}
	//shot
	if (Keyboard::isKeyPressed(Keyboard::P)) {
		shot = true;
	}
}

bool Gun::isShot() {
	return shot;
}

void Gun::setShot(bool _shot) {
	this->shot = _shot;
}

float Gun::getPower() {
	return power;
}

float Gun::getAngle() {
	return gunAngle;
}

Gun::Gun(float gunX, float gunY, float gunZ)
{
	position.x = gunX;
	position.y = gunY;
	position.z = gunZ;

	gunTexture = LoadGunTexture("resources/1441051.jpg");
	wheelTexture = LoadGunTexture("resources/wood.jpg");
	cylinderTexture = LoadGunTexture("resources/box_test/1.jpg");

	gunBody = gluNewQuadric();
	gunTop = gluNewQuadric();
	gunWheels = gluNewQuadric();

	gunAngle = -45.0;
	power = 80.0;
	rollAngle = 0.0;

	shot = false;
}

