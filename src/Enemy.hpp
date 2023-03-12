#ifndef ENEMY_H
#define ENEMY_H

#include "Direction.hpp"

class Enemy
{
private:
	sf::Sprite sprite;
	std::map<Direction, sf::IntRect> rectByDirection;

	Direction direction;
	float movementSpeed;
	float attackCooldown;
	float attackCooldownMax;

	void initVariables();
	void initTexture();
	void initSprite(sf::Texture* texture, float posX, float posY);

public:
	Enemy(sf::Texture* texture, float posX, float posY);
	virtual ~Enemy();

	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	Direction getDirection() const;

	void move(Direction direction);
	void setPosition(float posX, float posY);
	bool canAttack();
	void attackOnCooldown();

	void updateAttack();
	void update();
	void render(sf::RenderTarget& target);
};

#endif
