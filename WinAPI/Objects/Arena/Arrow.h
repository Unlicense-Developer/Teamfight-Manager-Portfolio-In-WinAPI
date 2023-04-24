#pragma once
class Arrow : public ImageRect
{
public:
	Arrow();
	~Arrow();

	void Update();
	void Render(HDC hdc);

	void Shoot(const Vector2& start, const Vector2& destination, bool AttackDirection);

private:
	float speed = 9.0f;
	Vector2 destination;
};