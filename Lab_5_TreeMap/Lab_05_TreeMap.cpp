#include "TreeMap.h"

void displayTreeMap()
{
	TreeMap myMap;
	for (int i = 0; i < 30; i++) {
		myMap.push(i, rand()%100);
	}
	myMap.pop(25);
	myMap.draw();
}

void Initialize()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 100.0, 100.0, 0.0);
}

int main(int argc, char **argv) {
	FreeConsole();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(900, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Graph");
	Initialize();
	displayTreeMap();
	glutMainLoop();
	return 0;
};