#pragma once
class Monk : public Champion
{
public:
	Monk();
	~Monk();

	virtual void Update() override;

private:
	virtual void Skill() override;
	virtual void EndSkill() override;

	void Heal();
	void CreateAnimations();

private:
	Rect* skillCollider_ally;
	Vector2 healChampion_pos;
};