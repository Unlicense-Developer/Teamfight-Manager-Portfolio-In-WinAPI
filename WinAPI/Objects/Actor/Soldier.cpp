#include "Framework.h"

Soldier::Soldier()
	:Champion(8, L"Textures/Class/Soldier/soldier_animation.bmp", 4, 22, RGB(255, 2, 255))
{
	CreateAnimations();
	animations[curType]->Play();
	imageRect->size = { 96, 96 };
}

Soldier::~Soldier()
{
}

void Soldier::Update()
{
	Champion::Update();
}

void Soldier::Skill()
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
		skillCollider->pos = pos + Vector2(44, -4);
		EffectManager::Get()->Play("Soldier_Skill_R", skillCollider->pos);
	}
	else if (!AttackDirection)
	{
		isAttack = true;
		SetAction(SKILL_L);
		skillCollider->isActive = true;
		skillCollider->pos = pos + Vector2(-44, -4);
		EffectManager::Get()->Play("Soldier_Skill_L", skillCollider->pos);
	}

	Audio::Get()->Play("Soldier_Skill", 0.5f);
	/*int damage = Random(10, 20);

	RecordKDA(damage);*/
}

void Soldier::EndSkill()
{
	int damage = Random(15, 25);

	RecordKDA(damage);

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

void Soldier::CreateAnimations()
{
	animations[IDLE_R] = new Animation(texture->GetFrame(), 0.4f);
	animations[IDLE_R]->SetPart(0, 4, true, true);

	animations[IDLE_L] = new Animation(texture->GetFrame(), 0.4f);
	animations[IDLE_L]->SetPart(48, 52, true, true);

	animations[RUN_R] = new Animation(texture->GetFrame());
	animations[RUN_R]->SetPart(5, 12, true);

	animations[RUN_L] = new Animation(texture->GetFrame());
	animations[RUN_L]->SetPart(53, 60, true);

	animations[ATTACK_R] = new Animation(texture->GetFrame());
	animations[ATTACK_R]->SetPart(13, 18);
	animations[ATTACK_R]->SetEndEvent(bind(&Soldier::EndAttack, this));

	animations[ATTACK_L] = new Animation(texture->GetFrame());
	animations[ATTACK_L]->SetPart(61, 66);
	animations[ATTACK_L]->SetEndEvent(bind(&Soldier::EndAttack, this));

	animations[SKILL_R] = new Animation(texture->GetFrame());
	animations[SKILL_R]->SetPart(19, 28);
	animations[SKILL_R]->SetEndEvent(bind(&Soldier::EndSkill, this));

	animations[SKILL_L] = new Animation(texture->GetFrame());
	animations[SKILL_L]->SetPart(67, 76);
	animations[SKILL_L]->SetEndEvent(bind(&Soldier::EndSkill, this));

	animations[ATTACKED_R] = new Animation(texture->GetFrame());
	animations[ATTACKED_R]->SetPart(29, 29);
	animations[ATTACKED_R]->SetEndEvent(bind(&Soldier::EndAttacked, this));

	animations[ATTACKED_L] = new Animation(texture->GetFrame());
	animations[ATTACKED_L]->SetPart(77, 77);
	animations[ATTACKED_L]->SetEndEvent(bind(&Soldier::EndAttacked, this));

	animations[DEAD] = new Animation(texture->GetFrame());
	animations[DEAD]->SetPart(30, 39);
	animations[DEAD]->SetEndEvent(bind(&Soldier::Dead, this));
}
