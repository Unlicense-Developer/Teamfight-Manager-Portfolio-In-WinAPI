#pragma once
class PickbanList : public ImageRect
{
private:
	const float SET_SPEED = 1800.0f;
	const float START_SET_TIME = 2.0f;
	const float BLOCK_SPEED = 0.25f;
	const UINT MAX_CHAMP_POOL = 10;
	const float BANPICKSLOT_INTERVAL = 82.0f;

	const string ATK = "공격력";
	const string DEF = "방어력";
	const string ATS = "공격 속도";
	const string HP = "체력";
	const string RANGE = "사거리";
	const string MOVESPEED = "이동 속도";

	const string SKILL = "기술";
	const string ULT = "궁극기";
	const string BANS = "BANS";

public:
	PickbanList();
	~PickbanList();

	void Update();
	void Render(HDC hdc);
	void ShowClassInfo(HDC hdc);
	void PrintBansText(HDC hdc);

	void CreateClassDatas();
	void SetList();

	vector<ClassSlot*> GetClassSlots() { return classslots; }

private:

private:
	float time;
	float block_speed;

	vector<ClassSlot*> classslots;
	ClassSlot* previewSlot;

	bool isSet = false;

	HFONT hfont_12;
	HFONT hfont_18;
	HFONT hfont_21;
	HFONT hfont_24;
	HFONT hfont_55;

	ImageRect* previewTexture;
	ImageRect* skillTexture;
	ImageRect* ultTexture;
};