#include "Framework.h"
#include "CharaCard.h"

CharaCard::CharaCard(int index, wstring file, UINT frameX, UINT frameY, COLORREF transColor)
	:ImageRect(file, frameX, frameY, transColor)
{
	hfont_16 = CreateFont(16, 0, 0, 0, 1, false, false, false, HANGUL_CHARSET,
		100, 0, 0, 0, L"Galmuri14 Regular");
	hfont_18 = CreateFont(18, 0, 0, 0, 1, false, false, false, HANGUL_CHARSET,
		100, 0, 0, 0, L"Galmuri14 Regular");
	hfont_21 = CreateFont(21, 0, 0, 0, 1, false, false, false, HANGUL_CHARSET,
		100, 0, 0, 0, L"Galmuri14 Regular");
	hfont_24 = CreateFont(24, 0, 0, 0, 1, false, false, false, HANGUL_CHARSET,
		100, 0, 0, 0, L"Galmuri14 Regular");


	if (file == L"Textures/Pickban/player_card.bmp")
	{
		gamerstat = PLAYER;
		pos.x = -size.x * 0.5f;
		pos.y = index * 160 + 155;
		kdatexture = new ImageRect(L"Textures/UI/player_kdacard.bmp");
	}
	else if (file == L"Textures/Pickban/computer_card.bmp")
	{
		gamerstat = COMPUTER;
		pos.x = WIN_WIDTH + size.x * 0.5f;
		pos.y = index * 160 + 155;
		kdatexture = new ImageRect(L"Textures/UI/computer_kdacard.bmp");
	}

	this->index = index;

	minitexture = new ImageRect();
	skillimage = new ImageRect();
	ultimage = new ImageRect();

	minitexture->isActive = false;
	kdatexture->isActive = false;
	skillimage->isActive = false;
	ultimage->isActive = false;
}

CharaCard::~CharaCard()
{
	delete minitexture;
	delete kdatexture;
	delete skillimage;
	delete ultimage;
}

void CharaCard::Update()
{
	SetCard();
	SetKDACard();

	minitexture->pos = { pos.x - 49, pos.y - 18 };
	skillimage->pos = { pos.x - 24, pos.y + 54 };
	ultimage->pos = { pos.x + 55, pos.y + 54 };
}

void CharaCard::Render(HDC hdc)
{
	kdatexture->Render(hdc);
	PrintKDAText(hdc);
	ImageRect::Render(hdc);
 	minitexture->Render(hdc);
	skillimage->Render(hdc);
	ultimage->Render(hdc);
	PrintCardText(hdc);
}


void CharaCard::PrintCardText(HDC hdc)
{
	if (!minitexture->isActive)
		return;
	SelectObject(hdc, hfont_18);
	TextOutA(hdc, pos.x - 12, pos.y - 9, HP.c_str(), HP.size());
	TextOutA(hdc, pos.x - 12, pos.y - 27, RANGE.c_str(), RANGE.size());
	TextOutA(hdc, pos.x - 12, pos.y - 45, ATS.c_str(), ATS.size());
	TextOutA(hdc, pos.x - 70, pos.y + 54, SKILL.c_str(), SKILL.size());
	TextOutA(hdc, pos.x - 2, pos.y + 54, ULT.c_str(), ULT.size());

	TextOutA(hdc, pos.x + 36, pos.y - 9, to_string(cardchamp->GetChampData().hp).c_str(), to_string(cardchamp->GetChampData().hp).size());
	TextOutA(hdc, pos.x + 36, pos.y - 27, to_string(cardchamp->GetChampData().range).c_str(), to_string(cardchamp->GetChampData().range).size());
	TextOutA(hdc, pos.x + 36, pos.y - 45, cardchamp->GetChampData().atkspeed.c_str(), cardchamp->GetChampData().atkspeed.size());

	SelectObject(hdc, hfont_24);
	TextOutA(hdc, pos.x - 20 , pos.y - 75, cardchamp->GetChampData().jobname.c_str(), cardchamp->GetChampData().jobname.size());
	//°ø°Ý·Â, ¹æ¾î·Â
	TextOutA(hdc, pos.x - 40, pos.y + 9, to_string(cardchamp->GetChampData().atk).c_str(), to_string(cardchamp->GetChampData().atk).size());
	TextOutA(hdc, pos.x + 30, pos.y + 9, to_string(cardchamp->GetChampData().def).c_str(), to_string(cardchamp->GetChampData().def).size());
}

void CharaCard::PrintKDAText(HDC hdc)
{
	if (kdatexture->isActive)
	{
		SelectObject(hdc, hfont_18);
		TextOutA(hdc, kdatexture->pos.x - 13, kdatexture->pos.y - 70, INFO.c_str(), INFO.size());
		
		SelectObject(hdc, hfont_16);
		//KDA
		TextOutA(hdc, kdatexture->pos.x - 28, kdatexture->pos.y - 45, KILL.c_str(), KILL.size());
		TextOutA(hdc, kdatexture->pos.x - 4, kdatexture->pos.y - 45, DEATH.c_str(), DEATH.size());
		TextOutA(hdc, kdatexture->pos.x  + 20, kdatexture->pos.y - 45, ASSIST.c_str(), ASSIST.size());

		TextOutA(hdc, kdatexture->pos.x - 28, kdatexture->pos.y - 25, to_string(cardchamp->GetChampData().killCount).c_str(), to_string(cardchamp->GetChampData().killCount).size());
		TextOutA(hdc, kdatexture->pos.x - 4, kdatexture->pos.y - 25, to_string(cardchamp->GetChampData().deathCount).c_str(), to_string(cardchamp->GetChampData().deathCount).size());
		TextOutA(hdc, kdatexture->pos.x + 20, kdatexture->pos.y - 25, to_string(cardchamp->GetChampData().assistCount).c_str(), to_string(cardchamp->GetChampData().assistCount).size());

		//µô,ÅÊ,Èú·®
		SelectObject(hdc, hfont_18);
		TextOutA(hdc, kdatexture->pos.x, kdatexture->pos.y + 4, to_string(cardchamp->GetChampData().DealCount).c_str(), to_string(cardchamp->GetChampData().DealCount).size());
		TextOutA(hdc, kdatexture->pos.x, kdatexture->pos.y + 28, to_string(cardchamp->GetChampData().DamageCount).c_str(), to_string(cardchamp->GetChampData().DamageCount).size());
		TextOutA(hdc, kdatexture->pos.x, kdatexture->pos.y + 52, to_string(cardchamp->GetChampData().HealCount).c_str(), to_string(cardchamp->GetChampData().HealCount).size());
	}
}

void CharaCard::SetCard()
{
	if (isSet)
		return;

	if (gamerstat == PLAYER)
	{
		time += DELTA;
		block_speed += BLOCK_SPEED;

		if (time >= START_SET_TIME)
		{
			pos.x += (SET_SPEED - block_speed) * DELTA;

			if (Left() >= 0)
			{
				isSet = true;
				time = 0.0f;
				return;
			}
		}
	}
	else if (gamerstat == COMPUTER)
	{
		time += DELTA;
		block_speed += BLOCK_SPEED;

		if (time >= START_SET_TIME)
		{
			pos.x -= (SET_SPEED - block_speed) * DELTA;

			if (Right() <= WIN_WIDTH)
			{
				isSet = true;
				time = 0.0f;
				return;
			}
		}
	}

}

void CharaCard::SetKDACard()
{
	if (isSet_KDA) return;

	if (gamerstat == PLAYER)
	{
		if (kdatexture->isActive)
		{
			block_speed += BLOCK_SPEED;
			kdatexture->pos.x += (SET_SPEED - block_speed) * DELTA;
			
			if (kdatexture->Left() >= Right())
			{
				isSet_KDA = true;
				return;
			}
		}
		else
		{
			kdatexture->pos = { pos.x + 40, pos.y };
		}
	}
	else if (gamerstat == COMPUTER)
	{
		if (kdatexture->isActive)
		{
			block_speed += BLOCK_SPEED;
			kdatexture->pos.x -= (SET_SPEED - block_speed) * DELTA;

			if (kdatexture->Right() <= Left())
			{
				isSet_KDA = true;
				return;
			}
		}
		else
		{
			kdatexture->pos = { pos.x - 40, pos.y };
		}
	}

}

void CharaCard::SetPickChampInfo(Champion* champ)
{
	cardchamp = champ; // ÇÈÇÑ Ã¨ÇÇ¾ðÀÇ Á¤º¸
	Texture* texture = Texture::Add(cardchamp->GetChampData().mini_texture);
	minitexture->SetTexture(texture);
	texture = Texture::Add(cardchamp->GetChampData().skilltexture);
	skillimage->SetTexture(texture);
	texture = Texture::Add(cardchamp->GetChampData().ulttexture);
	ultimage->SetTexture(texture);
	skillimage->size = { 38, 38 };
	ultimage->size = { 38, 38 };

	minitexture->isActive = true;
	skillimage->isActive = true;
	ultimage->isActive = true;
}

void CharaCard::SetKDAActive()
{
	kdatexture->isActive = true;
}
