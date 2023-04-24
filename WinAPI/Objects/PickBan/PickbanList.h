#pragma once
class PickbanList : public ImageRect
{
private:
	const float SET_SPEED = 1800.0f;
	const float START_SET_TIME = 2.0f;
	const float BLOCK_SPEED = 0.25f;
	const UINT MAX_CHAMP_POOL = 10;
	const float BANPICKSLOT_INTERVAL = 82.0f;

	const string ATK = "���ݷ�";
	const string DEF = "����";
	const string ATS = "���� �ӵ�";
	const string HP = "ü��";
	const string RANGE = "��Ÿ�";
	const string MOVESPEED = "�̵� �ӵ�";

	const string SKILL = "���";
	const string ULT = "�ñر�";
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