#include "Framework.h"

Pythoness::Pythoness()
	:Champion(7, L"Textures/Class/Pythoness/pythoness_animation.bmp", 4, 20)
{
	CreateAnimations();
	animations[curType]->Play();
	imageRect->size = { 96, 96 };
}

Pythoness::~Pythoness()
{
}

void Pythoness::Update()
{
	Champion::Update();
}

void Pythoness::Skill()
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
	}
	else if (!AttackDirection)
	{
		isAttack = true;
		SetAction(SKILL_L);
	}
}

void Pythoness::EndSkill()
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

void Pythoness::CreateAnimations()
{
	animations[IDLE_R] = new Animation(texture->GetFrame(), 0.4f);
	animations[IDLE_R]->SetPart(0, 4, true, true);

	animations[IDLE_L] = new Animation(texture->GetFrame(), 0.4f);
	animations[IDLE_L]->SetPart(44, 48, true, true);

	animations[RUN_R] = new Animation(texture->GetFrame());
	animations[RUN_R]->SetPart(5, 12, true);

	animations[RUN_L] = new Animation(texture->GetFrame());
	animations[RUN_L]->SetPart(49, 56, true);

	animations[ATTACK_R] = new Animation(texture->GetFrame());
	animations[ATTACK_R]->SetPart(13, 20);
	animations[ATTACK_R]->SetEndEvent(bind(&Pythoness::EndAttack, this));

	animations[ATTACK_L] = new Animation(texture->GetFrame());
	animations[ATTACK_L]->SetPart(57, 64);
	animations[ATTACK_L]->SetEndEvent(bind(&Pythoness::EndAttack, this));

	animations[SKILL_R] = new Animation(texture->GetFrame());
	animations[SKILL_R]->SetPart(32, 37);
	animations[SKILL_R]->SetEndEvent(bind(&Pythoness::EndSkill, this));

	animations[SKILL_L] = new Animation(texture->GetFrame());
	animations[SKILL_L]->SetPart(66, 71);
	animations[SKILL_L]->SetEndEvent(bind(&Pythoness::EndSkill, this));

	animations[ATTACKED_R] = new Animation(texture->GetFrame());
	animations[ATTACKED_R]->SetPart(21, 22);
	animations[ATTACKED_R]->SetEndEvent(bind(&Pythoness::EndAttacked, this));

	animations[ATTACKED_L] = new Animation(texture->GetFrame());
	animations[ATTACKED_L]->SetPart(65, 65);
	animations[ATTACKED_L]->SetEndEvent(bind(&Pythoness::EndAttacked, this));

	animations[DEAD] = new Animation(texture->GetFrame());
	animations[DEAD]->SetPart(22, 31);
	animations[DEAD]->SetEndEvent(bind(&Pythoness::Dead, this));
}
