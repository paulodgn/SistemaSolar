class Camera
{
public:
	void  InitCamera();
	void  Update();
	void  Input(unsigned char key);
	void  Move();

	float  x, y, z;
	float  strafe, forward;
	

private:

};

