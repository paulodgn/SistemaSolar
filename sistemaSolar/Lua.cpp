
#include <gl/glut.h>
#include <stdio.h>
#include <windows.h>
#include "tga.h"
#include <cmath>
#include "Lua.h"
#include "Planeta.h"





//construtor
void Lua::CreateLua(float radius, bool hasOrbit, float velocidadeOrbita, float distanceToPlanet, char imagePath[255], int idPlaneta)
{
	this->radius = radius;
	this->distanceToPlanet = distanceToPlanet;
	this->hasOrbit = hasOrbit;
	this->velocidadeOrbita = velocidadeOrbita;
	strcpy_s(impathfile, imagePath);
	this->x = distanceToPlanet;
	this->y = 0;
	this->z = 0;
	this->visible = false;
	this->angle = 0;
	this->idPlaneta = idPlaneta;
	load_tga_image();
	
}
//load textura
void Lua::load_tga_image()
{

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
//desenhar lua
void Lua::Draw(float planetaX, float planetaY, float planetaZ)
{
	glEnable(GL_TEXTURE_2D);
	// Select texture
	glBindTexture(GL_TEXTURE_2D, texture);
	glPushMatrix();

	//calculo orbita
	if (hasOrbit)
	{

		x = planetaX + distanceToPlanet * cos(angle);
		y = 0;
		z = planetaZ + distanceToPlanet *  sin(angle);
		glTranslatef(x, 0, z);
		angle += 0.1*velocidadeOrbita;



	}
	
	//rotacao
	glRotatef(-20, 0.0, 0.0, 1.0);
	glRotatef(spin, 0.0, 1.0, 0.0);
	glRotatef(-65, 1.0, 0.0, 0.0);
	gluSphere(mysolid, radius, 100, 100);
	glPopMatrix();

	

	glDisable(GL_TEXTURE_2D);
}

void Lua::DrawOrbit(float x, float y, float z, GLfloat radius)
{
	if (visible)
	{
		glBegin(GL_LINE_LOOP);

		for (float i = 0; i<(3.14 * 4); i += 3.14 / 180)

		{
			x = (sin(i)*distanceToPlanet );
			z = (cos(i)*distanceToPlanet );
			glVertex3f(x, 0, z);
		}

		glEnd();

	}
	
}


void Lua::Update()
{

	spin = spin + 0.1;
	if (spin > 360.0)
	{
		spin = spin - 360.0;
	}


}
