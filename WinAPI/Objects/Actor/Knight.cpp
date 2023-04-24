#include "Framework.h"

Knight::Knight()
	:Champion(2, L"Textures/Class/Knight/knight_animation.bmp", 5, 16)
{
	CreateAnimations();
	animations[curType]->Play();
	imageRect->size = { 128, 128 };
}

Knight::~Knight()
{

}

void Knight::Update()
{
	Champion::Update();
}

void Knight::Skill()
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
		Taunt();
		SetAction(SKILL_R);
	}
	else if (!AttackDirection)
	{
		isAttack = true;
		Taunt();
		SetAction(SKILL_L);
	}
}

void Knight::EndSkill()
{
	isAttack = false;
	skillOn = false;
	skillguage = 0.0f;

	if (AttackDirection)
	{
		SetAction(IDLE_R);
	}
	else
	{
		SetAction(IDLE_L);
	}
}

void Knight::CreateAnimations()
{
	animations[IDLE_R] = new Animation(texture->GetFrame(), 0.4f);
	animations[IDLE_R]->SetPart(0, 4, true, true);

	animations[IDLE_L] = new Animation(texture->GetFrame(), 0.4f);
	animations[IDLE_L]->SetPart(44, 48, true, true);

	animations[RUN_R] = new Animation(texture->GetFrame());
	animations[RUN_R]->SetPart(5, 12, true);

	animations[RUN_L] = new Animation(texture->GetFrame());
	animations[RUN_L]->SetPart(49, 56, true);

	animations[ATTACK_R] = new Animation(texture->GetFrame(), stof(champData.atkspeed));
	animations[ATTACK_R]->SetPart(13, 18);
	animations[ATTACK_R]->SetEndEvent(bind(&Knight::EndAttack, this));

	animations[ATTACK_L] = new Animation(texture->GetFrame(), stof(champData.atkspeed));
	animations[ATTACK_L]->SetPart(57, 62);
	animations[ATTACK_L]->SetEndEvent(bind(&Knight::EndAttack, this));

	animations[SKILL_R] = new Animation(texture->GetFrame());
	animations[SKILL_R]->SetPart(30, 36);
	animations[SKILL_R]->SetEndEvent(bind(&Knight::EndSkill, this));

	animations[SKILL_L] = new Animation(texture->GetFrame());
	animations[SKILL_L]->SetPart(64, 70);
	animations[SKILL_L]->SetEndEvent(bind(&Knight::EndSkill, this));

	animations[ATTACKED_R] = new Animation(texture->GetFrame());
	animations[ATTACKED_R]->SetPart(19, 19);
	animations[ATTACKED_R]->SetEndEvent(bind(&Knight::EndAttacked, this));

	animations[ATTACKED_L] = new Animation(texture->GetFrame());
	animations[ATTACKED_L]->SetPart(63, 63);
	animations[ATTACKED_L]->SetEndEvent(bind(&Knight::EndAttacked, this));

	animations[DEAD] = new Animation(texture->GetFrame());
	animations[DEAD]->SetPart(20, 29);
	animations[DEAD]->SetEndEvent(bind(&Knight::Dead, this));
}

void Knight::Taunt()
{
	if (isPlayer) // 플레이어 챔피언
	{
		int taunt = Random(0, 2); // 0이 도발, 1이 도발x
		for (int i = 0; i < GAMER_MAX_CHAMP; i++)
		{
			if (!GamerManager::Get()->GetComputer()->GetChampions()[i]->isActive)
				continue;

			if (taunt == 0)
			{
				GamerManager::Get()->GetComputer()->GetChampions()[i]->SetTarget(this);
				return;
			}
		}
	}
	else if (!isPlayer) // 컴퓨터 챔피언
	{
		int taunt = Random(0, 2); // 0이 도발, 1이 도발x
		for (int i = 0; i < GAMER_MAX_CHAMP; i++)
		{
			if (!GamerManager::Get()->GetPlayer()->GetChampions()[i]->isActive)
				continue;

			if (taunt == 0)
			{
				GamerManager::Get()->GetPlayer()->GetChampions()[i]->SetTarget(this);
				return;
			}
		}
	}
}
