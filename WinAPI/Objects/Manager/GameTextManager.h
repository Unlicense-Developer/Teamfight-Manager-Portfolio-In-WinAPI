#pragma once
class GameTextManager : public PoolingManager, public Singleton<GameTextManager>
{
public:
	GameTextManager();
	~GameTextManager();

	virtual void CreateObjects(string key, UINT poolSize) override;

	void PrintDamageText(const Vector2& pos, int damage);
	void PrintHealText(const Vector2& pos, int heal);
};