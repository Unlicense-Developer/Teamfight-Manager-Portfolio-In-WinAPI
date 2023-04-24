#include "Framework.h"

Arrow::Arrow()
	:ImageRect()
{
	isActive = false;
}

Arrow::~Arrow()
{
}

void Arrow::Update()
{
	if (!isActive) return;

	Vector2 direction = destination - pos;

	pos += direction * speed * DELTA;

	if (direction.Length() < 1)
	{
		isActive = false;
	}
}

void Arrow::Render(HDC hdc)
{
	if (!isActive) return;

	ImageRect::Render(hdc);
}

void Arrow::Shoot(const Vector2& start, const Vector2& destination, bool AttackDirection)
{
	Vector2 direction = destination - start;
	Texture* arrow = nullptr;

	if (direction.x == 0)
	{
		if (direction.y > 0) // UP
			arrow = Texture::Add(L"Textures/Class/Archer/arrow_up.bmp");
		else if (direction.y < 0) // DOWN
			arrow = Texture::Add(L"Textures/Class/Archer/arrow_down.bmp");
	}
	else if (direction.y == 0)
	{
		if (direction.x > 0) // RIGHT
			arrow = Texture::Add(L"Textures/Class/Archer/arrow_right.bmp");
		else if (direction.x < 0) // LEFT
			arrow = Texture::Add(L"Textures/Class/Archer/arrow_left.bmp");
	}

	if (direction.x > 0)
	{
		if (direction.y > 0) // RB
			arrow = Texture::Add(L"Textures/Class/Archer/arrow_rb.bmp");
		else if (direction.y < 0) // RT
			arrow = Texture::Add(L"Textures/Class/Archer/arrow_rt.bmp");
	}
	else if (direction.x < 0)
	{
		if ( direction.y > 0) // LB
			arrow = Texture::Add(L"Textures/Class/Archer/arrow_lb.bmp");
		else if ( direction.y < 0) // LT
			arrow = Texture::Add(L"Textures/Class/Archer/arrow_lt.bmp");
	}

	if (direction.x == 0 && direction.y == 0)
	{
		if (AttackDirection) // ¿À¸¥ÂÊ
		{
			arrow = Texture::Add(L"Textures/Class/Archer/arrow_right.bmp");
		}
		else
		{
			arrow = Texture::Add(L"Textures/Class/Archer/arrow_left.bmp");
		}
	}
	
	SetTexture(arrow);
	isActive = true;
	this->pos = start;
	this->destination = destination;
}
