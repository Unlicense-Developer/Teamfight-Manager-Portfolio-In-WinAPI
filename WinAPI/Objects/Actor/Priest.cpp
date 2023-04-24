#include "Framework.h"

Priest::Priest()
	:Champion(5, L"Textures/Class/Priest/priest_animation.bmp", 32, 3)
{
	CreateAnimations();
	animations[curType]->Play();
	imageRect->size = { 96, 96 };
}

Priest::~Priest()
{
}

void Priest::Update()
{
	Champion::Update();
}

void Priest::Skill()
{
	if (curType == SKILL_R) return;
	if (curType == SKILL_L) return;
	if (curType == ATTACK_R) return;
	if (curType == ATTACK_L) return;
	if (curType == ATTACKED_R) return;
	if (curType == ATTACKED_L) return;
	if (curType == DEAD) return;

	if (velocity.x > 0.0f)
		AttackDirection = true; // ¿À¸¥ÂÊ
	else if (velocity.x < 0.0f)
		AttackDirection = false; // ¿ÞÂÊ

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

	Audio::Get()->Play("Priest_Skill", 0.15f);
}

void Priest::EndSkill()
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

void Priest::CreateAnimations()
{
	animations[IDLE_R] = new Animation(texture->GetFrame(), 0.4f);
	animations[IDLE_R]->SetPart(0, 4, true, true);

	animations[IDLE_L] = new Animation(texture->GetFrame(), 0.4f);
	animations[IDLE_L]->SetPart(52, 56, true, true);

	animations[RUN_R] = new Animation(texture->GetFrame());
	animations[RUN_R]->SetPart(5, 12, true);

	animations[RUN_L] = new Animation(texture->GetFrame());
	animations[RUN_L]->SetPart(57, 64, true);

	animations[ATTACK_R] = new Animation(texture->GetFrame(), stof(champData.atkspeed));
	animations[ATTACK_R]->SetPart(44, 51);
	animations[ATTACK_R]->SetEndEvent(bind(&Priest::EndAttack, this));

	animations[ATTACK_L] = new Animation(texture->GetFrame(), stof(champData.atkspeed));
	animations[ATTACK_L]->SetPart(87, 94);
	animations[ATTACK_L]->SetEndEvent(bind(&Priest::EndAttack, this));

	animations[SKILL_R] = new Animation(texture->GetFrame());
	animations[SKILL_R]->SetPart(13, 22);
	animations[SKILL_R]->SetEndEvent(bind(&Priest::EndSkill, this));

	animations[SKILL_L] = new Animation(texture->GetFrame());
	animations[SKILL_L]->SetPart(65, 74);
	animations[SKILL_L]->SetEndEvent(bind(&Priest::EndSkill, this));

	animations[ATTACKED_R] = new Animation(texture->GetFrame());
	animations[ATTACKED_R]->SetPart(23, 23);
	animations[ATTACKED_R]->SetEndEvent(bind(&Priest::EndAttacked, this));

	animations[ATTACKED_L] = new Animation(texture->GetFrame());
	animations[ATTACKED_L]->SetPart(75, 75);
	animations[ATTACKED_L]->SetEndEvent(bind(&Priest::EndAttacked, this));

	animations[DEAD] = new Animation(texture->GetFrame());
	animations[DEAD]->SetPart(24, 32);
	animations[DEAD]->SetEndEvent(bind(&Priest::Dead, this));
}

void Priest::Heal()
{
	Champion* healchampion = nullptr;

	for (GameObject* ally : allychampions)
	{
		if (!ally->isActive) continue;
		if (((Champion*)ally)->GetcurHp() == ((Champion*)ally)->GetChampData().hp) continue;

		if (healchampion && healchampion->GetcurHp() < ((Champion*)ally)->GetcurHp())
		{
			break;
		}

		healchampion = (Champion*)ally;
	}

	if (healchampion == nullptr) // ¼¿ÇÁÈú
	{
		if (champData.hp < curHp + champData.atk)
		{
			PrintHealText(champData.hp - curHp);
			champData.HealCount += champData.hp - curHp;
			curHp = champData.hp;
			return;
		}
		else
		{
			PrintHealText(champData.atk);
			champData.HealCount += champData.atk;
			curHp += champData.atk;
			return;
		}
	}

	if (healchampion->GetChampData().hp < healchampion->GetcurHp() + champData.atk)
	{
		healchampion->PrintHealText(healchampion->GetChampData().hp - healchampion->GetcurHp());
		champData.HealCount += healchampion->GetChampData().hp - healchampion->GetcurHp();
		healchampion->SetCurHp(healchampion->GetChampData().hp);
	}
	else
	{
		healchampion->PrintHealText(champData.atk);
		champData.HealCount += champData.atk;
		healchampion->SetCurHp(healchampion->GetcurHp() + champData.atk);
	}
}
