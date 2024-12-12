#pragma once
#include "SFML/Graphics.hpp"
#include "Municion.h"
#include "Mapa.h"
class Player : public sf::Drawable, public sf::Transformable
{
private:

	sf::Vector2f _vel;
	sf::Sprite sp;
	sf::Texture textu;
	int _tickmove;
	int _state;
	int _tickTeclaZ;
	int _antEstado;
	int _lastkey;
	int Look;
	bool validMove;
	bool isContactShot;
	bool canShoot;
	bool chased;
	bool hunter;
	bool disparo = false;
	//bool movX = true;
	Mapa _mapa;

public:
	Player();
	bool checkCollision(int x, int y);
	sf::FloatRect returnBounds();
	void ResetPlayer();
	void handleInput(int posy, int posx);
	void handleInput2();
	void setLastkey(int key);
	int actualState();
	void update();
	int getEstado();
	int getAntEstado();
	int setEstado(int state);
	int getTickMove();
	bool getValidMove();
	bool getCanShoot();
	void setCanShoot(bool value);
	int setTickMove(int tick);
	bool getHunter();
	void setHunter(bool state);
	bool Shoot();
	bool getIsContactShot();	
	void setIsContactShot(bool value);
	void setChased(bool state);
	bool getChased();
	//bool SoloX(bool posx);
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
};

