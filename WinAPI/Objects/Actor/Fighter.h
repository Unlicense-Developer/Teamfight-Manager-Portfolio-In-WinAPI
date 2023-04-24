#pragma once
class Fighter : public Champion
{
public:
	Fighter();
	~Fighter();

	virtual void Update() override;

private:
	virtual void Skill() override;
	virtual void EndSkill() override;
	void CreateAnimations();
};