#pragma once
class Archer : public Champion
{
public:
	Archer();
	~Archer();

	virtual void Update() override;

private:
	virtual void Skill() override;
	virtual void EndSkill() override;

	void CreateAnimations();
};