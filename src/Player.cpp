#include "Player.hpp"

void Player::initVariables()
{
	this->direction = Direction::UP;
	this->movementSpeed = 1.f;
	this->attackCooldownMax = 100.f;
	this->attackCooldown = this->attackCooldownMax;
}

void Player::initTexture()
{
	rectByDirection[Direction::UP] = sf::IntRect(0, 0, 16, 16);
	rectByDirection[Direction::RIGHT] = sf::IntRect(96, 0, 16, 16);
	rectByDirection[Direction::DOWN] = sf::IntRect(64, 0, 16, 16);
	rectByDirection[Direction::LEFT] = sf::IntRect(32, 0, 16, 16);
}

void Player::initSprite(sf::Texture* texture, float posX, float posY)
{
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(posX, posY);
	this->sprite.setTextureRect(this->rectByDirection[this->direction]);
}

Player::Player(sf::Texture* texture, float posX, float posY)
{
	this->initVariables();
	this->initTexture();
	this->initSprite(texture, posX, posY);
}

Player::~Player()
{
}

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

Direction Player::getDirection() const
{
	return this->direction;
}

void Player::move(Direction direction)
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

void Player::setPosition(float posX, float posY)
{
	this->sprite.setPosition(posX, posY);
}

bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		return true;
	}
	return false;
}

void Player::attackOnCooldown()
{
	this->attackCooldown = 0;
}

void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 0.5f;
}

void Player::update()
{
	this->updateAttack();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
