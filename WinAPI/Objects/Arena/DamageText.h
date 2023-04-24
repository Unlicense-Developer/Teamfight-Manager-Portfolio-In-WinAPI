#pragma once
class DamageText : public GameText
{
public:
	DamageText();
	~DamageText();

	void Update();
	void Render(HDC hdc);

	virtual void Print(const Vector2& pos, int value) override;
};