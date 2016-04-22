class Camera
{
public:
	void  InitCamera();
	void  Update();
	void  Input(unsigned char key);
	void  Move();
	void MouseInput(int x, int y);
	void MouseMove(int x, int y);
	void MouseButton(int button, int state, int x, int y);

	float  x, y, z;
	float  strafe, forward;
	float speed;
	float angle;
	float distanceToSun;
	float velocidadeOrbita;
	float camAngle;
	float deltaAngle;
	int xOrigin;
	float diferencaX, diferencaY, posicaoRatoInicialX, posicaRatoInicialY;

private:

};

