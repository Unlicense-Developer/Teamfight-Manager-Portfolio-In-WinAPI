#include "Framework.h"

Ninja::Ninja()
	:Champion(4, L"Textures/Class/Ninja/ninja_animation.bmp", 4, 23, RGB(255, 2, 255))
{
	CreateAnimations();
	animations[curType]->Play();
	imageRect->size = { 96, 96 };
}

Ninja::~Ninja()
{
}

void Ninja::Update()
{
	Champion::Update();
}

void Ninja::Skill()
{
	if (curType == SKILL_R) return;
	if (curType == SKILL_L) return;
	if (curType == ATTACK_R) return;
	if (curType == ATTACK_L) return;
	if (curType == ATTACKED_R) return;
	if (curType == ATTACKED_L) return;
	if (curType == DEAD) return;

	if (velocity.x > 0.0f)
		AttackDirection = true; // 오른쪽
	else if (velocity.x < 0.0f)	
		AttackDirection = false; // 왼쪽

	velocity = {};

	if (AttackDirection)
	{
		isAttack = true;
		SetAction(SKILL_R);
		skillCollider->isActive = true;
		skillCollider->pos = { pos.x, pos.y - 7};
		EffectManager::Get()->Play("Ninja_Skill", skillCollider->pos);
	}
	else if (!AttackDirection)
	{
		isAttack = true;
		SetAction(SKILL_L);
		skillCollider->isActive = true;
		skillCollider->pos = { pos.x, pos.y - 7};
		EffectManager::Get()->Play("Ninja_Skill", skillCollider->pos);
	}
}

void Ninja::EndSkill()
{
	isAttack = false;
	/*skillOn = false;
	skillguage = 0.0f;*/

	if (AttackDirection)
	{
		SetAction(IDLE_R);
	}
	else
	{
		SetAction(IDLE_L);
	}
}

void Ninja::CreateAnimations()
{
	animations[IDLE_R] = new Animation(texture->GetFrame(), 0.4f);
	animations[IDLE_R]->SetPart(0, 4, true, true);

	animations[IDLE_L] = new Animation(texture->GetFrame(), 0.4f);
	animations[IDLE_L]->SetPart(50, 54, true, true);

	animations[RUN_R] = new Animation(texture->GetFrame());
	animations[RUN_R]->SetPart(5, 12, true);

	animations[RUN_L] = new Animation(texture->GetFrame());
	animations[RUN_L]->SetPart(55, 62, true);

	animations[ATTACK_R] = new Animation(texture->GetFrame());
	animations[ATTACK_R]->SetPart(13, 17);
	animations[ATTACK_R]->SetEndEvent(bind(&Ninja::EndAttack, this));

	animations[ATTACK_L] = new Animation(texture->GetFrame());
	animations[ATTACK_L]->SetPart(63, 67);
	animations[ATTACK_L]->SetEndEvent(bind(&Ninja::EndAttack, this));

	animations[SKILL_R] = new Animation(texture->GetFrame());
	animations[SKILL_R]->SetPart(28, 35);
	animations[SKILL_R]->SetEndEvent(bind(&Ninja::Teleport, this));

	animations[SKILL_L] = new Animation(texture->GetFrame());
	animations[SKILL_L]->SetPart(68, 75);
	animations[SKILL_L]->SetEndEvent(bind(&Ninja::Teleport, this));

	animations[SKILLMOVE_R] = new Animation(texture->GetFrame()); // 순간이동
	animations[SKILLMOVE_R]->SetPart(34, 40);
	animations[SKILLMOVE_R]->SetEndEvent(bind(&Ninja::EndSkill, this));

	animations[SKILLMOVE_L] = new Animation(texture->GetFrame()); // 순간이동
	animations[SKILLMOVE_L]->SetPart(74, 80);
	animations[SKILLMOVE_L]->SetEndEvent(bind(&Ninja::EndSkill, this));

	animations[ATTACKED_R] = new Animation(texture->GetFrame());
	animations[ATTACKED_R]->SetPart(18, 19);
	animations[ATTACKED_R]->SetEndEvent(bind(&Ninja::EndAttacked, this));

	animations[ATTACKED_L] = new Animation(texture->GetFrame());
	animations[ATTACKED_L]->SetPart(90, 90);
	animations[ATTACKED_L]->SetEndEvent(bind(&Ninja::EndAttacked, this));

	animations[DEAD] = new Animation(texture->GetFrame());
	animations[DEAD]->SetPart(19, 27);
	animations[DEAD]->SetEndEvent(bind(&Ninja::Dead, this));
}

Vector2 Ninja::CheckFarthestChampion()
{
	Vector2 teleport_pos;
	float length = 0;

	if (isPlayer)
	{
		for (int i = 0; i < GAMER_MAX_CHAMP; i++)
		{
			if (!GamerManager::Get()->GetComputer()->GetChampions()[i]->isActive)
				continue;

			if (length < (GamerManager::Get()->GetComputer()->GetChampions()[i]->pos - pos).Length())
			{
				length = (GamerManager::Get()->GetComputer()->GetChampions()[i]->pos - pos).Length();
				teleport_pos = GamerManager::Get()->GetComputer()->GetChampions()[i]->pos;
				target = GamerManager::Get()->GetComputer()->GetChampions()[i];
			}
		}
	}
	else
	{
		for (int i = 0; i < GAMER_MAX_CHAMP; i++)
		{
			if (!GamerManager::Get()->GetPlayer()->GetChampions()[i]->isActive)
				continue;

			if (length < (GamerManager::Get()->GetPlayer()->GetChampions()[i]->pos - pos).Length())
			{
				length = (GamerManager::Get()->GetPlayer()->GetChampions()[i]->pos - pos).Length();
				teleport_pos = GamerManager::Get()->GetPlayer()->GetChampions()[i]->pos;
				target = GamerManager::Get()->GetPlayer()->GetChampions()[i];
			}
		}
	}

	return teleport_pos;
}

void Ninja::Teleport()
{
	skillCollider->isActive = false;
	skillOn = false;
	skillguage = 0.0f;

	pos = CheckFarthestChampion();

	if (AttackDirection)
	{
		SetAction(SKILLMOVE_R);
	}
	else
	{
		SetAction(SKILLMOVE_L);
	}
}
