#include <gl/glut.h>
#include <stdio.h>
#include <windows.h>
#include "Planeta.h"
#include "tga.h"

tgaInfo *im;
GLuint texture;
GLUquadric *mysolid;
GLfloat spin = 0.05;



void Planeta::CreatePlaneta(int radius, float distanceToSun, char imagePath[255])
	{
		this->radius = radius;
		this->distanceToSun = distanceToSun;
		strcpy_s(impathfile, imagePath);

	}

void Planeta::load_tga_image()
	{
		//char impathfile[255] = "images/earth.tga";
		//char impathfile[255];
		//strcpy(impathfile, imagePath);
		// Carrega a imagem de textura
		im = tgaLoad(impathfile);

		//printf("IMAGE INFO: %s\nstatus: %d\ntype: %d\npixelDepth: %d\nsize%d x %d\n", impathfile, im->status, im->type, im->pixelDepth, im->width, im->height);

		// allocate one texture name
		glGenTextures(1, &texture);

		// select our current texture
		glBindTexture(GL_TEXTURE_2D, texture);

		//	 set up quadric object and turn on FILL draw style for it
		mysolid = gluNewQuadric();
		gluQuadricDrawStyle(mysolid, GLU_FILL);

		//	// turn on texture coordinate generator for the quadric
		gluQuadricTexture(mysolid, GL_TRUE);

		// select modulate to mix texture with color for shading
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // MIPMAP
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// build our texture mipmaps
		//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, im->width, im->height, GL_RGB, GL_UNSIGNED_BYTE, im->imageData); // MIPMAP
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, im->width, im->height, 0, GL_RGB, GL_UNSIGNED_BYTE, im->imageData);

		// Destroi a imagem
		tgaDestroy(im);
	}

void Planeta::DrawPlaneta()
	{
		load_tga_image();

		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();

		gluLookAt(1.0, 1.0, -20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

		glEnable(GL_TEXTURE_2D);

		glColor4f(1.0, 1.0, 1.0, 1.0);

		// Select texture
		glBindTexture(GL_TEXTURE_2D, texture);


		// Draw sphere
		glPushMatrix();
		glTranslatef(distanceToSun, 0, 0);
		glRotatef(spin, 0.0, 0.0, 1.0);
		glRotatef(spin, 0.0, 1.0, 0.0);
		gluSphere(mysolid, radius, 100, 100);
		glPopMatrix();

		spin = spin + 0.1;
		if (spin > 360.0) spin = spin - 360.0;

		glDisable(GL_TEXTURE_2D);

		glutSwapBuffers();

		glFlush();


	}

	








