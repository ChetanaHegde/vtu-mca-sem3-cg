/* Program 1: Write a program to implement Chessboard using DDA Line drawing algorithm.
   Coded by: Basavaraju R, Assistant Professor, RNSIT, Bangalore
 Email: basavaraju dot revanna at gmail dot com
*/

#include<gl\glut.h>
#include<math.h>

GLint start_x=50,start_y=40,end_x=start_x+80,end_y=start_y+80; 

void setPixel(GLint, GLint);
void init();
void display();
void lineDDA(GLint,GLint,GLint,GLint);
void fillRow(GLint,GLint,GLint,GLint,GLfloat);

void main(int argc, char** argv)
{
	glutInit(&argc, argv);		//initialize GLUT 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//initialize display mode 
	glutInitWindowPosition(250,100);	 //set display-window upper-left position
	glutInitWindowSize(600,500);		//set display-window width & height
	glutCreateWindow("Chess Board using DDA Line Algorithm");	//create display-window with a title 
	init();		//initialize window prpperties
	glutDisplayFunc(display);		//call graphics to be displayed on the window 
	glutMainLoop();		//display everything and wait 
}

inline int round(const float a)
{
	return int(a+0.5);
}

void setPixel(GLint xCoordinate, GLint yCoordinate)
{
	glBegin(GL_POINTS);
	glVertex2i(xCoordinate,yCoordinate);
	glEnd();
	glFlush(); //executes all OpenGL functions as quickly as possible
}

void init(void)
{
	glClearColor(0.0,0.5,0.5,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,200.0,0.0,150.0);
}

//DDA line drawing procedure
void lineDDA(GLint x0,GLint y0, GLint xe, GLint ye)
{
	GLint dx=xe-x0, dy=ye-y0, steps, k;
	GLfloat xinc, yinc, x=x0, y=y0;
	if(abs(dx)>abs(dy))
		steps=abs(dx);
	else
		steps=abs(dy);
	xinc=float(dx)/float(steps);
	yinc=float(dy)/float(steps);
    setPixel(round(x),round(y));
	for(k=0;k<steps;k++)
	{
		x+=xinc;
		y+=yinc;
		setPixel(round(x), round(y));
	}
}

//Function fills one row of chessbord with alternate black and white color
void fillRow(GLint x1,GLint y1,GLint x2,GLint y2,GLfloat c)
{
    while(x1<end_x)
	{
		glColor3f(c,c,c);
		glRecti(x1,y1,x2,y2);
		x1=x2;	
		x2+=10;
		if(c==0.0)
			c=1.0;
		else
			c=0.0;
	}
}

void display(void)
{
	GLint i=0,a,b;
	a=start_x;
	b=start_y;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,0.0);
	while(i<9)
	{
		lineDDA(a,start_y,a,end_y);
		a+=10;
		lineDDA(start_x,b,end_x,b);
		b+=10;
		i++;
	}
	GLint x1=start_x,y1=end_y,x2=start_x+10,y2=end_y-10;
	GLfloat cl=0.0;
	while(y1>start_y)
	{
		fillRow(x1,y1,x2,y2,cl);
		if(cl==0.0)
			cl=1.0;
		else
			cl=0.0;
		y1=y2;
		y2-=10;
	}
	glFlush();
}
