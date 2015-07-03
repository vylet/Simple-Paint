#include <stdlib.h>
#include <GL/glut.h>
#include<iostream>

using namespace std;

int prevX,prevY;
bool prevIsInitialized = false;

void init (void)
{
	
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
 
	glViewport( 0,0, 500, 500 );
	glMatrixMode( GL_PROJECTION );
	glOrtho( 0.0, 500.0, 0.0, 500.0, 1.0, -1.0 );
 

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void drawSquare(int x, int y) {
	//y = 250-y;
	//x = x-250;
	y = 500-y;
 
	glLineWidth(3);
	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_LINES);
		glVertex2f(prevX , prevY);
		glVertex2f(x , y);
	glEnd();

	prevX = x;
	prevY = y;

	glFlush();
}

void display (void){
	glClear(GL_COLOR_BUFFER_BIT);
	drawSquare(0,0);
}

void mouse(int bin, int state , int x , int y) {
	if(bin == GLUT_LEFT_BUTTON && state == GLUT_UP) 
		prevIsInitialized = false;
}

void mouse1(int x , int y) {
	//if(bin == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	if(!prevIsInitialized)	{
		prevX = x - 1;
		prevY = 500 - y - 1;
		prevIsInitialized = true;
	}
	drawSquare(x,y);
}

int main (int argc,char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE );
	glutInitWindowSize(500,500);

	glutInitWindowPosition(0,0);
	glutCreateWindow("My Vindow");

	init();

	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(mouse1);
	glutMainLoop();
 }