#include "Framework.h"
#include "HealText.h"

HealText::HealText()
{
}

HealText::~HealText()
{
}

void HealText::Update()
{
	GameText::Update();
}

void HealText::Render(HDC hdc)
{
	SetTextColor(hdc, RGB(0, 230, 0));
	GameText::Render(hdc);
}

void HealText::Print(const Vector2& pos, int value)
{
	isActive = true;
	this->pos = pos;
	this->champPos = pos;
	this->value = value;
}
