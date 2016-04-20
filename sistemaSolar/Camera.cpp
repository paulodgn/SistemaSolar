#include "camera.h"
#include <gl/glut.h>
#include <stdio.h>
#include <windows.h>

void Camera::InitCamera()
{
	this->x = 0;
	this->y = 0;
	this->z = -20;
	this->forward = 0;
	this->speed = 2;
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
	
}

void Camera::Move()
{

}

void Camera::Update()
{

}

