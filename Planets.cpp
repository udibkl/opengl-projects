#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

/*
Dave Shreiner. (2010). OPENGL Programming Guide 7th edition. The Official Guide to Learning Open GL, Versions 3.0 and 3.1. 
The Khronos OPENGL ARB Working Group.
*/

GLfloat theta;
GLfloat rot = 1.0;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	
}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);

	// Step 1:
	// set the color to blue
	glColor3f(0.0,0.0,1.0);
	
	
	// Step 2:
	// The topmost matrix is copied 
	// so that its contents are duplicated 
	// and located in the topmost and 
	// second from the top matrices
	// see fig. 3-21 pg. 166
	glPushMatrix();
	
	
	// Step 3:
	// rotate about the axis defined by:
	// (0.0, 0.0, 0.0) and (rot, rot, 0.0);
	glRotatef(theta, rot, rot, 0.0);
	

	// Step 4:
	// rotate about the axis defined by:
	// (0.0, 0.0, 0.0) and (rot, 0.0, rot);
	glRotatef(theta,rot,0.0,rot);
	

	// Step 5:
	// rotate about the axis defined by:
	// (0.0, 0.0, 0.0) and (0.0, rot, rot);
	glRotatef(theta,0.0,rot,rot);

	// Step 6:
	// draw sun (wire a sphere)
	glutWireSphere(0.5,20,20);
	

	// Step 7: 
	// translate of 2.0 along X (only)
	glTranslatef(2.0,0.0,0.0);

	// Step 8:
	// draw planet (wire a sphere)
	glutWireSphere(0.5,20,20);
	 

	// Step 9:
	// A. Removes the topmost matrix
	// The second from the top matrices
	// becomes the topmost matrix
	glPopMatrix();
	

	//B. reDraw the buffer from scratch for each frame displayed
	glutSwapBuffers();
	

}

void reshape(int w, int h)
{

	// Step 10:
	// set the viewport the same size of the window
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);


	// Step 11:
	// use glMatrixMode with argument 'GL_PROJECTION'
	glMatrixMode(GL_PROJECTION);
	
	
	// Step 12:
	// Load the Identity matrix
	glLoadIdentity();
	

	// Step 13:
	// Set the viewing volume:
	gluPerspective((GLdouble)60.0,(GLdouble) w / (GLdouble) h, (GLdouble) 1.0, (GLdouble)20.0);
	
	/* Creates a matrix for a symmetric perspective-view frustrum and multiplies the current matrix by it.
	   fovy is the angle of the field of view in the yz-plane; its value must be in the range [0.0, 180.0].
	   aspect is the aspect ratio of the frustrum, its width divided by its height. near and far values
	   are the distances between the viewpoint and the clipping planes, along the negative z-axis. They
	   should always be positive (see fig. 3-14 pg. 155) */

	// fovy = 60.0, GLdouble aspect = (GLfloat) w / (GLfloat) h, 
	// GLdouble near = 1.0, GLdouble far = 20.0


	// Step 14:
	// use glMatrixMode with argument 'GL_MODELVIEW'
	glMatrixMode(GL_MODELVIEW);
	
	
	// Step 13:
	// Load the Identity matrix
	glLoadIdentity();
	

	// Step 14:
	// Set the camera position:
	// (eyex, eyey, eyez) = (0.0, 0.0, 5.0)
	// (lookx, looky, lookz) = (0.0, 0.0, 0.0)
	// (Upx, Upy, Upz) = (0.0, 1.0, 0.0)
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	
	

}

void spin(void)
{

theta += (double)0.1;
if(theta > 360.0) theta -=360.0;

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
  glutCreateWindow("Planets");
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse); 
  glutIdleFunc(spin);
  glutMainLoop();
  
  return 0;             /* ANSI C requires main to return int. */

}
