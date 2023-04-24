#include "Framework.h"

CharaCardManager::CharaCardManager()
{
}

CharaCardManager::~CharaCardManager()
{
	for (CharaCard* playercard : playercards)
	{
		delete playercard;
	}

	for (CharaCard* computercard : computercards)
	{
		delete computercard;
	}

	playercards.clear();
	computercards.clear();
}

void CharaCardManager::Update()
{
	for (CharaCard* playercard : playercards)
	{
		playercard->Update();
	}

	for (CharaCard* computercard : computercards)
	{
		computercard->Update();
	}
}

void CharaCardManager::Render(HDC hdc)
{
	for (CharaCard* playercard : playercards)
	{
		playercard->Render(hdc);
	}

	for (CharaCard* computercard : computercards)
	{
		computercard->Render(hdc);
	}
}

void CharaCardManager::CreateCards()
{
	CharaCard* card;

	for (int i = 0; i < GAMER_MAX_CHAMP; i++)
	{
		card = new CharaCard(i, L"Textures/Pickban/player_card.bmp");
		playercards.push_back(card);
	}

	for (int i = 0; i < GAMER_MAX_CHAMP; i++)
	{
		card = new CharaCard(i, L"Textures/Pickban/computer_card.bmp");
		computercards.push_back(card);
	}
}

void CharaCardManager::SetCardTexture()
{
	for (int i = 0; i < GAMER_MAX_CHAMP; i++)
	{
		if (GamerManager::Get()->GetPlayer()->GetChampions().size() == i)
			return;

		playercards[i]->SetPickChampInfo(GamerManager::Get()->GetPlayer()->GetChampions()[i]);

		if (GamerManager::Get()->GetComputer()->GetChampions().size() == i)
			return;

		computercards[i]->SetPickChampInfo(GamerManager::Get()->GetComputer()->GetChampions()[i]);
	}
}

void CharaCardManager::SetKDAActive()
{
	for (int i = 0; i < GAMER_MAX_CHAMP; i++)
	{
		playercards[i]->SetKDAActive();
		computercards[i]->SetKDAActive();
	}
}
