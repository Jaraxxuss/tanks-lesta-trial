#ifndef GAME_H
#define GAME_H

#include "Bullet.hpp"
#include "Enemy.hpp"
#include "EnemySpawner.hpp"
#include "Player.hpp"
#include <map>
#include <vector>

class Game
{
private:
	sf::RenderWindow* window;

	sf::Font* font;
	sf::Text text;

	std::map<std::string, sf::Texture*> textures;

	Player* player;

	unsigned points;
	//TODO
	unsigned hp;

	std::vector<EnemySpawner*> enemySpawners;
	std::vector<Enemy*> enemies;
	std::vector<Bullet*> bullets;

	unsigned maxEnemies;
	unsigned enemySpawnersAmount;

	void initVariables();
	void initWindow(sf::RenderWindow* window);
	void initSystems();
	void initTextures();
	void initFonts();
	void initPlayer();
	void initEnemySpawners();
	void initGUI();

public:
	Game(sf::RenderWindow* window);
	virtual ~Game();

	void onEnemyKilled();
	void onPlayerHit();

	void updatePollEvents();
	void updateInput();
	void updateEnemySpawners();
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void updateCollision();
	void updateEnemyCollision(Enemy* enemy);
	void updateGUI();
	void update();

	void renderGUI(sf::RenderTarget& target);
	void render();

	void run();
};

#endif
