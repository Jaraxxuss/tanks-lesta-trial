#ifndef ENEMY_SPAWNER_H
#define ENEMY_SPAWNER_H

#include "Enemy.hpp"

class EnemySpawner
{
private:
	sf::Sprite sprite;

	unsigned enemyToSpawnCapacity;
	unsigned spawnedEnemies;

	float spawnCooldown;
	float spawnCooldownMax;

	void initSprite(sf::Texture* texture, float posX, float posY);
	void initVariables(int enemyToSpawnCapacity);

public:
	EnemySpawner();
	EnemySpawner(sf::Texture* texture, float posX, float posY, int enemyToSpawnCapacity);
	virtual ~EnemySpawner();

	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;

	bool canSpawn();

	Enemy* spawn(sf::Texture* texture);

	void onSpawnCooldown();

	void updateSpawn();
	void update();
	void render(sf::RenderTarget& target);
};

#endif
