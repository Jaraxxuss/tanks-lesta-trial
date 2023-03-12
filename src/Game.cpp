#include "Game.hpp"
#include "Player.hpp"

#include <sstream>
#include <string>

void Game::initVariables()
{
	this->window = nullptr;
	this->enemySpawnersAmount = 3;
	this->maxEnemies = 6;
}

void Game::initWindow(sf::RenderWindow* window)
{
	this->window = window;
	this->window->setFramerateLimit(60);
}

void Game::initSystems()
{
	this->points = 0;
	this->hp = 3;
}

void Game::initTextures()
{
	this->textures["TEXTURE"] = new sf::Texture();
	this->textures["TEXTURE"]->loadFromFile("content/textures.png");
}

void Game::initFonts()
{
	this->font = new sf::Font();
	if (!this->font->loadFromFile("content/Roboto-Black.ttf"))
	{
		// error...
	}
}

void Game::initPlayer()
{
	this->player = new Player(this->textures["TEXTURE"], this->window->getPosition().x + 100.f, this->window->getPosition().y + 100.f);
}

void Game::initEnemySpawners()
{
	float delta = (this->window->getSize().x - 16) / (this->enemySpawnersAmount - 1);

	for (size_t i = 0; i < this->enemySpawnersAmount; i++)
	{
		this->enemySpawners.push_back(new EnemySpawner(this->textures["TEXTURE"], i * delta, 0.f, static_cast<int>(this->maxEnemies / this->enemySpawnersAmount)));
	}
}

void Game::initGUI()
{
	this->text.setFont(*this->font);
	this->text.setCharacterSize(12);
	this->text.setFillColor(sf::Color::White);
}

Game::Game(sf::RenderWindow* window)
{
	this->initVariables();
	this->initWindow(window);
	this->initSystems();
	this->initTextures();
	this->initFonts();
	this->initPlayer();
	this->initEnemySpawners();
	this->initGUI();
}

Game::~Game()
{
	delete this->player;
	delete this->font;

	for (auto& textureEntry : this->textures)
	{
		delete textureEntry.second;
	}

	for (auto& bullet : this->bullets)
	{
		delete bullet;
	}

	for (auto& enemy : this->enemies)
	{
		delete enemy;
	}

	for (auto& enemySpawner : this->enemySpawners)
	{
		delete enemySpawner;
	}
}

void Game::onEnemyKilled()
{
	this->points++;
}

void Game::onPlayerHit()
{
	if (this->hp > 1)
	{
		this->hp--;
	}
}

void Game::updatePollEvents()
{
	sf::Event event;
	while (this->window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(Direction::LEFT);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(Direction::RIGHT);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(Direction::UP);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(Direction::DOWN);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		if (this->player->canAttack())
		{
			this->bullets.push_back(new Bullet(this->textures["TEXTURE"], this->player->getPos().x, this->player->getPos().y, this->player->getDirection(), 4, false));
			this->player->attackOnCooldown();
		}
	}
}

void Game::updateEnemySpawners()
{
	for (auto* enemySpawner : this->enemySpawners)
	{
		enemySpawner->update();
		if (enemySpawner->canSpawn())
		{
			this->enemies.push_back(enemySpawner->spawn(this->textures["TEXTURE"]));
			enemySpawner->onSpawnCooldown();
		}
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}
		else if (bullet->getBounds().top + bullet->getBounds().height >= this->window->getSize().y)
		{
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}

		if (bullet->getBounds().left + bullet->getBounds().width < 0.f)
		{
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}
		else if (bullet->getBounds().left + bullet->getBounds().width >= this->window->getSize().x)
		{
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}

		++counter;
	}
}

void Game::updateEnemies()
{
	for (auto* enemy : this->enemies)
	{
		enemy->update();
		this->updateEnemyCollision(enemy);
		enemy->move(Direction::DOWN);
		if (enemy->canAttack())
		{
			this->bullets.push_back(new Bullet(this->textures["TEXTURE"], enemy->getPos().x, enemy->getPos().y, enemy->getDirection(), 4, true));
			enemy->attackOnCooldown();
		}
	}
}

void Game::updateCombat()
{
	for (size_t i = 0; i < this->enemies.size(); i++)
	{
		bool enemyRemoved = false;
		for (size_t j = 0; j < this->bullets.size() && !enemyRemoved; j++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[j]->getBounds()))
			{
				if (this->bullets[j]->getIsEnemyBullet() == false)
				{
					delete this->enemies[i];
					this->enemies.erase(this->enemies.begin() + i);
					this->onEnemyKilled();
					enemyRemoved = true;
				}

				delete this->bullets[j];
				this->bullets.erase(this->bullets.begin() + j);
			}
			else if (this->player->getBounds().intersects(this->bullets[j]->getBounds()))
			{
				if (this->bullets[j]->getIsEnemyBullet() == true)
				{
					this->onPlayerHit();
					delete this->bullets[j];
					this->bullets.erase(this->bullets.begin() + j);
				}
			}
		}
	}
}

void Game::updateCollision()
{
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}

	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
}

void Game::updateEnemyCollision(Enemy* enemy)
{
	if (enemy->getBounds().left < 0.f)
	{
		enemy->setPosition(0.f, enemy->getBounds().top);
	}
	else if (enemy->getBounds().left + enemy->getBounds().width >= this->window->getSize().x)
	{
		enemy->setPosition(this->window->getSize().x - enemy->getBounds().width, enemy->getBounds().top);
	}

	if (enemy->getBounds().top < 0.f)
	{
		enemy->setPosition(enemy->getBounds().left, 0.f);
	}
	else if (enemy->getBounds().top + enemy->getBounds().height >= this->window->getSize().y)
	{
		enemy->setPosition(enemy->getBounds().left, this->window->getSize().y - enemy->getBounds().height);
	}
}

void Game::updateGUI()
{
	std::stringstream ss;

	ss << "Points " << this->points << "; HP " << this->hp;

	this->text.setString(ss.str());
}

void Game::update()
{
	this->updatePollEvents();
	this->updateInput();
	this->player->update();
	this->updateCollision();
	this->updateEnemySpawners();
	this->updateBullets();
	this->updateEnemies();
	this->updateCombat();
	this->updateGUI();
}

void Game::renderGUI(sf::RenderTarget& target)
{
	target.draw(this->text);
}

void Game::render()
{
	this->window->clear();

	this->player->render(*this->window);

	for (auto* bullet : this->bullets)
	{
		bullet->render(*this->window);
	}

	for (auto* enemySpawner : this->enemySpawners)
	{
		enemySpawner->render(*this->window);
	}

	for (auto* enemy : this->enemies)
	{
		enemy->render(*this->window);
	}

	this->renderGUI(*this->window);

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}
