#ifndef BULLET_H
#define BULLET_H

#include "Direction.hpp"

class Bullet
{
private:
	sf::Sprite sprite;

	sf::Vector2f direction;
	float movementSpeed;
	bool isEnemyBullet;

	void initSprite(sf::Texture* texture, sf::Vector2f vector);

public:
	Bullet(sf::Texture* texture, float posX, float posY, Direction direction, float movementSpeed, bool isEnemyBulltet);
	virtual ~Bullet();

	const sf::FloatRect getBounds() const;
	bool getIsEnemyBullet() const;

	void update();
	void render(sf::RenderTarget& target);
};

#endif
