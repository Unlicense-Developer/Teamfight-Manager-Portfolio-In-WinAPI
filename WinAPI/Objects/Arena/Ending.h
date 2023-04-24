#pragma once
class Ending : public ImageRect
{
	const float SET_SPEED = 1000.0f;
	const float START_SET_TIME = 1.0f;
	const float BLOCK_SPEED = 0.12f;
	const string PLAYER = "T1";
	const string COMPUTER = "SGA 서울게임아카데미";
	const string VICTORY = "승리";
	const string DRAW = "무승부";
	const string MVP = "MVP";

public:
	Ending();
	~Ending();

	void Update();
	void Render(HDC hdc);

	void PrintEndingText(HDC hdc);
	Champion* CheckMVP();
	void SetEnding();
	void StartEnd(int playerscore, int comupterscore);

private:
	HFONT hfont_40;
	HFONT hfont_50;
	ImageRect* playerlogo;
	ImageRect* computerlogo;
	ImageRect* trophy;
	ImageRect* MVPtexture;

	bool isEnd = false;
	bool isSet = false;

	int playerscore;
	int computerscore;
	float time;
	float block_speed;
};