#pragma once
class HealText : public GameText
{
public:
	HealText();
	~HealText();
	void Update();
	void Render(HDC hdc);

	virtual void Print(const Vector2& pos, int value) override;
};