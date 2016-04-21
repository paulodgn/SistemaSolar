class Camera
{
public:
	void  InitCamera();
	void  Update();
	void  Input(unsigned char key);
	void  Move();

	float  x, y, z;
	float  strafe, forward;
	float speed;
	float angle;
	float distanceToSun;
	float velocidadeOrbita;
	float camAngle;

private:

};

