#pragma once
class Character : public Rect
{
public:
	Character(wstring file, int frameX, int frameY, COLORREF transColor = MAGENTA);
	~Character();

	virtual void Update();
	virtual void Render(HDC hdc, int alpha = 255);

	GameObject* GetTarget() { return target; }
	void SetTarget(GameObject* target) { this->target = target; }
	void ResetTarget();

protected:
	void SetAction(int type);

protected:
	Texture* texture;

	GameObject* target = nullptr;
	Vector2 velocity;

	GameObject* attackRange;
	Rect* attackCollider;
	Rect* skillCollider;

	ImageRect* imageRect;
	Vector2 imageOffset;

	map<int, Animation*> animations;

	int curType = 0;
	string team;

	bool AttackDirection;
	bool isAttack = false;
};