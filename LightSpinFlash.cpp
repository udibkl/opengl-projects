#include <stdlib.h>
#include <math.h>
#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>

/* It was possible to make this program through the use of the books:

Dave Shreiner. (2010). OPENGL Programming Guide 7th edition. 
The Official Guide to Learning Open GL, Versions 3.0 and 3.1. 
The Khronos OPENGL ARB Working Group.

and

F.S. Hill, JR., Stephen M. (2007). Kelley Computer Graphics Using Open GL. 
Pearson International Edition

*/

GLfloat theta;
GLfloat rot = 1.0;
GLfloat lookx = -100, looky = -100, lookz = -100;

void init(void)
{
    // Clear the color of the window and set the color
    // to (0.0, 0.0, 0.0, 0.0)
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // defines the Shade Model either
    // FLAT with each pixel treated with
    // same shading, or SMOOTH with each pixel's
    // color resulting from interpolation
    glShadeModel(GL_SMOOTH);

    // Enable the Light Source and
    // assign it to the identifier GL_LIGHT0
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // used to eliminate hidden surface
    // (try to remove glEnable(GL_DEPTH_TEST);)
    glEnable(GL_DEPTH_TEST);

}

void rayTracing(void)
{

    int nRows = 20;
    int nCols = 20;
    float length = 1.0;

    // The topmost matrix is copied
    // so that its contents are duplicated
    // and located in the topmost and
    // second from the top matrices
    glPushMatrix();
    // The Light Source is temporarily disabled
    glDisable(GL_LIGHTING);
    // The color is set to (0.0, 0.0, 0.0)
    glColor3f(0.0, 0.0, 0.0);
    // The Light Source assigned to the identifier
    // GL_LIGHT0 is enabled
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // The rotations about the Z, Y and X
    // axis are given to the rays just
    // to be traced below
    glRotatef(theta, 0.0, 0.0, rot);
    glRotatef(theta, 0.0, rot, 0.0);
    glRotatef(theta, rot, 0.0, 0.0);

    // Trace the rays
    for (int row = 0; row < nRows; row++)
    {
        for (int col = 0; col < nCols; col++)
        {
            // compute the rays directions
            glBegin(GL_LINES);
            glVertex2f(0,0);
            glVertex2f( length + row, length + col );
            glEnd();
        }
    }

    // Removes the topmost matrix
    // The second from the top matrices
    // becomes the topmost matrix
    glPopMatrix();

}


void display(void)
{
	// sets a position
	GLfloat position [] = {0.0, 0.0, 1.5, 1.0};

	// Clear the COLOR_BUFFER 
	// and the DEPTH_BUFFER (used for hidden
	// surfaces removal)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// The topmost matrix is copied 
	// so that its contents are duplicated 
	// and located in the topmost and 
	// second from the top matrices
	glPushMatrix();

	/////// BEGING OF THE EXERCISE /////////
	// Positioning of the Scene
	// at (0.0, 0.0, -5.0)
	glTranslatef(0.0, 0.0, -5.0);


	
	// Rotation of the Torus about the Z axis
    glRotatef(theta, 0.0, 0.0, rot);


	
	// projects the rays of light
	rayTracing();



	
	// Rotation of the Light Source GL_LIGHT0
	// and the Torus: Choose a set of custom
	// rotations
    glRotatef(theta, 0.0, 0.0, 1.0);



	// Create the Light Source specified by GL_LIGHT0 with the 
	// characteristic to be a positioned light at the position
	// indicated through GLfloat position [] = {0.0, 0.0, 1.5, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glDisable(GL_LIGHTING);
    glEnable(GL_LIGHT0);




	// Draw green Cube while temporarily 
	// disabling the Light Source
	// position the green cube at Z = 1.5
    glDisable(GL_LIGHT0);
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
    glTranslatef(0.0, 1.0, 0.0);
    glRotatef(theta, 0.0, 1.0, 1.0);
    glutWireCube(0.2);
    glPopMatrix();




	// Draw the red Cube while temporarily 
	// disabling the Light Source
	// position the red cube at Z = 1.5 - 1.5 = 0
	glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(theta, 0.0, 1.0, 1.0);
    glutWireCube(0.15);
    glPopMatrix();



	// Enable the Light Source
	// GL_LIGHT0 again
    glEnable(GL_LIGHT0);
	


	
	// Define (-100, -100, -100) as the point in the center of the scene being looked at
	// Since the command gluLookAt defines a viewing matrix, the point (-100, -100, -100)
	// becomes practically the center of the scene
	gluLookAt(8.0, 8.0, 8.0, lookx, looky, lookz, 0.0, 0.0, 1.0);



	// Draw Torus
	// void SolidTorus(GLdouble innerRadius, GLdouble outerRadius, GLint nsides, GLint rings)
	glutSolidTorus(0.6, 1.8, 30, 30);


	// Removes the topmost matrix
	// The second from the top matrices
	// becomes the topmost matrix
	glPopMatrix();


	// swap buffers 
	// (You have 2 buffers:
	// see *** in the main function of the program)
	glutSwapBuffers();



	/////// END OF THE EXERCISE /////////


}

void reshape(int w, int h)
{
	// While reshaping sets the size of the viewport
	// the same as the size of the viewing window
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);

	// When used with the parameter GL_PROJECTION,
	// the command glMatrixMode() specifies that 
	// the subsequent transformation matrices are
	// made to the 'Projection Matrix': in this
	// case both of glLoadIdentity() and gluPerspective().
	glMatrixMode(GL_PROJECTION);

	// Load the Identity Matrix
	glLoadIdentity();

	// void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble near, GLdouble far)
	// Creates a matrix for symmetric perspective-view 
	// and multiplies the current matrix by it. 
	// fovy is the angle of the field of view in the YZ plane, 
	// its value must be in the range [0, 180]. 
	// aspect is the aspect ratio, which is width divided 
	// by height. near and far values are the distances 
	// between the viewpoint and the clipping planes along 
	// the Z axis. near and far should always be positive.
	// (try remove the command: gluPerspective(40.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);) 
	gluPerspective(40.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);

	// Now the command glMatrixMode() is called
	// with the parameter GL_MODELVIEW, which means
	// that the subsequent transformation matrices 
	// will be applied to the 'ModelView' Matrix (The current matrix)
	// instead of the 'Projection Matrix'
	glMatrixMode(GL_MODELVIEW);

	// Load the Identity Matrix
	glLoadIdentity();

}

// sets the value of the 
// rotational angle theta
void spin(void) 
{

theta += (double)0.17;
if(theta > 360.0) theta -=360.0;

// Practically causes the command:
// glutMainLoop() to call display()
// to render again (try remove the
// command: glutPostRedisplay();)
glutPostRedisplay();

}


int main(int argc, char **argv)
{
  
  glutInit(&argc, argv);

  // *** specifies a display mode, in this case the
  // display mode is a double buffer (GLUT_DOUBLE):
  // 1. RGB color model (GLUT_RGB) and 2. Depth buffer (GLUT_DEPTH)
  // used to remove hidden surfaces
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  
  // sets the Viewing Window Size
  glutInitWindowSize(500, 500);
  
  // set the Viewing Window position onto the screen
  glutInitWindowPosition(100,100);

  // Create the Viewing Window and assign it with
  // the name which is the argument passed to the
  // function glutCreateWindow()
  glutCreateWindow("Light Spin Flash");

  // call the function init()
  init();
  // receives as input the display function
  glutDisplayFunc(display);
  // receives as input the reshape function
  glutReshapeFunc(reshape);
  // specifies the function, 'spin' in this 
  // case, to be executed, if no other events
  // are pending. If NULL is passed
  // as argument, then the execution is disabled
  glutIdleFunc(spin);
  // enters the GLUT processing loop never to return
  glutMainLoop();
  
  return 0;             /* ANSI C requires main to return int. */

}