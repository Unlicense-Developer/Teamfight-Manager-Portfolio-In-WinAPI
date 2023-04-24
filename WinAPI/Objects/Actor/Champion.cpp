#include "Framework.h"

Champion::Champion(int key, wstring file, int frameX, int frameY, COLORREF transColor)
	:Character(file, frameX, frameY, transColor)
{
	Texture* Hpbar = Texture::Add(L"Textures/UI/champion_bar.bmp");
	Texture* Skillguage = Texture::Add(L"Textures/UI/skillguage.bmp");

	champData = DataManager::Get()->SearchClassData(key);
	curHp = champData.hp;

	hpBar = new ImageRect(Hpbar);
	skillGuage = new ImageRect(Skillguage);

	attackRange = new Circle(Vector2(), champData.range);
	skillRange = new Circle(Vector2(), champData.skillrange);
	size = { 35, 60 }; // 캐릭터 충돌 rect
}

Champion::~Champion()
{
	delete hpBar;
	delete hpGuage;
	delete hpGuage_bg;
	delete skillGuage;
}

void Champion::Update()
{
	speed = champData.movespeed * 20;
	attackRange->pos = pos;
	skillRange->pos = pos;

	attackCool += DELTA;

	if (isDead)
		RespawnTime += DELTA;

	Character::Update();
	SetBoundary();
	CheckHpSkillGuage();
	Respawn();
	Move();
	SetState();
	//ShowAttackedEffect();
	ActionState();
	SetAnimation();
	CheckMVPScore();
	CheckDead();
}

void Champion::Render(HDC hdc)
{
	HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
	SelectObject(hdc, brush);

	if (!isDead)
	{
		hpGuage_bg->Render(hdc);
		hpGuage->Render(hdc);
		skillGuage->Render(hdc);
		hpBar->Render(hdc);
	}
		
	Character::Render(hdc);
}

void Champion::SetState()
{
	if (state == State::ATTACKED) return;
	if (state == State::DEAD) return;

	if (attackRange->IsCollision(target))
	{
		if (skillOn)
		{
			state = State::SKILL;
			return;
		}
		else if (attackCool >= 1 / stof(champData.atkspeed))
		{
			state = State::ATTACK;
			return;
		}
		else if ((target->pos - pos).Length() < champData.range * 0.5f)
		{
			state = State::AVOID;
			return;
		}
		else
		{
			state = State::STAY;
		}
	}
	else if (skillRange->IsCollision(target) && skillOn)
	{
		state = State::SKILL;
		return;
	}
	else if (target)
	{
		state = State::TRACE;
	}
	else
	{
		state = State::STAY;
	}
}
void Champion::ActionState()
{
	switch (state)
	{
	case Champion::State::STAY:
		Stay();
		break;
	case Champion::State::TRACE:
		Trace();
		break;
	case Champion::State::ATTACK:
		Attack();
		break;
	case Champion::State::AVOID:
		Avoid();
		break;
	case Champion::State::SKILL:
		if (skillOn)
		{
			Skill();
		}
		break;
	case Champion::State::DEAD:
		Dead();
		break;
	}
}

void Champion::SetAnimation()
{
	if (curType == SKILL_R) return;
	if (curType == SKILL_L) return;
	if (curType == ATTACK_R) return;
	if (curType == ATTACK_L) return;
	if (curType == ATTACKED_R) return;
	if (curType == ATTACKED_L) return;
	if (curType == DEAD) return;

	if (velocity.x > 0.0f)
		SetAction(RUN_R);
	else if (velocity.x < 0.0f)
		SetAction(RUN_L);
	else if (AttackDirection) // true 오른쪽
		SetAction(IDLE_R);
	else if (!AttackDirection)
		SetAction(IDLE_L);
}

void Champion::Stay()
{
	velocity = {};

	if (AttackDirection) // true 오른쪽
		SetAction(IDLE_R);
	else if (!AttackDirection)
		SetAction(IDLE_L);

	isAttack = false;
}

void Champion::Trace()
{
	Vector2 direction = target->pos - pos;

	if(direction.Length() > 1)
		velocity = direction.GetNormalized();

	if (velocity.x > 0.0f)
		AttackDirection = true;
	else if (velocity.x < 0.0f)
		AttackDirection = false;
}
void Champion::Attack()
{
	if (curType == ATTACK_R) return;
	if (curType == ATTACK_L) return;
	if (curType == SKILL_R) return;
	if (curType == SKILL_L) return;
	if (curType == ATTACKED_R) return;
	if (curType == ATTACKED_L) return;
	if (curType == DEAD) return;

	Vector2 direction = target->pos - pos;

	if (direction.x > 0.0f)
		AttackDirection = true;
	else if (direction.x < 0.0f)
		AttackDirection = false;

	velocity = {};

	if (AttackDirection)
	{
		isAttack = true;
		SetAction(ATTACK_R);
	}
	else if (!AttackDirection)
	{
		isAttack = true;
		SetAction(ATTACK_L);
	}

	attackCollider->isActive = true;
	attackCollider->pos = GetChampionAttackOffset();
	EffectManager::Get()->Play(champData.effectname, attackCollider->pos);
	((Champion*)target)->Attacked();
}

void Champion::Move()
{
	if (isAttack) return;

	pos += velocity * speed * DELTA;
}

void Champion::EndAttack()
{
	if (target == nullptr)
	{
		isAttack = false;

		if (AttackDirection) // true 오른쪽
			SetAction(IDLE_R);
		else if (!AttackDirection)
			SetAction(IDLE_L);

		return;
	}
	Audio::Get()->Play(champData.soundname, 0.2f);

	if (((Champion*)target)->curHp < (champData.atk * 100 + 99 + champData.def) / (100 + champData.def) * 100 / (100 + ((Champion*)target)->champData.def))  // 킬 체크
	{
		champData.killCount++;
		((Champion*)target)->SetDeathCount();

		for (GameObject* ally : allychampions)
		{
			if (((Champion*)ally)->GetTarget() == target)
			{
				((Champion*)ally)->SetAssist(((Champion*)ally)->GetChampData().assistCount + 1);
			}
		}
	}

	((Champion*)target)->curHp -= (champData.atk * 100 + 99 + champData.def) / (100 + champData.def) * 100 / (100 + ((Champion*)target)->champData.def);
	((Champion*)target)->PrintDamageText((champData.atk * 100 + 99 + champData.def) / (100 + champData.def) * 100 / (100 + ((Champion*)target)->champData.def));
	champData.DealCount += (champData.atk * 100 + 99 + champData.def) / (100 + champData.def) * 100 / (100 + ((Champion*)target)->champData.def);
	((Champion*)target)->SetDamageCount((champData.atk * 100 + 99 + champData.def) / (100 + champData.def) * 100 / (100 + ((Champion*)target)->champData.def));
	attackCool = 0.0f;
	isAttack = false;

	if (AttackDirection) // true 오른쪽
		SetAction(IDLE_R);
	else if (!AttackDirection)
		SetAction(IDLE_L);
}

void Champion::ShowAttackedEffect() // 피격 알파
{
	if (curType == ATTACKED_L)
	{
		alphaTime += DELTA;

		if (isIncreaseAlpha)
		{
			alphaValue += ALPHA_SPEED * DELTA;
			if (alphaValue > 255.0f)
				isIncreaseAlpha = false;
		}
		else
		{
			alphaValue -= ALPHA_SPEED * DELTA;
			if (alphaValue < 0.0f)
				isIncreaseAlpha = true;
		}

		if (alphaTime >= ATTACKED_TIME)
		{
			alphaValue = 255.0f;
		}
	}
}

void Champion::Attacked()
{
	if (curType == ATTACK_L) return;
	if (curType == ATTACK_R) return;
	if (curType == SKILL_R) return;
	if (curType == SKILL_L) return;
	if (curType == ATTACKED_R) return;
	if (curType == ATTACKED_L) return;
	if (curType == DEAD) return;
	
	if (AttackDirection)
	{
		SetAction(ATTACKED_R);
	}
	else
	{
		SetAction(ATTACKED_L);
	}
}

void Champion::EndAttacked()
{
	if (AttackDirection) // true 오른쪽
		SetAction(IDLE_R);
	else if (!AttackDirection)
		SetAction(IDLE_L);
}

void Champion::Avoid()
{
	if (curType == SKILL_R) return;
	if (curType == SKILL_L) return;
	if (curType == ATTACK_R) return;
	if (curType == ATTACK_L) return;
	if (curType == ATTACKED_R) return;
	if (curType == ATTACKED_L) return;
	if (curType == DEAD) return;

	Vector2 direction = pos - target->pos;

	if (direction.Length() > 1)
		velocity = direction.GetNormalized();

	if (velocity.x > 0.0f)
		AttackDirection = false;
	else if (velocity.x < 0.0f)
		AttackDirection = true;
}

void Champion::CheckDead()
{
	if (state == State::DEAD) return;

	if (curHp <= 0.0f)
	{
		velocity = {};
		//champData.deathCount++;
		state = State::DEAD;
		SetAction(DEAD);
	}
}

void Champion::Dead()
{
	isDead = true;
	isActive = false;
}

void Champion::Respawn()
{
	if (RespawnTime >= 3.0f)
	{
		RespawnTime = 0.0f;
		curHp = champData.hp;
		skillguage = stof(champData.skillcool) * 0.5f;
		pos = RespawnLoction;
		skillOn = false;
		isDead = false;
		isAttack = false;
		SetTarget(nullptr);
		isActive = true;

		if (AttackDirection) // true 오른쪽
			SetAction(IDLE_R);
		else if (!AttackDirection)
			SetAction(IDLE_L);

		state = State::STAY;
	}
}

void Champion::SetBoundary()
{
	if (pos.x - size.x * 0.5f < MIN_ARENA_X) // 왼쪽 충돌
		pos.x = MIN_ARENA_X + size.x * 0.5f;
	if (pos.x + size.x * 0.5f > MAX_ARENA_X) // 오른쪽 충돌
		pos.x = MAX_ARENA_X - size.x * 0.5f;
	if (pos.y - size.y * 0.5f < MIN_ARENA_Y) // 위 충돌
		pos.y = MIN_ARENA_Y + size.y * 0.5f;
	if (pos.y + size.y * 0.5f > MAX_ARENA_Y) // 아래 충돌
		pos.y = MAX_ARENA_Y - size.y * 0.5f;
}

void Champion::SetAllyChampions(string team)
{
	if (team == "Player")
	{
		for (int i = 0; i < GAMER_MAX_CHAMP; i++)
		{
			if (champData.key == GamerManager::Get()->GetPlayer()->GetChampions()[i]->champData.key)
				continue;
			
			allychampions.push_back(GamerManager::Get()->GetPlayer()->GetChampions()[i]);
		}
	}
	else if (team == "Computer")
	{
		for (int i = 0; i < GAMER_MAX_CHAMP; i++)
		{
			if (champData.key == GamerManager::Get()->GetComputer()->GetChampions()[i]->champData.key)
				continue;

			allychampions.push_back(GamerManager::Get()->GetComputer()->GetChampions()[i]);
		}
	}
}

void Champion::SetHpBarColor(string gamer)
{
	Texture* Hpguage = Texture::Add(L"Textures/UI/player_hpguage.bmp");
	Texture* computerHpguage = Texture::Add(L"Textures/UI/computer_hpguage.bmp");
	Texture* hpguage_bg = Texture::Add(L"Textures/UI/player_hpguage_bg.bmp");
	Texture* computerhpguage_bg = Texture::Add(L"Textures/UI/computer_hpguage_bg.bmp");

	if (gamer == "Player")
	{
		hpGuage = new ImageRect(Hpguage);
		hpGuage_bg = new ImageRect(hpguage_bg);
	}
	else if (gamer == "Computer")
	{
		hpGuage = new ImageRect(computerHpguage);
		hpGuage_bg = new ImageRect(computerhpguage_bg);
	}
}

void Champion::PrintDamageText(int damage)
{
	GameTextManager::Get()->PrintDamageText({ pos.x + 15, pos.y - 30 }, damage);
}

void Champion::PrintHealText(int heal)
{
	GameTextManager::Get()->PrintHealText({ pos.x + 15, pos.y - 30 }, heal);
}

void Champion::CheckHpSkillGuage()
{
	hpBar->pos = pos + Vector2(-10, 30);

	hpGuage_bg->pos = hpBar->pos + Vector2(11, -4);

	hpGuage->size.x = ( 58.0f  / champData.hp) * curHp;
	hpGuage->pos.x = hpBar->pos.x - 18 + hpGuage->size.x * 0.5f;
	hpGuage->pos.y = hpBar->pos.y - 6;

	skillguage += DELTA;
	if (skillguage >= stof(champData.skillcool))
	{
		skillguage = stof(champData.skillcool);
		skillOn = true;
	}

	skillGuage->size.x = (58.0f / stof(champData.skillcool)) * skillguage;
	skillGuage->pos.x = hpBar->pos.x - 18 + skillGuage->size.x * 0.5f;
	skillGuage->pos.y = hpBar->pos.y - 1;
}

void Champion::RecordKDA(int damage)
{
	if (target == nullptr)
	{
		return;
	}

	if (((Champion*)target)->GetcurHp() < damage) // 킬, 어시 체크
	{
		champData.killCount++;
		((Champion*)target)->SetDeathCount();

		for (GameObject* ally : allychampions)
		{
			if (((Champion*)ally)->GetTarget() == target)
			{
				((Champion*)ally)->SetAssist(((Champion*)ally)->GetChampData().assistCount + 1);
			}
		}
	}

	((Champion*)target)->SetCurHp(((Champion*)target)->GetcurHp() - damage);
	((Champion*)target)->PrintDamageText(damage);

	((Champion*)target)->SetDamageCount(damage);
	champData.DealCount += damage;
}

void Champion::CheckMVPScore()
{
	if (champData.deathCount > 0 )
	{
		MVPScore = ((champData.killCount + champData.assistCount) / champData.deathCount) * 100 + (champData.DealCount + champData.DamageCount + champData.HealCount);
	}
	else
	{
		MVPScore = ((champData.killCount + champData.assistCount) * 100 + 200 + (champData.DealCount + champData.DamageCount + champData.HealCount));
	}
}

Vector2 Champion::GetChampionAttackOffset()
{
	if (champData.key == 6)
	{
		return target->pos + Vector2( 0, -20 );
	}
	else
	{
		return pos;
	}
}
