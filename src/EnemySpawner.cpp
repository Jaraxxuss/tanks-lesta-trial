#include "EnemySpawner.hpp"

void EnemySpawner::initVariables(int enemyToSpawnCapacity)
{
	this->enemyToSpawnCapacity = enemyToSpawnCapacity;
	this->spawnedEnemies = 0;
	this->spawnCooldownMax = 100.f;
	this->spawnCooldown = this->spawnCooldownMax;
}

void EnemySpawner::initSprite(sf::Texture* texture, float posX, float posY)
{
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(posX, posY);
	this->sprite.setTextureRect(sf::IntRect(256, 96, 16, 16));
}

EnemySpawner::EnemySpawner()
{
}

EnemySpawner::EnemySpawner(sf::Texture* texture, float posX, float posY, int enemyToSpawnCapacity)
{
	this->initVariables(enemyToSpawnCapacity);
	this->initSprite(texture, posX, posY);
}

EnemySpawner::~EnemySpawner()
{
}

const sf::Vector2f& EnemySpawner::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect EnemySpawner::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

bool EnemySpawner::canSpawn()
{
	if (this->spawnedEnemies >= this->enemyToSpawnCapacity)
	{
		return false;
	}

	if (this->spawnCooldown >= this->spawnCooldownMax)
	{
		return true;
	}
	return false;
}

Enemy* EnemySpawner::spawn(sf::Texture* texture)
{
	this->spawnedEnemies++;
	return new Enemy(texture, this->getPos().x, this->getPos().y);
}

void EnemySpawner::onSpawnCooldown()
{
	this->spawnCooldown = 0;
}

void EnemySpawner::updateSpawn()
{
	if (this->spawnCooldown < this->spawnCooldownMax)
		this->spawnCooldown += 0.5f;
}

void EnemySpawner::update()
{
	this->updateSpawn();
}

void EnemySpawner::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
