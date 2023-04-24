#pragma once
class ClassSlot : public Button
{
public:
	ClassSlot(ClassData data);
	~ClassSlot();

	void Update();
	void Render(HDC hdc);

	void ShowClassInfo(HDC hdc);
	void PrintPickOrder(HDC hdc);

	ClassData GetData() { return data; }

	void AddPlayer();
	void AddComputer();

	bool GetBaned() { return isBaned; }
	bool GetPicked() { return isPicked; }
	bool GetAdded() { return isAdded; }
	int GetPickOrder() { return pickOrder; }

	void SetAdded(bool isAdded) { this->isAdded = isAdded; }
	void SetpickOrder(int order) { this->pickOrder = order; }
	
	State Getstate() { return state; }
	void CheckBanEnd();
	void CheckPickEnd();

private:
	ClassData data;
	HFONT hfont_12;
	HFONT hfont_18;
	HFONT hfont_21;
	HFONT hfont_24;

	bool isBaned = false;
	bool isPicked = false;
	bool isAdded = false;

	int pickOrder = 0;

	ImageRect* previewTexture;
	ImageRect* skillTexture;
	ImageRect* ultTexture;
};