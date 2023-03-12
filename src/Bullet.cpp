#include "Bullet.hpp"
#include "Direction.hpp"

void Bullet::initSprite(sf::Texture* texture, sf::Vector2f vector)
{
	this->sprite.setTexture(*texture);
	sf::Vector2f temp = vector + (direction * 6.f) + (direction * 16.f);
	this->sprite.setPosition(temp);
	this->sprite.setTextureRect(sf::IntRect(323, 101, 6, 6));
}

Bullet::Bullet(sf::Texture* texture, float posX, float posY, Direction direction, float movementSpeed, bool isEnemyBullet)
{

	if (Direction::LEFT == direction)
	{
		this->direction.x = -1.f;
		this->direction.y = 0.f;
	}
	if (Direction::RIGHT == direction)
	{
		this->direction.x = 1.f;
		this->direction.y = 0.f;
	}
	if (Direction::UP == direction)
	{
		this->direction.x = 0.f;
		this->direction.y = -1.f;
	}
	if (Direction::DOWN == direction)
	{
		this->direction.x = 0.f;
		this->direction.y = 1.f;
	}
	this->initSprite(texture, sf::Vector2f(posX, posY));
	this->movementSpeed = movementSpeed;
	this->isEnemyBullet = isEnemyBullet;
}

Bullet::~Bullet()
{
}

const sf::FloatRect Bullet::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

bool Bullet::getIsEnemyBullet() const
{
	return this->isEnemyBullet;
}

void Bullet::update()
{
	this->sprite.move(this->movementSpeed * this->direction);
}

void Bullet::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
