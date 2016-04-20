#include <gl/glut.h>
#include <stdio.h>
#include <windows.h>
#include "Planeta.h"
#include "tga.h"
#include <cmath>
#include "Lua.h"


tgaInfo *im;

GLUquadric *mysolid;
GLfloat spin = 0.05;

Lua lua;
unsigned char key;


void Planeta::CreatePlaneta(double radius, bool hasOrbit,bool hasMoon, float velocidadeOrbita, float distanceToSun, char imagePath[255])
	{
		this->radius = radius;
		this->distanceToSun = distanceToSun;
		this->hasOrbit = hasOrbit;
		this->velocidadeOrbita = velocidadeOrbita;
		strcpy_s(impathfile, imagePath);
		this->x = distanceToSun;
		this->y = 0;
		this->z = 0;
		this->angle = 0;
		this->hasMoon = hasMoon;
		this->orbitSpeed = 100;
		load_tga_image();
		
		if (hasMoon)
			AddMoon();
		
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

void Planeta::AddMoon()
{

	lua.CreateLua(0.2, true, 0.2, 1.5, "images/moon.tga");
}

void Planeta::Draw()
	{
	
		//load da textura
	
		glEnable(GL_TEXTURE_2D);
		// Select texture
		glBindTexture(GL_TEXTURE_2D, texture);
		// Desenha esfera
		glPushMatrix();
		
		int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
		
		if (hasOrbit)
		{

			x = distanceToSun * cos(angle*velocidadeOrbita);
			y = 0;
			z = distanceToSun *  sin(angle*velocidadeOrbita);
			glTranslatef(x, 0, z);
			angle += 0.1;

		}
		
		glRotatef(-20, 0.0, 0.0, 1.0);
		glRotatef(spin, 0.0, 1.0, 0.0);
		glRotatef(-65, 1.0, 0.0, 0.0);
		gluSphere(mysolid, radius, 100, 100);
		
		glPopMatrix();
		DrawOrbit(x,y,z,distanceToSun);
		if (hasMoon)
		{
			lua.Draw(this->x,this->y, this->z);
			
			lua.Update();
		}
		
		glDisable(GL_TEXTURE_2D);
		
	}

void Planeta::Input(unsigned char key)
{
	key = toupper(key);
	if (key == '+')
	{
		velocidadeOrbita += 0.001;
	}
	if (key == '-')
	{
		velocidadeOrbita -= 0.001;
	}
}

void Planeta::Update()
{
	
	//rotacao planeta
	spin = spin + 0.1;
	if (spin > 360.0)
	{
		spin = spin - 360.0;
	}
	
}

void Planeta::DrawOrbit(float x, float y, float z, GLint radius)
{
	glBegin(GL_LINE_LOOP);

	for (float i = 0; i<(3.14 * 2); i += 3.14 / 180)

	{
		x = sin(i)*radius;
		z = cos(i)*radius;
		glVertex3f(x, 0, z);
	}

	glEnd();
}

float Planeta::getX()
{
	return x;
}
float Planeta::getY()
{
	return y;
}
float Planeta::getZ()
{
	return z;
}

	








