#pragma once
class PickBanScene : public Scene
{
private:
	const int MAX_CHMAPION = 3;
public:
	PickBanScene();
	~PickBanScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Start() override;
	virtual void End() override;

	void StartArena();

private:
	Header* header;
	PickBanTurn* pickbanturn;
	PickbanList* pickbanlist;
	Button* arenabutton;

	ImageRect* bg;

	bool isChangeScene = false;
};