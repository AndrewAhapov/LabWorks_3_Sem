#include "Player.h"

void Player::show() {
	 gluLookAt(	playerPosition.x, playerPosition.y, playerPosition.z, 
				viewPoint.x, viewPoint.y, viewPoint.z, 
				viewAngle.x, viewAngle.y, viewAngle.z );
}

void Player::applyShift() {
	float dx = 0.0, dy = 0.0, dz = 0.0;
	//player movement
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		dx = -sin(angleX / 180 * PI)*speed;
		dy = tan(angleY / 180 * PI)*speed;
		dz = -cos(angleX / 180 * PI)*speed;
	}
	if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::LShift)) {
		dx = -sin(angleX / 180 * PI) * 5 * speed;
		dy = tan(angleY / 180 * PI) * 5 * speed;
		dz = -cos(angleX / 180 * PI) * 5 * speed;
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		dx = sin(angleX / 180 * PI)*speed;
		dy = -tan(angleY / 180 * PI)*speed;
		dz = cos(angleX / 180 * PI)*speed;
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		dx = sin((angleX + 90) / 180 * PI)*speed;
		dz = cos((angleX + 90) / 180 * PI)*speed;
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		dx = sin((angleX - 90) / 180 * PI)*speed;
		dz = cos((angleX - 90) / 180 * PI)*speed;
	}
	//apply move
	playerPosition.x += dx;
	playerPosition.y += dy;
	playerPosition.z += dz;
}

void Player::applyRotate(RenderWindow &window) {
	POINT mouseCoor;
	GetCursorPos(&mouseCoor);
	//centre of window
	int xt = window.getPosition().x + 500;
	int yt = window.getPosition().y + 350;
	//shift from centre
	angleX += (xt - mouseCoor.x) / 4;
	angleY += (yt - mouseCoor.y) / 4;
	//Y limit
	if (angleY<-89.0) angleY = -89.0; 
	if (angleY>89.0) angleY = 89.0; 
	//back cursor to the centre of window
	SetCursorPos(xt, yt);
	setViewPoint();
}

void Player::setPosition(float posX, float posY, float posZ) {
	playerPosition.x = posX;
	playerPosition.y = posY;
	playerPosition.z = posZ;
}

void Player::setViewPoint() {
	viewPoint.x = playerPosition.x - sin(angleX / 180 * PI);
	viewPoint.y = playerPosition.y + tan(angleY / 180 * PI);
	viewPoint.z = playerPosition.z - cos(angleX / 180 * PI);
}

float* Player::getPosition() {
	float playerplayerPosition[] = { playerPosition.x, playerPosition.y, playerPosition.z };
	return playerplayerPosition;
}

Player::Player(float playerX, float playerY, float playerZ)
{
	setPosition(playerX, playerY, playerZ);
	viewPoint.x = 0.0;
	viewPoint.y = 0.0;
	viewPoint.z = 0.0;
	viewAngle.x = 0.0;
	viewAngle.y = 1.0;
	viewAngle.z = 0.0;
	speed = 7.0f;
	angleX = 0.0;
	angleY = 0.0;
}
