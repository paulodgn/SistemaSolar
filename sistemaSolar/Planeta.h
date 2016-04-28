
class Planeta
{
public:
	void CreatePlaneta(double radius,int material, bool rotate, float velocidadeOrbita, float distanceToSun, char imagePath[255], int id);
	
	void Draw();
	void Update();
	void load_tga_image();
	float getX();
	float getY();
	float getZ();
	
	void DrawOrbit(float x, float y, float z, GLint radius);
	void AddMoon(float radius, bool hasOrbit, float velocidadeOrbita, float distaceToPlanet, int indiceLuas);
	void Input(unsigned char key);
	int material;
	//int numberOfMoons;
	int id;
	

private:
	double radius;
	float distanceToSun;
	char impathfile[255];
	bool hasOrbit;
	float velocidadeOrbita;
	float x, y, z;
	GLuint texture;
	float angle;
	float orbitSpeedInc;
	

};





//class Planeta
//{
//
//
//public:
//	Planeta(int radius, float distanceToSun, char imagePath[255]);
//	//~Planeta();
//
//	int radius;
//	float distanceToSun;
//	char impathfile[255];
//
//	//construtor
//	Planeta::Planeta(int radius, float distanceToSun, char imagePath[255]);
//
//	//deconstrutor
//	//Planeta::~Planeta();
//
//	void DrawPlaneta();
//	void load_tga_image();
//};

