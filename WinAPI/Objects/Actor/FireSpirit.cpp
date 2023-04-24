#include "Framework.h"

FireSpirit::FireSpirit()
	:Character(L"Textures/Class/Pyromancer/firespirit_animation.bmp", 30, 1)
{
	texture = Texture::Add(L"Textures/Class/Pyromancer/firespirit_animation.bmp", 30, 1);
	imageRect = new ImageRect(texture);
	CreateAnimations();
	animations[curType]->Play();
	attackRange = new Circle(Vector2(), ATTACK_RANGE);

	red = CreatePen(PS_SOLID, 1, RED);
}

FireSpirit::~FireSpirit()
{
	delete imageRect;

	for (pair<int, Animation*> animation : animations)
		delete animation.second;
}

void FireSpirit::Update()
{
	if (animations.count(curType) > 0)
		animations[curType]->Update();
	SetTarget();
	CheckSummonTime();
	SetState();
	ActionState();
}

void FireSpirit::Render(HDC hdc)
{
	SelectObject(hdc, red);
	attackRange->Render(hdc);

	if (animations.count(curType) == 0)
	{
		imageRect->Render(hdc);
		return;
	}

	imageRect->Render(hdc, animations[curType]->GetFrame());
}

void FireSpirit::Stay()
{
	if (AttackDirection) // true 오른쪽
		SetAction(IDLE_R);
	else if (!AttackDirection)
		SetAction(IDLE_L);

	isAttack = false;
}

void FireSpirit::Attack()
{
	if (curType == ATTACK_R) return;
	if (curType == ATTACK_L) return;
	if (curType == DEAD) return;

	Vector2 direction = target->pos - pos;

	if (direction.x > 0.0f)
		AttackDirection = true;
	else if (direction.x < 0.0f)
		AttackDirection = false;

	if (AttackDirection)
	{
		isAttack = true;
		SetAction(ATTACK_R);
	}
	else if (!AttackDirection)
	{
		isAttack = true;
		SetAction(ATTACK_L);
	}

	//((Champion*)target)->Attacked();
}

void FireSpirit::EndAttack()
{
	if (target == nullptr)
	{
		isAttack = false;

		if (AttackDirection) // true 오른쪽
			SetAction(IDLE_R);
		else if (!AttackDirection)
			SetAction(IDLE_L);

		return;
	}


}

void FireSpirit::Dead()
{
	isActive = false;
	attackRange->isActive = false;
	imageRect->isActive = false;
}

void FireSpirit::Summon(Vector2 pos)	
{
	this->pos = pos;
	imageRect->pos = pos;
	attackRange->pos = pos;
	isActive = true;
	attackRange->isActive = true;
	imageRect->isActive = true;

	if (AttackDirection) // true 오른쪽
		SetAction(IDLE_R);
	else if (!AttackDirection)
		SetAction(IDLE_L);
}

void FireSpirit::CheckSummonTime()
{
	if (isActive)
	{
		summoningTime += DELTA;

		if (summoningTime >= SUMMON_TIME)
		{
			summoningTime = 0.0f;
			SetAction(DEAD);
		}
	}
}

void FireSpirit::SetState()
{
	if (curType == DEAD) return;

	if (attackRange->IsCollision(target))
	{
		state = State::ATTACK;
		return;
	}
	else
	{
		state = State::STAY;
	}
}

void FireSpirit::SetAction(int type)
{
	if (curType == type) return;

	curType = type;
	animations[type]->Play();
}

void FireSpirit::SetTarget()
{
	float length = 0.0f;


	if (pyromancer->GetIsPlayer())
	{
		if (enemies.size() < 3)
		{
			if (GamerManager::Get()->GetComputer()->GetChampions().size() == 3)
			{
				for (int i = 0; i < GAMER_MAX_CHAMP; i++)
				{
					enemies.push_back(GamerManager::Get()->GetComputer()->GetChampions()[i]);
				}
			}
		}
	}
	else
	{
		if (enemies.size() < 3)
		{
			if (GamerManager::Get()->GetPlayer()->GetChampions().size() == 3)
			{
				for (int i = 0; i < GAMER_MAX_CHAMP; i++)
				{
					enemies.push_back(GamerManager::Get()->GetPlayer()->GetChampions()[i]);
				}
			}
		}
	}
	
	for (int i = 0; i < enemies.size(); i++)
	{
		if (!enemies[i]->isActive)
			continue;

		if (length > (enemies[i]->pos - pos).Length())
		{
			target = enemies[i];
			continue;
		}

		if (target == NULL)
		{
			target = enemies[i];
		}

	}
}

void FireSpirit::ActionState()
{
	switch (state)
	{
	case FireSpirit::State::STAY:
		Stay();
		break;
	case FireSpirit::State::ATTACK:
		Attack();
		break;
	case FireSpirit::State::DEAD:
		Dead();
		break;
	}
}

void FireSpirit::CreateAnimations()
{
	animations[IDLE_R] = new Animation(texture->GetFrame(), 0.4f);
	animations[IDLE_R]->SetPart(0, 4, true, true);

	animations[IDLE_L] = new Animation(texture->GetFrame(), 0.4f);
	animations[IDLE_L]->SetPart(15, 19 , true, true);

	animations[ATTACK_R] = new Animation(texture->GetFrame());
	animations[ATTACK_R]->SetPart(5, 10);
	animations[ATTACK_R]->SetEndEvent(bind(&FireSpirit::EndAttack, this));

	animations[ATTACK_L] = new Animation(texture->GetFrame());
	animations[ATTACK_L]->SetPart(20, 25);
	animations[ATTACK_L]->SetEndEvent(bind(&FireSpirit::EndAttack, this));

	animations[DEAD] = new Animation(texture->GetFrame());
	animations[DEAD]->SetPart(11, 14);
	animations[DEAD]->SetEndEvent(bind(&FireSpirit::Dead, this));
}
