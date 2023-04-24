#include "Framework.h"

Swordman::Swordman()
	:Champion(9, L"Textures/Class/Swordman/swordman_animation.bmp", 16, 5, RGB(255, 2, 255))
{
	CreateAnimations();
	animations[curType]->Play();
	imageRect->size = { 192, 192 };
}

Swordman::~Swordman()
{
}

void Swordman::Update()
{
	Champion::Update();
}

void Swordman::Skill() // 데미지 계산식 넣지말것
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
		Audio::Get()->Play("Swordman_Skill", 0.4f);
	}
	else if (!AttackDirection)
	{
		isAttack = true;
		SetAction(SKILL_L);
		Audio::Get()->Play("Swordman_Skill", 0.4f);
	}
}

void Swordman::EndSkill()
{
	RecordKDA(30);

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

void Swordman::CreateAnimations()
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
	animations[ATTACK_R]->SetPart(13, 17);
	animations[ATTACK_R]->SetEndEvent(bind(&Swordman::EndAttack, this));

	animations[ATTACK_L] = new Animation(texture->GetFrame());
	animations[ATTACK_L]->SetPart(57, 61);
	animations[ATTACK_L]->SetEndEvent(bind(&Swordman::EndAttack, this));

	animations[SKILL_R] = new Animation(texture->GetFrame());
	animations[SKILL_R]->SetPart(18, 26);
	animations[SKILL_R]->SetEndEvent(bind(&Swordman::EndSkill, this));

	animations[SKILL_L] = new Animation(texture->GetFrame());
	animations[SKILL_L]->SetPart(62, 70);
	animations[SKILL_L]->SetEndEvent(bind(&Swordman::EndSkill, this));

	animations[ATTACKED_R] = new Animation(texture->GetFrame());
	animations[ATTACKED_R]->SetPart(35, 35);
	animations[ATTACKED_R]->SetEndEvent(bind(&Swordman::EndAttacked, this));

	animations[ATTACKED_L] = new Animation(texture->GetFrame());
	animations[ATTACKED_L]->SetPart(71, 71);
	animations[ATTACKED_L]->SetEndEvent(bind(&Swordman::EndAttacked, this));

	animations[DEAD] = new Animation(texture->GetFrame());
	animations[DEAD]->SetPart(27, 34);
	animations[DEAD]->SetEndEvent(bind(&Swordman::Dead, this));
}
