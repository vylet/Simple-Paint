#include <cstdlib>
#include <windows.h>
#include <GL/glut.h>
#include<iostream>
#include<vector>
#include <math.h>
#include "toolbox.h"
#include <stdio.h>
//#include <pngwriter.cpp>

using namespace std;

std::vector<std::vector<int> > lineBuffer;
std::vector<std::vector<int> >::iterator lineBufferIterator;

std::vector<std::vector<int> > rectBuffer;
std::vector<std::vector<int> >::iterator rectBufferIterator;

std::vector<std::vector<int> > pencilBuffer;
std::vector<std::vector<int> >::iterator pencilBufferIterator;

int startXLine,startYLine,	startXRect,startYRect,	prevXLine,prevYLine,	prevXRect,prevYRect,	prevXPencil, prevYPencil;

bool startLineIsInitialized = false;
bool prevLineIsInitialized = false;

bool startRectIsInitialized = false;
bool prevRectIsInitialized = false;

bool prevPencilIsInitialized = false;

int color = 7;
int size = 1;
int tool = 2;

int windowIdCanvas, windowIdToolbox;

int SaveBitmap(const char *ptrcFileName, int nX, int nY, int nWidth, int nHeight)
{
	ptrcFileName = "output.bmp";
	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;
	unsigned char *ptrImage = (unsigned char*)malloc(
		sizeof(unsigned char) * nWidth * nHeight * 3
		+ (4 - (3 * nWidth) % 4) * nHeight);
	FILE *ptrFile = fopen(ptrcFileName, "wb");
	//read pixels from framebuffer
	glReadPixels(nX, nY, nWidth, nHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE,
		ptrImage);
	// set memory buffer for bitmap header and informaiton header
	memset(&bf, 0, sizeof(bf));
	memset(&bi, 0, sizeof(bi));
	// configure the headers with the give parameters
	bf.bfType = 0x4d42;
	bf.bfSize = sizeof(bf) + sizeof(bi) + nWidth * nHeight * 3
		+ (4 - (3 * nWidth) % 4) * nHeight;
	bf.bfOffBits = sizeof(bf) + sizeof(bi);
	bi.biSize = sizeof(bi);
	bi.biWidth = nWidth + nWidth % 4;
	bi.biHeight = nHeight;
	bi.biPlanes = 1;
	bi.biBitCount = 24;
	bi.biSizeImage = nWidth * nHeight * 3 + (4 - (3 * nWidth) % 4) * nHeight;
	// to files
	fwrite(&bf, sizeof(bf), 1, ptrFile);
	fwrite(&bi, sizeof(bi), 1, ptrFile);
	fwrite(ptrImage, sizeof(unsigned char),
		nWidth * nHeight * 3 + (4 - (3 * nWidth) % 4) * nHeight, ptrFile);
	fclose(ptrFile);
	free(ptrImage);
	return 0;
}

void useColor(int c){
	switch(c){
		case 0: 
			glColor3f(1.0f, 0.0f, 0.0f);
			break;
		case 1: 
			glColor3f(0.0f, 1.0f, 0.0f);
			break;
		case 2: 
			glColor3f(0.0f, 0.0f, 1.0f);
			break;
		case 3: 
			glColor3f(0.0f, 1.0f, 1.0f);
			break;
		case 4: 
			glColor3f(1.0f, 1.0f, 0.0f);
			break;
		case 5: 
			glColor3f(1.0f, 0.0f, 1.0f);
			break;
		case 6: 
			glColor3f(1.0f, 1.0f, 1.0f);
			break;
		case 7: 
			glColor3f(0.0f, 0.0f, 0.0f);
			break;
	}
}

void useSize(int s) {
	if(s == 1){
		glLineWidth(3);
	}
	else if(s == 0){
		glLineWidth(8);
	}
}

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

void drawLinePerm(int x1, int y1,int x2,int y2,int c,int s) {

	useSize(s);
	
	useColor(c);

	glBegin(GL_LINES);
		glVertex2f(x1 , y1);
		glVertex2f(x2 , y2);
	glEnd();

	glFlush();
}

void drawLineTemp(int x, int y) {

	y = 400-y;
 
	useSize(size);
	
	useColor(color);

	glBegin(GL_LINES);
		glVertex2f(startXLine , startYLine);
		glVertex2f(x , y);
	glEnd();

	glFlush();
}

void drawRectPerm(int x1, int y1,int x2,int y2,int c,int s) {

	useSize(s);
	
	useColor(c);

	glBegin(GL_LINE_LOOP);
		glVertex2f(x1 , y1);
		glVertex2f(x2 , y1);
		glVertex2f(x2 , y2);
		glVertex2f(x1 , y2);
	glEnd();

	glFlush();
}

void drawRectTemp(int x, int y) {

	y = 400 - y;

	useSize(size);
	
	useColor(color);

	glBegin(GL_LINE_LOOP);
		glVertex2f(startXRect , startYRect);
		glVertex2f(x , startYRect);
		glVertex2f(x , y);
		glVertex2f(startXRect , y);
	glEnd();

	glFlush();
}

/*void eraseLine(){
	glLineWidth(3);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex2f(startX , startY);
		glVertex2f(prevX , prevY);
	glEnd();
}
*/

void drawPencil (int x, int y) {
	//y = 250-y;
	//x = x-250;
	y = 400 - y;

	useSize(size);
	
	useColor(color);

	glBegin(GL_LINE_STRIP);
		glVertex2f(prevXPencil , prevYPencil);
		glVertex2f(x , y);
	glEnd();

	int temp[] = {prevXPencil,prevYPencil,x,y,color,size};

	prevXPencil = x;
	prevYPencil = y;

	pencilBuffer.push_back(std::vector<int> (temp, temp + sizeof(temp) / sizeof(int) ));

	glutSwapBuffers();
	//glFlush();
}

void displayCanvas (void){
	glClear(GL_COLOR_BUFFER_BIT);
	std::vector<int> temp;
	for(lineBufferIterator = lineBuffer.begin();	lineBufferIterator != lineBuffer.end();	lineBufferIterator++)	{
		temp = *lineBufferIterator;
		drawLinePerm(temp[0], temp[1], temp[2], temp[3], temp[4], temp[5]);
	}

	for(rectBufferIterator = rectBuffer.begin();	rectBufferIterator != rectBuffer.end();	rectBufferIterator++)	{
		temp = *rectBufferIterator;
		drawRectPerm(temp[0], temp[1], temp[2], temp[3], temp[4], temp[5]);
	}

	for(pencilBufferIterator = pencilBuffer.begin();	pencilBufferIterator != pencilBuffer.end();	pencilBufferIterator++)	{
		temp = *pencilBufferIterator;
		drawLinePerm(temp[0], temp[1], temp[2], temp[3], temp[4], temp[5]);
	}

	//glFlush();
	//glutSwapBuffers();
}

void mouseCanvas(int bin, int state , int x , int y) {
	if(bin == GLUT_LEFT_BUTTON && state == GLUT_UP ){
		if(tool == 0){
			prevPencilIsInitialized = false;
		}
		else if(tool == 1){
			SaveBitmap("output.bmp", 0, 0, 640, 480);
		/*
			GLfloat* pixels = new GLfloat[200000];
			glReadPixels(0, 0, 500, 400, GL_RGB, GL_FLOAT, pixels);
			double R,G,B;
			pngwriter PNG(500, 400, 1.0, fileName);
			for(int i=0; i<500*400; i++) // 
			{
				  switch(i%3)
				 {
					   case 2:
							 B = (double)(pixels[i]); break;
					   case 1:
							 G = (double)(pixels[i]); break;
					   case 0:
							 R = (double)(pixels[i]);
							 PNG.plot(x, y, R, G, B);    
							 if( x == 1080 )             
							 {
								   x=1;
								   y++;
							  }
							  else                      
							  { x++; }
							  break;
				 }
			}
			PNG.close();
			*/
		}
		else if(tool == 2){
			int temp[] = {startXLine,startYLine,prevXLine,400 - prevYLine,color,size};
			std::vector<int> newEntry  (temp, temp + sizeof(temp) / sizeof(int) );
			if(lineBuffer.empty()){
				lineBuffer.push_back(std::vector<int> (temp, temp + sizeof(temp) / sizeof(int) ));
			}
			else{
				std::vector<int> prevEntryLine = lineBuffer.back();
				if(newEntry[0] == prevEntryLine[0] && newEntry[1] == prevEntryLine[1] && newEntry[2] == prevEntryLine[2] && newEntry[3] == prevEntryLine[3]){

				}
				else{
					lineBuffer.push_back(std::vector<int> (temp, temp + sizeof(temp) / sizeof(int) ));
				}
			}
			startLineIsInitialized = false;

		}
		else if(tool == 3){
			int temp[] = {startXRect,startYRect,prevXRect,400 - prevYRect,color,size};
			std::vector<int> newEntry  (temp, temp + sizeof(temp) / sizeof(int) );
			if(rectBuffer.empty()){
				rectBuffer.push_back(std::vector<int> (temp, temp + sizeof(temp) / sizeof(int) ));
			}
			else{
				std::vector<int> prevEntryRect = rectBuffer.back();
				if(newEntry[0] == prevEntryRect[0] && newEntry[1] == prevEntryRect[1] && newEntry[2] == prevEntryRect[2] && newEntry[3] == prevEntryRect[3]){

				}
				else{
					rectBuffer.push_back(std::vector<int> (temp, temp + sizeof(temp) / sizeof(int) ));
				}
			}
			startRectIsInitialized = false;

		}
	}
	glutPostRedisplay();
}

void motionCanvas(int x , int y) {
	if(tool == 0){
		if(!prevPencilIsInitialized )	{
			prevXPencil = x - 1;
			prevYPencil = 400 - y - 1;
			prevPencilIsInitialized = true;
		}
		drawPencil(x,y);
	}
	else if(tool == 2){
		if(!startLineIsInitialized )	{
			startXLine = x - 1;
			startYLine = 400 - y - 1;
			startLineIsInitialized  = true;
		}

		if(!prevLineIsInitialized )	{
			prevXLine = x - 1;
			prevYLine = 400 - y - 1;
			prevLineIsInitialized  = true;
		}
		glutPostRedisplay();
		drawLineTemp(x,y);
		glutSwapBuffers();
		
		prevXLine = x;
		prevYLine = y;
	}
	else if(tool == 3){
		if(!startRectIsInitialized )	{
			startXRect = x - 1;
			startYRect = 400 - y - 1;
			startRectIsInitialized  = true;
		}

		if(!prevRectIsInitialized )	{
			prevXRect = x - 1;
			prevYRect = 400 - y - 1;
			prevRectIsInitialized  = true;
		}
		glutPostRedisplay();
		drawRectTemp(x,y);
		glutSwapBuffers();
		
		prevXRect = x;
		prevYRect = y;
	}
}

/*
void myReshapeCanvas(int w, int h) {
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
	
}*/

void myReshapeCanvas(int w, int h) {
	glutReshapeWindow( 500, 400);
	/*
	glutPostRedisplay();
	glutSwapBuffers();
	*/
}

int main (int argc,char** argv){
	glutInit(&argc,argv);

//Canvas

	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_SINGLE);
	glutInitWindowSize(500,400);
	glutInitWindowPosition(250,100);
	windowIdCanvas = glutCreateWindow("Canvas");

	initCanvas();

	glutReshapeFunc(myReshapeCanvas);
	glutDisplayFunc(displayCanvas);
	glutMouseFunc(mouseCanvas);
	glutMotionFunc(motionCanvas);


	glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE );
	glutInitWindowSize(300,600);

	glutInitWindowPosition(1000,100);
	windowIdToolbox = glutCreateWindow("Toolbox");

//Toolbox

	initToolbox();

	glutReshapeFunc(myReshapeToolbox);
	glutDisplayFunc(displayToolboxBasic);
	glutMouseFunc(mouseToolbox);

	glutSetWindow(windowIdCanvas);
	glutMainLoop();
 }

