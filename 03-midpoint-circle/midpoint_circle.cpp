/* Program 3: Write a program to implement Mid point circle generation algorithm */

#include<GL/glut.h>
#include<stdio.h>

GLint radius;

class screenPoint
{
	private:
			GLint x,y;
	public:
			screenPoint()
			{
				x = 0;
				y = 0;
			}
			void setCoordinates(GLint xCoordinateValue, GLint yCoordinateValue)
			{
				x = xCoordinateValue;
				y = yCoordinateValue;
			}
			GLint getx () const
			{
				return x;
			}
			GLint gety () const
			{
				return y;
			}
			void incrementx ()
			{
				x++;
			}
			void decrementy ()
			{
				y--;
			}
};

void resize(int, int);
void display();
void setPixel(GLint, GLint);
void circleMidPoint(GLint, GLint, GLint);
void circlePlotPoints(GLint, GLint, screenPoint);

void main(int argc, char** argv)
{
	printf("Enter Radius value (less than 150):\n");
	scanf("%d",&radius);
	
	glutInit(&argc, argv);		//initialize GLUT 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//initialize display mode 
	glutInitWindowPosition(250,50);	 //set display-window upper-left position
	glutInitWindowSize(400,400);		//set display-window width & height
	glutCreateWindow("Circle using Mid Point Algorithm");	//create display-window with a title 
	glutDisplayFunc(display);		//call graphics to be displayed on the window 
	glutReshapeFunc(resize);		//calls whenever frame buffer window is resized
	glutMainLoop();		//display everything and wait 
}

void setPixel(GLint xCoordinate, GLint yCoordinate)
{
	glBegin(GL_POINTS);
	glVertex2i(xCoordinate, yCoordinate);
	glEnd();
	glFlush(); //process all OpenGL functions as quickly as possible
}

void resize(int w, int h)
{
	//set projection paramaters 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	gluOrtho2D(0.0,w,0.0,h); 
	glViewport(0.0, 0.0, w, h);
} 

void circleMidPoint(GLint xc, GLint yc, GLint raduis)
{
	screenPoint circlePoint;

	GLint p = 1-raduis;	//initialize value for midpoint parameter
	circlePoint.setCoordinates(0,raduis);  //set coordinates for top point of circle

	circlePlotPoints(xc, yc, circlePoint); //plot the initial point in each quadrant

	//calculate the next point and plot in each octant
	while(circlePoint.getx() < circlePoint.gety())
	{
		circlePoint.incrementx();
		if(p<0)
			p += 2 * circlePoint.getx() + 1;
		else
		{
			circlePoint.decrementy ();
			p += 2 * (circlePoint.getx () - circlePoint.gety ()) + 1;
		}
		circlePlotPoints(xc, yc, circlePoint);
	}
}

void circlePlotPoints(GLint xc, GLint yc, screenPoint circPoint)
{
	setPixel(xc + circPoint.getx () , yc + circPoint.gety ());
	setPixel(xc - circPoint.getx () , yc + circPoint.gety ());
	setPixel(xc + circPoint.getx () , yc - circPoint.gety ());
	setPixel(xc - circPoint.getx () , yc - circPoint.gety ());
	setPixel(xc + circPoint.gety () , yc + circPoint.getx ());
	setPixel(xc - circPoint.gety () , yc + circPoint.getx ());
	setPixel(xc + circPoint.gety () , yc - circPoint.getx ());
	setPixel(xc - circPoint.gety () , yc - circPoint.getx ());
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(0.0,0.0,1.0); 
	glPointSize(3.0);
	GLint xCenter=150;
	GLint yCenter=150;
	circleMidPoint(xCenter, yCenter, radius);
}


