#pragma once
class Swordman : public Champion
{
public:
	Swordman();
	~Swordman();

	virtual void Update() override;

private:
	virtual void Skill() override;
	virtual void EndSkill() override;
	void CreateAnimations();
};