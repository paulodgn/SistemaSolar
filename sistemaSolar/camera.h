class Camera
{
public:
	Camera();
	~Camera();
	void Update();
	void Input();
	void Move();

	float x, y, z;

private:

};

Camera::Camera()
{
}

Camera::~Camera()
{
}