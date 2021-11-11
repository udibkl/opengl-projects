#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

/* It was possible to make this program through the use of the books:

Dave Shreiner. (2010). OPENGL Programming Guide 7th edition. 
The Official Guide to Learning Open GL, Versions 3.0 and 3.1. 
The Khronos OPENGL ARB Working Group.

and

F.S. Hill, JR., Stephen M. (2007). Kelley Computer Graphics Using Open GL. 
Pearson International Edition

*/

#define winx 400
#define winy 400
#define M_PI 3.14
#define M 15

GLfloat theta = 0, theta1 = 0, theta2 = 0;
int mode;
int ox, oy;


void reshape(int w, int h);
void init(void);
void display(void);
void mouse(int btn, int state, int x, int y);

void init(void)
{

glClearColor(0.0, 0.0, 0.0, 0.0);
glShadeModel(GL_FLAT);

}

void display(void) {

glClearColor(0.0, 0.0, 0.0, 0.0); 

glClearDepth(1.0); 

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

glMatrixMode(GL_MODELVIEW); 

glPushMatrix(); 

//// Your code begins here

// Step 1:
// set color to blue
glColor3f(0.0,0.0,1.0);



// Step 2:
// translate of (0.0, 0.0, -5.0)
glTranslatef(0.0, 0.0, -5.0);



// Step 3:
// rotate of theta about the axis passing through (0.0, 0.0, 0.0) & (1.0, 0.0, 0.0);
glRotatef(theta,1.0,0.0,0.0);

// Step 4:
// wireSphere
glutWireSphere(0.5,20,20);

// Step 5:
// set color to red
glColor3f(1.0,0.0,0.0);


// Step 6:
// rotate of theta1 about the axis passing through (0.0, 0.0, 0.0) & (0.0, 1.0, 0.0);
glRotatef(theta1,0.0,1.0,0.0);

// Step 7:
// wireSphere
glutWireSphere(0.3,20,20);

// Step 8:
// set color to green
glColor3f(0.0,1.0,0.0);


// Step 9:
// rotate of theta2 about the axis passing through (0.0, 0.0, 0.0) & (0.0, 0.0, 1.0);
glRotatef(theta2,0.0,0.0,1.0);

// Step 10:
// wireSphere
glutWireSphere(0.1,20,20);

/// Your code ends here

glPopMatrix();

// pg. 38, 39: glFlush() is a command that is used when writing a program
// which we want to work properly both with and without a network.
// Usually the client gathers a collection of commands into a single network 
// packet before sending it. glFlush() forces the client to send the network packet 
// even though the network packet might not be full.
glFlush();

}

void reshape(int w, int h)
{
	
glViewport(0, 0, (GLsizei) w, (GLsizei)h);
	
glMatrixMode(GL_PROJECTION);

glLoadIdentity();
	 
gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);

glMatrixMode(GL_MODELVIEW);
	
}

void spin(void) 
{

theta += (double)10;
if(theta > 360.0) theta =-360.0;

theta1 += (double)50;
if(theta1 > 360.0) theta1 =-360.0;

theta2 += (double)100;
if(theta2 > 360.0) theta2 =-360.0;

glutPostRedisplay();

}


void motion(int x, int y)
{
static GLfloat ang=0;
static GLfloat eyez=0;
static GLfloat eyex=0, eyey=0;

if(mode==GLUT_LEFT_BUTTON){

ang+= ((GLfloat)(x-ox)/(GLfloat)winx) * M_PI;
eyez+=(GLfloat)(y-oy)/(GLfloat)winy;

glLoadIdentity();
glTranslatef(0.0, 0.0, M*eyez);
glRotatef((GLfloat)M*ang, 0.0, 0.0, 1.0);

glutPostRedisplay();

ox=x;
oy=y;
                          }

}

void mouse(int btn, int state, int x, int y)
{

if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN) 
{

ox=x;
oy=y;
}

if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN) 
{
exit(0);
}

}

int main(int argc, char** argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(winx,winy);
glutInitWindowPosition(100,100);
glutCreateWindow("Spheres"); 
init();
glutMouseFunc(mouse);
glutMotionFunc(motion);
glutIdleFunc(spin);
glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutMainLoop();

return 0;
}
