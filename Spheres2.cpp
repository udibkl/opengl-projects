// The commented lines here reported are found in:
// Dave Shreiner (2010). OPEN GL Programming Guide 7th edition. 
// The Official Guide to Learning Open GL, Versions 3.0 and 3.1. 	
// The Khronos OPENGL ARB Working Group.
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define winx 400
#define winy 400

GLfloat theta = 0, theta1 = 0, theta2 = 0;

GLfloat xx = 0, yy = 0, zz = 0; 
GLfloat rot = 0;

void reshape(int w, int h);
void init(void);
void display(void);
void mouse(int btn, int state, int x, int y);

void RayTracingWhite(void);
void RayTracingBlue(void);
void RayTracingRed(void);

void init(void)
{

glClearColor(0.0, 0.0, 0.0, 0.0);

// glShadeModel(GLenum mode): pg. 200; Sets the shading model. The mode parameter can be either
// GL_SMOOTH (which is the default) or GL_FLAT. With flat shading (GL_FLAT), the color at each 
// vertex is the same, whereas with smoooth shading (GL_SMOOTH), the color at each vertex is treated 
// individually. For instance when using GL_SMOOTH in drawing a line, the colors along the line 
// segments are interpolated between the vertex colors.
glShadeModel(GL_FLAT);

}

void display(void) {

// pg. 251: Alpha values controls blending. When blending is enabled, the alpha value is often used 
// to combine the color value of the fragment being processed with that of the pixel already
// stored in the buffer.
glClearDepth(1.0); // clears the buffers of the screen, the default depth-clearing value is 1.0.

// pg. 493: The color buffer is the one which is used for drawing. In general, the color buffer contains
// color data in RGB and may also contain Alpha values.
	
// pg. 494: Depth buffer: stores a depth value for each pixel. The depth is measured in terms of
// the distance to the eye, so pixels with larger depth-buffer values are overwritten by pixels
// with smaller values.

// pg. 494: The stencil buffer is used to restrict drawing to certain portions of the screen.
// For example the program draws all of the instruments and components of a car once, and 
// as the car moves, only the outside scene needs to be updated.

// pg. 494: The accumulation buffer holds RGBA color data just as the color buffer does in RGBA mode.
// The use of the accumulation buffer is usually that one of accumulating a series of images into a
// final, composite image. Usually the programmer do not draw directly in the accumulation buffer.
// Usually accumulation operations are transfers of data to or from a color buffer.
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // pg. 35, 36, pg. 496


// pg. 132, 133: Two basic types of projections are provided by OpenGL. One type is the 
// perspective projection (pg. 153), which matches how you see things in daily life. Perspective 
// makes objects that are farther away appear smaller, for example, it makes railroad 
// tracks appear to converge. The perspective projection is governed through the command:
// gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble near, GLdouble far) see figure 3-14
// pg. 155.

// The other type of projection is the orthographic (pg. 157) which 
// maps directly onto the screen without affecting their relative sizes. 
// The orthographic projection is governed through the command:
// glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far)
// see figure 3-15 pg. 157.


// Step 1:
// The topmost matrix is copied 
// so that its contents are duplicated 
// and located in the topmost and 
// second from the top matrices
// see fig. 3-21 pg. 166
glPushMatrix();

// draw the sphere at the center of the scene (begins):

// Step 2:
// glTranslate{fd}(TYPE x, TYPE y, TYPE z); pg. 141
// Multiplies the current matrix by a matrix that moves (translates) an
// object by the given x, y, and z values: (0.0, 0.0, -5.0);
 glTranslatef(0.0, 0.0, -5.0);

// Step 3:
// Multiplies the current matrix by a matrix that rotates the object (or the local coordinate 
// system) of an angle 'angle' in a counterclokwise direction about the ray from the origin 
// through the point (1.0, 1.0, 1.0).
glRotatef(theta, 1.0, 1.0, 1.0);


// Step 4:
// Wire the sphere
// pgs. 21, 172, 735 
glutWireSphere(0.3,15,15);

// Step 5:
// call to function RayTracingWhite();

// draw the sphere at the center of the scene (ends)
RayTracingWhite();

// Step 6:
// draw the second sphere (begins):

// A. rotate of theta1 about the axis defined by:
// (0.0, 0.0, 0.0) - (0.0, 1.0, 0.0) 
glRotatef(theta1, 0.0, 1.0, 0.0);

// B. translate of (0.0, 0.0, rot)

glTranslatef(0.0, 0.0, rot);


// C. Wire the Sphere
// pgs. 21, 172, 735
glutWireSphere(0.2,5,5);

//D.  call to function RayTracingBlue();
RayTracingBlue();
 
// draw the second sphere (ends)


// draw the third sphere (begins):

// Step 7:
// A. rotate of theta2 about the axis defined by
// (0.0, 0.0, 0.0) - (0.0, 0.0, 1.0)
 glRotatef(theta2, 0.0, 0.0, 1.0);

// B. Tranlate of (0.0, 0.0, rot);
 glTranslatef(0.0,0.0,rot);

// C. Wire sphere
// pgs. 21, 172, 735 
 glutWireSphere(0.2,5,5);

// call to function RayTracingRed();
RayTracingRed();
// draw the third sphere (ends):
  

	// Step 8:
	// A. Removes the topmost matrix
	// The second from the top matrices
	// becomes the topmost matrix
glPopMatrix();

	// B. pg. 38, 39: glFlush() is a command that is used when writing a program
	// which we want to work properly both with and without a network.
	// Usually the client gathers a collection of commands into a single network 
	// packet before sending it. glFlush() forces the client to send the network packet 
	// even though the network packet might not be full.
	// forces prevously issued commands to 
	// begin execution ('try to remove glFlush();')
	glFlush();

}/*end of display*/

void reshape(int w, int h)
{

	// Step 9:
	// While reshaping sets the size of the viewport
	// the same as the size of the viewing window
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	

	// Step 10:
	// Load the Identity Matrix 
	// (assure reshaping)
	glLoadIdentity();
	
	// Step 11:
	// Creates a matrix for symmetric perspective-view 
	// and multiplies the current matrix by it. 
	// fovy is the angle of the field of view in the YZ plane, 
	// its value must be in the range [0, 180]. 
	// aspect is the aspect ratio, which is width divided 
	// by height. near and far values are the distances 
	// between the viewpoint and the clipping planes along 
	// the Z axis. near and far should always be positive:
	// fovy = 40.0, GLdouble aspect = (GLfloat) w / (GLfloat) h, 
	// GLdouble near = 1.0, GLdouble far = 20.0
    gluPerspective((GLdouble) 40.0, (GLdouble) w / (GLdouble) h, (GLdouble) 1.0, (GLdouble) 20.0);
	
}

void spin(void) 
{

theta += (double)0.01;
if(theta > 360.0) theta -=360.0;

theta1 += (double)0.03;
if(theta1 > 360.0) theta1 -=360.0;

theta2 += (double)0.06;
if(theta2 > 360.0) theta2 -=360.0;


if(xx >= 0.0 && xx < 0.75) 
{ xx += 0.0001; }
else if (xx >= 0.75 && xx <= 1.5) 
{ xx -= 0.0001; }

if(yy >= 0.0 && yy < 0.75) 
{ yy += 0.0001; }
else if (yy >= 0.75 && yy <= 1.5) 
{ yy -= 0.0001; }

if(zz >= 0.0 && zz < 0.75) 
{ zz += 0.0001; }
else if (zz >= 0.75 && zz <= 1.5) 
{ zz -= 0.0001; }

float r = 0.5;
rot = (xx - r)*(xx - r) + (yy - r)*(yy - r) + (zz - r)*(zz - r) + r; 


glutPostRedisplay();

}


void mouse(int btn, int state, int x, int y)
{

if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN) 
{
exit(0);
}

}

void RayTracingRed(void)
{

	int nRows = 20;
	int nCols = 20;
	float length = 1.0;

	// the colors along the line 
	// segments are interpolated between the vertex colors.
	glShadeModel(GL_SMOOTH);

	// Create the Light Source specified by GL_LIGHT2 
	// with the characteristic to be a positioned light at the position
	// indicated through GLfloat position [] = {0.0, 0.0, 1.0, 1.0};
	 GLfloat Red [] = {1.0, 0.0, 0.0, 1.0};	
	 glLightfv(GL_LIGHT2, GL_DIFFUSE, Red);// pgs.214-227
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

}

void RayTracingBlue(void)
{

	int nRows = 20;
	int nCols = 20;
	float length = 1.0;

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

}

void RayTracingWhite(void)
{

	int nRows = 20;
	int nCols = 20;
	float length = 1.0;

	// the colors along the line 
	// segments are interpolated between the vertex colors.
	glShadeModel(GL_SMOOTH);

	// Create the Light Source specified by GL_LIGHT2 
	// with the characteristic to be a positioned light at the position
	// indicated through GLfloat position [] = {0.0, 0.0, 1.0, 1.0};
	 GLfloat White [] = {1.0, 1.0, 1.0, 1.0};	
	 glLightfv(GL_LIGHT2, GL_DIFFUSE, White);// pgs.214-227
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

}

void main(int argc, char** argv)
{

glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(winx,winy);
glutInitWindowPosition(100,100);
glutCreateWindow("Spheres"); 
init();
glutMouseFunc(mouse);
glutIdleFunc(spin);
glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutMainLoop();

}