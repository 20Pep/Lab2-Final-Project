#pragma once
#include "SFML/Graphics.hpp"
#include "iostream"

class Mapa : public sf::Drawable, public sf::Transformable {
protected:
	int cell = 32;
	float _ancho = 23;
	float _altura = 25;
	int logicmap[100][92] = { 0 };
	float _mapa[25][23];

public:
	Mapa();
	void initialMap();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void setMapa(int y, int x, float value);
	float getMapa(int y, int x);
	int getRetorno(int i, int j)const ;
	int getLogicMap(int y, int x);
	void Boss();
};

