#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

GLfloat thetaSun = 0, thetaMoon;
GLfloat rot = 1.0; 
GLfloat eyex = -2.7, eyey = -2.7, eyez = -2.7;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void DrawSun(void){

	// 1. set the color yellow
	glColor3f(1.0,1.0,0.0);
	

	// 2. spin of the sun about its own Y axis
	glRotatef(thetaSun,0.0,1.0,0.0);
	

	// 3. draw sun
	glutWireSphere(0.3,20,20);

}

void DrawMars(void){

	// 1. set the color red
	glColor3f(1.0,0.0,0.0);
	

	// 2. positioning of Mars
	// Mars revolves around the sun
	// because inherits the rotation from
	// the sun, once its position is determined
	// through: glTranslatef(1.0, 0.0, 0.0);
	glTranslatef(1.0,0.0,0.0);
	

	// 3. Wire Mars
	glutWireSphere(0.1,20,20);
	

}

void DrawMarsMoon(void){

	// 1. set the color to white
	glColor3f(1.0,1.0,1.0);
	
	// 2. positioning of Mars' moon
    // the moon inherits the rotations
	// from the sun - (0.5, 0.0, 0.0);
	glTranslatef(0.5,0.0,0.0);

	
	
	// 3. wire Mars' moon
	glutWireSphere(0.05,20,20);
	
}

void DrawVenus(void){

	// 1. Set the color for Venus to magenta
	glColor3f(1.0,0.0,1.0);
	

	// 2. go back to the sun position in two steps:
	glTranslatef(-0.5,0.5,0.5);
	glTranslatef(-1.0,0.5,0.5);



	// 3. Now move along the z axis (1.0)
	glTranslatef(0.0,0.0,1.0);
	

	// 4. Wire Venus
	glutWireSphere(0.1,20,20);
	

}

void DrawVenusMoon(void)
{

	// 1. set Venus' Moon in rotation about the Y axis
	glRotatef(thetaMoon, 0.0, 1.0, 0.0);
	

	// 2. Now move along the z axis again (0.5)
	glTranslatef( 0.0, 0.0, 0.5);
	

	// 3. Change color 
	glColor3f(0.0,1.0,1.0);
	

	// 4. Wire Venus moon 
	glutWireSphere(0.05,20,20);
	

}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();

	// 1. draw the sun
	DrawSun();
	

	// 2. draw Mars
	DrawMars();
   

	// 3. draw Mars' moon
	DrawMarsMoon();
	

	// 4. draw Venus
	DrawVenus();

	// 5. draw Venus' moon
	DrawVenusMoon();
	
	
	glPopMatrix();

	glutSwapBuffers();
		
}

void reshape(int w, int h)
{

	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	
	glMatrixMode(GL_PROJECTION); // sets gluPerspective(...)
	glLoadIdentity(); // assure reshaping

	gluPerspective(30.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);
	/* void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble near, GLdouble far)
	   Creates a matrix for a symmetric perspective-view frustrum and multiplies the current matrix by it.
	   fovy is the angle of the field of view in the yz-plane; its value must be in the range [0.0, 180.0].
	   aspect is the aspect ratio of the frustrum, its width divided by its height. near and far values
	   are the distances between the viewpoint and the clipping planes, along the negative z-axis. They
	   should always be positive (see fig. 3-14 pg. 155)*/
	
	glMatrixMode(GL_MODELVIEW); // sets gluLookAt(...)
	glLoadIdentity(); // assure reshaping
	gluLookAt(eyex, eyey, eyez, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
}

void spin(void)
{

thetaSun += (double)0.05;
if(thetaSun > 360.0) thetaSun -=360.0;

thetaMoon += (double)0.15;
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
void main(int argc, char **argv)
{
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100,100);
  glutCreateWindow("SolarSystem");
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse); 
  glutIdleFunc(spin);
  glutMainLoop();
  
}
