#pragma once
class StartScene : public Scene
{
public:
	StartScene();
	~StartScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Start() override;
	virtual void End() override;

	void StartPickBanScene();

private:
	HFONT hfont;

	ImageRect* startmenuBg;
	ImageRect* stadium_sky;
	ImageRect* stadium;
	ImageRect* logo;

	Button* newgame;
};