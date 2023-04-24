#pragma once
class GameText : public Rect
{
public:
	GameText();
	~GameText();

	void Update();
	void Render(HDC hdc);

	virtual void Print(const Vector2& pos, int value) = 0;

protected:
	Vector2 direction;
	Vector2 champPos;

	HFONT hfont_24;

	float speed = 90.0f;
	int value;
};