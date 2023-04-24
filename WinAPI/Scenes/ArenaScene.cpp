#include "Framework.h"
#include "ArenaScene.h"

ArenaScene::ArenaScene()
{
	bg = new ImageRect(L"Textures/Arena/Arena_1.bmp", 1, 1, WHITE);
	Audio::Get()->Add("Arena", "Sounds/Arena_bgm.wav", true);
}

ArenaScene::~ArenaScene()
{
	delete bg;
}

void ArenaScene::Update()
{
	SetChampionsTarget();

	waterfall1->Update();
	waterfall2->Update();
	header->Update();
	ending->Update();

	for (Champion* champs : player_champions)
	{
		champs->Update();
	}

	for (Champion* champs : computer_champions)
	{
		champs->Update();
	}

	CharaCardManager::Get()->Update();
	GameTextManager::Get()->Update();
	ProjectileManager::Get()->Update();

	CheckFinishGame();
}

void ArenaScene::Render(HDC hdc)
{
	waterfall1->Render(hdc);
	waterfall2->Render(hdc);
	bg->Render(hdc);

	for (Champion* champs : player_champions)
	{
		champs->Render(hdc);
	}

	for (Champion* champs : computer_champions)
	{
		champs->Render(hdc);
	}

	ending->Render(hdc);
	header->Render(hdc);
	PrintKillScore(hdc);
	PrintGameTime(hdc);
	CharaCardManager::Get()->Render(hdc);
	GameTextManager::Get()->Render(hdc);
	ProjectileManager::Get()->Render(hdc);
}

void ArenaScene::Start()
{
	Audio::Get()->Play("Arena", 0.4f);
	bg->pos = { CENTER_X, CENTER_Y };

	hfont_28 = CreateFont(28, 0, 0, 0, 1, false, false, false, HANGUL_CHARSET,
		100, 0, 0, 0, L"Galmuri14 Regular");
	hfont_50 = CreateFont(50, 0, 0, 0, 1, false, false, false, HANGUL_CHARSET,
		100, 0, 0, 0, L"Galmuri14 Regular");

	waterfall1 = new Waterfall();
	waterfall2 = new Waterfall();
	waterfall1->pos = { 480, WIN_HEIGHT + 10 };
	waterfall2->pos = { 800, WIN_HEIGHT + 10 };
	waterfall1->size.x = 70;
	waterfall2->size.x = 70;

	GameTextManager::Get();
	ProjectileManager::Get();
	CharaCardManager::Get()->SetKDAActive();

	header = new Header();
	header->SetArenaHeader();

	ending = new Ending();

	CreateChampions();
	CreateEffect();
	CreateSound();
	CreateRespawnSlot();

	SetAlly();
}

void ArenaScene::End()
{
	for (Champion* champs : player_champions)
	{
		delete champs;
	}

	for (Champion* champs : computer_champions)
	{
		delete champs;
	}

	player_champions.clear();
	computer_champions.clear();

	GameTextManager::Delete();
	ProjectileManager::Delete();
	
	DeleteObject(hfont_28);
	DeleteObject(hfont_50);
	delete waterfall1;
	delete waterfall2;
	delete header;
	delete ending;
}

void ArenaScene::CreateEffect()
{
	//일반 공격 이펙트
	Texture* texture = Texture::Add(L"Textures/Arena/None.bmp"); // Default
	EffectManager::Get()->Add("None", 15, texture);
	texture = Texture::Add(L"Textures/Class/Pyromancer/pyromancer_effect.bmp", 13, 1);
	EffectManager::Get()->Add("Pyromancer_Attack", 5, texture);

	//기술 이펙트
	texture = Texture::Add(L"Textures/Class/Fighter/fighter_effect_L.bmp", 1, 8);
	EffectManager::Get()->Add("Fighter_Skill_L", 5, texture);
	texture = Texture::Add(L"Textures/Class/Fighter/fighter_effect_R.bmp", 8, 1);
	EffectManager::Get()->Add("Fighter_Skill_R", 5, texture);
	texture = Texture::Add(L"Textures/Class/Monk/monk_effect.bmp", 9, 1);
	EffectManager::Get()->Add("Monk_Skill", 4, texture);
	texture = Texture::Add(L"Textures/Class/Ninja/ninja_effect.bmp", 8, 1);
	EffectManager::Get()->Add("Ninja_Skill", 5, texture);
	texture = Texture::Add(L"Textures/Class/Soldier/soldier_effect_R.bmp", 1, 10);
	EffectManager::Get()->Add("Soldier_Skill_R", 2, texture);
	texture = Texture::Add(L"Textures/Class/Soldier/soldier_effect_L.bmp", 1, 10);
	EffectManager::Get()->Add("Soldier_Skill_L", 2, texture);
}

void ArenaScene::CreateSound()
{
	//스킬 사운드
	Audio::Get()->Add("Monk_Skill", "Sounds/Monk_skill.wav");
	Audio::Get()->Add("Priest_Skill", "Sounds/Priest_skill.wav");
	Audio::Get()->Add("Soldier_Skill", "Sounds/Soldier_skill.wav");
	Audio::Get()->Add("Swordman_Skill", "Sounds/Swordman_skill.wav");

	//일반 공격 사운드
	Audio::Get()->Add("Archer_Attack", "Sounds/Arhcer_attack.wav");
	Audio::Get()->Add("Fighter_Attack", "Sounds/Fighter_attack.wav");
	Audio::Get()->Add("Knight_Attack", "Sounds/Knight_attack.wav");
	Audio::Get()->Add("Monk_Attack", "Sounds/Monk_attack.wav");
	Audio::Get()->Add("Ninja_Attack", "Sounds/Ninja_attack.wav");
	Audio::Get()->Add("Pyromancer_Attack", "Sounds/Pyromancer_attack.wav");
	Audio::Get()->Add("Pythoness_Attack", "Sounds/Pythoness_attack.wav");
	Audio::Get()->Add("Soldier_Attack", "Sounds/Soldier_attack.wav");
	Audio::Get()->Add("Swordman_Attack", "Sounds/Swordman_attack.wav");
}

void ArenaScene::CreateRespawnSlot()
{
}

void ArenaScene::CreateChampions()
{
	player_champions = GamerManager::Get()->GetPlayer()->GetChampions();
	computer_champions = GamerManager::Get()->GetComputer()->GetChampions();

	for (int i = 0; i < 3; i++)
	{
		player_champions[i]->pos = { 400, (float)( i * 100 + 300)};
		computer_champions[i]->pos = { 880,(float)(i * 100 + 300)};

		player_champions[i]->SetRespawnLocation({ 400,400 });
		computer_champions[i]->SetRespawnLocation({ 880,400 });

		player_champions[i]->SetHpBarColor("Player");
		computer_champions[i]->SetHpBarColor("Computer");
	}
}

void ArenaScene::SetAlly()
{
	for (Champion* champs : player_champions)
	{
		champs->SetAllyChampions("Player");
		champs->SetIsPlayer(true);
	}

	for (Champion* champs : computer_champions)
	{
		champs->SetAllyChampions("Computer");
		champs->SetIsPlayer(false);
	}
}

void ArenaScene::SetChampionsTarget()
{
	if (isFinish) return; // 게임이 끝나면 타게팅 중지

	for (Champion* champs : player_champions)
	{
		champs->SetTarget(GetClosestComputerChampion(champs->pos));

		if (champs->GetTarget() == nullptr)
			continue;

		if (champs->GetTarget()->isActive == false)
		{
			champs->SetTarget(nullptr);
		}
		
	}

	for (Champion* champs : computer_champions)
	{
		if (champs->GetTarget())
			continue;

		champs->SetTarget(GetClosestPlayerChampion(champs->pos));

		if (champs->GetTarget() == nullptr)
			continue;

		if (champs->GetTarget()->isActive == false)
		{
			champs->SetTarget(nullptr);
		}
	}
}

void ArenaScene::PrintKillScore(HDC hdc)
{
	playerscore = 0;
	computerscore = 0;
	
	for (Champion* champs : player_champions)
	{
		playerscore += champs->GetKillCount();
	}
	for (Champion* champs : computer_champions)
	{
		computerscore += champs->GetKillCount();
	}


	SelectObject(hdc, hfont_50);
	SetTextColor(hdc, WHITE);
	TextOutA(hdc, 515, 3, to_string(playerscore).c_str(), to_string(playerscore).size());
	TextOutA(hdc, 740, 3, to_string(computerscore).c_str(), to_string(computerscore).size());
}

void ArenaScene::PrintGameTime(HDC hdc)
{
	SelectObject(hdc, hfont_28);

	gameTime -= DELTA ;
	string gameTimeText = ": " + to_string((int)gameTime);

	TextOutA(hdc, CENTER_X - 22, 54, gameTimeText.c_str(), gameTimeText.size());
}

void ArenaScene::CheckFinishGame()
{
	if (gameTime <= 0.0f)
	{
		gameTime = 0.0f;
		isFinish = true;

		for (Champion* champs : player_champions)
		{
			champs->SetTarget(nullptr);
		}

		for (Champion* champs : computer_champions)
		{
			champs->SetTarget(nullptr);
		}

		ending->StartEnd(playerscore, computerscore);
	}
}


GameObject* ArenaScene::GetClosestPlayerChampion(Vector2 pos)
{
	Champion* closest = nullptr; // 담는 곳
	float length = 0.0f;

	for (int i = 0; i < player_champions.size(); i++)
	{
		if (!player_champions[i]->isActive)
			continue;

		if (length > (player_champions[i]->pos - pos).Length())
		{
			closest = player_champions[i];
			continue;
		}

		if (closest == NULL)
		{
			closest = player_champions[i];
		}
		
	}

	return closest;
}

GameObject* ArenaScene::GetClosestComputerChampion(Vector2 pos)
{
	Champion* closest = nullptr;
	float length = 0.0f;

	for (int i = 0; i < computer_champions.size(); i++)
	{
		if (!computer_champions[i]->isActive)
			continue;

		if (length > (computer_champions[i]->pos - pos).Length())
		{
			closest = computer_champions[i];
			continue;
		}

		if (closest == NULL)
		{
			closest = computer_champions[i];
		}

	}

	return closest;
}
