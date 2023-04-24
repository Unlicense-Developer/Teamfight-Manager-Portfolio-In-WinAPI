#pragma once
class ProjectileManager : public PoolingManager, public Singleton<ProjectileManager>
{
public:
	ProjectileManager();
	~ProjectileManager();

	virtual void CreateObjects(string key, UINT poolSize) override;

	void ShootProjectile(string key, const Vector2& start, const Vector2& destination, bool AttackDirection);
};