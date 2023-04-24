#include "Framework.h"

DamageText::DamageText()
{
}

DamageText::~DamageText()
{
}

void DamageText::Update()
{
	GameText::Update();
}

void DamageText::Render(HDC hdc)
{
	SetTextColor(hdc, RED);
	GameText::Render(hdc);
}

void DamageText::Print(const Vector2& pos, int value)
{
	isActive = true;
	this->pos = pos;
	this->champPos = pos;
	this->value = value;
}
