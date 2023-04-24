#pragma once
class Pyromancer : public Champion
{
public:
	Pyromancer();
	~Pyromancer();

	virtual void Update() override;
	void Render(HDC hdc);

private:
	virtual void Skill() override;
	virtual void EndSkill() override;
	void CreateAnimations();
	
	GameObject* firespirit;
};