#include <stdlib.h>
#include <GL/glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>

/*
Dave Shreiner. (2010). OPENGL Programming Guide 7th edition. The Official Guide to Learning Open GL, Versions 3.0 and 3.1. 
The Khronos OPENGL ARB Working Group.
*/

GLfloat thetaSun = 0, thetaSatellite = 0;
GLfloat thetaMoon = 0;
GLfloat rot = 1.0;


void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	
}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	
	////beginning of the exercise///

	// Step 1: 
	// push matrix
	glPushMatrix();
	
	// Step 2:
	// A. Set the color
	// B. rotate about an axis of your choice
	// C. Wire Sphere (radius = 0.3) -> Sun
    glColor3f(0.5, 0.2, 0.3);
    glRotatef(thetaSun, 0.0, 0.0, rot);
    glutWireSphere(0.3, 15, 15);


	// Step 3:
	// A. Set the color
	// B. translate away from the Sun (x = 2.0)
	// C. Wire sphere (radius = 0.1) -> Planet
	// note that the Planet inherits the rotation
	// from the Sun
    glColor3f(1.0, 0.0, 2.0);
    glTranslatef(2.0, 0.0, 0.0);
    glutWireSphere(0.1, 7, 10);



	//Step 4: 
	// pop matrix
	glPopMatrix();


	// Step 5:
	// push matrix
	glPushMatrix();


	// Step 6:
	// Because of the previous two pop matrix
	// and push matrix you have reset the matrix
	// pipeline. So, only the next transformations
	// will be applied to the next objects. The
	// next objects will not inherit from the 
	// previous two planets.
	// A. Set the color
	// B. translate (x = -1.0)
	// C. Rotate using thetaMoon as angle and Y as axis.
	// D. Wire the sphere (radius = 0.1) -> Moon
	// Note that this time you translate first and then rotate.
	// Which means that the Y axis passes through the center of
	// gravity of the Moon, the Moon will not rotate around the Sun
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(-1.0, 0.0, 0.0);
	glRotatef(thetaMoon, 0.0, rot, 0.0);
    glutWireSphere(0.1, 7, 10);




	// Step 7:
	// pop matrix
	glPopMatrix();


	// Step 8:
	// push matrix
	glPushMatrix();


	// Step 9:
	// Because of the previous two pop matrix
	// and push matrix you have reset the matrix
	// pipeline. So, only the next transformations
	// will be applied to the next objects. The
	// next objects will not inherit from the 
	// previous three planets.
	// A. Set the color
	// B. Rotate using thetaSatellite as angle 
	// and Y as axis.
	// C. translate (x = 2.0)
	// D. Wire the sphere (radius = 0.1) -> Satellite

	// Note that this time you rotate first and then translate.
	// That means (versus the Moon) that the object will start
	// rotating then is shifted and so the rotation is about
	// Y axis not passing from the center of gravity of the satellite
	// Which means the object will rotate around the Sun
    glColor3f(0.0, 0.0, 1.0);
    glRotatef(thetaSatellite, 0.0, rot, 0.0);
    glTranslatef(2.0, 0.0, 0.0);
    glutWireSphere(0.1, 7, 10);



	
	// Step 10: 
	// pop matrix
    glPopMatrix();




	// STEP 11:
	// Now introduce with the method
	// outlined in Step 9 a new satellite
	// with color magenta and with rotation
	// about an axis not passing through its
	// center of gravity -> use the angle thetaSatellite

	// Total: 6 lines of code
	// Here:
	glPushMatrix();
	glColor3f(1.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
	glRotatef(thetaSatellite, rot, 0.0, rot);
	glutWireSphere(0.1, 7, 10);
	glPopMatrix();
	glFlush();



	
	////end of the exercise///

	glutSwapBuffers();
	// reDraw the buffer from scratch for each frame displayed

}

void reshape(int w, int h)
{

	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);
	/* void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble near, GLdouble far)
	   Creates a matrix for a symmetric perspective-view frustrum and multiplies the current matrix by it.
	   fovy is the angle of the field of view in the yz-plane; its value must be in the range [0.0, 180.0].
	   aspect is the aspect ratio of the frustrum, its width divided by its height. near and far values
	   are the distances between the viewpoint and the clipping planes, along the negative z-axis. They
	   should always be positive (see fig. 3-14 pg. 155)*/
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	

}

void spin(void)
{

thetaSun += (double)0.3;
if(thetaSun > 360.0) thetaSun -=360.0;

thetaSatellite += (double)0.1;
if(thetaSatellite > 360.0) thetaSatellite -=360.0;

thetaMoon += (double)0.5;
if(thetaMoon > 360.0) thetaMoon -=360.0;

glutPostRedisplay();

}

void mouse(int btn, int state, int x, int y)
{
// The mouse function uses the right button (GLUT_RIGHT_BUTTON) 
// to exit the program in the state clicked (GLUT_DOWN).
if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN) 
exit(0);

}
int main(int argc, char **argv)
{
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100,100);
  glutCreateWindow("Flash");
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse); 
  glutIdleFunc(spin);
  glutMainLoop();
  
  return 0;             /* ANSI C requires main to return int. */

}
