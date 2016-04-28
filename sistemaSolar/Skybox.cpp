#include "Skybox.h"
#include <gl/glut.h>
#include <stdio.h>
#include <windows.h>
#include "tga.h"
#include <cmath>


tgaInfo *im[6];

//GLUquadric *mysolid;
//GLfloat spin = 0.05;
GLuint texture[6];

void Skybox::CreateSkybox()
{
	load_tga_image();
	this->cX = 200;
	this->cY = 200;
	this->cZ = 200;
	
}

void Skybox::load_tga_image()
{
	

	char *impathfile[6] = { "images/skybox_front5.tga", "images/skybox_back6.tga", "images/skybox_right1.tga", "images/skybox_left2.tga", "images/skybox_top3.tga", "images/skybox_bottom4.tga" };
	int i;

	// Carrega as imagens de textura
	for (i = 0; i<6; i++)
	{
		im[i] = tgaLoad(impathfile[i]);

		printf("IMAGE INFO: %s\nstatus: %d\ntype: %d\npixelDepth: %d\nsize%d x %d\n", impathfile[i], im[i]->status, im[i]->type, im[i]->pixelDepth, im[i]->width, im[i]->height); fflush(stdout);
	}

	// Cria nomes de texturas
	glGenTextures(6, texture);

	for (i = 0; i<6; i++)
	{
		// Selecciona uma textura
		glBindTexture(GL_TEXTURE_2D, texture[i]);

		// Selecciona a mistura da textura com a cor
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		// Cria textura de mipmaps
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, im[i]->width, im[i]->height, GL_RGB, GL_UNSIGNED_BYTE, im[i]->imageData);
		// Se não tem mipmaps
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, im[i]->width, im[i]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, im[i]->imageData);
	}

	// Destroi as imagens
	for (i = 0; i<6; i++) tgaDestroy(im[i]);
}


void Skybox::Draw(void)
{
	//myDL = glGenLists(1);

	//glNewList(myDL, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	// Z+ Face
	// Selecciona textura
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-cX+x, -cY+y, cZ+z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(cX+x, -cY+y, cZ+z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(cX+x, cY+y, cZ+z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-cX+x, cY+y, cZ+z);
	glEnd();
	// Z- Face
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-cX+x, -cY+y, -cZ+z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(cX+x, -cY+y, -cZ+z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(cX+x, cY+y, -cZ+z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-cX+x, cY+y, -cZ+z);
	glEnd();
	// X+ Face
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(cX + x, -cY + y, cZ + z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(cX + x, -cY + y, -cZ + z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(cX + x, cY + y, -cZ + z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(cX + x, cY + y, cZ + z);
	glEnd();
	// X- Face
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-cX + x, -cY + y, -cZ + z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-cX + x, -cY + y, cZ + z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-cX + x, cY + y, cZ + z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-cX + x, cY + y, -cZ + z);
	glEnd();
	// Y+ Face
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-cX + x, cY + y, cZ + z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(cX + x, cY + y, cZ + z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(cX + x, cY + y, -cZ + z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-cX + x, cY + y, -cZ + z);
	glEnd();
	// Y- Face
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-cX + x, -cY + y, cZ + z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(cX + x, -cY + y, cZ + z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(cX + x, -cY + y, -cZ + z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-cX + x, -cY + y, -cZ + z);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	//glEndList();
}

void Skybox::Update(float camX, float camY, float camZ)
{
	glPushMatrix();
	this->x = camX;
	this->y = camY;
	this->z = camZ;

	glPopMatrix();
}