#include "Enemy.hpp"

void Enemy::initVariables()
{
	this->direction = Direction::DOWN;
	this->movementSpeed = 1.f;
	this->attackCooldownMax = 100.f;
	this->attackCooldown = this->attackCooldownMax;
}

void Enemy::initTexture()
{
	rectByDirection[Direction::UP] = sf::IntRect(128, 0, 16, 16);
	rectByDirection[Direction::RIGHT] = sf::IntRect(224, 0, 16, 16);
	rectByDirection[Direction::DOWN] = sf::IntRect(192, 0, 16, 16);
	rectByDirection[Direction::LEFT] = sf::IntRect(160, 0, 16, 16);
}

void Enemy::initSprite(sf::Texture* texture, float posX, float posY)
{
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(posX, posY);
	this->sprite.setTextureRect(this->rectByDirection[this->direction]);
}

// float dirX, float dirY, float movementSpeed
Enemy::Enemy(sf::Texture* texture, float posX, float posY)
{
	this->initVariables();
	this->initTexture();
	this->initSprite(texture, posX, posY);
}

Enemy::~Enemy()
{
}

const sf::Vector2f& Enemy::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

Direction Enemy::getDirection() const
{
	return this->direction;
}

void Enemy::move(Direction direction)
{
	this->direction = direction;
	this->sprite.setTextureRect(this->rectByDirection[this->direction]);
	if (Direction::LEFT == direction)
		this->sprite.move(sf::Vector2f(-1.f, 0.f) * this->movementSpeed);
	if (Direction::RIGHT == direction)
		this->sprite.move(sf::Vector2f(1.f, 0.f) * this->movementSpeed);
	if (Direction::UP == direction)
		this->sprite.move(sf::Vector2f(0.f, -1.f) * this->movementSpeed);
	if (Direction::DOWN == direction)
		this->sprite.move(sf::Vector2f(0.f, 1.f) * this->movementSpeed);
}

void Enemy::setPosition(float posX, float posY)
{
	this->sprite.setPosition(posX, posY);
}

bool Enemy::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		return true;
	}
	return false;
}

void Enemy::attackOnCooldown()
{
	this->attackCooldown = 0;
}

void Enemy::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 0.5f;
}

void Enemy::update()
{
	this->updateAttack();
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
