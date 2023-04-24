#pragma once
class Priest : public Champion
{
public:
	Priest();
	~Priest();

	virtual void Update() override;

private:
	virtual void Skill() override;
	virtual void EndSkill() override;
	void CreateAnimations();
	
	void Heal();
};