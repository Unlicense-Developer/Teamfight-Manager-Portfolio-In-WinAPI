#pragma once
class CharaCard : public ImageRect
{
private:
	enum GamerState
	{
		PLAYER, COMPUTER
	};

	const float SET_SPEED = 500.0f;
	const float START_SET_TIME = 1.0f;
	const float BLOCK_SPEED = 0.12f;
	const string ATK = "���ݷ�";
	const string DEF = "����";
	const string HP = "ü��";
	const string RANGE = "��Ÿ�";
	const string ATS = "����";
	const string SKILL = "���";
	const string ULT = "�ñر�";

	const string INFO = "����";
	const string KILL = "K";
	const string DEATH = "D";
	const string ASSIST = "A";

public:
	CharaCard(int index, wstring file, UINT frameX = 1, UINT frameY = 1, COLORREF transColor = MAGENTA);
	~CharaCard();

	void Update();
	void Render(HDC hdc);

	void PrintCardText(HDC hdc);
	void PrintKDAText(HDC hdc);

	void SetCard();
	void SetKDACard();
	void SetPickChampInfo(Champion* champ);
	void SetKDAActive();

private:
	float time = 0;
	float block_speed = 0;

	GamerState gamerstat;
	Champion* cardchamp;
	ImageRect* minitexture;
	ImageRect* kdatexture;
	ImageRect* skillimage;
	ImageRect* ultimage;

	HFONT hfont_16;
	HFONT hfont_18;
	HFONT hfont_21;
	HFONT hfont_24;

	bool isSet = false;
	bool isSet_KDA = false;
	bool isArena = false;

	int index;
};