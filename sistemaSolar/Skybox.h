class Skybox
{
public:
	void CreateSkybox();
	void load_tga_image();

	void Draw();
	
	char impathfile[255];

private:
	int cX, cY, cZ;

};

