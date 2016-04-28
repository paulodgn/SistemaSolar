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
#include "Skybox.h"
#include <list>




// Protótipos de funções
void init(void);
void display(void);
void reshape(GLsizei w, GLsizei h);
void load_tga_image(void);
void reshapeSubWindow(GLsizei w2, GLsizei h2);



int width, height;
float solX=0, solY=0, solZ=0;
float raioDoSol;

Planeta sol,mercurio,venus, terra, marte, jupiter, saturno, uranus, neptuno;
std::list<Planeta> listaPlanetas;
Camera freeCamera;
float xOrigin;
Skybox skybox;

GLuint window, subWindow;
GLuint subWindow_width, subWindow_height;

Lua luas[50]; 

void init(void)
{
	// Define técnica de shading: GL_FLAT, GL_SMOOTH
	glShadeModel(GL_SMOOTH);
	
	// Activa o teste de profundidade
	glEnable(GL_DEPTH_TEST);

	
}

void initLights(void)
{
	
	GLfloat lightAmbient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat lightDiffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lightSpecular[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
}

void applylights(void)
{
	// Define a posição de light0
	GLfloat light0_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	// Define a posição de direcção de light1
	GLfloat spot_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat spot_direction[] = { 0.0f, 0.0f, 0.0f };
	
	// Aplica a light0
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	
	// Aplica a light1
	glLightfv(GL_LIGHT1, GL_POSITION, spot_position);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);

	glDisable(GL_LIGHTING);
	
	glEnable(GL_LIGHTING);
}
void reshape(GLsizei w, GLsizei h)
{
	//main window
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.5, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
	subWindow_width = 256;
	subWindow_height = 256;

	//subwindow
	glutSetWindow(subWindow);
	glutPositionWindow(25, 25);
	glutReshapeWindow(subWindow_width, subWindow_height);
	
	
}



void applymaterial(int type)
{
	// Define as propriedades dos materiais
	// Type: 0 (Branco); 1 (Amarelo); 2 (Ciano); 3 (Branco-Emissor)
	GLfloat mat_ambient[4][4] = { { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } };
	GLfloat mat_diffuse[4][4] = { { 0.5f, 0.5f, 0.5f, 1.0f }, { 0.5f, 0.5f, 0.0f, 1.0f }, { 0.0f, 0.5f, 0.5f, 1.0f }, { 0.5f, 0.5f, 0.5f, 1.0f } };
	GLfloat mat_specular[4][4] = { { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } };
	GLfloat mat_emission[4][4] = { { 0.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } };
	GLfloat mat_shininess[4][1] = { { 20.0f }, { 20.0f }, { 20.0f }, { 20.0f } };

	if ((type >= 0) && (type < 4))
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient[type]); // GL_FRONT, GL_FRONT_AND_BACK , GL_BACK, 
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse[type]);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular[type]);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission[type]);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess[type]);
	}
}

void CreatePlanetas()
{
	
	//sol, mercurio, venus, terra, marte, jupiter, saturno, uranus, neptuno;
	//distancias à escala
	//distancia original de mercurio ao sol corresponde a 5 unidades
	//todas a distancias são calculadas com base na anterior
	//raio original de mercurio corresponde a 0.5 unidades
	//todos os outros raios são calculados atravez deste ultimo 
	//raios de Jupiter Saturno Urano e Neptuno são divididos por 2 !!!
	
	sol.CreatePlaneta(raioDoSol, 3, true, 0, 0, "images/sun.tga", 0);
	
	mercurio.CreatePlaneta(0.25, 0, true, 0.05, 5 + raioDoSol, "images/mercury.tga", 1);
	venus.CreatePlaneta(0.62, 0, true, 0.03, 9 + raioDoSol, "images/venus.tga", 2);
	terra.CreatePlaneta(0.65, 0, true, 0.02, 12.92 + raioDoSol, "images/earth.tga", 3);

	terra.AddMoon(0.4, true, 0.1, 4,3);
	terra.AddMoon(0.4, true, 0.5, 5,3);
	terra.AddMoon(0.4, true, 0.7, 6,3);
	
	
	
	marte.CreatePlaneta(0.35, 0, true, 0.09, 19 + raioDoSol, "images/mars.tga", 4);
	marte.AddMoon(0.3, true, 0.35, 6,4);
	marte.AddMoon(0.3, true, 0.35, 3, 4);

	jupiter.CreatePlaneta(1.83, 0, true, 0.008, 33.6 + raioDoSol, "images/jupiter.tga", 5);
	saturno.CreatePlaneta(1.545, 0, true, 0.005, 61.71 + raioDoSol, "images/saturn.tga", 6);
	uranus.CreatePlaneta(0.66, 0, true, 0.002, 123.945 + raioDoSol, "images/uranus.tga", 7);
	neptuno.CreatePlaneta(0.64, 0, true, 0.001, 194.455 + raioDoSol, "images/neptune.tga", 8);
	
}

void DrawPlanetas()
{
	applymaterial(3);
	sol.Draw();
	applymaterial(0);
	mercurio.Draw();
	venus.Draw();
	terra.Draw();
	marte.Draw();
	

	
	jupiter.Draw();
	saturno.Draw();
	uranus.Draw();
	neptuno.Draw();
	
	
	
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
	glutSetWindow(window);
	
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	
	//gluLookAt(0, 50, 20 - freeCamera.z, freeCamera.x, freeCamera.y, freeCamera.z, 0.0, 1.0, 0.0);
	freeCamera.Update();
	applylights();
	
	//desenha e faz update aos planetas
	skybox.Draw();
	skybox.Update(freeCamera.x, freeCamera.y, freeCamera.z);
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
	
	//janelas
	if ((key == 'n') || (key == 'N')){
		glutSetWindow(window);
		glutReshapeWindow(width - 14, height - 76);
		glutPositionWindow(0, 0);
	}
	if ((key == 'm') || (key == 'M')){
		glutSetWindow(window);
		glutFullScreen();
	}
	
}



void mouseMove(int x, int y) 
{

	freeCamera.MouseMove( x,  y);
}

void mouseButton(int button, int state, int x, int y)
{
	freeCamera.MouseButton(button, state, x, y);

}



void renderSubWindow()
{
	glutSetWindow(subWindow);
	

	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)subWindow_width / (GLfloat)subWindow_height, 0.5, 1000.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
	
	//gluLookAt(0.0, 50.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	gluLookAt(freeCamera.x, 50, freeCamera.z-2, freeCamera.x, 0.0, freeCamera.z, 0.0, 1.0, 0.0);
	//desenha teapot na posicao da camara
	glPushMatrix();
	glTranslatef(freeCamera.x, freeCamera.y, freeCamera.z);
	glutWireTeapot(0.5);
	glPopMatrix();

	DrawPlanetas();
	UpdatePlanetas();
	
	glPopMatrix();

	glutSwapBuffers();
	
}

void renderAll()
{
	display();
	renderSubWindow();
}

int main(int argc, char** argv)
{
	

	// Inicialização do GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	raioDoSol = 4.0f;

	width = glutGet(GLUT_SCREEN_WIDTH);
	height = glutGet(GLUT_SCREEN_HEIGHT);

	// Cria a janela de visualização
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width - 14, height - 76);
	//glutCreateWindow("Programa-25");

	window = glutCreateWindow("ViewPort Test");
	glutDisplayFunc(display);
	// Inicializações
	init();
	initLights();
	skybox.CreateSkybox();
	freeCamera.InitCamera();
	CreatePlanetas();
	// Registar funções de callback
	glutReshapeFunc(reshape);
	glutIdleFunc(renderAll);
	//teclado
	glutKeyboardFunc(Input);
	//mouse
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	//subjanela

	subWindow = glutCreateSubWindow(window, 25, 25, subWindow_width, subWindow_height);

	glutDisplayFunc(renderSubWindow);


	
	
	
		


	// Ciclo infinito do GLUT
	glutMainLoop();

	return 0;
}

/*************************************FIM***************************************/