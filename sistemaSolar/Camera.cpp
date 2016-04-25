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

float direcaoX=0, direcaoY=0,direcaoZ = 5;
cameraMode camMode;
float deltaAngleY;

void Camera::InitCamera()
{
	this->x = 0;
	this->y = 0;
	this->z = -10;
	this->forward = 0;
	this->speed = 0.1;
	this->distanceToSun = 20;
	this->angle = 0;
	this->velocidadeOrbita = 0.1;
	this->camAngle = 0;
	this->camAngleY = 0;
	camMode = freeCam;
	this->deltaAngle = 0;
	deltaAngleY = 0;
	xOrigin = -1;
	yOrigin = -1;
}

void Camera::Input(unsigned char key)
{
	
		key = toupper(key);

		if (key == 27) exit(0);

		if (key == 'Q')
		{
			printf("tecla a \n");
			this->x += 0.05 * speed;

		}
		if (key == 'S')
		{
			printf("tecla s\n");
			this->x -= direcaoX * speed;
			this->y -= direcaoY * speed;
			this->z -= direcaoZ * speed;
			
		}
		if (key == 'E')
		{
			printf("tecla d\n");
			this->x -= 0.05 * speed;
		}
		if (key == 'W')
		{
			printf("tecla w\n");
			//this->z += 0.05 * speed;
			this->x += direcaoX * speed * 0.1;
			this->y += direcaoY * speed * 0.1;
			this->z += direcaoZ * speed * 0.1;
			
		}
		if (key == 'Z')
		{
			printf("tecla q\n");
			this->y += 0.05 * speed;
		}
		if (key == 'C')
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
		//left arrow
	/*	if (key == 'D')
		{
			camAngle += 0.01;
				
		}
		if (key == 'A')
		{
			camAngle -= 0.01;

		}*/
		/*if (key == 'T')
		{
			direcaoY += 0.1;

		}
		if (key == 'G')
		{
			direcaoY -= 0.1;

		}*/
		
		
	
}




//https://gist.github.com/23ars/4545671, codigo adaptado do algoritmo do link
void Camera::MouseMove(int xr, int yr)
{
	
	if (xOrigin >= 0) {

		// update deltaAngle, diferença da posicao atual com a da origem
		deltaAngle = (xr - xOrigin) * 0.001f;
		deltaAngleY = (yr - yOrigin) * 0.001f;
		// calculada nova direçao
		direcaoX = sin(camAngle + deltaAngle);
		direcaoY = -sin(camAngleY + deltaAngleY);
		direcaoZ = -cos(camAngle + deltaAngle);
	}
	
	
}

void Camera::MouseButton(int button, int state, int xr, int yr)
{
	
	 //inicia quando botao esta pressionado
	if (button == GLUT_LEFT_BUTTON) {

		// quanto botao é largado
		if (state == GLUT_UP) {
			camAngle += deltaAngle;
			camAngle += deltaAngleY;
			xOrigin = -1;
			yOrigin = -1;
		}
		else  {// origem passa a ser posicao actual
			xOrigin = xr;
			yOrigin = yr;
		}
	}
}


void Camera::Update()
{

	if (camMode == freeCam)
	{

		gluLookAt(x,y,z, x + direcaoX, y + direcaoY, z + direcaoZ, 0.0f, 1.0f, 0.0f);

	}
	if (camMode == orbit)
	{
		x = distanceToSun * cos(angle*velocidadeOrbita);
		
		z = distanceToSun * sin(angle*velocidadeOrbita);
		
		gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);
		
		angle += 0.1;
	}
	
	
}


//float angle = 0.0, deltaAngle = 0.0, ratio;
//float x = 0.0f, y = 1.75f, z = 5.0f;
//float lx = 0.0f, ly = 0.0f, lz = -1.0f;
//int deltaMove = 0, h = 400, w = 400, border = 6;
//
//void orientMe(float ang)
//{
//	lx = sin(ang);
//	lz = -cos(ang);
//}
//
//
//void moveMeFlat(int i)
//{
//	x = x + i * (lx)* 0.1;
//	z = z + i * (lz)* 0.1;
//}
//
//void pressKey(int key, int x, int y)
//{
//	switch (key)
//	{
//	case GLUT_KEY_LEFT:
//		deltaAngle = -0.01f;
//		break;
//	case GLUT_KEY_RIGHT:
//		deltaAngle = 0.01f;
//		break;
//	case GLUT_KEY_UP:
//		deltaMove = 1;
//		break;
//	case GLUT_KEY_DOWN:
//		deltaMove = -1;
//		break;
//	default:
//		break;
//	}
//}
//
//
//void releaseKey(int key, int x, int y)
//{
//	switch (key)
//	{
//	case GLUT_KEY_LEFT:
//		if (deltaAngle < 0.0f) deltaAngle = 0.0f;
//		break;
//	case GLUT_KEY_RIGHT:
//		if (deltaAngle > 0.0f) deltaAngle = 0.0f;
//		break;
//	case GLUT_KEY_UP:
//		if (deltaMove > 0) deltaMove = 0;
//		break;
//	case GLUT_KEY_DOWN:
//		if (deltaMove < 0) deltaMove = 0;
//		break;
//	default:
//		break;
//	}
//}
//
//
//void renderSceneAll(void)
//{
//	if (deltaMove)
//	{
//		moveMeFlat(deltaMove);
//	}
//	if (deltaAngle)
//	{
//		angle += deltaAngle;
//		orientMe(angle);
//	}
//
//	//	renderScene();
//	renderScenesw1();
//	renderScenesw2();
//	renderScenesw3();
//}
