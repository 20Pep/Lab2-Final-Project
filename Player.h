#pragma once
#include "SFML/Graphics.hpp"
#include "Municion.h"

class Player : public sf::Drawable, public sf::Transformable
{
private:

	sf::CircleShape _body;
	int _tickmove;
	int _state;
	sf::Vector2f _vel;
	bool hunter;
	bool disparo = false;
	bool movX = true;
	sf::Sprite sp;
	int _tickTeclaZ;

public:
	Player();
	int actualState();
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
	int getEstado();
	int setEstado(int state);
	int getTickMove();
	int setTickMove(int tick);
	bool getHunter();
	void setHunter(bool state);
	bool Shoot();
	bool SoloX(bool posx);
};

