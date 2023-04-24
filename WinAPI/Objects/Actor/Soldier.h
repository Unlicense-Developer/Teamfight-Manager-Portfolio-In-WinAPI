#pragma once
class Soldier : public Champion
{
public:
	Soldier();
	~Soldier();

	virtual void Update() override;

private:
	virtual void Skill() override;
	virtual void EndSkill() override;
	void CreateAnimations();
};