#pragma once
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Ghost.h"
#include "GhostManager.h"
#include "Mapa.h"
#include "Collision.h"
#include "vida.h"
#include "Boss.h"
#include "AStar.h"
#include "Municion.h"

class Scene : public sf::Drawable, public sf::Transformable
{
private:
	Player _player;
	Mapa _mapa;
	Collision _collision;
	Ghost _ghost;
	GhostManager _ghostManager;
	Vida _vidas;
	Boss _boss;
	Balas _balas;
	
	bool isPlaying;
	int pause;
	bool nombre;
	float cont;
	bool banderaScared;
	int ticktest;
	
public:
	Scene();
	void update();
	void scene2();
	void setScene();
	void setScene2();
	void ResetAll();
	bool getIsPlaying();
	void setIsPlaying();
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;


};
