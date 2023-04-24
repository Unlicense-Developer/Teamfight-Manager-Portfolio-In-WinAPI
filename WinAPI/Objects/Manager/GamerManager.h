#pragma once
class GamerManager : public Singleton<GamerManager>
{
private:
	friend class Singleton;

	GamerManager();
	~GamerManager();

public:
	
	Gamer* GetPlayer() { return player; }
	Gamer* GetComputer() { return computer; }

	void CreateGamer();
	

private:
	Player* player;
	Computer* computer;
};