#pragma once
#include "SFML/Graphics.hpp"
#include "Mapa.h"


class Ghost : public sf::Drawable, public sf::Transformable
{
protected:
	sf::CircleShape _head;
	sf::Vector2f _vel;
	int _estado;
	int _EstadoAnt;
	int _homeY;
	int _homeX;
	int Colour;
	bool isAlive;
	bool Scared;
	bool isValidMove;
	int tickValidMove;
	sf::Sprite sp;
	sf::Texture textu;
public:
	Ghost(int y, int x, int coloor, int tam);
	Ghost();

	sf::FloatRect getBounds();
	void setColor(int colour = 5);
	void setAll(int color);
	void setEstAnt(int e);
	void setEstado(int e);
	void setIsAlive(bool live);
	void setScared(bool is);
	/*void setColor(int color);*/
	void setValidMove(bool valid);
	bool getValidMove();
	int getHomeY();
	int getHomeX();
	bool getIsAlive();
	bool getScared();
	int getEstAnt();
	int getEstado();
	int getOppositeState(int state);
	int EstadoActual(int e);
	
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
	
};
