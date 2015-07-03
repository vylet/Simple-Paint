#include <stdlib.h>
#include <GL/glut.h>
#include<iostream>
#include<vector>

using namespace std;

#define COLOR_WIDTH 200
#define COLOR_HEIGHT 25
/*
int color = 7;
int size = 1;
int tool = 0;
*/

extern	int color ;
extern	int size ;
extern	int tool ;


void initToolbox (void);

void displayToolboxSelect();

void displayToolboxBasic (void);

void myReshapeToolbox(int w, int h) ;

void mouseToolbox (int button, int state, int x, int y);

