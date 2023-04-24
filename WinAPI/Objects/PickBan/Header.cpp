#include "Framework.h"

Header::Header()
	:ImageRect(L"Textures/Pickban/header.bmp")
{
	hfont_50 = CreateFont(50, 0, 0, 0, 1, false, false, false, HANGUL_CHARSET,
		100, 0, 0, 0, L"Galmuri14 Regular");

	pos = { CENTER_X, -size.y * 0.5f };
	playerlogo = new ImageRect(L"Textures/Teamlogo/T1.bmp");
	computerlogo = new ImageRect(L"Textures/Teamlogo/Drx.bmp");
	
}

Header::~Header()
{
	delete playerlogo;
	delete computerlogo;
	DeleteObject(hfont_50);
}

void Header::Update()
{
	SetHeader();
	playerlogo->pos = { 40, pos.y - 8 };
	computerlogo->pos = { WIN_WIDTH - 40 , pos.y - 8 };
}

void Header::Render(HDC hdc)
{
	ImageRect::Render(hdc);
	PrintGamerName(hdc);
	playerlogo->Render(hdc);
	computerlogo->Render(hdc);
}

void Header::PrintGamerName(HDC hdc)
{
	SelectObject(hdc, hfont_50);
	SetTextColor(hdc, WHITE);

	TextOutA(hdc, pos.x - 400, pos.y - 35, PLAYER.c_str(), PLAYER.size());
	TextOutA(hdc, pos.x + 180, pos.y - 35, COMPUTER.c_str(), COMPUTER.size());
}

void Header::SetArenaHeader() // 아레나용 헤더
{
	isSet = true;
	pos = { CENTER_X, size.y * 0.5f };
}

void Header::SetHeader() // 초기 위치 세팅
{
	if (isSet)
		return;

	time += DELTA;
	block_speed += BLOCK_SPEED;

	if (time >= START_SET_TIME)
	{
		pos.y += ( SET_SPEED - block_speed ) * DELTA;

		if (Bottom() >= size.y)
		{
			isSet = true;
			return;
		}
	}
}
