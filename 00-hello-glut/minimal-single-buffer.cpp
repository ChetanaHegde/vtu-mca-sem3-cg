/*
Computer Graphics Laboratory -- VTU 3rd Semester MCA Course (2013 Scheme)

This is a minimal program to help understand basic GLUT usage.  GLUT is a cross-platform
toolkit for writing simple OpenGL applications. We use GLUT in all programs for simplicity. 

Run this program and note the prints on the terminal. Resize the window and see what happens.

Author: Dr. Chetana Hegde, Associate Professor, RNS Institute of Technology, Bangalore
        chetanahegde at ieee dot org
*/

#include<GL/glut.h>
#include<stdio.h>

void resize(int w, int h)
{
	printf("Window size set to %d x %d pixels\n", w, h); 
}

void display()
{
	// clear the frame buffer
	glClear(GL_COLOR_BUFFER_BIT);

	// ensure all OpenGL commands are done
	glFinish();

	printf("Display done!\n");

	// request repainting - this will cause GLUT to call
	// display() repeatedly
	//glutPostRedisplay();
}

int main(int argc, char**argv)
{
	// Initialize GLUT
	glutInit(&argc, argv);

	// Created windows will be single buffered, and full color
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Instruct GLUT to position windows (by default) at screen coordinate 50,50
	glutInitWindowPosition(50,50); 

	// Instruct GLUT to create windows (by default) of size 600x600
	glutInitWindowSize(600,600);

	// Create a window with title
	glutCreateWindow("Minimal Single Buffer GLUT app");

	// Register a display function. This will be called when there is a need
	// to repaint the window. Windows will typically get repainted just after
	// creation, and on every resize, and on response to glutPostRedisplay()
	glutDisplayFunc(display);

	// Register a reshape function.  This will be called when the window is created,
	// and when it is subsequently resized
	glutReshapeFunc(resize);

	// GLUT main loop
	glutMainLoop();

	// glutMainLoop never exits
	// Control will never come here!
	return 0;
}