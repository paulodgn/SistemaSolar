class Planeta
{
public:
	void CreatePlaneta(int radius, bool rotate, float velocidadeOrbita, float distanceToSun, char imagePath[255]);
	
	void Draw();
	void Update();
	void load_tga_image();
	void getX();
	void getY();
	void getZ();
	void DrawOrbit(float x, float y, float z, GLint radius);

	int radius;
	float distanceToSun;
	char impathfile[255];
	bool hasOrbit;
	float velocidadeOrbita;

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

