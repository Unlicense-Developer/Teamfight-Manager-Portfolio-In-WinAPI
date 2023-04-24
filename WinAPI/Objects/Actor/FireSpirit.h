#pragma once
class FireSpirit : public Character
{
private:
	enum ActionType
	{
		IDLE_R, IDLE_L, ATTACK_R, 
		ATTACK_L, DEAD
	};

	enum class State
	{
		STAY, ATTACK, DEAD
	};

	const float ATTACK_RANGE = 100.0f;
	const float SUMMON_TIME = 3.5f;
public:
	FireSpirit();
	~FireSpirit();

	void Update();
	void Render(HDC hdc);

	void Stay();
	void Attack();
	void EndAttack();
	void Dead();

	void Summon(Vector2 pos);
	void CheckSummonTime();
	void SetState();
	void ActionState();
	void SetAction(int type);
	void SetPyromancer(Pyromancer* pyromancer) { this->pyromancer = pyromancer; }
	void SetTarget();

	void CreateAnimations();

private:
	map<int, Animation*> animations;
	vector<Champion*> enemies;
	Pyromancer* pyromancer;
	Champion* target = nullptr;
	GameObject* attackRange;
	ImageRect* imageRect;
	Texture* texture;
	State state;
	HPEN red;

	bool AttackDirection;
	bool isAttack;

	int curType = 0;
	int atk = 15;
	float summoningTime = 0.0f;
};