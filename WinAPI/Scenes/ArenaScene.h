#pragma once
class ArenaScene : public Scene
{
public:
	ArenaScene();
	~ArenaScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Start() override;
	virtual void End() override;

	void CreateEffect();
	void CreateSound();
	void CreateRespawnSlot();

	void CreateChampions();
	void SetAlly();
	void SetChampionsTarget();
	void PrintKillScore(HDC hdc);
	void PrintGameTime(HDC hdc);

	void CheckFinishGame();

	GameObject* GetClosestPlayerChampion(Vector2 pos);
	GameObject* GetClosestComputerChampion(Vector2 pos);

private:
	ImageRect* bg;
	Ending* ending;
	Header* header;
	Waterfall* waterfall1;
	Waterfall* waterfall2;

	HFONT hfont_28;
	HFONT hfont_50;

	vector<ImageRect*> player_respawn;
	vector<ImageRect*> computer_respawn;
	vector<Champion*> player_champions;
	vector<Champion*> computer_champions;

	float gameTime = 60.0f;
	bool isFinish = false;

	int playerscore;
	int computerscore;
};