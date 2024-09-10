#pragma once
#include "SFML/Graphics.hpp"
#include "Municion.h"

class Player : public sf::Drawable, public sf::Transformable
{
private:


	int _tickmove;
	int _state;
	sf::Vector2f _vel;
	bool hunter;
	bool disparo = false;
	bool movX = true;
	sf::Sprite sp;
	sf::Texture textu;
	int _tickTeclaZ;
	bool validMove;
	int _antEstado;
	int _lastkey;
	int Look;

public:
	Player();
	sf::FloatRect returnBounds();
	void ResetPlayer();
	void handleInput();
	void setLastkey(int key);
	int actualState();
	void update();
	int getEstado();
	int getAntEstado();
	int setEstado(int state);
	int getTickMove();
	bool getValidMove();
	int setTickMove(int tick);
	bool getHunter();
	void setHunter(bool state);
	bool Shoot();
	bool SoloX(bool posx);
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
};

