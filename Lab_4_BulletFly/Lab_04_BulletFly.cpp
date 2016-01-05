#include "stdafx.h"
#include "Bullet.h"
#include "Gun.h"
#include "World.h"
#include "Player.h"

void Initialize(){
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glClearDepth(1.f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.f, 1.43f, 1.f, 2000.f);
	glEnable(GL_TEXTURE_2D);
}

int main()
{
	RenderWindow window(VideoMode(1000, 700), "Gun");
	Initialize();
	ShowCursor(false);
	World myWorld(1000);
	Player myPlayer(0.0, 70.0, 180.0);
	Gun myGun(0.0, 30.0, 0.0);
	Bullet myBullet(0.0, 30.0, 0.0);
	Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		glClear(GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		myPlayer.applyShift();
		myPlayer.applyRotate(window);
		myPlayer.show();

		myGun.applyMovement();
		myGun.drawGun();

		myBullet.drawBullet();
		myBullet.applyPhysic(myGun);

		myWorld.drawWorld(myPlayer.getPosition()[0], myPlayer.getPosition()[1], myPlayer.getPosition()[2]);

		window.display();
		window.clear();
	}

    return 0;
}

