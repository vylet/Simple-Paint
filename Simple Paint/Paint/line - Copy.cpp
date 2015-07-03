#include <stdlib.h>
#include <GL/glut.h>
#include<iostream>
#include<vector>

using namespace std;

std::vector<std::vector<int> > lineBuffer;
std::vector<std::vector<int> >::iterator lineBufferIterator;

int startX,startY,prevX,prevY;
bool startIsInitialized = false;
bool prevIsInitialized = false;

void initCanvas (void)
{
	
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
 
	
	glViewport( 0,0, 500, 400 );
	glMatrixMode( GL_PROJECTION );
	glOrtho( 0.0, 500.0, 0.0, 400.0, 1.0, -1.0 );
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void drawLinePerm(int x1, int y1,int x2,int y2) {
	//y = 250-y;
	//x = x-250;
	//y1 = 500-y1;
	//y2 = 500-y2;

	glLineWidth(3);
	
	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_LINES);
		glVertex2f(x1 , y1);
		glVertex2f(x2 , y2);
	glEnd();

	glFlush();
}

void drawLineTemp(int x, int y) {
	//y = 250-y;
	//x = x-250;
	y = 400-y;
 
	glLineWidth(3);
	
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex2f(startX , startY);
		glVertex2f(x , y);
	glEnd();

	glFlush();
}

void eraseLine(){
	glLineWidth(3);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex2f(startX , startY);
		glVertex2f(prevX , prevY);
	glEnd();
}

void display (void){
	glClear(GL_COLOR_BUFFER_BIT);
	std::vector<int> temp;
	for(lineBufferIterator = lineBuffer.begin();	lineBufferIterator != lineBuffer.end();	lineBufferIterator++)	{
		temp = *lineBufferIterator;
		drawLinePerm(temp[0], temp[1], temp[2], temp[3]);
	}
	//glFlush();
	//glutSwapBuffers();
}

void mouse(int bin, int state , int x , int y) {
	if(bin == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		startIsInitialized = false;
		prevIsInitialized = false;
	}
	int temp[] = {startX,startY,prevX,400 - prevY};
	lineBuffer.push_back(std::vector<int> (temp, temp + sizeof(temp) / sizeof(int) ));
	glutPostRedisplay();
}

void motion(int x , int y) {
	//if(bin == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	if(!startIsInitialized)	{
		startX = x - 1;
		startY = 400 - y - 1;
		startIsInitialized = true;
		//glPushMatrix();
	}

	if(!prevIsInitialized)	{
		prevX = x - 1;
		prevY = 400 - y - 1;
		prevIsInitialized = true;
	}
	
	//eraseLine();
	glutPostRedisplay();
	drawLineTemp(x,y);
	glutSwapBuffers();
	prevX = x;
	prevY = y;
}

void myReshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(130.0, GLfloat(w)/h, 10, 100);
	//glOrtho(-5, +5, -10, +10, -20, +20);
	glOrtho( 0.0, 500.0, 0.0, 500.0, 1.0, -1.0 );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/*
	glutPostRedisplay();
	glutSwapBuffers();
	*/
}

int main (int argc,char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
	glutInitWindowSize(500,400);

	glutInitWindowPosition(0,0);
	glutCreateWindow("Paint");

	init();

	/*
	int screen_pos_x = glutGet((GLenum)GLUT_WINDOW_X);
	int screen_pos_y = glutGet((GLenum)GLUT_WINDOW_Y);
	*/

	//glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutMainLoop();
 }