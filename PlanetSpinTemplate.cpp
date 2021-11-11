#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

GLfloat thetaSun = 0, thetaSatellite = 0;
GLfloat thetaLight = 0;
GLfloat rot = 1.0;
GLfloat eyex = -2.7, eyey = -2.7, eyez = -2.7;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void RayTracing(void) {

    int nRows = 20;
    int nCols = 20;
    float length = 1.0;

    // the colors along the line
    // segments are interpolated between the vertex colors.
    glShadeModel(GL_SMOOTH);

    // Create the Light Source specified by GL_LIGHT2
    // with the characteristic to be a positioned light at the position
    // indicated through GLfloat position [] = {0.0, 0.0, 1.0, 1.0};
    GLfloat White[] = {1.0, 1.0, 1.0, 1.0};
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

    // The topmost matrix is copied
    // so that its contents are duplicated
    // and located in the topmost and
    // second from the top matrices
    // see fig. 3-21 pg. 166
    glPushMatrix();

    // void glRotate{fd}(TYPE angle, TYPE x, TYPE y, TYPE z) // pgs. 142, 172
    // Multiplies the current matrix by a matrix that rotates the object (or the local coordinate
    // system) of an angle 'angle' in a counterclokwise direction about the ray from the origin 
    // through the point (x, y, z).

    // Rotation of the rays
    glRotated(thetaLight, rot, 0.0, 0.0);
    glRotated(thetaLight, 0.0, rot, 0.0);
    glRotated(thetaLight, 0.0, 0.0, rot);

    // Removes the topmost matrix
    // The second from the top matrices
    // becomes the topmost matrix
    glPopMatrix();

    // Trace the rays
    for (int row = 0; row < nRows; row++) {
        for (int col = 0; col < nCols; col++) {
            // compute the rays directions
            glBegin(GL_LINES);
            glVertex2f(0, 0);
            glVertex2f(length + row, length + col);
            glEnd();
        }
    }
}


void DrawSun(void) {

    // Step 1:
    // A. spin the sun about Y axis:
    // look to the spin function to determine
    // which one is the angle to chose
    glRotatef(thetaSun, 0.0, 1.0, 0.0);

    // B. Wire a sphere using radius = 0.3,
    // then chose the other two parameters
    glutWireSphere(0.3, 20, 20);

    // C. Call the function: ' RayTracing() '
    RayTracing();

}

void DrawSatellite(void) {

    // Step 2:
    // positioning of the satellite:
    // translate of (1.0, 0.0, 0.0);
    // the satellite revolves around the sun
    // because inherits the rotation from the sun
    glTranslatef(1.0, 0.0, 0.0);


    // Step 3:
    // A. spin the satellite about Y axis:
    // look to the spin function to determine
    // which one is the angle to chose
    glRotatef(thetaSatellite, 0.0, 1.0, 0.0);

    // B. Wire a sphere using radius = 0.13,
    // then chose the other two parameters
    glutWireSphere(0.13, 20, 20);

    // C. Call the function: ' RayTracing() '
    RayTracing();

}

void DrawMoon(void) {

    // Step 4:
    // positioning of the moon:
    // translate of (0.5, 0.0, 0.0);
    glTranslatef(0.5, 0.0, 0.0);

    // Step 5:
    // Wire a sphere using radius = 0.05,
    // then chose the other two parameters
    // the moon inherits the rotations
    // from the sun and the satellite
    glutWireSphere(0.05, 20, 20);

}


void DrawSecondMoon(void) {

    // Step 6:
    // positioning of the moon:
    // translate of (0.2, 0.0, 0.0);
    glTranslatef(0.2, 0.0, 0.0);

    // Step 7:
    // Wire a sphere using radius = 0.05,
    // then chose the other two parameters
    // the moon inherits the rotations
    // from the sun and the satellite
    glutWireSphere(0.05, 20, 20);

}


void display(void) {

    glClear(GL_COLOR_BUFFER_BIT);

    // Step 8:
    // The topmost matrix is copied
    // so that its contents are duplicated
    // and located in the topmost and
    // second from the top matrices
    glPushMatrix();

    // Step 9, Step 10, Step 11, Step 12:
    // draw the solar system sun using the
    // appropriate function calls in the
    // correct order
    DrawSun();
    DrawSatellite();
    DrawMoon();
    DrawSecondMoon();

    // Step 13:
    // Removes the topmost matrix
    // The second from the top matrices
    // becomes the topmost matrix
    glPopMatrix();

    // Step 14:
    // swap the buffers
    glutSwapBuffers();
}

void reshape(int w, int h) {

    // Step 15:
    // While reshaping sets the size of the viewport
    // the same as the size of the viewing window
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);

    // Step 16:
    // Use ' glMatrixMode(GL_PROJECTION) '
    // sets gluPerspective(...)
    glMatrixMode(GL_PROJECTION);

    // Step 17:
    // Load the Identity Matrix
    // (assure reshaping)
    // initialize and assures reshaping
    glLoadIdentity();

    // Step 18:
    // Creates a matrix for symmetric perspective-view
    // and multiplies the current matrix by it.
    // fovy is the angle of the field of view in the YZ plane,
    // its value must be in the range [0, 180].
    // aspect is the aspect ratio, which is width divided
    // by height. near and far values are the distances
    // between the viewpoint and the clipping planes along
    // the Z axis. near and far should always be positive:
    // fovy = 30.0, GLdouble aspect = (GLfloat) w / (GLfloat) h,
    // GLdouble near = 1.0, GLdouble far = 20.0
    gluPerspective(30.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);


    // Step 19:
    // Use ' glMatrixMode(GL_MODELVIEW) '
    // sets gluLookAt(...)
    glMatrixMode(GL_MODELVIEW);

    // Step 20:
    // Load the Identity Matrix
    // (assure reshaping)
    // initialize and assures reshaping
    glLoadIdentity();

    // Step 21:
    // (a) Use the command gluLookAt(...).
    // (b) use (eyex, eyey, eyez) = (-2.7, -2.7, -2.7).
    // (c) define (0.0, 0.0, 0.0) as the point in the center of the scene being looked at
    // Since the command gluLookAt(...) defines a viewing matrix, the point (0.0, 0.0, 0.0)
    // becomes practically the center of the scene. (d) Set the up vector to be the Y axis.
    gluLookAt(eyex, eyey, eyez, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

}

void spin(void) {

    thetaSun += (double) 0.1;
    if (thetaSun > 360.0) thetaSun -= 360.0;

    thetaLight += (double) 0.01;
    if (thetaLight > 360.0) thetaLight -= 360.0;

    thetaSatellite += (double) 0.9;
    if (thetaSatellite > 360.0) thetaSatellite -= 360.0;

    // Step 22:
    // What GLUT function do you need
    // to call to see animation?
    glutPostRedisplay();

}

void mouse(int btn, int state, int x, int y) {
// The mouse function uses the right button (GLUT_RIGHT_BUTTON) 
// to exit the program in the state clicked (GLUT_DOWN).
    if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        exit(0);

}

void keyboard(unsigned char key, int x, int y) {

    switch (key) {
        case 127:

            thetaSun = (GLfloat) 0.1;
            thetaSatellite = (GLfloat) 0.9;
            thetaLight = (GLfloat) 0.01;

            break;
    }

    glutPostRedisplay();

}

void main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Step 23:
    // initialize a window having
    // your preferred size
    glutInitWindowSize(900, 600);

    // Step 24:
    // Initialize the window position
    // onto the screen at the beginning
    // of the program
    glutInitWindowPosition(100,100);

    // Step 25:
    // Create a Window and name it
    glutCreateWindow("SolarSystem");


    /////////
    init();
    /////////

    // Step 26:
    // What GLUT function you need
    // to call and what argument you
    // need to provide to the GLUT
    // function so to see the scene?
    glutDisplayFunc(display);



    /////////////////////////
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutIdleFunc(spin);
    glutKeyboardFunc(keyboard);
    /////////////////////////


    // Step 27:
    // What GLUT function you need
    // to call to run the program?
    glutMainLoop();

}