#include "Framework.h"

GamerManager::GamerManager()
{
	CreateGamer();
}

GamerManager::~GamerManager()
{
}


void GamerManager::CreateGamer()
{
	player = new Player();
	computer = new Computer();
}
