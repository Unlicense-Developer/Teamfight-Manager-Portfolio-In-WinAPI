#include "Framework.h"

PickBanTurn::PickBanTurn()
	:ImageRect(L"Textures/Pickban/pickban_turn_blue.bmp", 1, 1, WHITE)
{
	hfont_18 = CreateFont(18, 0, 0, 0, 1, false, false, false, HANGUL_CHARSET,
		100, 0, 0, 0, L"Galmuri14 Regular");
	hfont_25 = CreateFont(25, 0, 0, 0, 1, false, false, false, HANGUL_CHARSET,
		100, 0, 0, 0, L"Galmuri14 Regular");
	hfont_40 = CreateFont(40, 0, 0, 0, 1, false, false, false, HANGUL_CHARSET,
		100, 0, 0, 0, L"Galmuri14 Regular");

	pos = { CENTER_X, WIN_HEIGHT + size.y * 2.2f };

	Texture* arenabutton_texture = Texture::Add(L"Textures/Pickban/arenabutton_normal.bmp");
	Texture* arenabutton_overtexture = Texture::Add(L"Textures/Pickban/arenabutton_over.bmp");
	Texture* arenabutton_downtexture = Texture::Add(L"Textures/Pickban/arenabutton_down.bmp");

	arenabutton = new Button(arenabutton_texture);
	arenabutton->SetNormalTexture(arenabutton_texture);
	arenabutton->SetOverTexture(arenabutton_overtexture);
	arenabutton->SetDownTexture(arenabutton_downtexture);
	arenabutton->pos = { CENTER_X, CENTER_Y };
	arenabutton->SetDownEvent(bind(&PickBanTurn::ChangeArena, this));
	arenabutton->isActive = false;

	ban1 = new ImageRect();
	ban2 = new ImageRect();
	ban1->pos = { CENTER_X - 280, 662 };
	ban2->pos = { CENTER_X + 280, 662 };
}

PickBanTurn::~PickBanTurn()
{
	DeleteObject(hfont_25);
	DeleteObject(hfont_40);
	delete arenabutton;
	delete ban1;
	delete ban2;
}

void PickBanTurn::Update() // 함수 순서 꼭 지킬것 pick -> checkturn
{
	SetPhaseSlot();
	SetHeight();
	ComputerBan();
	Pick();
	CheckTurn();

	arenabutton->Update();
}

void PickBanTurn::Render(HDC hdc)
{
	ImageRect::Render(hdc);
	PrintTurnText(hdc);
	PrintArenaButton(hdc);
	PrintBanSlot(hdc);
}

void PickBanTurn::SetHeight()
{
	if (isSet)
		return;

	time += DELTA;
	block_speed += BLOCK_SPEED;

	if (time >= START_SET_TIME)
	{
		pos.y -= (SET_SPEED - block_speed) * DELTA;

		if (Top() <= BLOCK_HEIGHT)
		{
			isSet = true;
			time = 0;
			return;
		}
	}
}

void PickBanTurn::PrintTurnText(HDC hdc)
{
	if (isSet && BanPhase)
	{
		if (isPlayerTurn)
		{
			Texture* bluetexture = Texture::Add(L"Textures/Pickban/pickban_turn_blue.bmp", 1, 1, WHITE);
			texture = bluetexture;
			SelectObject(hdc, hfont_40);
			TextOutA(hdc, pos.x - 180, pos.y - 20, PLAYER_BAN_STR.c_str(), PLAYER_BAN_STR.size());
			SelectObject(hdc, hfont_25);
			TextOutA(hdc, pos.x - 370, pos.y - 22, BAN_PROGRESS_STR.c_str(), BAN_PROGRESS_STR.size());
			TextOutA(hdc, pos.x - 370, pos.y, banpickProgress_Text.c_str(), banpickProgress_Text.size());
		}
		else if (isComputerTurn)
		{
			Texture* redtexture = Texture::Add(L"Textures/Pickban/pickban_turn_red.bmp", 1, 1, WHITE);
			texture = redtexture;
			// 중앙
			SelectObject(hdc, hfont_40);
			TextOutA(hdc, pos.x - 180, pos.y - 20, COMPUTER_BAN_STR.c_str(), COMPUTER_BAN_STR.size());
			// 턴 텍스트
			SelectObject(hdc, hfont_25);
			TextOutA(hdc, pos.x + 370, pos.y - 22, BAN_PROGRESS_STR.c_str(), BAN_PROGRESS_STR.size());
			TextOutA(hdc, pos.x + 370, pos.y, banpickProgress_Text.c_str(), banpickProgress_Text.size());
		}
	}

	if (isSet && PickPhase)
	{
		if (isPlayerTurn)
		{
			Texture* bluetexture = Texture::Add(L"Textures/Pickban/pickban_turn_blue.bmp", 1, 1, WHITE);
			texture = bluetexture;
			SelectObject(hdc, hfont_40);
			TextOutA(hdc, pos.x - 180, pos.y - 20, PLAYER_PICK_STR.c_str(), PLAYER_PICK_STR.size());
			SelectObject(hdc, hfont_25);
			TextOutA(hdc, pos.x - 370, pos.y - 22, PICK_PROGRESS_STR.c_str(), PICK_PROGRESS_STR.size());
			TextOutA(hdc, pos.x - 370, pos.y, banpickProgress_Text.c_str(), banpickProgress_Text.size());
		}
		else if (isComputerTurn)
		{
			Texture* redtexture = Texture::Add(L"Textures/Pickban/pickban_turn_red.bmp", 1, 1, WHITE);
			texture = redtexture;
			// 중앙
			SelectObject(hdc, hfont_40);
			TextOutA(hdc, pos.x - 180, pos.y - 20, COMPUTER_PICK_STR.c_str(), COMPUTER_PICK_STR.size());
			// 턴 텍스트
			SelectObject(hdc, hfont_25);
			TextOutA(hdc, pos.x + 370, pos.y - 22, PICK_PROGRESS_STR.c_str(), PICK_PROGRESS_STR.size());
			TextOutA(hdc, pos.x + 370, pos.y, banpickProgress_Text.c_str(), banpickProgress_Text.size());
		}
	}

	if (!BanPhase && !PickPhase)
	{
		SelectObject(hdc, hfont_40);
		TextOutA(hdc, pos.x - 180, pos.y - 20, PICK_END_STR.c_str(), PICK_END_STR.size());
	}

}

void PickBanTurn::PrintArenaButton(HDC hdc)
{
	arenabutton->Render(hdc);
	if (!BanPhase && !PickPhase)
	{
		arenabutton->SetText("전투 시작");
		arenabutton->SetFont(hfont_40, 40, WHITE);
		arenabutton->isActive = true;
	}
}

void PickBanTurn::PrintBanSlot(HDC hdc)
{
	SelectObject(hdc, hfont_18);
	SetTextColor(hdc, WHITE);



	if (ban1->GetTexture())
	{
		Vector2 textpos;

		if (DataManager::Get()->SearchClassData(ban1key).jobname.size() == 4) // 이름 두글자
		{
			textpos = { ban1->pos.x- 12, ban1->pos.y + 27 };
		}
		else if (DataManager::Get()->SearchClassData(ban1key).jobname.size() == 6) // 이름 세글자
		{
			textpos = { ban1->pos.x - 19, ban1->pos.y + 27 };
		}
		else if (DataManager::Get()->SearchClassData(ban1key).jobname.size() == 8) // 이름 네글자
		{
			textpos = { ban1->pos.x - 25, ban1->pos.y + 27 };
		}

		ban1->Render(hdc);
		TextOutA(hdc, textpos.x, textpos.y, DataManager::Get()->SearchClassData(ban1key).jobname.c_str(), DataManager::Get()->SearchClassData(ban1key).jobname.size());
	}

	if (ban2->GetTexture())
	{
		Vector2 textpos;

		if (DataManager::Get()->SearchClassData(ban2key).jobname.size() == 4) // 이름 두글자
		{
			textpos = { ban2->pos.x - 12, ban2->pos.y + 27 };
		}
		else if (DataManager::Get()->SearchClassData(ban2key).jobname.size() == 6) // 이름 세글자
		{
			textpos = { ban2->pos.x - 19, ban2->pos.y + 27 };
		}
		else if (DataManager::Get()->SearchClassData(ban2key).jobname.size() == 8) // 이름 네글자
		{
			textpos = { ban2->pos.x - 25, ban2->pos.y + 27 };
		}

		ban2->Render(hdc);
		TextOutA(hdc, textpos.x, textpos.y, DataManager::Get()->SearchClassData(ban2key).jobname.c_str(), DataManager::Get()->SearchClassData(ban2key).jobname.size());
	}
}


void PickBanTurn::CheckTurn()
{
	banpickProgress_Text = "(" + to_string(banpickProgress) + "/" + to_string(MAX_BANPICK_PROGRESS) + ")";

	if (isPlayerTurn && BanPhase)
	{
		int count = 0;

		for (ClassSlot* classslot : classslots)
		{
			if (classslot->GetBaned())
			{
				ActiveBanSlot(classslot->GetData().key);
				count++;
			}

			if (count == banpickProgress)
			{
				isPlayerTurn = false;
				isComputerTurn = true;
				banpickProgress++;
				break;
			}
		}
	}
	else if (isComputerTurn && BanPhase) // 컴퓨터턴
	{
		int count = 0;

		for (ClassSlot* classslot : classslots)
		{
			if (classslot->GetBaned())
			{
				count++;
			}

			if (count == banpickProgress)
			{
				if (banpickProgress == MAX_BANPICK_PROGRESS)
				{
					PickPhase = false;
					return;
				}

				isComputerTurn = false;
				isPlayerTurn = true;
				banpickProgress++;
				break;
			}

		}
	}

	if (isPlayerTurn && PickPhase) // 플레이어턴
	{
		int count = 2;

		for (ClassSlot* classslot : classslots)
		{
			if (classslot->GetPicked())
			{
				count++;
			}
			
			if (count == banpickProgress)
			{
				isPlayerTurn = false;
				isComputerTurn = true;
				banpickProgress++;
				break;
			}
		}
	}
	else if (isComputerTurn && PickPhase) // 컴퓨터턴
	{
		int count = 2;

		for (ClassSlot* classslot : classslots)
		{
			if (classslot->GetPicked())
			{
				count++;
			}

			if (count == banpickProgress )
			{

				if (banpickProgress == MAX_BANPICK_PROGRESS)
				{
					PickPhase = false;
					isPlayerTurn = true;
					isComputerTurn = false;
					return;
				}

				isPlayerTurn = true;
				isComputerTurn = false;
				banpickProgress++;
				break;
			}

		}
	}

	if (banpickProgress == 3 )
	{
		BanPhase = false;
		PickPhase = true;
	}
}

void PickBanTurn::ComputerBan()
{
	if (PickPhase)
		return;

	for (ClassSlot* classslot : classslots) // 컴퓨터 랜덤 밴
	{
		if (isComputerTurn)
		{
			if (classslot->GetBaned())
			{
				continue;
			}

			int Computerpick = Random(0, 3);

			if (Computerpick == 1) // 밴함
			{
				ActiveBanSlot(classslot->GetData().key);
				classslot->CheckBanEnd();
				break;
			}
		}
	}
}

void PickBanTurn::Pick() // 픽 데이터 추가 
{
	if (BanPhase)
	{
		return;
	}

	for (ClassSlot* classslot : classslots) // 컴퓨터 랜덤 픽 
	{
		if (isComputerTurn) 
		{
			int Computerpick = Random(0, 3);

			if (Computerpick == 1) // 픽함
			{
				if (classslot->GetAdded() == true)
					continue;

				if (classslot->GetBaned() == true)
					continue;

				classslot->CheckPickEnd();
				break;
			}
		}
	}

	for (ClassSlot* classslot : classslots)
	{
		if (classslot->GetPicked() && !classslot->GetAdded()) // 픽됨
		{
			if (isComputerTurn) // 컴퓨터턴
			{
				classslot->SetpickOrder(banpickProgress - 2);

				GamerManager::Get()->GetComputer()->AddPickChampion(classslot->GetData().key);
				classslot->AddComputer();
				break;
			}
			else if (isPlayerTurn) // 플레이어 픽
			{
				{
					classslot->SetpickOrder(banpickProgress - 2);
					GamerManager::Get()->GetPlayer()->AddPickChampion(classslot->GetData().key);
					classslot->AddPlayer();
					break;
				}
			}
		}
	}
}

void PickBanTurn::ChangeArena()
{
	Observer::Get()->ExcuteParamEvents("ChangeArena");
}

void PickBanTurn::ActiveBanSlot(int key)
{
	Texture* bantexture = Texture::Add(DataManager::Get()->SearchClassData(key).file);

	if (banpickProgress == 1)
	{
		ban1->SetTexture(bantexture);
		ban1->size = { BANSLOT_WIDTH, BANSLOT_HEIGHT };
		ban1key = key;
	}
	if (banpickProgress == 2)
	{
		ban2->SetTexture(bantexture);
		ban2->size = { BANSLOT_WIDTH, BANSLOT_HEIGHT };
		ban2key = key;
	}
}

void PickBanTurn::SetPhaseSlot()
{
	for (ClassSlot* classslot : classslots)
	{
		if(BanPhase)
			classslot->SetDownEvent(bind(&ClassSlot::CheckBanEnd, classslot));
		else if (PickPhase)
		{
			if (classslot->GetBaned())
				continue;

			classslot->SetDownEvent(bind(&ClassSlot::CheckPickEnd, classslot));
		}
	}	
	
}
