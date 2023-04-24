#include "Framework.h"

Archer::Archer()
	:Champion(0, L"Textures/Class/Archer/archer_animation.bmp", 4, 21)
{
	CreateAnimations();
	animations[curType]->Play();
	imageRect->size = { 96, 96 };
	//size = { 35, 55 };
}

Archer::~Archer()
{
}

void Archer::Update()
{
	Champion::Update();
}


void Archer::Skill()
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

void Archer::EndSkill()
{
	ProjectileManager::Get()->ShootProjectile("Arrow", pos, target->pos, AttackDirection);
	
	int damage = Random(25, 36);
	
	RecordKDA(damage);

	isAttack = false;
	skillOn = false;
	skillguage = 0.0f;

	if (AttackDirection)
	{
		SetAction(IDLE_R);
	}
	else if (!AttackDirection)
	{
		SetAction(IDLE_L);
	}
}

void Archer::CreateAnimations()
{
	animations[IDLE_R] = new Animation(texture->GetFrame(), 0.4f);
	animations[IDLE_R]->SetPart(0, 4, true, true);

	animations[IDLE_L] = new Animation(texture->GetFrame(), 0.4f);
	animations[IDLE_L]->SetPart(47, 51, true, true);

	animations[RUN_R] = new Animation(texture->GetFrame());
	animations[RUN_R]->SetPart(5, 12, true);

	animations[RUN_L] = new Animation(texture->GetFrame());
	animations[RUN_L]->SetPart(52, 59, true);

	animations[ATTACK_R] = new Animation(texture->GetFrame());
	animations[ATTACK_R]->SetPart(13, 19);
	animations[ATTACK_R]->SetEndEvent(bind(&Archer::EndAttack, this));

	animations[ATTACK_L] = new Animation(texture->GetFrame());
	animations[ATTACK_L]->SetPart(60, 66);
	animations[ATTACK_L]->SetEndEvent(bind(&Archer::EndAttack, this));

	animations[SKILL_R] = new Animation(texture->GetFrame());
	animations[SKILL_R]->SetPart(30, 46);
	animations[SKILL_R]->SetEndEvent(bind(&Archer::EndSkill, this));

	animations[SKILL_L] = new Animation(texture->GetFrame());
	animations[SKILL_L]->SetPart(67, 83);
	animations[SKILL_L]->SetEndEvent(bind(&Archer::EndSkill, this));

	animations[ATTACKED_R] = new Animation(texture->GetFrame());
	animations[ATTACKED_R]->SetPart(20, 21);
	animations[ATTACKED_R]->SetEndEvent(bind(&Archer::EndAttacked, this));

	animations[ATTACKED_L] = new Animation(texture->GetFrame());
	animations[ATTACKED_L]->SetPart(20, 21);
	animations[ATTACKED_L]->SetEndEvent(bind(&Archer::EndAttacked, this));

	animations[DEAD] = new Animation(texture->GetFrame());
	animations[DEAD]->SetPart(21, 29);
	animations[DEAD]->SetEndEvent(bind(&Archer::Dead, this));
}
