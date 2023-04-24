#include "Framework.h"

Monk::Monk()
	:Champion(3, L"Textures/Class/Monk/monk_animation.bmp", 32, 3, RGB(255, 2, 255))
{
	CreateAnimations();
	animations[curType]->Play();
	imageRect->size = { 96, 96 };

	skillCollider_ally = new Rect();
	skillCollider_ally->isActive = false;
}

Monk::~Monk()
{
	delete skillCollider_ally;
}

void Monk::Update()
{
	Champion::Update();
}


void Monk::Skill()
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
		Heal();
		SetAction(SKILL_R);
	}
	else if (!AttackDirection)
	{
		isAttack = true;
		Heal();
		SetAction(SKILL_L);
	}

	skillCollider->isActive = true;
	skillCollider->pos = pos + Vector2(0, -14);
	EffectManager::Get()->Play("Monk_Skill",skillCollider->pos);

	if (!healChampion_pos.x == 0 && !healChampion_pos.y == 0)
	{
		skillCollider_ally->isActive = true;
		skillCollider_ally->pos = healChampion_pos + Vector2(0, -14);
		EffectManager::Get()->Play("Monk_Skill", skillCollider_ally->pos);
	}

	Audio::Get()->Play("Monk_Skill", 0.15f);
}

void Monk::EndSkill()
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

void Monk::Heal()
{
	Champion* healchampion = nullptr;

	for (GameObject* ally : allychampions) // 힐해줄 아군 캐릭터 선정
	{
		if (!ally->isActive) continue;
		if (((Champion*)ally)->GetcurHp() == ((Champion*)ally)->GetChampData().hp) continue;

		if (healchampion && healchampion->GetcurHp() < ((Champion*)ally)->GetcurHp())
		{
			break;
		}

		healchampion = (Champion*)ally;
	}

	int heal = Random(10, 16);

	//셀프힐
	if (champData.hp < curHp + heal)
	{
		PrintHealText(champData.hp - curHp);
		champData.HealCount += champData.hp - curHp;
		curHp = champData.hp;
	}
	else
	{
		PrintHealText(heal);
		champData.HealCount += heal;
		curHp += heal;
	}

	if (healchampion == nullptr)
	{
		healChampion_pos = { 0, 0 };
		return;
	}

	if (healchampion->GetChampData().hp < healchampion->GetcurHp() + heal)
	{
		healchampion->PrintHealText(healchampion->GetChampData().hp - healchampion->GetcurHp());
		champData.HealCount += healchampion->GetChampData().hp - healchampion->GetcurHp();
		healchampion->SetCurHp(healchampion->GetChampData().hp);
	}
	else
	{
		healchampion->PrintHealText(heal);
		champData.HealCount += heal;
		healchampion->SetCurHp(healchampion->GetcurHp() + heal);
	}

	healChampion_pos = healchampion->pos;
}

void Monk::CreateAnimations()
{
	animations[IDLE_R] = new Animation(texture->GetFrame(), 0.4f);
	animations[IDLE_R]->SetPart(0, 4, true, true);

	animations[IDLE_L] = new Animation(texture->GetFrame(), 0.4f);
	animations[IDLE_L]->SetPart(55, 59, true, true);

	animations[RUN_R] = new Animation(texture->GetFrame());
	animations[RUN_R]->SetPart(5, 12, true);

	animations[RUN_L] = new Animation(texture->GetFrame());
	animations[RUN_L]->SetPart(60, 67, true);

	animations[ATTACK_R] = new Animation(texture->GetFrame(), stof(champData.atkspeed));
	animations[ATTACK_R]->SetPart(13, 18);
	animations[ATTACK_R]->SetEndEvent(bind(&Monk::EndAttack, this));

	animations[ATTACK_L] = new Animation(texture->GetFrame(), stof(champData.atkspeed));
	animations[ATTACK_L]->SetPart(68, 73);
	animations[ATTACK_L]->SetEndEvent(bind(&Monk::EndAttack, this));

	animations[SKILL_R] = new Animation(texture->GetFrame());
	animations[SKILL_R]->SetPart(34, 43);
	animations[SKILL_R]->SetEndEvent(bind(&Monk::EndSkill, this));

	animations[SKILL_L] = new Animation(texture->GetFrame());
	animations[SKILL_L]->SetPart(74, 83);
	animations[SKILL_L]->SetEndEvent(bind(&Monk::EndSkill, this));

	animations[ATTACKED_R] = new Animation(texture->GetFrame());
	animations[ATTACKED_R]->SetPart(19, 20);
	animations[ATTACKED_R]->SetEndEvent(bind(&Monk::EndAttacked, this));

	animations[ATTACKED_L] = new Animation(texture->GetFrame());
	animations[ATTACKED_L]->SetPart(95, 95);
	animations[ATTACKED_L]->SetEndEvent(bind(&Monk::EndAttacked, this));

	animations[DEAD] = new Animation(texture->GetFrame());
	animations[DEAD]->SetPart(20, 33);
	animations[DEAD]->SetEndEvent(bind(&Monk::Dead, this));
}
