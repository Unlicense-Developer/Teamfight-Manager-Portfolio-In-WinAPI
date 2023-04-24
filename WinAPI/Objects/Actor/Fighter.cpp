#include "Framework.h"

Fighter::Fighter()
	:Champion(1, L"Textures/Class/Fighter/fighter_animation.bmp", 32, 3)
{
	CreateAnimations();
	animations[curType]->Play();
	imageRect->size = { 96, 96 };

}

Fighter::~Fighter()
{
}

void Fighter::Update()
{
	Champion::Update();
}

void Fighter::Skill()
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
		skillCollider->pos = pos + Vector2(42, -13);
		EffectManager::Get()->Play("Fighter_Skill_R", skillCollider->pos);
	}
	else if (!AttackDirection)
	{
		isAttack = true;
		SetAction(SKILL_L);
		skillCollider->isActive = true;
		skillCollider->pos = pos + Vector2(-42, -17);
		EffectManager::Get()->Play("Fighter_Skill_L", skillCollider->pos);
	}
}

void Fighter::EndSkill()
{
	int damage = Random(25, 36);

	RecordKDA(damage);

	skillCollider->isActive = false;
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

void Fighter::CreateAnimations()
{
	animations[IDLE_R] = new Animation(texture->GetFrame(), 0.4f);
	animations[IDLE_R]->SetPart(0, 4, true, true);

	animations[IDLE_L] = new Animation(texture->GetFrame(), 0.4f);
	animations[IDLE_L]->SetPart(54, 58, true, true);

	animations[RUN_R] = new Animation(texture->GetFrame());
	animations[RUN_R]->SetPart(5, 12, true);

	animations[RUN_L] = new Animation(texture->GetFrame());
	animations[RUN_L]->SetPart(59, 66, true);

	animations[ATTACK_R] = new Animation(texture->GetFrame());
	animations[ATTACK_R]->SetPart(13, 20);
	animations[ATTACK_R]->SetEndEvent(bind(&Fighter::EndAttack, this));

	animations[ATTACK_L] = new Animation(texture->GetFrame());
	animations[ATTACK_L]->SetPart(67, 74);
	animations[ATTACK_L]->SetEndEvent(bind(&Fighter::EndAttack, this));

	animations[SKILL_R] = new Animation(texture->GetFrame());
	animations[SKILL_R]->SetPart(86, 93);
	animations[SKILL_R]->SetEndEvent(bind(&Fighter::EndSkill, this));

	animations[SKILL_L] = new Animation(texture->GetFrame());
	animations[SKILL_L]->SetPart(46, 53);
	animations[SKILL_L]->SetEndEvent(bind(&Fighter::EndSkill, this));

	animations[ATTACKED_R] = new Animation(texture->GetFrame());
	animations[ATTACKED_R]->SetPart(21, 22);
	animations[ATTACKED_R]->SetEndEvent(bind(&Fighter::EndAttacked, this));

	animations[ATTACKED_L] = new Animation(texture->GetFrame());
	animations[ATTACKED_L]->SetPart(94, 94);
	animations[ATTACKED_L]->SetEndEvent(bind(&Fighter::EndAttacked, this));

	animations[DEAD] = new Animation(texture->GetFrame());
	animations[DEAD]->SetPart(21, 34);
	animations[DEAD]->SetEndEvent(bind(&Fighter::Dead, this));
}
