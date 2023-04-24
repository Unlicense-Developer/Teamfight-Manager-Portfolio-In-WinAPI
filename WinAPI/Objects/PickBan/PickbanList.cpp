#include "Framework.h"

PickbanList::PickbanList()
	:ImageRect(L"Textures/Pickban/banpick_ui_5.bmp")
{
	pos = { CENTER_X, WIN_HEIGHT + size.y * 0.5f };

	hfont_12 = CreateFont(12, 0, 0, 0, 1, false, false, false, HANGUL_CHARSET,
		100, 0, 0, 0, L"Galmuri14 Regular");
	hfont_18 = CreateFont(18, 0, 0, 0, 1, false, false, false, HANGUL_CHARSET,
		100, 0, 0, 0, L"Galmuri14 Regular");
	hfont_21 = CreateFont(21, 0, 0, 0, 1, false, false, false, HANGUL_CHARSET,
		100, 0, 0, 0, L"Galmuri14 Regular");
	hfont_24 = CreateFont(24, 0, 0, 0, 1, false, false, false, HANGUL_CHARSET,
		100, 0, 0, 0, L"Galmuri14 Regular");
	hfont_55 = CreateFont(55, 0, 0, 0, 1, false, false, false, HANGUL_CHARSET,
		100, 0, 0, 0, L"Galmuri14 Regular");

	previewTexture = new ImageRect();
	skillTexture = new ImageRect();
	ultTexture = new ImageRect();

	CreateClassDatas();
}

PickbanList::~PickbanList()
{
	DeleteObject(hfont_12);
	DeleteObject(hfont_18);
	DeleteObject(hfont_21);
	DeleteObject(hfont_24);
	DeleteObject(hfont_55);

	for (ClassSlot* classslot : classslots)
	{
		delete classslot;
	}

	delete skillTexture;
	delete ultTexture;
}

void PickbanList::Update()
{
	SetList();

	for (ClassSlot* classslot : classslots)
	{
		classslot->Update();
		classslot->pos.x = Left() + 270 + classslot->GetData().key * BANPICKSLOT_INTERVAL;
		classslot->pos.y = Top() + 235;
	}
}

void PickbanList::Render(HDC hdc)
{
	ImageRect::Render(hdc);
	PrintBansText(hdc);

	for (ClassSlot* classslot : classslots)
	{
		classslot->Render(hdc);
	}

	ShowClassInfo(hdc);
}

void PickbanList::ShowClassInfo(HDC hdc)
{
	SetTextColor(hdc, WHITE);
	SelectObject(hdc, hfont_24);

	TextOutA(hdc, pos.x - 278, pos.y + 55, ATK.c_str(), ATK.size());
	TextOutA(hdc, pos.x - 170, pos.y + 55, DEF.c_str(), DEF.size());
	TextOutA(hdc, pos.x - 278, pos.y + 100, ATS.c_str(), ATS.size());
	TextOutA(hdc, pos.x - 170, pos.y + 100, HP.c_str(), HP.size());
	TextOutA(hdc, pos.x - 278, pos.y + 146, RANGE.c_str(), RANGE.size());
	TextOutA(hdc, pos.x - 170, pos.y + 146, MOVESPEED.c_str(), MOVESPEED.size());

	TextOutA(hdc, pos.x + 3, pos.y + 62, SKILL.c_str(), SKILL.size());
	TextOutA(hdc, pos.x - 4, pos.y + 132, ULT.c_str(), ULT.size());
	
	

	for (ClassSlot* classslot : classslots)
	{
		if (classslot->Getstate() == 1 || classslot->Getstate() == 2)
		{
			previewSlot = classslot;
		}

	
		if (previewSlot)
		{
			Texture* texture = Texture::Add(this->previewSlot->GetData().previewtexture);
			previewTexture->SetTexture(texture);
			texture = Texture::Add(this->previewSlot->GetData().skilltexture);
			skillTexture->SetTexture(texture);
			texture = Texture::Add(this->previewSlot->GetData().ulttexture);
			ultTexture->SetTexture(texture);

			SelectObject(hdc, hfont_18);

			//스킬 설명란
			TextOutA(hdc, CENTER_X + 84, CENTER_Y + 78, previewSlot->GetData().skilltxt.c_str(), previewSlot->GetData().skilltxt.size());
			TextOutA(hdc, CENTER_X + 84, CENTER_Y + 150, previewSlot->GetData().ulttxt.c_str(), previewSlot->GetData().ulttxt.size());

			SelectObject(hdc, hfont_21);
			TextOutA(hdc, CENTER_X - 261, CENTER_Y + 74, to_string(previewSlot->GetData().atk).c_str(), to_string(previewSlot->GetData().atk).size());
			TextOutA(hdc, CENTER_X - 147, CENTER_Y + 74, to_string(previewSlot->GetData().def).c_str(), to_string(previewSlot->GetData().def).size());
			TextOutA(hdc, CENTER_X - 261, CENTER_Y + 121, previewSlot->GetData().atkspeed.c_str(), previewSlot->GetData().atkspeed.size());
			TextOutA(hdc, CENTER_X - 147, CENTER_Y + 121, to_string(previewSlot->GetData().hp).c_str(), to_string(previewSlot->GetData().hp).size());
			TextOutA(hdc, CENTER_X - 261, CENTER_Y + 168, to_string(previewSlot->GetData().range).c_str(), to_string(previewSlot->GetData().range).size());
			TextOutA(hdc, CENTER_X - 147, CENTER_Y + 168, to_string(previewSlot->GetData().movespeed).c_str(), to_string(previewSlot->GetData().movespeed).size());

			SelectObject(hdc, hfont_24);

			//직업군 이름
			TextOutA(hdc, CENTER_X - 380, CENTER_Y + 53, previewSlot->GetData().classname.c_str(), previewSlot->GetData().classname.size());
			TextOutA(hdc, CENTER_X - 380, CENTER_Y + 161, previewSlot->GetData().jobname.c_str(), previewSlot->GetData().jobname.size());

			//쿨타임
			TextOutA(hdc, CENTER_X - 2, CENTER_Y + 85, (previewSlot->GetData().skillcool + "초").c_str(), (previewSlot->GetData().skillcool + "초").size());
			TextOutA(hdc, CENTER_X - 2, CENTER_Y + 155, (to_string(previewSlot->GetData().ultcount) + "회").c_str(), (to_string(previewSlot->GetData().ultcount) + "회").size());

			previewTexture->Render(hdc);
			skillTexture->Render(hdc);
			ultTexture->Render(hdc);
			previewTexture->pos = { CENTER_X - 355, CENTER_Y + 130 };
			skillTexture->pos = { CENTER_X - 58, CENTER_Y + 88 };
			ultTexture->pos = { CENTER_X - 58, CENTER_Y + 156 };
		}
	}
}

void PickbanList::PrintBansText(HDC hdc)
{
	SelectObject(hdc, hfont_55);
	SetTextColor(hdc, WHITE);

	TextOutA(hdc, pos.x - 54, pos.y + 270, BANS.c_str(), BANS.size());
}

void PickbanList::CreateClassDatas()
{
	map <int, ClassData> classdatas = DataManager::Get()->GetClassDatas();
	
	int widthCount = 10;

	int count = 0;

	for (pair<int, ClassData> classdata : classdatas)
	{
		ClassSlot* classslot = new ClassSlot(classdata.second);
		Texture* overTexture = Texture::Add(classslot->GetData().overslot);
		classslot->SetOverTexture(overTexture);
		classslots.push_back(classslot);
		count++;
	}
}

void PickbanList::SetList() // 리스트 올리기
{
	if (isSet)
		return;

	time += DELTA;
	block_speed += BLOCK_SPEED;

	if (time >= START_SET_TIME)
	{
		pos.y -= (SET_SPEED - block_speed) * DELTA;

		if (Bottom() <= WIN_HEIGHT)
		{
			isSet = true;
			return;
		}
	}
}
