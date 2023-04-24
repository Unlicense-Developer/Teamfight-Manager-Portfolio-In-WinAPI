#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#define WIN_START_X 1250
#define WIN_START_Y 200

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

#define CENTER_X (WIN_WIDTH * 0.5f)
#define CENTER_Y (WIN_HEIGHT * 0.5f)

#define PI 3.141592f

#define RED RGB(255, 0, 0)
#define GREEN RGB(0, 255, 0)
#define BLUE RGB(0, 0, 255)
#define YELLOW RGB(255, 255, 0)
#define CYAN RGB(0, 255, 255)
#define MAGENTA RGB(255, 0, 255)
#define BLACK RGB(0, 0, 0)
#define WHITE RGB(255, 255, 255)

#define DELTA Timer::Get()->GetElapsedTime()

#define KEY_DOWN(k) Keyboard::Get()->Down(k)
#define KEY_UP(k) Keyboard::Get()->Up(k)
#define KEY_PRESS(k) Keyboard::Get()->Press(k)

#define GAMER_MAX_CHAMP 3
#define MIN_ARENA_X 255
#define MAX_ARENA_X 1020
#define MIN_ARENA_Y 235
#define MAX_ARENA_Y 635

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <functional>
#include <iomanip>

using namespace std;

typedef function<void()> Event;
typedef function<void(void*)> ParamEvent;

//FMOD Library
#include "Libraries/inc/fmod.hpp"
#pragma comment(lib, "Libraries/lib/fmod_vc.lib")

//Framework Header
#include "Framework/Utilities/Utility.h"
#include "Framework/Utilities/Singleton.h"
#include "Framework/Utilities/Timer.h"
#include "Framework/Utilities/Keyboard.h"
#include "Framework/Utilities/Audio.h"

using namespace Utility;

#include "Framework/Math/Vector2.h"
#include "Framework/Math/GameMath.h"

using namespace GameMath;

#include "Framework/Render/Texture.h"
#include "Framework/Render/Animation.h"	
#include "Framework/Render/Camera.h"

//Object Header
#include "Objects/Basic/GameObject.h"
#include "Objects/Basic/Rect.h"
#include "Objects/Basic/Circle.h"
#include "Objects/Basic/Line.h"
#include "Objects/Basic/ImageRect.h"
#include "Objects/Basic/Effect.h"

#include "Objects/Gamer/Gamer.h"
#include "Objects/Gamer/Player.h"
#include "Objects/Gamer/Computer.h"

#include "Objects/UI/ProgressBar.h"
#include "Objects/UI/Button.h"

#include "Objects/Arena/Waterfall.h"
#include "Objects/Arena/GameText.h"
#include "Objects/Arena/DamageText.h"
#include "Objects/Arena/HealText.h"
#include "Objects/Arena/Arrow.h"
#include "Objects/Arena/Ending.h"

#include "Objects/Manager/PoolingManager.h"
#include "Objects/Manager/EffectManager.h"
#include "Objects/Manager/Observer.h"
#include "Objects/Manager/DataManager.h"
#include "Objects/Manager/GamerManager.h"
#include "Objects/Manager/CharaCardManager.h"
#include "Objects/Manager/GameTextManager.h"
#include "Objects/Manager/ProjectileManager.h"

#include "Objects/Actor/Character.h"
#include "Objects/Actor/Champion.h"

#include "Objects/Actor/Archer.h"
#include "Objects/Actor/Fighter.h"
#include "Objects/Actor/Knight.h"
#include "Objects/Actor/Monk.h"
#include "Objects/Actor/Ninja.h"
#include "Objects/Actor/Priest.h"
#include "Objects/Actor/Pyromancer.h"
#include "Objects/Actor/Pythoness.h"
#include "Objects/Actor/Soldier.h"
#include "Objects/Actor/Swordman.h"
#include "Objects/Actor/FireSpirit.h"

#include "Objects/PickBan/Header.h"
#include "Objects/PickBan/CharaCard.h"
#include "Objects/PickBan/ClassSlot.h"
#include "Objects/PickBan/PickbanList.h"
#include "Objects/PickBan/PickbanTurn.h"



//Scene Header
#include "Scenes/Scene.h"

//Manager Header
#include "Manager/SceneManager.h"
#include "Manager/GameManager.h"

extern Vector2 mousePos;
extern HINSTANCE hInst;
extern HWND hWnd;