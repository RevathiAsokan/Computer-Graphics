#include<GL/glut.h>
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

float et[4][4]={{100,250,200,-1},
{100,250,200,1},
{200,150,300,1},
{200,350,300,-1}};
int np=4;
float ae[4][3];
float js=100;
int iaet=0;
int ymax=0;

void addaet()
{
	int i;
	
	for(i=0;i<np;i++)
	{
		printf("Scan line=%f & iate=%d\n",js,iaet);
		
		if(js==et[i][0])
		{
			ae[iaet][0]=et[i][1];
			ae[iaet][1]=et[i][2];		
			ae[iaet][2]=et[i][3];

			if(ae[iaet][1]>ymax) ymax=ae[iaet][1];
				iaet++;
		}
	}
}


void upaet()
{
	int i;
		
	for(i=0;i<np;i++)
		ae[i][0]=ae[i][0]+ae[i][2];
}

void draw_pixel(float x1,float x2)
{
	int i;
	float n;

	for(i=0;i<1000;i++)
	for(n=x1;n<x2;n++)
	{
		glColor3f(1.0,1.0,0.0);
		glBegin(GL_POINTS);
		glVertex2f(n,js);
		glEnd();
		glFlush();
	}

	printf(" x1=%f x2=%f\n",x1,x2);
}


void fill_tri()
{
	float x[3]={0,0,0};
	int i=0;
	bool done=false;

	do
	{
		i=0;
		addaet();
		printf(" 1=%f 2=%f%f\n",ae[0][1],ae[1][1],js);
		
		if(ae[0][1]>js)
		{
			x[i]=ae[0][0];
			i++;
			printf(" 1=%f ae=%f\n",ae[0][0],x[0]);
		}
		if(ae[1][1]>js)
		{
			x[i]=ae[1][0];
			i++;
			printf(" 1=%f ae=%f\n",ae[0][0],x[0]);
		}
		if(ae[2][1]>js)
		{
			x[i]=ae[2][0];
			i++;
		}
		if(ae[3][1]>js)
		{
			x[i]=ae[3][0];
			i++;
		}
		
		draw_pixel(x[0],x[1]);
		upaet();
		js++;
	}

	while(js<=ymax);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0,0.0,0.0,1.0);
	fill_tri();
	glFlush();
}

void myinit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,499.0,0.0,499.0);
	glMatrixMode(GL_MODELVIEW);
	//glFlush();
}

void main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(400,400);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Polygon filling algorithm");
	myinit();
	glutDisplayFunc(display);
	glutMainLoop();
}
	


		







