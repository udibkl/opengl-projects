#define _CRT_SECURE_NO_WARNINGS

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <cstdio>
#include <cstdlib>
#include <process.h>
#include <malloc.h>
#include <iostream>
#include <fstream>
#include <string>

#define SCALE 255

#define DU 1
#define UD 2
#define LR 3
#define RL 4
#define QUIT 0

using namespace std;

double *ImageData = 0;
FILE * logfile;

int planeWindow;
GLfloat  * planeWindowImage; 

int setflagvalue=0;

void reshape(int w, int h);
void init();
void OnImageDisplay(char m_VolumeFileName[], int rcxres_in, int rcyres_in, double m_Xsize_in, double m_Ysize_in, char dataLabelc_in);
void LaunchOpenGL();
double * data(char filename[], int rcxres, int rcyres);
void runOpenGL(void);
void TwoDdisplay(void);
void menu_select(int item);

void main ( int argc, char * argv[] ) {

	if (argc < 4) { std::cout << endl;
				 std::cout << "Please type the image file name" << endl;
				 std::cout << "Please enter the number of pixels along the X direction (integer)" << endl;
				 std::cout << "Please enter the number of pixels along the Y direction (integer)" << endl;
				 std::cout << endl;
				 exit(0); }

  // run the program (begin)
  printf("\n");
  printf("THE PROGRAM DISPLAY AN IMAGE\n");
  printf("Use the menu to Flip the Image and then Reshape the Window to see the result\n");
  printf("\n");

  OnImageDisplay(argv[1], atoi(argv[2]), atoi(argv[3]), 1.0, 1.0, 'D');

} // end of main

void OnImageDisplay(char m_VolumeFileName[], int rcxres_in, int rcyres_in, double m_Xsize_in, double m_Ysize_in, char dataLabelc_in) 
{
	
	int rcxres = rcxres_in;
	int rcyres = rcyres_in;
	double m_Xsize = m_Xsize_in;
	double m_Ysize = m_Ysize_in;

	/// make the keyboard ///
	FILE * pointTokeyboardFile;
	char keyboard[128]="keyboard.txt";

	std::cout << "Initial Pixel Size in X: " << m_Xsize << endl;
	std::cout << "Initial Pixel Size in Y: " << m_Ysize << endl;

	if ((pointTokeyboardFile = fopen(keyboard,"w"))==NULL)
	{

    fprintf(logfile,"%s\n", "Cannot Open File: keyboard.txt: Exit");
	exit(0);
	
	}else{


	fprintf(pointTokeyboardFile,"%d\n", rcxres);

	fprintf(pointTokeyboardFile,"%d\n", rcyres);

	fprintf(pointTokeyboardFile,"%lf\n", m_Xsize);

	fprintf(pointTokeyboardFile,"%lf\n", m_Ysize);
	
	fclose(pointTokeyboardFile);


	}


	char logfilename[300];

	sprintf(logfilename, "%s%s%s", "ImageViewer", m_VolumeFileName, ".log");
	
    if ((logfile = fopen(logfilename,"w"))==NULL)
	{

	 exit(0);
	
	}

	fprintf(logfile,"%s\t %s\n", "Processing the Image: ", m_VolumeFileName);

	fprintf(logfile,"%s\t %d\n", "X Matrix Resolution: ", rcxres);

	fprintf(logfile,"%s\t %d\n", "Y Matrix Resolution: ", rcyres);

	fprintf(logfile,"%s\t %lf\n", "X Pixel Size: ", m_Xsize);

	fprintf(logfile,"%s\t %lf\n", "Y Pixel Size: ", m_Ysize);

	fprintf(logfile,"%s\t %c\n", "Data Type: ", dataLabelc_in);

	fclose(logfile);

	std::cout << "Visualizing the Image: " << m_VolumeFileName << endl;

	ImageData = data(m_VolumeFileName, rcxres, rcyres);
 
	if( (planeWindowImage = (float *) malloc( rcyres * rcxres * 3 * sizeof(float) )) == NULL )
	{
		std::cout << "Memory Allocation Failure" << endl;
		
	    free(ImageData);
		
		exit(0);
	}
 	
	runOpenGL();

}

void runOpenGL(void)
{

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	//plane window
	glutInitWindowSize(200, 200);
	glutInitWindowPosition(100, 100);	
	init();

	// pg. 19. int glutCreateWindow(char *string) creates a window with an OpenGL
    // context. It returns a unique identifier for the new window. 
    // Until glutMainLoop() is called, the window is not yet displayed.
	planeWindow = glutCreateWindow("XY VIEW: FLIP THE IMAGE THEN RESHAPE");
	// pg. 732 Before you can open a window, you must specify its characteristics. Should
	// it be single-buffered or double-buffered? Should it store colors as RGBA values
	// or as color indices? Where should it appear on your display? To specify
	// the answers to these questions, call glutInit(), glutInitDisplayMode(),
	// glutInitWindowSize(), and glutInitWindowPosition() before you call
	// glutCreateWindow() to open the window.
	
	// pg. 733 The value returned is a unique integer identifier for the window. This
	// identifier can be used for controlling and rendering to multiple windows
	// (each with an OpenGL rendering context) from the same application.

	glutDisplayFunc(TwoDdisplay); 
	

	// menu related functions (begin)
	glutCreateMenu(menu_select);

	glutAddMenuEntry("Flip U/D", UD);
	glutAddMenuEntry("Flip D/U", DU);
	glutAddMenuEntry("Flip L/R", LR);
	glutAddMenuEntry("Flip R/L", RL);
	glutAddMenuEntry("QUIT", QUIT);
	
	glutAttachMenu(GLUT_LEFT_BUTTON);
	// menu related functions (ends)

	glutReshapeFunc(reshape);

	glutMainLoop(); 

}

double * data(char filename[], int rcxres, int rcyres)
{

     FILE *pf;
     
	 int j,i,k2;
     double number = 0;
     double *pointer = 0;

    if ((pf = fopen(filename,"rb+"))==NULL)
	{

		exit(0);

	} else { // else (1)
		 
		if ((pointer = (double *) calloc( rcyres*rcxres, sizeof(double)) ) == NULL)
		{

			fprintf(logfile,"%s\n", "Not enough memory to allocate Image data");

			exit(0);

		}
	        
		for(j=0;j<rcyres;j++){
		
			for(i=0;i<rcxres;i++){
            			     
				fread(&number,sizeof(double),1,pf);
      
				k2 = ((int) ((rcyres - j - 1) * rcxres) + (rcxres - i - 1));

				*(pointer+k2) = (double)number;

           }
		}

        fclose (pf);

		/// compute max and min of data (begins)
		double max = *(pointer);
		double min = *(pointer);
					
		for(j=0;j<rcyres;j++){
		
			for(i=0;i<rcxres;i++){
							     
				k2=(j*rcxres+i);

				if( *(pointer+k2) > (double)max ) 
			
					max = (double)*(pointer+k2);
              
				if( *(pointer+k2) < (double)min ) 
			
					min = (double)*(pointer+k2);
		
				}
		}
		/// compute max and min of data (end)

	    // scale (begin)
		for(j=0;j<rcyres;j++){
		
			for(i=0;i<rcxres;i++){
							     
				k2=(j*rcxres+i);

				if ( max == min ) *(pointer+k2) = (double) 0.0;

				else *(pointer+k2) = (double) SCALE * (double) fabs( ((double)(min - (double)*(pointer+k2))) / ((double) (min - max)) );
				// the absolute vale is needed otherwise the minimum is -0 which is nonsense in computers. The value -0 was discovered
				// printing to the screen. Mathematically, the scaling formula gives values in between [0, SCALE] and not [-0, SCALE].
				// Therefore the nonsense is removed taking the absolute value of:
				// (double) fabs( ((double)(min - (double)*(pointer+k2))) / ((double) (min - max)) );	
		}   
	}
	// scale (end)

    std::cout << "IMAGE DATA LOADED AND SCALED" << endl;        	 
	
	}// else (1)

	return pointer;    
	
}// end of funct

void menu_select(int item)
{

	int j, i, k3, k4;

    // Variables that can be retrieved from file: 'keyboard.txt' 
	int rcxres;
	int rcyres;

	double PSPY;
	double PSPX;

	/// now read the matrix resolution from file: 'keyboard.txt' (begin)///
	FILE * pointToKeyboardFile;

	char keyboard[128]="keyboard.txt";

	if ((pointToKeyboardFile = fopen(keyboard,"r"))==NULL)
	{

	std::cout << "Cannot Open File: keyboard.txt: Now Exit" << endl;
	
	free(ImageData);
	free(planeWindowImage);
	
	exit(0);
	
	}else{


	fscanf(pointToKeyboardFile,"%d\n", &rcxres);

	fscanf(pointToKeyboardFile,"%d\n", &rcyres);

    fscanf(pointToKeyboardFile,"%lf\n", &PSPX);
	
	fscanf(pointToKeyboardFile,"%lf\n", &PSPY);
   
	fclose(pointToKeyboardFile);

	}
	
	std::cout << "Menu Supported Pixel Size in X: " << PSPX << endl;
	std::cout << "Menu Supported Pixel Size in Y: " << PSPY << endl;

	std::cout << "Menu: The number of Pixels along X is: " << rcxres << endl;
	std::cout << "Menu: The number of Pixels along Y is: " << rcyres << endl;
	/// now read the matrix resolution from file: 'keyboard.txt' (end)///

	// pointer used for flipping the image. The memory freed at the end of 
	// the function 'void menu_select(int item)' with free(pointer). This 
	// pointer has local visibility into the function 'void menu_select(int item)'
	float * pointer = 0;

	if ((pointer = (float *) calloc( rcyres*rcxres, sizeof(float)) ) == NULL)
		{

			fprintf(logfile,"%s\n", "Not enough memory to allocate Image data");

			free(ImageData);
			free(planeWindowImage);

			exit(0);

		}

if (item == UD &&  setflagvalue != UD)
  {

	if(glutGetWindow() == planeWindow)
	{ // planeWindow

		// flip the image Up Down (begins)
		// 1. store the image in 'pointer' (begins)
		for(j=0;j<rcyres;j++){
  
			for(i=0;i<rcxres;i++){

				k3 = (j*rcxres+i);

				*(pointer+k3) = *(ImageData+k3);
				
			}
		}
		// 1. store the image in 'pointer' (ends)
		// 2. flip the image Up Down (begins)
		for(j=0;j<rcyres;j++){
  
			for(i=0;i<rcxres;i++){

				k3 = (j*rcxres+i);
				k4 = ((int) ((rcyres - j - 1) * rcxres) + (rcxres - i - 1));

				*(ImageData+k3) = *(pointer+k4);
				
			}
		}
		// 2. flip the image Up Down (ends)
		// flip the image Up Down (ends)

	// render the image (begins)
	for(j=0;j<rcyres;j++){
  
		for(i=0;i<rcxres;i++){

			k3 = (j*rcxres+i);

			*(planeWindowImage + k3)   = (GLfloat) *(ImageData+k3)/SCALE;
	
			*(planeWindowImage + k3*2) = (GLfloat) *(ImageData+k3)/SCALE;
	
			*(planeWindowImage + k3*3) = (GLfloat) *(ImageData+k3)/SCALE;

                      }
                    }

 glDrawBuffer(GL_FRONT);
 glRasterPos2i(0,0);
 glPixelZoom((GLfloat) PSPX, (GLfloat) PSPY);
 glDrawPixels((GLsizei)rcxres, (GLsizei)rcyres, GL_LUMINANCE, GL_FLOAT, planeWindowImage);

 setflagvalue = UD;
 // render the image (ends)

		 } // if planeWindow

	} // if item

if (item == DU  &&  setflagvalue != DU)
  {

	if(glutGetWindow() == planeWindow)
	{ // planeWindow

		// flip the image Down Up (begins)
		// 1. store the image in 'pointer' (begins)
		for(j=0;j<rcyres;j++){
  
			for(i=0;i<rcxres;i++){

				k3 = (j*rcxres+i);

				*(pointer+k3) = *(ImageData+k3);
				
			}
		}
		// 1. store the image in 'pointer' (ends)
		// 2. flip the image Down Up (begins)
		for(j=0;j<rcyres;j++){
  
			for(i=0;i<rcxres;i++){

				k3 = (j*rcxres+i);
				k4 = ((int) ((rcyres - j - 1) * rcxres) + (rcxres - i - 1));

				*(ImageData+k3) = *(pointer+k4);
				
			}
		}
		// 2. flip the image Down Up (ends)
		// flip the image Down Up (ends)

	for(j=0;j<rcyres;j++){
  
		for(i=0;i<rcxres;i++){

			k3 = (j*rcxres+i);

			k4 = ((int) ((rcyres - j - 1) * rcxres) + (rcxres - i - 1));

			*(planeWindowImage + k4)   = (GLfloat) *(ImageData+k3)/SCALE;
	
			*(planeWindowImage + k4*2) = (GLfloat) *(ImageData+k3)/SCALE;
	
			*(planeWindowImage + k4*3) = (GLfloat) *(ImageData+k3)/SCALE;

							}
             
					}

 glDrawBuffer(GL_FRONT);
 glRasterPos2i(0,0);
 glPixelZoom((GLfloat) PSPX, (GLfloat) PSPY);
 glDrawPixels((GLsizei)rcxres, (GLsizei)rcyres, GL_LUMINANCE, GL_FLOAT, planeWindowImage);

 setflagvalue = DU;

		 } // if planeWindow

	} // if item

if (item == LR &&  setflagvalue != LR)
  {

	if(glutGetWindow() == planeWindow)
	{ // planeWindow

		// flip the image left right (begins)
		// 1. store the image in 'pointer' (begins)
		for(j=0;j<rcyres;j++){
  
			for(i=0;i<rcxres;i++){

				k3 = (j*rcxres+i);

				*(pointer+k3) = *(ImageData+k3);
				
			}
		}
		// 1. store the image in 'pointer' (ends)
		// 2. flip the image left right (begins)
		for(j=0;j<rcyres;j++){
  
			for(i=0;i<rcxres;i++){

				k3 = (j*rcxres+i);
				k4 = ((int) (j * rcxres) + (rcxres - i - 1));
				
				*(ImageData+k3) = *(pointer+k4);
				
			}
		}
		// 2. flip the image left right (ends)
		// flip the image left right (ends)

	for(j=0;j<rcyres;j++){
  
		for(i=0;i<rcxres;i++){

			k3 = (j*rcxres+i);
			k4 = ((int) ((rcyres - j - 1) * rcxres) + (rcxres - i - 1));

			*(planeWindowImage + k4)   = (GLfloat) *(ImageData+k3)/SCALE;
	
			*(planeWindowImage + k4*2) = (GLfloat) *(ImageData+k3)/SCALE;
	
			*(planeWindowImage + k4*3) = (GLfloat) *(ImageData+k3)/SCALE;

                      }
                    }

 glDrawBuffer(GL_FRONT);
 glRasterPos2i(0,0);
 glPixelZoom((GLfloat) PSPX, (GLfloat) PSPY);
 glDrawPixels((GLsizei)rcxres, (GLsizei)rcyres, GL_LUMINANCE, GL_FLOAT, planeWindowImage);

 setflagvalue = LR;

		 } // if planeWindow

	} // if item
	

if (item == RL &&  setflagvalue != RL)
  {

	if(glutGetWindow() == planeWindow)
	{ // planeWindow

		// flip the image right left (begins)
		// 1. store the image in 'pointer' (begins)
		for(j=0;j<rcyres;j++){
  
			for(i=0;i<rcxres;i++){

				k3 = (j*rcxres+i);

				*(pointer+k3) = *(ImageData+k3);
				
			}
		}
		// 1. store the image in 'pointer' (ends)
		// 2. flip the image right left (begins)
		for(j=0;j<rcyres;j++){
  
			for(i=0;i<rcxres;i++){

				k3 = (j*rcxres+i);
				k4 = ((int) (j * rcxres) + (rcxres - i - 1));
				
				*(ImageData+k3) = *(pointer+k4);
				
			}
		}
		// 2. flip the image right left (ends)
		// flip the image right left (ends)

	for(j=0;j<rcyres;j++){
  
		for(i=0;i<rcxres;i++){

			k3 = (j*rcxres+i);
			k4 = ((int) ((rcyres - j - 1) * rcxres) + (rcxres - i - 1));

			*(planeWindowImage + k4)   = (GLfloat) *(ImageData+k3)/SCALE;
	
			*(planeWindowImage + k4*2) = (GLfloat) *(ImageData+k3)/SCALE;
	
			*(planeWindowImage + k4*3) = (GLfloat) *(ImageData+k3)/SCALE;
 
                      }
                    }

 glDrawBuffer(GL_FRONT);
 glRasterPos2i(0,0);
 glPixelZoom((GLfloat) PSPX, (GLfloat) PSPY);
 glDrawPixels((GLsizei)rcxres, (GLsizei)rcyres, GL_LUMINANCE, GL_FLOAT, planeWindowImage);
 

 setflagvalue = RL;

		 } // if planeWindow

} // if item

	if (item == QUIT)
	{

		free(ImageData);
		free(planeWindowImage);

		setflagvalue = QUIT;
		
		exit(0);

	}

	// pointer used for flipping the image. The memory freed at the end of 
	// the function 'void menu_select(int item)' with free(pointer). This 
	// pointer has local visibility into the function 'void menu_select(int item)'
	free(pointer);
}// end of function

void TwoDdisplay(void)
{
	int i, j, k3;
	
    // Variables that can be retrieved from file: 'keyboard.txt' 
	int rcxres;
	int rcyres;

	double PSPY;
	double PSPX;

	/// now read the matrix resolution from file: 'keyboard.txt' ///
	FILE * pointToKeyboardFile;

	char keyboard[128]="keyboard.txt";

	if ((pointToKeyboardFile = fopen(keyboard,"r"))==NULL)
	{

	std::cout << "Cannot Open File: keyboard.txt: Now Exit" << endl;

	free(ImageData);
	free(planeWindowImage);

	exit(0);
	
	}else{


	fscanf(pointToKeyboardFile,"%d\n", &rcxres);

	fscanf(pointToKeyboardFile,"%d\n", &rcyres);

    fscanf(pointToKeyboardFile,"%lf\n", &PSPX);
	
	fscanf(pointToKeyboardFile,"%lf\n", &PSPY);
   
	fclose(pointToKeyboardFile);

	}
	
	std::cout << "Display Pixel Size in X: " << PSPX << endl;
	std::cout << "Display Pixel Size in Y: " << PSPY << endl;

	std::cout << "The number of Pixels along X is: " << rcxres << endl;
	std::cout << "The number of Pixels along Y is: " << rcyres << endl;

	glClear(GL_COLOR_BUFFER_BIT);

	/// Your Input starts here

	// glutGetWindow() return value is 
	// compared to the value of the
	// identifier 'planeWindow' which
	// has been assigned the return value
	// from glutCreateWindow() (see runOpenGL())
	if(glutGetWindow() == planeWindow)
	{ // planeWindow

	for(j=0;j<rcyres;j++){
  
		for(i=0;i<rcxres;i++){

			k3 = (j*rcxres+i);
			
			*(planeWindowImage + k3)   = (GLfloat) *(ImageData+k3)/SCALE;
	
			*(planeWindowImage + k3*2) = (GLfloat) *(ImageData+k3)/SCALE;
	
			*(planeWindowImage + k3*3) = (GLfloat) *(ImageData+k3)/SCALE;
    
						}
                    }

	// When using glDrawPixels() to write RGBA or color-index information, you
	// may need to control the current drawing buffers with glDrawBuffer()
	// 'glDrawBuffer()' (pgs. 341, 343, 498) selects the color buffer enabled 
	// for writing or clearing. The value of mode is 'GL_FRONT' in this case.
	// You use glDrawBuffer() to select the buffer to be written
	glDrawBuffer(GL_FRONT);
 
	// pgs. 324-325. The current raster position is the screen position where the           
    // next bitmap (or image) is to be drawn.
	// void glRasterPos{234}{sifd}(TYPE x, TYPE y, TYPE z, TYPE w); sets the 
    // current raster position. The x, y, z, 
	// and w arguments specify the coordinates of the raster position. If the 
    // vector form of the function is used, 
	// the coords array contains the coordinates of the raster position. If 
    // glRasterPos2*() is used, z is implicitly 
	// set to zero and w is implicitly set to 1; glRasterPos2i(0, 0) positions the 
    // lower left corner of the image.
	// glRasterPos2i(0, 0) reliably positions an unzoomed image at the lower left 
    // of the viewport (pg. 2).
	glRasterPos2i(0, 0);

	// (pgs. 356, 648) You can also magnify or reduce a pixel rectangle before it’s 
    // drawn by calling glPixelZoom().
	// Normally, each pixel in an image is written to a single pixel on the screen. 
    // However, you can 
	// arbitrarily magnify, reduce, or even flip (reflect) an image by using 
    // glPixelZoom().
	// void glPixelZoom(GLfloat zoomx, GLfloat zoomy); Sets the magnification or 
    // reduction factors 
	// for pixel-write operations (glDrawPixels() and glCopyPixels()) in the x- and 
    // y-dimensions. 
	// By default, zoomx and zoomy are 1.0. If they’re both 2.0, each image pixel 
    // is drawn to 4 
	// screen pixels. Note that fractional magnification or reduction factors are 
    // allowed, as are 
	// negative factors. Negative zoom factors reflect the resulting image about 
    // the current raster 
	// position. A negative zoom can be useful for flipping an image. 
	glPixelZoom((GLdouble) PSPX, (GLdouble) PSPY);
	
    // 'glDrawPixels() (pgs. 333, 340, 506, 662)' Writes a rectangular array of 
    // pixels from data kept in
    // processor memory into the framebuffer at the current raster position specified 
    // by glRasterPos*().
    // void glDrawPixels(GLsizei width, GLsizei height, GLenum format, GLenum type, 
    // const GLvoid *pixels);
    // Draws a rectangle of pixel data with dimensions width and height. The pixel 
    // rectangle is drawn 
    // with its lower-left corner at the current raster position. format and type can 
    // be retreived from
    // Table 8-1 and Table 8-2. format (for instance 'GL_LUMINANCE') indicates the 
    // kind of pixel data 
    // elements that are read (a color-index, depth, or stencil value or an R, G, B, 
    // or A component 
    // value, as listed in Table 8-1), and type indicates the data type (for instance 
    // 'GL_FLOAT') 
    // of each element (see Table 8-2). The array 'planeWindowImage' pointed to by 
    // pixels contains 
    // the pixel data to be drawn. GL_LUMINANCE indicates a single luminance 
    // component.	
    glDrawPixels((GLsizei)rcxres, (GLsizei)rcyres, GL_LUMINANCE, GL_FLOAT, planeWindowImage);
 
	glFlush();

	} // planeWindow


	/// Your Input ends here

} // end of function


void init()
{

	int winx, winy;

	int rcxres;
	int rcyres;
	double PSPX, PSPY;
	
	/// now read the matrix resolution from file: 'keyboard.txt' ///
	FILE * pointToKeyboardFile;
	char keyboardFile[128]="keyboard.txt";


	if ((pointToKeyboardFile = fopen(keyboardFile,"r"))==NULL)
	{

	std::cout << "Cannot Open File: keyboard.txt: Now Exit" << endl;
	 
	free(ImageData);
	free(planeWindowImage);

	exit(0);
	
	}else{	

	fscanf(pointToKeyboardFile,"%d\n", &rcxres);

	fscanf(pointToKeyboardFile,"%d\n", &rcyres);
	
	fscanf(pointToKeyboardFile,"%lf\n", &PSPX);

	fscanf(pointToKeyboardFile,"%lf\n", &PSPY);

	fclose(pointToKeyboardFile);

	}
    

    winx=(int)rcxres*PSPX;
	winy=(int)rcyres*PSPY;

	std::cout << "rcx in X: " << rcxres << endl;
	std::cout << "rcy in Y: " << rcyres << endl;

	std::cout << "win in X: " << winx << endl;
	std::cout << "win in Y: " << winy << endl;

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);

	if(glutGetWindow() == planeWindow) 
	{

	glViewport(0, 0, (GLsizei)winx, (GLsizei)winy);
	glLoadIdentity();

	// To convert the mathematical description of objects and their associated
	// color information to pixels on the screen. This process is called
	// rasterization.

	// If exact two-dimensional rasterization is desired, you must carefully
	// specify both the orthographic projection and the vertices of primitives
	// that are to be rasterized. The orthographic projection should be specified
	// with integer coordinates, as shown in the following example: gluOrtho2D(0, width, 0, height);
	// where width and height are the dimensions of the viewport.

	// pgs. 157, 158. void gluOrtho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top);
	// Creates a matrix for projecting two-dimensional coordinates onto the screen and 
	// multiplies the current projection matrix by it. The clipping region is a rectangle 
	// with the lower left corner at (left, bottom) and the upper right corner at (right, top).
	// For the special case of projecting a two-dimensional image onto a twodimensional
	// screen, use the Utility Library routine gluOrtho2D(). This routine is identical to the 
	// three-dimensional version, glOrtho(), except that all the z coordinates for objects in 
	// the scene are assumed to lie between -1.0 and 1.0. If you’re drawing two-dimensional 
	// objects using the two-dimensional vertex commands, all the z coordinates are zero; 
	// thus, no object is clipped because of its z-value.

	gluOrtho2D(0.0, (GLdouble)winx, 0.0, (GLdouble)winy);

	}

}


void reshape(int w, int h)
{

	int rcxres;
	int rcyres;
	
	double valueX = 0, valueY = 0;

    /// now read the matrix resolution from file: 'keyboard.txt' ///
	FILE * pointToKeyboardFile;
	char keyboardFile[128]="keyboard.txt";

	if ((pointToKeyboardFile = fopen(keyboardFile,"r"))==NULL)
	{

	std::cout << "Cannot read keyboard file" << endl;
	
	free(ImageData);
	free(planeWindowImage);

	exit(0);
	
	}else{

	fscanf(pointToKeyboardFile,"%d\n", &rcxres);

	fscanf(pointToKeyboardFile,"%d\n", &rcyres);
	
	fscanf(pointToKeyboardFile,"%lf\n", &valueX);
	
	fscanf(pointToKeyboardFile,"%lf\n", &valueY);

	fclose(pointToKeyboardFile);

	}
    

	std::cout << "Current Pixel Size in X: " << valueX << endl;
	std::cout << "Current Pixel Size in Y: " << valueY << endl;

	std::cout << "N of Pixels in X: " << rcxres << endl;
	std::cout << "N of Pixels in Y: " << rcyres << endl;

	//// initialize variables: PSPX, PSPY
	double PSPX = (double)valueX;
	double PSPY = (double)valueY;
	////								   ////    

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);

	if(glutGetWindow() == planeWindow) 
	{

	PSPX=((double)w/rcxres);
	PSPY=((double)h/rcyres);
	
	}

	// Once the windows' size is changed:
    // re-write keyboard.txt containing the modified values of 
	// the variables: double PSPX; double PSPY;

	std::cout << "Current Pixel Size in X now: " << PSPX << endl;
	std::cout << "Current Pixel Size in Y now: " << PSPY << endl;

	if ((pointToKeyboardFile = fopen(keyboardFile,"w"))==NULL)
	{

	std::cout << "Cannot Open File keyboard.txt: Now Exit" << endl;

	free(ImageData);
	free(planeWindowImage);
	
	exit(0);
	
	}else{

	fprintf(pointToKeyboardFile,"%d\n", rcxres);
	fprintf(pointToKeyboardFile,"%d\n", rcyres);

	if(glutGetWindow() == planeWindow) 
	{
	
	fprintf(pointToKeyboardFile,"%lf\n", PSPX);
	fprintf(pointToKeyboardFile,"%lf\n", PSPY);

	}

	fclose(pointToKeyboardFile);

	}

}// end of funct

