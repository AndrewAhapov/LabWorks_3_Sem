#include <iostream>
#include "Graph.h"
#include "Population.h"
using namespace std;

void Initialize()
{
	glClearColor(0.0,0.0,0.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,900.0,0.0,600.0);
}

void draw(){
	Graph myGraph(29, 50);
	myGraph.draw();
	class Population firstOne(myGraph.size(), myGraph);
}

void Keys(unsigned char Key,int x,int y)
{
	 switch(Key)
	 {
	 case 'g': draw();
		 break;
	 };
}

int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(900,600);		
	glutInitWindowPosition(50,50);	
	glutCreateWindow("Graph");	
	Initialize();
	glutDisplayFunc(draw);
	//draw();
	glutKeyboardFunc(Keys);
	glutMainLoop();
	return 0;
}
