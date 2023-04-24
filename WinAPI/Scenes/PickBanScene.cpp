#include "Framework.h"
#include "PickBanScene.h"

PickBanScene::PickBanScene()
{
	bg = new ImageRect(L"Textures/Pickban/pickban_bg.bmp");
	Audio::Get()->Add("PickBan", "Sounds/Banpick_bgm.wav", true);
	Audio::Get()->Add("Ban", "Sounds/Ban_sound.wav");
	Audio::Get()->Add("Pick", "Sounds/Pick_sound.wav");

	Observer::Get()->AddEvent("ChangeArena",
		bind(&PickBanScene::StartArena, this));
}

PickBanScene::~PickBanScene()
{
	delete bg;
}

void PickBanScene::Update()
{
	header->Update();
	CharaCardManager::Get()->SetCardTexture();
	CharaCardManager::Get()->Update();
	pickbanlist->Update();
	pickbanturn->Update();
}

void PickBanScene::Render(HDC hdc)
{
	bg->Render(hdc); 
	header->Render(hdc);
	pickbanlist->Render(hdc);
	pickbanturn->Render(hdc);

	CharaCardManager::Get()->Render(hdc);
}

void PickBanScene::Start()
{
	bg->pos = { CENTER_X, CENTER_Y };
	header = new Header();

	CharaCardManager::Get()->CreateCards();

	pickbanturn = new PickBanTurn();
	pickbanlist = new PickbanList();
	pickbanturn->SetClassSlot(pickbanlist->GetClassSlots());
	Audio::Get()->Play("PickBan");
}

void PickBanScene::End()
{
	delete header;
	delete pickbanlist;
	delete pickbanturn;
	delete arenabutton;
	Audio::Get()->Stop("PickBan");
}


void PickBanScene::StartArena()
{
	SceneManager::Get()->ChangeScene("Arena");
}
