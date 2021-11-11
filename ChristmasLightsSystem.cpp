#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

GLfloat thetaSun = 0, thetaMoon = 0;
GLfloat rot = 1.0;
GLfloat eyex = -3.0, eyey = -3.0, eyez = -3.0;

int counterRainbowColor = 0;
GLfloat* VenusMoonColorTray = new GLfloat[]{0.0, 1.0, 0.0, 1.0};
GLfloat* MarsMoonColorTray = new GLfloat[]{0.0, 1.0, 1.0, 1.0};
GLfloat* MarsColor = new GLfloat[]{0.0, 0.0, 1.0, 1.0};
GLfloat* SunColor = new GLfloat[]{1.0, 1.0, 0.0, 1.0};
GLfloat* VenusColor = new GLfloat[]{1.0, 0.0, 1.0, 1.0};
GLfloat* PlutoColor = new GLfloat[]{0.5, 0.5, 1.0, 1.0};

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
}

void DrawSun(void) {

    // 1. set the color yellow
    glColor3f(SunColor[0], SunColor[1], SunColor[2]);

    // 2. spin of the sun about its own Y axis
    glRotatef(thetaSun, 0.0, 1.0, 0.0);

    // 3. draw sun
    glutWireSphere(0.3, 40, 40);
}

void DrawMars(void) {

    // 1. set the color red
    glColor3f(MarsColor[0], MarsColor[1], MarsColor[2]);

    // 2. positioning of Mars
    // Mars revolves around the sun
    // because inherits the rotation from
    // the sun, once its position is determined
    // through: glTranslatef(1.0, 0.0, 0.0);
    glTranslatef(1.0, 0.0, 0.0);

    // 3. Wire Mars
    glutWireSphere(0.1, 20, 20);
}

void DrawMarsMoon(void) {
    // 1. set the color to white
    glColor3f(MarsMoonColorTray[0], MarsMoonColorTray[1], MarsMoonColorTray[2]);

    // 1. set Venus' Moon in rotation about the Y axis
    glRotatef(thetaMoon, 0.0, 1.0, 1.0);
    glRotatef(thetaMoon, 1.0, 0.0, 1.0);
    glRotatef(thetaMoon, 1.0, 1.0, 0.0);

    // 2. positioning of Mars' moon
    // the moon inherits the rotations
    // from the sun - (0.5, 0.0, 0.0);
    glTranslatef(0.5, 0.0, 0.0);

    // 3. wire Mars' moon
    glutWireSphere(0.05, 20, 20);

}

//Rainbow Colors for Tray Rays
void updateRainbowColor(GLfloat RainbowColor[], int threshold) {
    if(threshold == 0) {
        return;
    }

    //reset counter from time to time
    if(counterRainbowColor > 1000)
        counterRainbowColor = 0;

    if (counterRainbowColor % threshold == 0) {
        RainbowColor[0] += GLfloat(rand() % 10) / 100;
        if (RainbowColor[0] > 1)
            RainbowColor[0] -= 1;
        RainbowColor[1] += GLfloat(rand() % 10) / 100;
        if (RainbowColor[1] > 1)
            RainbowColor[1] -= 1;
        RainbowColor[2] += GLfloat(rand() % 10) / 100;
        if (RainbowColor[2] > 1)
            RainbowColor[2] -= 1;
    }
}
void RayTracing(GLfloat Color[], int thresholdRainbowColor = 0.0) {
    int nRows = 20;
    int nCols = 20;
    float length = 1.0;

    // the colors along the line
    // segments are interpolated between the vertex colors.
    glShadeModel(GL_SMOOTH);

    // Create the Light Source specified by GL_LIGHT2
    // with the characteristic to be a positioned light at the position
    // indicated through GLfloat position [] = {0.0, 0.0, 1.0, 1.0};
    glLightfv(GL_LIGHT2, GL_DIFFUSE, Color);// pgs.214-227
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
    for (int row = 0; row < nRows; row++) {
        for (int col = 0; col < nCols; col++) {
            // compute the rays directions
            glBegin(GL_LINES);
            glVertex2f(0, 0);
            glVertex2f(length + row, length + col);
            glEnd();
        }
    }

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT2);

    if(thresholdRainbowColor > 0.0) {
        updateRainbowColor(Color, thresholdRainbowColor);
    }
}

void DrawVenus(void) {
    // 1. Set the color for Venus to magenta
    glColor3f(VenusColor[0], VenusColor[1], VenusColor[2]);

    // 2. go back to the sun position in two steps:
    //glTranslatef(-1.5, 0, 0);
    //glTranslatef(-0.5,0.5,0.5);
    //glTranslatef(-1.0,0.5,0.5);

    // 2. spin of the sun about its own Y axis
    glRotatef(thetaSun, 0.0, 1.0, 0.0);

    // 3. Now move along the z axis (1.0)
    glTranslatef(0.0, 0.0, 1.3);

    // 4. Wire Venus
    glutWireSphere(0.1, 20, 20);
}

void DrawVenusMoon(void) {
    // 1. set Venus' Moon in rotation about the Y axis
    glRotatef(thetaMoon, 0.0, 1.0, 0.0);
    glRotatef(thetaMoon, 1.0, 0.0, 1.0);
    glRotatef(thetaMoon, 1.0, 1.0, 0.0);

    // 2. Now move along the z axis again (0.5)
    glTranslatef(0.0, 0.0, 0.5);

    // 3. Change color
    glColor3f(VenusMoonColorTray[0], VenusMoonColorTray[1], VenusMoonColorTray[2]);

    // 4. Wire Venus moon
    glutWireSphere(0.05, 20, 20);
}

void DrawPluto() {
    // 1. spin of the sun about its own Y axis
    glRotatef(thetaSun, 1.0, 0.5, 0.0);

    // 2. Now move along the z axis again (0.5)
    glTranslatef(0.0, 0.0, 1.5);

    // 3. Change color
    glColor3f(PlutoColor[0], PlutoColor[1], PlutoColor[2]);

    // 4. Wire Venus moon
    glutWireSphere(0.05, 20, 20);
}

void display(void) {
    glClearDepth(1.0); // clears the buffers of the screen, the default depth-clearing value is 1.0.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // pg. 35, 36, pg. 496

    glPushMatrix();

    // 1. draw the sun
    DrawSun();
    updateRainbowColor(SunColor, 15);

    // 2. draw Mars
    DrawMars();
    updateRainbowColor(MarsColor, 25);

    // 3. draw Mars' moon
    DrawMarsMoon();
    RayTracing(MarsMoonColorTray, 15);

    glPopMatrix();
    glPushMatrix();

    // 4. draw Venus
    DrawVenus();
    updateRainbowColor(VenusColor, 35);

    // 5. draw Venus' moon
    DrawVenusMoon();
    RayTracing(VenusMoonColorTray, 15);

    glPopMatrix();
    glPushMatrix();

    DrawPluto();
    updateRainbowColor(PlutoColor, 45);

    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void reshape(int w, int h) {

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


void spin(void) {

    thetaSun += (double) 0.05;
    if (thetaSun > 360.0) {
        thetaSun -= 360.0;
    }

    thetaMoon += (double) 0.15;
    if (thetaMoon > 360.0) {
        thetaMoon -= 360.0;
    }

    counterRainbowColor += 1;

    glutPostRedisplay();

}

void mouse(int btn, int state, int x, int y) {
// The mouse function uses the right button (GLUT_RIGHT_BUTTON) 
// to exit the program in the state clicked (GLUT_DOWN).
    if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        exit(0);

}

void main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("SolarSystem");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutIdleFunc(spin);
    glutMainLoop();

}
