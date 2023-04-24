#include "Framework.h"

Ending::Ending()
	:ImageRect(L"Textures/UI/pickban_bg.bmp")
{
	hfont_40 = CreateFont(40, 0, 0, 0, 1, false, false, false, HANGUL_CHARSET,
		100, 0, 0, 0, L"Galmuri14 Regular");
	hfont_50 = CreateFont(50, 0, 0, 0, 1, false, false, false, HANGUL_CHARSET,
		100, 0, 0, 0, L"Galmuri14 Regular");

	pos = { CENTER_X, -size.y * 0.5f };
	playerlogo = new ImageRect(L"Textures/Teamlogo/T1.bmp");
	computerlogo = new ImageRect(L"Textures/Teamlogo/Drx.bmp");
	trophy = new ImageRect(L"Textures/UI/trophy.bmp");
	MVPtexture = new ImageRect();
}

Ending::~Ending()
{
	delete playerlogo;
	delete computerlogo;
	delete trophy;
	delete MVPtexture;
	DeleteObject(hfont_40);
	DeleteObject(hfont_50);
}

void Ending::Update()
{
	SetEnding();
}

void Ending::Render(HDC hdc)
{
	ImageRect::Render(hdc);
	PrintEndingText(hdc);
}

void Ending::PrintEndingText(HDC hdc)
{
	if (isEnd)
	{
		if (playerscore > computerscore)
		{
			playerlogo->pos = { pos.x - 200, pos.y - 55 };
			playerlogo->Render(hdc);
			SelectObject(hdc, hfont_40);
			SetTextColor(hdc, WHITE);
			TextOutA(hdc, pos.x - 20, pos.y - 80, PLAYER.c_str(), PLAYER.size());
			SetTextColor(hdc, GREEN);
			TextOutA(hdc, pos.x + 160, pos.y - 80, VICTORY.c_str(), VICTORY.size());

		}
		else if (playerscore < computerscore)
		{
			computerlogo->pos = { pos.x - 200, pos.y - 55 };
			computerlogo->Render(hdc);
			SelectObject(hdc, hfont_40);
			SetTextColor(hdc, WHITE);
			TextOutA(hdc, pos.x - 160, pos.y - 80, COMPUTER .c_str(), COMPUTER.size());
			SetTextColor(hdc, GREEN);
			TextOutA(hdc, pos.x + 160, pos.y - 80, VICTORY.c_str(), VICTORY.size());
		}
		else
		{
			SelectObject(hdc, hfont_40);
			SetTextColor(hdc, WHITE);
			TextOutA(hdc, pos.x - 45, pos.y - 80, DRAW.c_str(), DRAW.size());
		}

		//MVP Ãâ·Â
		trophy->pos = { pos.x - 80, pos.y + 75 };
		trophy->Render(hdc);
		SelectObject(hdc, hfont_50);
		SetTextColor(hdc, WHITE);
		TextOutA(hdc, pos.x - 210, pos.y + 50, MVP.c_str(), MVP.size());

		Champion* mvp_temp = CheckMVP();
		SelectObject(hdc, hfont_40);
		MVPtexture->pos = { pos.x + 5, pos.y + 75 };
		Texture* texture = Texture::Add(mvp_temp->GetChampData().mini_texture);
		MVPtexture->SetTexture(texture);
		MVPtexture->Render(hdc);
		TextOutA(hdc, pos.x + 65, pos.y + 55, mvp_temp->GetChampData().jobname.c_str(), mvp_temp->GetChampData().jobname.size());
	}
}

void Ending::SetEnding()
{
	if (isSet)
		return;
	if (isEnd)
	{
		time += DELTA;
		block_speed += BLOCK_SPEED;

		if (time >= START_SET_TIME)
		{
			pos.y += (SET_SPEED - block_speed) * DELTA;

			if (Top() >= 0)
			{
				isSet = true;
				return;
			}
		}
	}
}

void Ending::StartEnd(int playerscore, int computerscore)
{
	isEnd = true;
	this->playerscore = playerscore;
	this->computerscore = computerscore;

}

Champion* Ending::CheckMVP()
{
	Champion* mvp = nullptr;

	if (playerscore > computerscore)
	{
		for (int i = 0; i < GAMER_MAX_CHAMP; i++)
		{
			if (mvp == nullptr || mvp->GetMVPScore() < GamerManager::Get()->GetPlayer()->GetChampions()[i]->GetMVPScore())
			{
				mvp = GamerManager::Get()->GetPlayer()->GetChampions()[i];
			}
		}
	}
	else if (playerscore < computerscore)
	{
		for (int i = 0; i < GAMER_MAX_CHAMP; i++)
		{
			if (mvp == nullptr || mvp->GetMVPScore() < GamerManager::Get()->GetComputer()->GetChampions()[i]->GetMVPScore())
			{
				mvp = GamerManager::Get()->GetComputer()->GetChampions()[i];
			}
		}
	}
	else
	{
		for (int i = 0; i < GAMER_MAX_CHAMP; i++)
		{
			if (mvp == nullptr)
			{
				mvp = GamerManager::Get()->GetPlayer()->GetChampions()[i];
			}

			if (mvp->GetMVPScore() < GamerManager::Get()->GetPlayer()->GetChampions()[i]->GetMVPScore())
			{
				mvp = GamerManager::Get()->GetPlayer()->GetChampions()[i];
			}

			if (mvp->GetMVPScore() < GamerManager::Get()->GetComputer()->GetChampions()[i]->GetMVPScore())
			{
				mvp = GamerManager::Get()->GetComputer()->GetChampions()[i];
			}
		}
	}
	
	return mvp;
}
