#include "Framework.h"

Waterfall::Waterfall()
	:ImageRect(L"Textures/Arena/waterfall.bmp", 8, 1)
{
	animation = new Animation(texture->GetFrame());
	animation->SetDefault(true);
	animation->Play();
}

Waterfall::~Waterfall()
{
	delete animation;
}

void Waterfall::Update()
{
	animation->Update();
}

void Waterfall::Render(HDC hdc)
{
	ImageRect::Render(hdc, animation->GetFrame());
}
