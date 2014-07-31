/*  Program 4: Write a program to create a wire frame model of a globe using equation of ellipse.
	
	Coded By: Dr. Chetana Hegde
*/

#include <GL/glut.h>
#include<math.h>
#define PI 3.1416

void setPixel(GLint, GLint);
void ellipse(GLint, GLint, GLint, GLint, GLfloat);
void display();
void resize(int, int);

void main(int argc, char**argv) 
{ 
	//initialize GLUT 
	glutInit(&argc,argv); 
	//initialize display mode 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	//set display-window width & height 
	glutInitWindowSize(400,400); 
	//set display-window upper-left position 
	glutInitWindowPosition(50,50); 
	//create display-window with a title 
	glutCreateWindow("Wire Frame Model of Globe"); 
		
	//call graphics to be displayed on the window 
	glutDisplayFunc(display); 

	//calls whenever frame buffer window is resized
	glutReshapeFunc(resize);

	//display everything and wait 
	glutMainLoop(); 
}

void resize(int w, int h)
{
	//set projection paramaters 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	gluOrtho2D(0.0,w,0.0,h); 

	glViewport(0.0, 0.0, w, h);
	
} 

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(1.0,0.0,0.0); 
	glPointSize(2.0); 

	GLint xc=200;  // setting the center of globe 
	GLint yc=200;
	
	GLint ry=100; // setting the radius_accross_y-axis of ellipse as constant

	for(GLint theta =1;theta<=360;theta++)
		for(GLint rx=100;rx>=0;rx-=10)  //change radius_accross_x-axis (0 to 100 in steps of 10) and draw ellipses
			ellipse(xc, yc, rx, ry, theta);  
		
	GLint rx=100;   //setting the radius_accross_x-axis of ellipse as constant

	for(GLint theta =1;theta<=360;theta++)
		for(GLint ry=100;ry>=0;ry-=10)  //change radius_accross_y-axis (0 to 100 in steps of 10) and draw ellipses
			ellipse(xc, yc, rx, ry, theta);

	glFlush();
				
}

void ellipse(GLint xc, GLint yc, GLint rx, GLint ry, GLfloat theta)
{
	GLint x = xc + rx *cos(theta* PI/180.0); 
	GLint y = yc + ry * sin(theta* PI/180.0);
	setPixel(x,y);
}

void setPixel(GLint xCoordinate, GLint yCoordinate) 
{ 
	glBegin(GL_POINTS); 
	glVertex2i(xCoordinate,yCoordinate); 
	glEnd(); 
} 

