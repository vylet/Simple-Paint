/*
#include <stdlib.h>
#include <GL/glut.h>
#include<iostream>
#include<vector>

using namespace std;

#define COLOR_WIDTH 200
#define COLOR_HEIGHT 25


*/

#include "toolbox.h"

void initToolbox (void)
{
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
 	
	glViewport( 0,0, 300, 600 );
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D (0.0, 300.0, 0.0, 600.0);	
}

void text(int x, int y, char *string)
{
  glColor3f( 0.0, 0.0, 0.0 );
  glRasterPos2f(x, y);
  int len, i;
  len = (int)strlen(string);
  for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
  }
}

void displayToolboxSelect(){

	glLineWidth(4);

	if(color == 6 || color == 7){
		glColor3f(0.8f, 0.8f, 0.8f);
	}
	else{
		glColor3f(0.0f, 0.0f, 0.0f);
	}
	int y = 50;

	glBegin(GL_LINE_LOOP);
		glVertex2f(50 , y + color*COLOR_HEIGHT);
		glVertex2f(50 + COLOR_WIDTH , y + color*COLOR_HEIGHT);
		glVertex2f(50 + COLOR_WIDTH , y + (color+1)*COLOR_HEIGHT);
		glVertex2f(50 , y + (color+1)*COLOR_HEIGHT);		
	glEnd();

	y += 10*COLOR_HEIGHT;
	glColor3f(0.0f, 0.0f, 0.0f);

	glBegin(GL_LINE_LOOP);
		glVertex2f(50 , y + size*COLOR_HEIGHT);
		glVertex2f(50 + COLOR_WIDTH , y + size*COLOR_HEIGHT);
		glVertex2f(50 + COLOR_WIDTH , y + (size+1)*COLOR_HEIGHT);
		glVertex2f(50 , y + (size+1)*COLOR_HEIGHT);		
	glEnd();

	y += 4*COLOR_HEIGHT;

	glBegin(GL_LINE_LOOP);
		glVertex2f(50 , y + tool*COLOR_HEIGHT);
		glVertex2f(50 + COLOR_WIDTH , y + tool*COLOR_HEIGHT);
		glVertex2f(50 + COLOR_WIDTH , y + (tool+1)*COLOR_HEIGHT);
		glVertex2f(50 , y + (tool+1)*COLOR_HEIGHT);		
	glEnd();
	glFlush();
}

void displayToolboxBasic (void){

	glClear(GL_COLOR_BUFFER_BIT);

	int startHeight = 50;

	// RED
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
		glVertex2f(50 , startHeight);
		glVertex2f(50 + COLOR_WIDTH , startHeight);
		glVertex2f(50 + COLOR_WIDTH , startHeight + COLOR_HEIGHT);
		glVertex2f(50 , startHeight + COLOR_HEIGHT);		
	glEnd();

	startHeight+= COLOR_HEIGHT;

	// GREEN
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
		glVertex2f(50 , startHeight);
		glVertex2f(50 + COLOR_WIDTH , startHeight);
		glVertex2f(50 + COLOR_WIDTH , startHeight + COLOR_HEIGHT);
		glVertex2f(50 , startHeight + COLOR_HEIGHT);		
	glEnd();

	startHeight+= COLOR_HEIGHT;

	// BLUE
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
		glVertex2f(50 , startHeight);
		glVertex2f(50 + COLOR_WIDTH , startHeight);
		glVertex2f(50 + COLOR_WIDTH , startHeight + COLOR_HEIGHT);
		glVertex2f(50 , startHeight + COLOR_HEIGHT);		
	glEnd();

	startHeight+= COLOR_HEIGHT;

	// CYAN
	glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
		glVertex2f(50 , startHeight);
		glVertex2f(50 + COLOR_WIDTH , startHeight);
		glVertex2f(50 + COLOR_WIDTH , startHeight + COLOR_HEIGHT);
		glVertex2f(50 , startHeight + COLOR_HEIGHT);		
	glEnd();

	startHeight+= COLOR_HEIGHT;

	//YELLOW
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
		glVertex2f(50 , startHeight);
		glVertex2f(50 + COLOR_WIDTH , startHeight);
		glVertex2f(50 + COLOR_WIDTH , startHeight + COLOR_HEIGHT);
		glVertex2f(50 , startHeight + COLOR_HEIGHT);		
	glEnd();

	startHeight+= COLOR_HEIGHT;

	//MAGENTA
	glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
		glVertex2f(50 , startHeight);
		glVertex2f(50 + COLOR_WIDTH , startHeight);
		glVertex2f(50 + COLOR_WIDTH , startHeight + COLOR_HEIGHT);
		glVertex2f(50 , startHeight + COLOR_HEIGHT);		
	glEnd();

	startHeight+= COLOR_HEIGHT;

	//WHITE
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
		glVertex2f(50 , startHeight);
		glVertex2f(50 + COLOR_WIDTH , startHeight);
		glVertex2f(50 + COLOR_WIDTH , startHeight + COLOR_HEIGHT);
		glVertex2f(50 , startHeight + COLOR_HEIGHT);		
	glEnd();

	startHeight+= COLOR_HEIGHT;

	//BLACK
	glColor3f(0.0f, 0.0f,0.0f);
	glBegin(GL_POLYGON);
		glVertex2f(50 , startHeight);
		glVertex2f(50 + COLOR_WIDTH , startHeight);
		glVertex2f(50 + COLOR_WIDTH , startHeight + COLOR_HEIGHT);
		glVertex2f(50 , startHeight + COLOR_HEIGHT);		
	glEnd();

	startHeight+= COLOR_HEIGHT * 3;

	//BIG_LINE

	glColor3f(0.8f, 0.8f,0.8f);
	glBegin(GL_POLYGON);
		glVertex2f(50 , startHeight);
		glVertex2f(50 + COLOR_WIDTH , startHeight);
		glVertex2f(50 + COLOR_WIDTH , startHeight + COLOR_HEIGHT);
		glVertex2f(50 , startHeight + COLOR_HEIGHT);		
	glEnd();

	glColor3f(0.0f, 0.0f,0.0f);
	glLineWidth(8);
	glBegin(GL_LINES);
		glVertex2f(50 +25, startHeight + COLOR_HEIGHT/2);
		glVertex2f(50 + COLOR_WIDTH -25, startHeight + COLOR_HEIGHT/2);
	glEnd();

	startHeight+= COLOR_HEIGHT ;

	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(2);
	glBegin(GL_LINES);
		glVertex2f(50 , startHeight );
		glVertex2f(50 + COLOR_WIDTH , startHeight );
	glEnd();

	//SMALL_LINE

	glColor3f(0.8f, 0.8f,0.8f);
	glBegin(GL_POLYGON);
		glVertex2f(50 , startHeight);
		glVertex2f(50 + COLOR_WIDTH , startHeight);
		glVertex2f(50 + COLOR_WIDTH , startHeight + COLOR_HEIGHT);
		glVertex2f(50 , startHeight + COLOR_HEIGHT);		
	glEnd();

	glColor3f(0.0f, 0.0f,0.0f);
	glLineWidth(2);
	glBegin(GL_LINES);
		glVertex2f(50 + 40, startHeight + COLOR_HEIGHT/2);
		glVertex2f(50 + COLOR_WIDTH - 40, startHeight + COLOR_HEIGHT/2);
	glEnd();

	startHeight+= COLOR_HEIGHT*3;

	// PENCIL RED
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
		glVertex2f(50 , startHeight);
		glVertex2f(50 + COLOR_WIDTH , startHeight);
		glVertex2f(50 + COLOR_WIDTH , startHeight + COLOR_HEIGHT);
		glVertex2f(50 , startHeight + COLOR_HEIGHT);		
	glEnd();

	text(100,startHeight,"Pencil");
	startHeight+= COLOR_HEIGHT;

	// ERASER GREEN
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
		glVertex2f(50 , startHeight);
		glVertex2f(50 + COLOR_WIDTH , startHeight);
		glVertex2f(50 + COLOR_WIDTH , startHeight + COLOR_HEIGHT);
		glVertex2f(50 , startHeight + COLOR_HEIGHT);		
	glEnd();

	text(100,startHeight,"Save");
	startHeight+= COLOR_HEIGHT;

	// LINE BLUE
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
		glVertex2f(50 , startHeight);
		glVertex2f(50 + COLOR_WIDTH , startHeight);
		glVertex2f(50 + COLOR_WIDTH , startHeight + COLOR_HEIGHT);
		glVertex2f(50 , startHeight + COLOR_HEIGHT);		
	glEnd();

	text(100,startHeight,"Line");
	startHeight+= COLOR_HEIGHT;

	// RECTANGLE CYAN
	glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
		glVertex2f(50 , startHeight);
		glVertex2f(50 + COLOR_WIDTH , startHeight);
		glVertex2f(50 + COLOR_WIDTH , startHeight + COLOR_HEIGHT);
		glVertex2f(50 , startHeight + COLOR_HEIGHT);		
	glEnd();

	text(100,startHeight,"Rectangle");
	displayToolboxSelect();

	glFlush();
}

void myReshapeToolbox(int w, int h) {
	glutReshapeWindow( 300, 600);
}

void mouseToolbox (int button, int state, int x, int y){
	y = 600 - y;
	if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){
		if( x>= 50 && x<= 50 + COLOR_WIDTH){
			if( y>= 50 && y<= 50 + 8*COLOR_HEIGHT){
					color = (y - 50)/COLOR_HEIGHT;
					/*
					glColor3f(1.0f, 0.0f, 0.0f);
					glPointSize(10);
					glBegin(GL_POINTS);
						glVertex2f(0 , 0 );
					glEnd();
					*/
					glutPostRedisplay();
					//glFlush();
			}

			else if( y>= 50 + 10*COLOR_HEIGHT && y<= 50 + 12*COLOR_HEIGHT){
					size = (y - 50 - 10*COLOR_HEIGHT)/COLOR_HEIGHT;
					/*
					glColor3f(1.0f, 0.0f, 0.0f);
					glPointSize(10);
					glBegin(GL_POINTS);
						glVertex2f(0 , 0 );
					glEnd();
					*/
					glutPostRedisplay();
					//glFlush();
			}

			else if(y>= 50 + 14*COLOR_HEIGHT && y<= 50 + 18*COLOR_HEIGHT){
					tool = (y - 50 - 14*COLOR_HEIGHT)/COLOR_HEIGHT;
					/*
					glColor3f(1.0f, 0.0f, 0.0f);
					glPointSize(10);
					glBegin(GL_POINTS);
						glVertex2f(0 , 0 );
					glEnd();
					*/
					glutPostRedisplay();
					//glFlush();
			}
		}
	}
}


