#pragma once
class Ninja : public Champion
{
public:
	Ninja();
	~Ninja();

	virtual void Update() override;

private:
	virtual void Skill() override;
	virtual void EndSkill() override;
	void CreateAnimations();

	Vector2 CheckFarthestChampion();
	void Teleport();
};