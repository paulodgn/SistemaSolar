#include "camera.h"
#include <gl/glut.h>
#include <stdio.h>
#include <windows.h>

Camera::Camera()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->forward = 0;
}

void Camera::Input(unsigned char key)
{
	
		key = toupper(key);

		if (key == 27) exit(0);

		/*if (key == 'A')
		{
			printf("tecla a \n");
			angle -= 0.2f;

		}
		if (key == 'S')
		{
			printf("tecla s\n");
			angleVertical += 0.2f;
		}
		if (key == 'D')
		{
			printf("tecla d\n");
			angle += 0.2f;
		}*/
		if (key == 'W')
		{
			printf("tecla w\n");
			this->forward += 0.1;
		}
	
}

void Camera::Move()
{

}

void Camera::Update()
{

}

