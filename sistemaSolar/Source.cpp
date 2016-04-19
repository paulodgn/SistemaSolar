/***********************************PROGRAMA-25*********************************/
// Geração automática de coordenadas de textura - Quadric
// Quádrica: Conjunto de pontos no espaço tridimensional.

#include <gl/glut.h>
#include <stdio.h>
#include <windows.h>
#include "tga.h"
#include "Planeta.h"



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
float solX=0, solY=0, solZ=0;
Planeta sol, terra, marte;


void init(void)
{
	// Define técnica de shading: GL_FLAT, GL_SMOOTH
	glShadeModel(GL_SMOOTH);

	// Activa o teste de profundidade
	glEnable(GL_DEPTH_TEST);
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
	sol.CreatePlaneta(2,false,0, 0, "images/sun.tga");
<<<<<<< HEAD
	terra.CreatePlaneta(1, true, 0.05, 7, "images/earth.tga");
	marte.CreatePlaneta(1,true,0.08, 10, "images/mars.tga");
	
=======
	terra.CreatePlaneta(1,true,0.005, 7, "images/earth.tga");
	marte.CreatePlaneta(1,true,0.0003, 10, "images/mars.tga");
>>>>>>> a493b6bb8dc3d8ed9131177bac8d44ad6745742c
}

void DrawPlanetas()
{
	
	sol.Draw();
	terra.Draw();
	marte.Draw();
}

void UpdatePlanetas()
{
	sol.Update();
	terra.Update();

	marte.Update();
}

void display(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	
	gluLookAt(0, 50, 20, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	

	DrawPlanetas();
	UpdatePlanetas();


	glutSwapBuffers();

	glFlush();
}

int main(int argc, char** argv)
{
	int width, height;

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
	CreatePlanetas();
	//load_tga_image();
	
	


	// Registar funções de callback
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);//display

	// Ciclo infinito do GLUT
	glutMainLoop();

	return 0;
}

/*************************************FIM***************************************/