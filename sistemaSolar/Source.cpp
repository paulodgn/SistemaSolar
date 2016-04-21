/***********************************PROGRAMA-25*********************************/
// Geração automática de coordenadas de textura - Quadric
// Quádrica: Conjunto de pontos no espaço tridimensional.

#include <gl/glut.h>
#include <math.h>
#include <stdio.h>
#include <windows.h>
#include "tga.h"
#include "Planeta.h"
#include "Lua.h"
#include "Camera.h"
#include <list>


// Protótipos de funções
void init(void);
void display(void);
void reshape(GLsizei w, GLsizei h);
void load_tga_image(void);


// Variáveis globais
//tgaInfo *im;
//GLuint texture;
//GLUquadric *mysolid;
//GLfloat spin = 0.05;
int width, height;
float solX=0, solY=0, solZ=0;
Planeta sol,mercurio,venus, terra, marte, jupiter, saturno, uranus, neptuno;
std::list<Planeta> listaPlanetas;
Camera freeCamera;

void init(void)
{
	// Define técnica de shading: GL_FLAT, GL_SMOOTH
	glShadeModel(GL_SMOOTH);
	
	// Activa o teste de profundidade
	glEnable(GL_DEPTH_TEST);

	freeCamera.InitCamera();
}

void initLights(void)
{
	// Define a luz ambiente global
	GLfloat global_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	// Define a luz light0. Existem 8 fontes de luz no total.
	GLfloat light0_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat light0_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat light0_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	// Define a luz light1. Existem 8 fontes de luz no total.
	GLfloat light1_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat light1_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light1_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat spot_angle = 45.0f;
	GLfloat spot_exp = 12.0f; // Maior valor = maior concentração de luz no centro

	// Fonte de luz ambiente
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

	// Fonte de luz posicional
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.05);

	// Fonte de luz cónica
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spot_angle);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spot_exp);

	// Activa a utilização de iluminação
	glEnable(GL_LIGHTING);
	// Activa a fonte de luz light0
	glEnable(GL_LIGHT0);
	// Activa a fonte de luz light1
	glEnable(GL_LIGHT1);
}

void applylights(void)
{
	// Define a posição de light0
	GLfloat light0_position[] = { 0.0f, 3.0f, 0.0f, 1.0f };
	// Define a posição de direcção de light1
	GLfloat spot_position[] = { 0.0f, 3.0f, -10.0f, 1.0f };
	GLfloat spot_direction[] = { 0.0f, -1.0f, 0.0f };

	// Aplica a light0
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	// Aplica a light1
	glLightfv(GL_LIGHT1, GL_POSITION, spot_position);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);

	glDisable(GL_LIGHTING);

	// Desenha uma esfera que sinaliza a posição da light0
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.0f, 3.0f, 0.0f);
	glutSolidSphere(0.1, 20, 20);
	glPopMatrix();

	// Desenha uma esfera que sinaliza a posição da light1
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.0f, 3.0f, -10.0f);
	glutSolidSphere(0.1, 20, 20);
	glPopMatrix();

	glEnable(GL_LIGHTING);
}
void reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.5, 200.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -10.0);
}



void CreatePlanetas()
{
	//sol, mercurio, venus, terra, marte, jupiter, saturno, uranus, neptuno;
	sol.CreatePlaneta(2,true,false,0, 0, "images/sun.tga");
	mercurio.CreatePlaneta(0.5, true, false, 0.03, 5, "images/mercury.tga");
	venus.CreatePlaneta(0.7, true, false, 0.06, 7, "images/venus.tga");
	terra.CreatePlaneta(1, true, true, 0.05, 10, "images/earth.tga");

	marte.CreatePlaneta(1,true,false,0.08, 15, "images/mars.tga");
	jupiter.CreatePlaneta(3, true, false, 0.04,20, "images/jupiter.tga");
	saturno.CreatePlaneta(2.8, true, false, 0.09,29, "images/saturn.tga");
	uranus.CreatePlaneta(1.5, true, false, 0.07, 35, "images/uranus.tga");
	neptuno.CreatePlaneta(1.5, true, false, 0.03, 42, "images/neptune.tga");

}

void DrawPlanetas()
{
	
	sol.Draw();
	mercurio.Draw();
	venus.Draw();
	

	marte.Draw();
	jupiter.Draw();
	saturno.Draw();
	uranus.Draw();
	neptuno.Draw();
	terra.Draw();
}

void UpdatePlanetas()
{
	sol.Update();
	mercurio.Update();
	venus.Update();
	terra.Update();

	marte.Update();
	jupiter.Update();
	saturno.Update();
	uranus.Update();
	neptuno.Update();
}



void display(void)
{


	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	
	//gluLookAt(0, 50, 20 - freeCamera.z, freeCamera.x, freeCamera.y, freeCamera.z, 0.0, 1.0, 0.0);
	freeCamera.Update();
	applylights();
	
	//desenha e faz update aos planetas
	DrawPlanetas();
	UpdatePlanetas();
	


	
	glutSwapBuffers();

	glFlush();
}

void Input(unsigned char key, int x, int y)
{
	freeCamera.Input(key);
	sol.Input(key);
	mercurio.Input(key);
	venus.Input(key);
	terra.Input(key);

	marte.Input(key);
	jupiter.Input(key);
	saturno.Input(key);
	uranus.Input(key);
	neptuno.Input(key);
	
}



int main(int argc, char** argv)
{
	

	// Inicialização do GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);

	width = glutGet(GLUT_SCREEN_WIDTH);
	height = glutGet(GLUT_SCREEN_HEIGHT);

	// Cria a janela de visualização
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width - 14, height - 76);
	glutCreateWindow("Programa-25");


	
	
	// Inicializações
	init();
	initLights();
	CreatePlanetas();
	//load_tga_image();
	
	

	
	// Registar funções de callback
	glutKeyboardFunc(Input);
	//glutKeyboardFunc(UpdateOrbitaSpeed);
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);//display

	// Ciclo infinito do GLUT
	glutMainLoop();

	return 0;
}

/*************************************FIM***************************************/