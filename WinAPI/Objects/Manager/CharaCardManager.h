#pragma once
class CharaCard;

class CharaCardManager : public Singleton<CharaCardManager>
{
private:
	friend class Singleton;

	CharaCardManager();
	~CharaCardManager();


public:
	void Update();
	void Render(HDC hdc);

	void CreateCards();
	void SetCardTexture();
	void SetKDAActive();

	vector<CharaCard*> GetPlayerCard() { return playercards; }
	vector<CharaCard*> GetComputerCard() { return computercards; }
	

private:
	vector<CharaCard*> playercards;
	vector<CharaCard*> computercards;
};