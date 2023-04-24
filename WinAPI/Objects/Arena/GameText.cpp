#include "Framework.h"

GameText::GameText()
{
	hfont_24 = CreateFont(24, 0, 0, 0, 700, false, false, false, HANGUL_CHARSET,
		100, 0, 0, 0, L"Galmuri14 Regular");
	size = { 30, 30 };
	isActive = false;
}

GameText::~GameText()
{
	DeleteObject(hfont_24);
}

void GameText::Update()
{
	if (!isActive) return;

	direction.y += DELTA;

	pos += direction * speed * DELTA;

	if (pos.y > champPos.y + 25)
	{
		isActive = false;
		direction.y = 0;
	}
}

void GameText::Render(HDC hdc)
{
	if (!isActive) return;

	SelectObject(hdc, hfont_24);
	TextOutA(hdc, pos.x, pos.y, to_string(value).c_str(), to_string(value).size());
}
