#pragma once
class Pythoness : public Champion
{
public:
	Pythoness();
	~Pythoness();

	virtual void Update() override;

private:
	virtual void Skill() override;
	virtual void EndSkill() override;
	void CreateAnimations();
};