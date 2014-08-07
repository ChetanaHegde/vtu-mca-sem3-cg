/*	Write a program to create a cube and implement reflection algorithm
	on (i) X axis and (ii) Y axis

	By: Dr. Chetana Hegde
*/

#include<stdio.h>
#include <GL/glut.h>
#include<math.h>

void Option();

typedef struct Point
{
	float x, y, z;
};
const float Center_x=2, Center_y=0, Center_z=-2;

Point cube_vertex[8]={
	{-0.5 + Center_x, 0.5 + Center_y, 0.5 + Center_z},
	{0.5 + Center_x, 0.5 + Center_y, 0.5 + Center_z},
	{0.5 + Center_x, -0.5 + Center_y, 0.5 + Center_z},
	{-0.5 + Center_x, -0.5 + Center_y, 0.5 + Center_z},

	{-0.5 + Center_x, 0.5 + Center_y,- 0.5 + Center_z},
	{0.5 + Center_x, 0.5 + Center_y, -0.5 + Center_z},
	{0.5 + Center_x, -0.5 + Center_y, -0.5 + Center_z},
	{-0.5 + Center_x, -0.5 + Center_y, -0.5 + Center_z}};
	

void init(void) 
{ 
	//set projection paramaters 
	glMatrixMode(GL_MODELVIEW); 
	//gluOrtho2D(0.0,400.0,0.0,400.0); 
	glLoadIdentity();
	gluLookAt(10,2,1,		//change these values to see the cube from different directions
			  0,0, 0, 
			  0, 1, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); //reset to identity matrix
	gluPerspective(45, 1, 1, 100);
} 

void drawCube(Point vertex[8])
{
	glBegin(GL_LINE_LOOP);
		glVertex3f(vertex[0].x, vertex[0].y, vertex[0].z);
		glVertex3f(vertex[1].x, vertex[1].y, vertex[1].z);
		glVertex3f(vertex[2].x, vertex[2].y, vertex[2].z);
		glVertex3f(vertex[3].x, vertex[3].y, vertex[3].z);
	glEnd();

	glBegin(GL_LINE_LOOP);
		glVertex3f(vertex[4].x, vertex[4].y, vertex[4].z);
		glVertex3f(vertex[5].x, vertex[5].y, vertex[5].z);
		glVertex3f(vertex[6].x, vertex[6].y, vertex[6].z);
		glVertex3f(vertex[7].x, vertex[7].y, vertex[7].z);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(vertex[0].x, vertex[0].y, vertex[0].z);
		glVertex3f(vertex[4].x, vertex[4].y, vertex[4].z);

		glVertex3f(vertex[1].x, vertex[1].y, vertex[1].z);
		glVertex3f(vertex[5].x, vertex[5].y, vertex[5].z);

		glVertex3f(vertex[2].x, vertex[2].y, vertex[2].z);
		glVertex3f(vertex[6].x, vertex[6].y, vertex[6].z);

		glVertex3f(vertex[3].x, vertex[3].y, vertex[3].z);
		glVertex3f(vertex[7].x, vertex[7].y, vertex[7].z);
	glEnd();

}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(1.0,1.0,1.0); 
	glMatrixMode(GL_MODELVIEW); 
	
	drawCube(cube_vertex);

	glBegin(GL_LINES);
		glColor3f(1,0,0);
		glVertex3f(0,0,0);
		glVertex3f(5, 0, 0);

		glColor3f(0,1,0);
		glVertex3f(0,0,0);
		glVertex3f(0,3,0);

		glColor3f(0,0,1);
		glVertex3f(0,0,0);
		glVertex3f(0,0,3);
	
	glEnd();

	glFinish();	
	Option();
}

void transform(Point in_v, float mat[3][3], Point &out_v)
{
	out_v.x = in_v.x * mat[0][0] + in_v.y * mat[1][0] + in_v.z * mat[2][0];
	out_v.y = in_v.x * mat[0][1] + in_v.y * mat[1][1] + in_v.z * mat[2][1];
	out_v.z = in_v.x * mat[0][2] + in_v.y * mat[1][2] + in_v.z * mat[2][2];
}

void transformCube(Point source_v[8], float mat[3][3], Point dest_v[8])
{
	int i=0;

	for(i=0;i<8;i++)
		transform(source_v[i], mat, dest_v[i]);
}
void Option()
{
	int opt;
	Point cube_dest[8];

	printf("\n1. X- axis \n 2. Y - axis \n");
	printf("Enter your option:");
	scanf("%d",&opt);

	switch(opt)
	{
		case 1: { 
				float mat[3][3]={
									{1,0,0},
									{0,1,0},
									{0,0,-1}
								};
			
				transformCube(cube_vertex,mat,  cube_dest);
				glColor3f(0.5, 0.8, 0.5);
				drawCube(cube_dest);
				glFinish();
				}
				break;
			
		case 2:	{
					float mat[3][3]={
										{-1,0,0},
										{0,1,0},
										{0,0,1}
									};
			
					transformCube(cube_vertex,mat,  cube_dest);
					glColor3f(0.5, 0.8, 0.5);
					drawCube(cube_dest);
					glFinish();
				}	
			break;
	
		default:
			return;
	}
}

void main(int argc, char**argv) 
{ 
	//initialize GLUT 
	glutInit(&argc,argv); 
	//initialize display mode 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	//set display-window width & height 
	glutInitWindowSize(600,600); 
	//set display-window upper-left position 
	glutInitWindowPosition(450,50); 
	//create display-window with a title 
	glutCreateWindow("Cube Reflection"); 
	//initialze OpenGL 
	init(); 
	//call graphics to be displayed on the window 
	glutDisplayFunc(display); 
	//display everything and wait 
	glutMainLoop(); 
}

