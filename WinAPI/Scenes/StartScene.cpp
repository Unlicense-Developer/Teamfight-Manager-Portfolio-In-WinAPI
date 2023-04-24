#include "Framework.h"
#include "StartScene.h"

StartScene::StartScene()
{
	hfont = CreateFont(40, 0, 0, 0, 1, false, false, false, HANGUL_CHARSET,
		100, 0, 0, 0, L"Galmuri9 Regular");

	startmenuBg = new ImageRect(L"Textures/Startmenu/Startmenu_bg.bmp", 1, 1, WHITE);
	stadium_sky = new ImageRect(L"Textures/Startmenu/Stadium_sky.bmp");
	stadium = new ImageRect(L"Textures/Startmenu/Stadium.bmp", 1, 1, WHITE);
	logo = new ImageRect(L"Textures/Startmenu/Logo.bmp", 1, 1, WHITE);

	Texture* normal = Texture::Add(L"Textures/Startmenu/Normal.bmp", 1, 1, WHITE);
	Texture* over = Texture::Add(L"Textures/Startmenu/Over.bmp", 1, 1, WHITE);
	Texture* down = Texture::Add(L"Textures/Startmenu/Down.bmp", 1, 1, WHITE);

	newgame = new Button(normal);
	newgame->SetOverTexture(over);
	newgame->SetDownTexture(down);
	newgame->pos = { CENTER_X, CENTER_Y };
	newgame->SetEvent(bind(&StartScene::StartPickBanScene, this));


	Audio::Get()->Add("Startmenu", "Sounds/Start_bgm.wav", true);
}

StartScene::~StartScene()
{
	DeleteObject(hfont);

	delete startmenuBg;
	delete stadium_sky;
	delete stadium;
	delete logo;

	delete newgame;
}

void StartScene::Update()
{
	newgame->Update();
}

void StartScene::Render(HDC hdc)
{
	stadium_sky->Render(hdc);
	stadium->Render(hdc);
	startmenuBg->Render(hdc);
	logo->Render(hdc);

	newgame->Render(hdc);
}

void StartScene::Start()
{
	startmenuBg->pos = { CENTER_X, CENTER_Y };
	stadium_sky->pos = { CENTER_X, CENTER_Y };
	stadium->pos = { CENTER_X, CENTER_Y };
	logo->pos = { CENTER_X, CENTER_Y - 200 };

	Audio::Get()->Play("Startmenu");
}

void StartScene::End()
{
	Audio::Get()->Stop("Startmenu");
}

void StartScene::StartPickBanScene()
{
	SceneManager::Get()->ChangeScene("PickBan");
}
