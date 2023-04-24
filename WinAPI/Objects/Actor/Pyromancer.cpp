#include "Framework.h"

Pyromancer::Pyromancer()
	:Champion(6, L"Textures/Class/Pyromancer/pyromancer_animation.bmp", 5, 16, RGB(255, 2, 255))
{
	CreateAnimations();
	animations[curType]->Play();
	imageRect->size = { 144, 144 };

	firespirit = new FireSpirit();
	((FireSpirit*)firespirit)->isActive = false;
	((FireSpirit*)firespirit)->SetPyromancer(this);
}

Pyromancer::~Pyromancer()
{
	delete firespirit;
}

void Pyromancer::Update()
{
	Champion::Update();
	((FireSpirit*)firespirit)->Update();
}

void Pyromancer::Render(HDC hdc)
{
	Champion::Render(hdc);
	firespirit->Render(hdc);
}

void Pyromancer::Skill()
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
	Vector2 summon_pos = target->pos + Vector2(Random(-50, 51), Random(-50, 51));

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

	((FireSpirit*)firespirit)->Summon(summon_pos);
}

void Pyromancer::EndSkill()
{
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

void Pyromancer::CreateAnimations()
{
	animations[IDLE_R] = new Animation(texture->GetFrame(), 0.4f);
	animations[IDLE_R]->SetPart(0, 4, true, true);

	animations[IDLE_L] = new Animation(texture->GetFrame(), 0.4f);
	animations[IDLE_L]->SetPart(43, 47, true, true);

	animations[RUN_R] = new Animation(texture->GetFrame());
	animations[RUN_R]->SetPart(5, 8, true);

	animations[RUN_L] = new Animation(texture->GetFrame());
	animations[RUN_L]->SetPart(48, 51, true);

	animations[ATTACK_R] = new Animation(texture->GetFrame());
	animations[ATTACK_R]->SetPart(9, 16);
	animations[ATTACK_R]->SetEndEvent(bind(&Pyromancer::EndAttack, this));

	animations[ATTACK_L] = new Animation(texture->GetFrame());
	animations[ATTACK_L]->SetPart(52, 59);
	animations[ATTACK_L]->SetEndEvent(bind(&Pyromancer::EndAttack, this));

	animations[SKILL_R] = new Animation(texture->GetFrame(), 0.5f);
	animations[SKILL_R]->SetPart(39, 42);
	animations[SKILL_R]->SetEndEvent(bind(&Pyromancer::EndSkill, this));

	animations[SKILL_L] = new Animation(texture->GetFrame(), 0.5f);
	animations[SKILL_L]->SetPart(74, 77);
	animations[SKILL_L]->SetEndEvent(bind(&Pyromancer::EndSkill, this));

	animations[ATTACKED_R] = new Animation(texture->GetFrame(), 0.5f);
	animations[ATTACKED_R]->SetPart(17, 17);
	animations[ATTACKED_R]->SetEndEvent(bind(&Pyromancer::EndAttacked, this));

	animations[ATTACKED_L] = new Animation(texture->GetFrame(), 0.5f);
	animations[ATTACKED_L]->SetPart(60, 60);
	animations[ATTACKED_L]->SetEndEvent(bind(&Pyromancer::EndAttacked, this));

	animations[DEAD] = new Animation(texture->GetFrame());
	animations[DEAD]->SetPart(18, 25);
	animations[DEAD]->SetEndEvent(bind(&Pyromancer::Dead, this));
}
