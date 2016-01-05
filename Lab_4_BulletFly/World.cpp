#include "World.h"

#define GL_CLAMP_TO_EDGE 0x812F

GLuint LoadWorldTexture(String name)
{
	Image image;
	if (!image.loadFromFile(name))
		return EXIT_FAILURE;
	image.flipVertically();
	GLuint texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	gluBuild2DMipmaps(	GL_TEXTURE_2D, GL_RGBA, image.getSize().x, image.getSize().y, 
						GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return texture;
}

void World::drawSky()
{
	glBindTexture(GL_TEXTURE_2D, skyBox[0]);
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);   glVertex3f(-skySize, -skySize, -skySize);
	glTexCoord2f(1, 0);   glVertex3f(skySize, -skySize, -skySize);
	glTexCoord2f(1, 1);   glVertex3f(skySize, skySize, -skySize);
	glTexCoord2f(0, 1);   glVertex3f(-skySize, skySize, -skySize);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, skyBox[1]);
	glBegin(GL_QUADS);
	//back
	glTexCoord2f(0, 0); glVertex3f(skySize, -skySize, skySize);
	glTexCoord2f(1, 0); glVertex3f(-skySize, -skySize, skySize);
	glTexCoord2f(1, 1); glVertex3f(-skySize, skySize, skySize);
	glTexCoord2f(0, 1); glVertex3f(skySize, skySize, skySize);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, skyBox[2]);
	glBegin(GL_QUADS);
	//left
	glTexCoord2f(0, 0); glVertex3f(-skySize, -skySize, skySize);
	glTexCoord2f(1, 0); glVertex3f(-skySize, -skySize, -skySize);
	glTexCoord2f(1, 1); glVertex3f(-skySize, skySize, -skySize);
	glTexCoord2f(0, 1); glVertex3f(-skySize, skySize, skySize);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, skyBox[3]);
	glBegin(GL_QUADS);
	//right
	glTexCoord2f(0, 0); glVertex3f(skySize, -skySize, -skySize);
	glTexCoord2f(1, 0); glVertex3f(skySize, -skySize, skySize);
	glTexCoord2f(1, 1); glVertex3f(skySize, skySize, skySize);
	glTexCoord2f(0, 1); glVertex3f(skySize, skySize, -skySize);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, skyBox[4]);
	glBegin(GL_QUADS);
	//bottom
	glTexCoord2f(0, 0); glVertex3f(-skySize, -skySize, skySize);
	glTexCoord2f(1, 0); glVertex3f(skySize, -skySize, skySize);
	glTexCoord2f(1, 1); glVertex3f(skySize, -skySize, -skySize);
	glTexCoord2f(0, 1); glVertex3f(-skySize, -skySize, -skySize);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, skyBox[5]);
	glBegin(GL_QUADS);
	//top  		
	glTexCoord2f(0, 0); glVertex3f(-skySize, skySize, -skySize);
	glTexCoord2f(1, 0); glVertex3f(skySize, skySize, -skySize);
	glTexCoord2f(1, 1); glVertex3f(skySize, skySize, skySize);
	glTexCoord2f(0, 1); glVertex3f(-skySize, skySize, skySize);
	glEnd();
}

void createPick(GLuint pick, int size) {
	glBindTexture(GL_TEXTURE_2D, pick);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-size, 0, size);
	glTexCoord2f(1, 0); glVertex3f(size, 0, size);
	glTexCoord2f(1, 1); glVertex3f(size, 0, -size);
	glTexCoord2f(0, 1); glVertex3f(-size, 0, -size);
	glEnd();
}

void World::drawFloor() {
	int R = 50; //floor radius
	for (int i = -R; i < R; i++)
		for (int j = -R; j < R; j++) {
			glTranslatef(i * 25, -30.0, j * 25);
			createPick(floor, 25);
			glTranslatef(-i * 25, 30.0, -j * 25);
		}
}

void World::drawWorld(float _newWorldX, float _newWorldY, float _newWorldZ) {
	glTranslatef(_newWorldX, _newWorldY, _newWorldZ);
	drawSky();
	glTranslatef(-_newWorldX, -_newWorldY, -_newWorldZ);
	glTranslatef(_newWorldX - this->worldX, 0.0, _newWorldZ - this->worldZ);
	drawFloor();
	glTranslatef(-(_newWorldX - this->worldX), 0.0, -(_newWorldZ - this->worldZ));

	this->worldX = _newWorldX;
	this->worldY = _newWorldY;
	this->worldZ = _newWorldZ;
}

World::World(int _skySize)
{
	skySize = _skySize;
	floor = LoadWorldTexture("resources/Black-Metal-Texture.jpg");
	skyBox[0] = LoadWorldTexture("resources/skybox2/skybox_front.bmp");
	skyBox[1] = LoadWorldTexture("resources/skybox2/skybox_back.bmp");
	skyBox[2] = LoadWorldTexture("resources/skybox2/skybox_left.bmp");
	skyBox[3] = LoadWorldTexture("resources/skybox2/skybox_right.bmp");
	skyBox[4] = LoadWorldTexture("resources/skybox2/skybox_bottom.bmp");
	skyBox[5] = LoadWorldTexture("resources/skybox2/skybox_top.bmp");
}
