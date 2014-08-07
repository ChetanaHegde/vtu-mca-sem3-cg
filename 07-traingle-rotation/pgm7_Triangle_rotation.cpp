/* Program 7. Write a program to create(without using builtin functions)
	and rotate ( (i)given angle (ii)around X and Y axis) a triangle by
	implementing rotation algorithm.
	Coded by: Dr. Chetana Hegde
*/

#include <GL/glut.h>
#include<math.h>
#include<stdio.h>
#define PI 3.1416

float angle=10;
float theta;

typedef struct Point
{
	float x, y, z;
};

void rotate_x(float);
void rotate_y(float);
void init();

Point p[3]={
	{3.0, 0, -0.50},
	{3.0, 0, -1.50},
	{3.0, 1, -1.0}};


void drawTriangle(Point p[3]) 
{ 
	glColor3f(0.3, 0.6, 0.9);

	glLineWidth(2.0);

	glBegin(GL_LINES); 
		glVertex3f(p[0].x, p[0].y, p[0].z); 
		glVertex3f(p[1].x, p[1].y, p[1].z);
	glEnd();

	glColor3f(0.6, 0.9, 0.3);

	glBegin(GL_LINES);
		glVertex3f(p[1].x, p[1].y, p[1].z);
		glVertex3f(p[2].x, p[2].y, p[2].z); 
	glEnd(); 
	 
	glColor3f(0.9, 0.3, 0.6);

	glBegin(GL_LINES);
		glVertex3f(p[0].x, p[0].y, p[0].z); 
		glVertex3f(p[2].x, p[2].y, p[2].z);
	glEnd(); 
	
	glFlush(); 

} 

void display() 
{ 

	init();
	int opt;
	glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(1.0,1.0,1.0); 
	glMatrixMode(GL_MODELVIEW); 
	
	glBegin(GL_LINES);
		glColor3f(1,0,0);
		glVertex3f(0,0,0);
		glVertex3f(7, 0, 0);

		glColor3f(0,1,0);
		glVertex3f(0,0,0);
		glVertex3f(0,3,0);

		glColor3f(0,0,1);
		glVertex3f(0,0,0);
		glVertex3f(0,0,3);
	glEnd();

	glRasterPos3f(7, 0, 0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'X');

	glRasterPos3f(0, 3, 0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'Y');

	glRasterPos3f(0, 0, 3);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'Z');

	glFinish();	
	
	drawTriangle(p);

	
	printf("************ Traingle Rotation ***************");
	printf("\n1. Rotate around x-axis \n 2. Rotate around y-axis \n");
	printf("Enter your option:");
	scanf("%d", & opt);
	printf("\n Enter value for theta: ");
	scanf("%f", &theta);

	switch(opt)
	{
		case 1: rotate_x(theta);
				break;
		case 2:	rotate_y(theta);
				break;
	}
	glFlush(); 
	
} 

void rotate_x(float theta)
{
	int i;
	Point new_p[3];

	for(i=0;i<3;i++)
	{
		new_p[i].x= p[i].x;
		new_p[i].y = p[i].y * cos(theta * PI/180.0) - p[i].z * sin(theta*PI/180.0);
		new_p[i].z = p[i].y * sin(theta * PI/180.0) + p[i].z * cos(theta*PI/180.0);
	}

	drawTriangle(new_p);
}
void rotate_y(float theta)
{
	int i;
	Point new_p[3];

	for(i=0;i<3;i++)
	{
		new_p[i].x = p[i].z * sin(theta * PI/180.0) + p[i].x * cos(theta*PI/180.0);
		new_p[i].y= p[i].y;
		new_p[i].z = p[i].z * cos(theta * PI/180.0) - p[i].x * sin(theta*PI/180.0);
	}

	drawTriangle(new_p);
}

void init(void) 
{ 
	//set projection paramaters 
	glMatrixMode(GL_MODELVIEW); 
	//gluOrtho2D(0.0,400.0,0.0,400.0); 
	glLoadIdentity();

	float eyeX, eyeY, eyeZ;

	eyeX= 10* cos(angle * PI/180.0);
	eyeY =1;
	eyeZ = 10 * sin(angle *PI/180.0);

	gluLookAt(eyeX,eyeY,eyeZ,		//change these values to see the cube from different directions
			  0,0, 0, 
			  0, 1, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); //reset to identity matrix
	gluPerspective(45, 1, 1, 100);
} 

void main(int argc, char**argv) 
{ 
	//initialize GLUT 
	glutInit(&argc,argv); 
	//initialize display mode 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	//set display-window width & height 
	glutInitWindowSize(400,400); 
	//set display-window upper-left position 
	glutInitWindowPosition(500,100); 
	//create display-window with a title 
	glutCreateWindow(" Triangle Rotation"); 
	//initialze OpenGL 
	init(); 
	//call graphics to be displayed on the window 
	glutDisplayFunc(display); 

	//display everything and wait 
	glutMainLoop(); 
}
