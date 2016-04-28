class Skybox
{
public:
	void CreateSkybox();
	void load_tga_image();

	void Draw();
	void Update(float camX, float camY, float camZ);
	float x, y, z;
	char impathfile[255];

private:
	int cX, cY, cZ;

};

