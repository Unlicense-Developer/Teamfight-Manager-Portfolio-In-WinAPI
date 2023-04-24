#pragma once
class Knight : public Champion
{
public:
	Knight();
	~Knight();

	virtual void Update() override;

private:
	virtual void Skill() override;
	virtual void EndSkill() override;
	void CreateAnimations();

	void Taunt();
};