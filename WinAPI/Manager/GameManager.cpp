#include "Framework.h"
#include "Scenes/StartScene.h"
#include "Scenes/PickBanScene.h"
#include "Scenes/ArenaScene.h"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager()    
{    
    srand(time(NULL));
    Init();

    SceneManager::Get()->Add("Start", new StartScene());
    SceneManager::Get()->Add("PickBan", new PickBanScene());
    SceneManager::Get()->Add("Arena", new ArenaScene());

    SceneManager::Get()->ChangeScene("Start");
}

GameManager::~GameManager()
{
    Timer::Delete();
    Keyboard::Delete();
    Texture::Delete();
    Audio::Delete();
    EffectManager::Delete();
    Camera::Delete();
    Observer::Delete();
    SceneManager::Delete();
    DataManager::Delete();
    GamerManager::Delete();
    CharaCardManager::Delete();
}

void GameManager::Init()
{
    hdc = GetDC(hWnd);

    hBackDC = CreateCompatibleDC(hdc);
    hBackBitmap = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT);
    SelectObject(hBackDC, hBackBitmap);    

    Timer::Get();
    Keyboard::Get();
    Audio::Get();
    EffectManager::Get();
    DataManager::Get();
    GamerManager::Get();
    Camera::Get();
    Observer::Get();    

    SetBkMode(hBackDC, TRANSPARENT);
}

void GameManager::Update()
{
    if (KEY_DOWN(VK_TAB))
        Texture::SetDebug();

    Timer::Get()->Update();
    Keyboard::Get()->Update();
    Audio::Get()->Update();
    EffectManager::Get()->Update();

    SceneManager::Get()->Update();

    Camera::Get()->Update();
}

void GameManager::Render()
{
    PatBlt(hBackDC, 0, 0, WIN_WIDTH, WIN_HEIGHT, WHITENESS);

    //InvalidateRect(hWnd, nullptr, false);
    SceneManager::Get()->Render(hBackDC);
    EffectManager::Get()->Render(hBackDC);

    Timer::Get()->Render(hBackDC);

    BitBlt(hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT,
        hBackDC, 0, 0, SRCCOPY);
}
