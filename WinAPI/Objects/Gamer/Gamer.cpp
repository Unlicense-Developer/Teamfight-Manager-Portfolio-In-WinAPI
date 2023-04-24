#include "Framework.h"

Gamer::Gamer()
{
}

Gamer::~Gamer()
{
}

void Gamer::AddPickChampion(int key)
{
	champions.push_back(DataManager::Get()->GetChampion(key));

}
