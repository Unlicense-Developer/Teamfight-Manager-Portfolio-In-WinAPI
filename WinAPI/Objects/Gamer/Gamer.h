#pragma once
class Champion;

class Gamer
{
public:
	Gamer();
	~Gamer();

	void AddPickChampion(int key);
	vector<Champion*> GetChampions() { return champions; }

private:
	vector<Champion*> champions;
};