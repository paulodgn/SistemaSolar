class Planeta
{
public:
	void CreatePlaneta(int radius, float distanceToSun, char imagePath[255]);
	
	void DrawPlaneta();
	void load_tga_image();

	int radius;
	float distanceToSun;
	char impathfile[255];

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

