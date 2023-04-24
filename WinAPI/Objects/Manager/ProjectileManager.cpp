#include "Framework.h"

ProjectileManager::ProjectileManager()
{
	CreateObjects("Arrow", 30);
}

ProjectileManager::~ProjectileManager()
{
}

void ProjectileManager::CreateObjects(string key, UINT poolSize)
{
	vector<GameObject*> projectiles(poolSize);

	if (key == "Arrow")
	{
		for (GameObject*& projectile : projectiles)
		{
			projectile = new Arrow();
			projectile->tag = key;
		}

	}

	totalObjects[key] = projectiles;
}

void ProjectileManager::ShootProjectile(string key, const Vector2& start, const Vector2& destination, bool AttackDirection)
{
	if (key == "Arrow")
	{
		Arrow* projectile = (Arrow*)Pop("Arrow");
		projectile->Shoot(start, destination, AttackDirection);
	}
}
