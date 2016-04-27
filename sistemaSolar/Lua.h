
class Lua
{
public:
	
	float x, y, z, planetX, planetY, planetZ;
	float distanceToPlanet;
	float radius;
	char impathfile[255];
	bool hasOrbit;
	float velocidadeOrbita;
	float angle;
	bool visible;
	GLuint texture;
	tgaInfo *im;

	GLUquadric *mysolid;
	GLfloat spin = 0.05;



	void CreateLua(float radius, bool hasOrbit, float velocidadeOrbita, float distanceToPlanet, char imagePath[255]);
	void Draw(float planetaX, float planetaY, float planetaZ);
	void Update();
	void load_tga_image();
	void DrawOrbit(float x, float y, float z, GLfloat radius);
	





};

