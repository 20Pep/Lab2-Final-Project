#pragma once
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Municion.h"

class Boss : public sf::Drawable, public sf::Transformable
{
protected:
	//LLamar al pacman
	Player _player;
	Balas _bala;
	//crear otro fantasma pero mas grande?
	//crear un escenario
	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::FloatRect _hitbox;
	int cell = 32;
	float vel;
	int estado;
	float _tick;
	static const int TICK_LIMIT = 8;
	static const int MAX_VELOCITY = 10;
	sf::Vector2f position;
	int _vida;

public:
	Boss();
	void update();
	bool CheckCollision(const Balas& bala);
	void updateHitbox();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void setvida(int vida);
	int getvida();

};

