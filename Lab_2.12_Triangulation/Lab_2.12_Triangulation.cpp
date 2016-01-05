#include "stdafx.h"
#include <windows.h>
#include <GL/glut.h> 
#include "vertex.h"

void mouseClicks(int button, int state, int x1, int y1);

vertex myVertex; 

void Initialize()
{
	glClearColor(0.0,0.0,0.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,400.0,0.0,400.0,-1.0,1.0);
}

//building triangulation
void triangulation()
{
	myVertex.triangulate();
	myVertex.draw();
}

//add new vertex with mouse
void mouseClicks(int button, int state, int x1, int y1){
	if ((button == GLUT_LEFT_BUTTON ) && (state == GLUT_DOWN)){
		myVertex.push(x1, y1);
	}
}

void Keys(unsigned char Key,int x,int y)
 {
	 switch(Key)
	 {
	 case 't': myVertex.triangulate();//building triangulation by key
		 break;
	 }
	 glutPostRedisplay();
}

int main(int argc, char **argv)
{
	FreeConsole();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(400,400);		
	glutInitWindowPosition(100,100);	
	glutCreateWindow("Polygon");		
	Initialize();	
	glutKeyboardFunc(Keys);
	glutMouseFunc(mouseClicks);
	glutDisplayFunc(triangulation);
	glutMainLoop();
	return 0;
}