#pragma once
class PickBanScene;

class PickBanTurn : public ImageRect
{
private:
	const float SET_SPEED = 1800.0f;
	const float START_SET_TIME = 2.0f;
	const float BLOCK_SPEED = 0.25f;
	const float BLOCK_HEIGHT = 98.0f;
	const float BANSLOT_WIDTH = 72.0f;
	const float BANSLOT_HEIGHT = 98.0f;

	const string PLAYER_BAN_STR = "������ è�Ǿ��� �����ϼ���";
	const string COMPUTER_BAN_STR = "��ǻ�Ͱ� ������ è�Ǿ��� �������Դϴ�";
	const string PLAYER_PICK_STR = "����� è�Ǿ��� �����ϼ���";
	const string COMPUTER_PICK_STR = "��ǻ�Ͱ� ����� è�Ǿ��� �������Դϴ�";
	const string BAN_PROGRESS_STR = "���� �ܰ�";
	const string PICK_PROGRESS_STR = "���� �ܰ�";
	const string PICK_END_STR = "è�Ǿ� ������ �������ϴ�";
	const int MAX_BANPICK_PROGRESS = 8;

public:
	PickBanTurn();
	~PickBanTurn();

	void Update();
	void Render(HDC hdc);

	void PrintTurnText(HDC hdc);
	void PrintArenaButton(HDC hdc);
	void PrintBanSlot(HDC hdc);


	void SetClassSlot(vector<ClassSlot*> classslots) { this->classslots = classslots; }
	void SetHeight();
	void CheckTurn();
	void ComputerBan();
	void Pick();
	void ChangeArena();
	void ActiveBanSlot(int key);

	void SetPhaseSlot();

private:
	float time;
	float block_speed;

	vector<ClassSlot*> classslots;

	Button* arenabutton;

	ImageRect* ban1;
	ImageRect* ban2;
	int ban1key;
	int ban2key;

	int turn;
	bool isSet = false;

	bool isPlayerTurn = true;
	bool isComputerTurn = false;

	bool BanPhase = true;
	bool PickPhase = false;

	int banpickProgress = 1;
	string banpickProgress_Text;

	HFONT hfont_18;
	HFONT hfont_25;
	HFONT hfont_40;
};