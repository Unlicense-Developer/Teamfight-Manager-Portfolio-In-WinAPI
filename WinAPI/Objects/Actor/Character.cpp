#include "Framework.h"

Character::Character(wstring file, int frameX, int frameY, COLORREF transColor)
{
	texture = Texture::Add(file, frameX, frameY, transColor);

	imageRect = new ImageRect(texture);

	attackCollider = new Rect();
	attackCollider->isActive = false;

	skillCollider = new Rect();
	skillCollider->isActive = false;
}

Character::~Character()
{
	delete attackCollider;
	delete skillCollider;
	delete imageRect;

	for (pair<int, Animation*> animation : animations)
		delete animation.second;
}

void Character::Update()
{
	imageRect->pos = pos + imageOffset;
	ResetTarget();

	if (animations.count(curType) > 0)
		animations[curType]->Update();
}

void Character::Render(HDC hdc, int alpha)
{
	if (animations.count(curType) == 0)
	{
		imageRect->Render(hdc);
		return;
	}

	if (alpha < 255)
		imageRect->Render(hdc, alpha, animations[curType]->GetFrame());
	else
		imageRect->Render(hdc, animations[curType]->GetFrame());
}

void Character::ResetTarget()
{
	if (target == nullptr) return;

	if (((Champion*)target)->GetcurHp() <= 0)
	{
		target = nullptr;
		isAttack = false;
	}
}

void Character::SetAction(int type)
{
	if (curType == type) return;

	curType = type;
	animations[type]->Play();
}
