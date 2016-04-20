#include "camera.h"
#include <gl/glut.h>
#include <stdio.h>
#include <windows.h>
#include <math.h>

enum cameraMode
{
	freeCam,
	orbit

};

cameraMode camMode;

void Camera::InitCamera()
{
	this->x = 0;
	this->y = 0;
	this->z = -20;
	this->forward = 0;
	this->speed = 2;
	this->distanceToSun = 20;
	this->angle = 0;
	this->velocidadeOrbita = 0.1;
	camMode = orbit;
}

void Camera::Input(unsigned char key)
{
	
		key = toupper(key);

		if (key == 27) exit(0);

		if (key == 'A')
		{
			printf("tecla a \n");
			this->x += 0.05 * speed;

		}
		if (key == 'S')
		{
			printf("tecla s\n");
			this->z -= 0.05 * speed;
		}
		if (key == 'D')
		{
			printf("tecla d\n");
			this->x -= 0.05 * speed;
		}
		if (key == 'W')
		{
			printf("tecla w\n");
			this->z += 0.05 * speed;
		}
		if (key == 'Q')
		{
			printf("tecla q\n");
			this->y += 0.05 * speed;
		}
		if (key == 'E')
		{
			printf("tecla q\n");
			this->y -= 0.05 * speed;
		}

		if (key == 'F')
		{
			camMode = freeCam;
		}
		if (key == 'O')
		{
			camMode = orbit;
		}
		
	
}

void Camera::Move()
{

}

void Camera::Update()
{
	if (camMode == freeCam)
	{
		glTranslatef(x, y, z);
	}
	if (camMode == orbit)
	{
		x = distanceToSun * cos(angle*velocidadeOrbita);
		y = 0;
		z = distanceToSun * sin(angle*velocidadeOrbita);
		
		gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);
		
		angle += 0.1;
	}
	
}

