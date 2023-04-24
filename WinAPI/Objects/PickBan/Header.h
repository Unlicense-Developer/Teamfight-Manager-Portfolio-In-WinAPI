#pragma once
class Header : public ImageRect
{
private:
	const float SET_SPEED = 450.0f;
	const float START_SET_TIME = 1.0f;
	const float BLOCK_SPEED = 0.12f;
	const string PLAYER = "T1";
	const string COMPUTER = "SGA 서울게임아카데미";

public:
	Header();
	~Header();

	void Update();
	void Render(HDC hdc);

	void PrintGamerName(HDC hdc);
	void SetArenaHeader();
	void SetHeader();

private:
	ImageRect* playerlogo;
	ImageRect* computerlogo;

	HFONT hfont_50;

	float time;
	float block_speed;

	bool isSet = false;
};