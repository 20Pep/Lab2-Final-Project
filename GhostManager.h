#pragma once
#include "SFML/Graphics.hpp"
#include "Ghost.h"
#include "AStar.h"
#include "Collision.h"
#include "Mapa.h"
#include <cstdlib>
#include <vector>
#include <ctime>

class GhostManager :  public Ghost{
private:
	Ghost _red;
	Ghost _pink;
	Ghost _blue;
	Ghost _orange;
	AStar _AStar;
	Collision _col;
	Mapa _mapa;

	int tick;
	int Py;
	int Px;
	int Pest;
	
	
	bool homePink;
	bool homeBlue;
	bool homeOrange;

public:
	
	GhostManager();
	void setAll();
	void setTick(int t);
	void setScared(bool is);
	void setPacman(int y, int x);
	void setPest(int estado);
	void setPos(int y, int x, int n);
	float GetPosY(int n);
	float GetPosX(int n);
	sf::FloatRect getBounds(int x);
	void exitHome();
	void returnHome(int ghost);
	//bool pathHome(Ghost& _ghost, int Ygoal, int Xgoal);
	sf::Vector2i targetPink(int estado, int y, int x);
	bool Scatter(Ghost& _ghost, int Ygoal, int Xgoal);
	bool Chase(Ghost& _ghost, int pacmanY, int pacmanX);
	bool Frightened(Ghost& _ghost);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
};

