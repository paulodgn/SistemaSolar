static class Camera
{
public:
	Camera();
	~Camera();
	void Update();
	void Input(unsigned char key);
	void Move();

	float x, y, z;
	float strafe, forward;

private:

};

Camera::Camera()
{
}

Camera::~Camera()
{
}