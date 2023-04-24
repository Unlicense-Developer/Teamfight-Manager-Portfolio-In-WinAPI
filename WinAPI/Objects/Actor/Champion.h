#pragma once

class Champion : public Character
{
protected:
	enum ActionType
	{
		IDLE_R, IDLE_L, RUN_R, 
		RUN_L, ATTACK_R, ATTACK_L,
		SKILL_R, SKILL_L, SKILLMOVE_R,
		SKILLMOVE_L, ATTACKED_R, ATTACKED_L, 
		ULT, DEAD,
	};

	enum class State
	{
		STAY, TRACE,ATTACK,
		SKILL, ATTACKED, AVOID, DEAD
	};

	const float ALPHA_SPEED = 1000.0f;
	const float ATTACKED_TIME = 1.0f;

public:
	Champion(int key, wstring file, int frameX, int frameY, COLORREF transColor = MAGENTA);
	~Champion();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	Rect* GetAttackCollider() { return skillCollider; }

	void SetState();
	void ActionState();
	void SetAnimation();

	void Stay();
	void Trace();
	void Attack();
	void EndAttack();
	void ShowAttackedEffect();
	void Attacked();
	void EndAttacked();
	void Avoid();
	virtual void Skill() {};
	virtual void EndSkill() {};
	void CheckDead();
	void Dead();
	void Respawn();

	void PrintDamageText(int damage);
	void PrintHealText(int heal);
	void CheckHpSkillGuage();
	void RecordKDA(int damage);
	void CheckMVPScore();
	Vector2 GetChampionAttackOffset();

	void SetBoundary();
	void SetAllyChampions(string team);
	void SetHpBarColor(string gamer);
	void SetRespawnLocation(Vector2 respawn) { this->RespawnLoction = respawn; }
	void SetCurHp(int curHp) { this->curHp = curHp; }
	void SetIsPlayer(bool player) { this->isPlayer = player; }
	void SetAssist(int assist) { this->champData.assistCount = assist; }
	void SetDamageCount(int Damage) { this->champData.DamageCount += Damage; }
	void SetDeathCount() { this->champData.deathCount++; }

	ClassData GetChampData() { return champData; }
	bool GetIsDead() { return isDead; }
	bool GetIsPlayer() { return isPlayer; }
	int GetcurHp() { return curHp; }
	int GetKillCount() { return champData.killCount; }
	int GetDeathCount() { return champData.deathCount; }
	int GetMVPScore() { return MVPScore; }
	float GetRespawnTime() { return RespawnTime; }

protected:
	void Move();

protected:
	ClassData champData;
	State state;

	vector<GameObject*> allychampions;

	ImageRect* hpBar;
	ImageRect* hpGuage;
	ImageRect* hpGuage_bg;
	ImageRect* skillGuage;

	GameObject* skillRange;

	bool isAttack = false;
	bool skillOn = false;
	bool isDead = false;
	bool isPlayer;
	bool isIncreaseAlpha = false;

	Vector2 RespawnLoction;

	float alphaValue = 255;
	float alphaTime = 0.0f;
	float skillguage = 0.0f;
	float RespawnTime = 0.0f;
	float attackCool;
	float speed;
	int curHp;
	int MVPScore;
};