#include "Framework.h"

GameTextManager::GameTextManager()
{
	CreateObjects("DamageText", 100);
	CreateObjects("HealText", 50);
}

GameTextManager::~GameTextManager()
{
}

void GameTextManager::CreateObjects(string key, UINT poolSize)
{
	vector<GameObject*> texts(poolSize);

	if (key == "DamageText")
	{
		for (GameObject*& text : texts)
		{
			text = new DamageText();
			text->tag = key;
		}

	}
	else if (key == "HealText")
	{
		for (GameObject*& text : texts)
		{
			text = new HealText();
			text->tag = key;
		}

	}

	totalObjects[key] = texts;
}

void GameTextManager::PrintDamageText(const Vector2& pos, int damage)
{
	DamageText* text = (DamageText*)Pop("DamageText");
	text->Print(pos, damage);
}

void GameTextManager::PrintHealText(const Vector2& pos, int heal)
{
	HealText* text = (HealText*)Pop("HealText");
	text->Print(pos, heal);
}
