#include <stdlib.h>
#include <math.h>
#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>

/* It was possible to make this program through the use of the books:

Dave Shreiner (2010). OPENGL Programming Guide 7th edition. 
The Official Guide to Learning Open GL, Versions 3.0 and 3.1. 
The Khronos OPENGL ARB Working Group.

and

F.S. Hill, JR., Stephen M. (2007). Kelley Computer Graphics Using Open GL. 
Pearson International Edition

author: Carlo Ciulla

*/

double theta = 0, bf = 0;
double oscillation = 0.0;

void init(void)
{
	// Clear the color of the window and set the color 
	// to (0.0, 0.0, 0.0, 0.0)
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// glShadeModel(GLenum mode): pg. 200; Sets the shading model. The mode parameter can be either
	// GL_SMOOTH (which is the default) or GL_FLAT. With flat shading (GL_FLAT), the color at each 
	// vertex is the same, whereas with smoooth shading (GL_SMOOTH), the color at each vertex is treated 
	// individually. For instance when using GL_SMOOTH in drawing a line, the colors along the line 
	// segments are interpolated between the vertex colors.
	glShadeModel(GL_SMOOTH);

	// Enable the Light Source and
	// assign it to the identifier GL_LIGHT0, //pgs.10, 54, 213
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
}

void RayTracing(void)
{

	int nRows = 20;
	int nCols = 20;
	float length = 1.0;

	// The topmost matrix is copied 
	// so that its contents are duplicated 
	// and located in the topmost and 
	// second from the top matrices
	// see fig. 3-21 pg. 166
	glPushMatrix();

	// the colors along the line 
	// segments are interpolated between the vertex colors.
	glShadeModel(GL_SMOOTH);

	// Create the Light Source specified by GL_LIGHT2 
	// with the characteristic to be a positioned light at the position
	// indicated through GLfloat position [] = {0.0, 0.0, 1.0, 1.0};
	 GLfloat Blue [] = {0.0, 0.0, 1.0, 1.0};	
	 glLightfv(GL_LIGHT2, GL_DIFFUSE, Blue);// pgs.214-227
	// syntax: glLight{if}(GL_ENUM light, GLenum pname, TYPE param), 
	// syntax: glLight{if}v(GL_ENUM light, GLenum pname, TYPE *param);
    // The characteristic of the light is defined by pname, which specifies
	// a named parameter (see Table 5-1, pg. 215).
	// 'param' indicates the values to which the 'pname' characteristic is set.
	// 'param' is a pointer to an array if the vector version is used OR
	// 'param' is the vaue itself if the non-vector version is used.
	// The nonvector version can be used to set only single-valued light characteristics:
	// Try: glLightf(GL_LIGHT2, GL_DIFFUSE, 45.0);

	// The Light Source assigned to the identifier
	// GL_LIGHT2 is enabled: //pgs. 10, 54, 213
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT2);

	// void glRotate{fd}(TYPE angle, TYPE x, TYPE y, TYPE z) // pgs. 142, 172
	// Multiplies the current matrix by a matrix that rotates the object (or the local coordinate 
    // system) of an angle 'angle' in a counterclokwise direction about the ray from the origin 
    // through the point (x, y, z).
    glRotatef(theta, 1.0, 1.0, 1.0);

	// STEP 1:
	// The rotations about the Z, Y and X
	// axis are given to the rays.
	// Choose your set of rotations
    glRotatef(theta, 0.0, 0.0, 1.0);
    glRotatef(theta, 0.0, 1.0, 0.0);
    glRotatef(theta, 1.0, 0.0, 0.0);




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

	// glClear(GL_COLOR_BUFFER_BIT); Clears the specified buffers to thir current clearing values
	// syntax: void glClear(GLbifield mask); The mask argument
	// is a logical OR combination of the values listed in Table 2-1, pg. 36
	// color buffer: GL_COLOR_BUFFER_BIT --> CHAPTER 4
	// depth buffer: GL_DEPTH_BUFFER_BIT --> CHAPTER 10
	// accumulation buffer: GL_ACCUM_BUFFER_BIT --> CHAPTER 10
	// stencil buffer: GL_STENCIL_BUFFER_BIT --> CHAPTER 10

	// pg. 493: The color buffer is the one which is used for drawing. In general, the color buffer contains
	// color data in RGB and may also contain Alpha values.
    glClear(GL_COLOR_BUFFER_BIT);
	
	// pg. 494: Depth buffer: stores a depth value for each pixel. The depth is measured in terms of
	// the distance to the eye, so pixels with larger depth-buffer values are overwritten by pixels
	// with smaller values.
    glClear(GL_DEPTH_BUFFER_BIT);

	// pg. 494: The stencil buffer is used to restrict drawing to certain portions of the screen.
    // For example the program draws all of the instruments and components of a car once, and 
    // as the car moves, only the outside scene needs to be updated.
    glClear(GL_STENCIL_BUFFER_BIT);

    // pg. 494: The accumulation buffer holds RGBA color data just as the color buffer does in RGBA mode.
    // The use of the accumulation buffer is usually that one of accumulating a series of images into a
    // final, composite image. Usually the programmer do not draw directly in the accumulation buffer.
	// Usually accumulation operations are transfers of data to or from a color buffer.
	glClear(GL_ACCUM_BUFFER_BIT); // pg. 35, 36, pg. 496
	
	// The topmost matrix is copied 
	// so that its contents are duplicated 
	// and located in the topmost and 
	// second from the top matrices
	// see fig. 3-21 pg. 166
	glPushMatrix();

	
	// STEP 2:
	// set into motion the rotational 
	// system of the planets.
	// Choose your set of rotations	
	glRotatef(theta, 0.0, 1.0, 1.0);
	glRotatef(theta, 1.0, 0.0, 1.0);
	glRotatef(theta, 1.0, 1.0, 0.0);






	// STEP 3:
	// Position 4 spheres at the corners of
	// the rectangle with vertices as:
	// (1.5, 1.5, 0.0); (-1.5, -1.5, 0.0);
	// (-1.5, 1.5, 0.0); (1.5, -1.5, 0.0);

	// Each time: A. Translate of the necessary
	// shift amount. B. Wire the sphere.
	// C. Call the function ' RayTracing(); '
	glPushMatrix();
	glTranslatef(1.5 + oscillation, 1.5 + oscillation, 0.0 + oscillation);
	glutWireSphere(0.4, 20, 20);
	RayTracing();
	glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5 + oscillation, -1.5 + oscillation, 0.0 + oscillation);
    glutWireSphere(0.4, 20, 20);
    RayTracing();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5 + oscillation, 1.5 + oscillation, 0.0 + oscillation);
    glutWireSphere(0.4, 20, 20);
    RayTracing();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5 + oscillation, -1.5 + oscillation, 0.0 + oscillation);
    glutWireSphere(0.4, 20, 20);
    RayTracing();
    glPopMatrix();

	// To have the oscillation effect use 
	// a variable that updates itself through
	// the spin function
















	// Removes the topmost matrix
	// The second from the top matrices
	// becomes the topmost matrix
	glPopMatrix();

	// reDraw the buffer from scratch for each frame displayed; see pgs. 24-25 
	glutSwapBuffers();
	// Try to remove the instruction glutSwapBuffers();
	// pg. 22, 23, 25. In the animation of this program the objects are redrawn with
	// two different buffers. To clear the screen and to draw a frame it takes some time. 
	// Most OpenGL implementations provide the program with double buffering,
	// which is the use of two color buffers. One buffer is displayed while the other buffer
	// is being drawn. When drawing of a frame is complete, the two buffers are swapped.
	// This is like a movie projector with only two frames (the buffer contains the frame)
	// in a loop: while one frame is being projected on the screen, an 'artist' is quick enough 
	// to erase and redrawing the frame that is not visible and which is going to be displayed next.
		
}


void reshape(int w, int h)
{
	// While reshaping sets the size of the viewport
	// the same as the size of the viewing window

	// pgs. 41, 134, 159: The command glViewport() sets the size of the viewport to be the entire
	// window. The fact that glViewport() takes the inputs (GLsizei)w, (GLsizei)h which are the
	// same inputs of the reshape(int w, int h), makes it possible to have the viewport size exactly 
	// the same size as the viewing window. 
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	// The first two inputs: 0 and 0 define the origin 
	// of the available screen space within the window. If the window changes size, the viewport
	// needs to change accordingly. The window system, not OpenGL, is responsible for opening a window on the
	// screen. The default size of the viewport is set to be the same size of the viewing window.

	// void glViewport(GLint x, GLint y, GLsizei width, GLsizei height) defines a rectangle where
	// the image is mapped. The (x, y) parameter specifies the lower left corner of the viewport
	// and 'width' and 'height' are the size of viewport rectangle. 

	// When used with the parameter GL_PROJECTION,
	// the command glMatrixMode() specifies that 
	// the subsequent transformation matrices are
	// made to the 'Projection Matrix': in this
	// case both of glLoadIdentity() and gluPerspective().
	glMatrixMode(GL_PROJECTION);
	// pg. 133, 135, 166: The command glMatrixMode() used with argument GL_PROJECTION indicates
	// that the current matrix specifies the projection transformation and that subsequent 
	// transformation calls affect the projection matrix. The command glMatrixMode() used 
	// with argument GL_MODELVIEW as the argument indicates that the susequent transformations 
	// now affect the modelview matrix instead of the projection matrix. To see both of 
	// modelview matrix and projection matrix see PPT: Addendum 12-2-2013

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
	gluPerspective(65.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);
	// the effect of 'gluPerspective' is that one of setting the boundaries of the 
	// viewing volume (frustrum) see figure 3-14 pg. 155.

	// (try remove the command: gluPerspective(40.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);) 


	// Now the command glMatrixMode() is called
	// with the parameter GL_MODELVIEW, which means
	// that the subsequent transformation matrices 
	// will be applied to the 'ModelView' Matrix (The current matrix)
	// instead of the 'Projection Matrix'
	glMatrixMode(GL_MODELVIEW);

	// Load the Identity Matrix
	glLoadIdentity();

	// (a) Use the command gluLookAt(...).
	// (b) use (eyex, eyey, eyez) = (0.0, 0.0, -5.0).
	// (c) define (0.0, 0.0, 0.0) as the point in the center of the scene being looked at
	// Since the command gluLookAt(...) defines a viewing matrix, the point (0.0, 0.0, 0.0)
	// becomes practically the center of the scene. (d) Set the up vector to be the Y axis.
	gluLookAt(0.0, 0.0, -5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

}

void motion (void)
{
		theta += (double)0.05;
		if (theta > 360) theta -= 360;
		

		// STEP 4:
		// use and update a variable that 
		// determines the oscillation effect
		// connect this variable to the code
		// you write in the display() function

		// Two lines of code:
        oscillation = oscillation + double(double(rand() % 100) / 1000.0);
        if(oscillation > 0.1)
            oscillation = 0.0;




		glutPostRedisplay();
}

int main(int argc, char **argv)
{
  
  glutInit(&argc, argv);

  // specifies a display mode, in this case the
  // display mode is either a single buffer (GLUT_SINGLE)
  // or a RGB color model (GLUT_RGB) or a depth buffer (GLUT_DEPTH)
  // used to remove hidden surfaces
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  
  // sets the Viewing Window Size
  glutInitWindowSize(500, 500);
  
  // set the Viewing Window position onto the screen
  glutInitWindowPosition(100,100);

  // Create the Viewing Window and assign it with
  // the name which is the argument passed to the
  // function glutCreateWindow()
  glutCreateWindow("System");

  // call the function init()
  init();
  // receives as input the display function
  glutDisplayFunc(display);
  // receives as input the reshape function
  glutReshapeFunc(reshape);
  // specifies the function, 'motion' in this 
  // case, to be executed, if no other events
  // are pending. If NULL is passed
  // as argument, then the execution is disabled
  glutIdleFunc(motion);
  // enters the GLUT processing loop never to return
  glutMainLoop();
  
  return 0;             /* ANSI C requires main to return int. */

}