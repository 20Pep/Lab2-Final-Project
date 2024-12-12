#pragma once
#include "SFML/Graphics.hpp"
#include "Mapa.h"
#include "Player.h"
#include "Ghost.h"
#include "Boss.h"

class Collision {
private:

	Mapa mapa;
	int cell = 32;
	int contFood = 0;
	bool origen = true;
	int energizerTick = 0;
	
public:
	
	bool CheckCollision(int state, Mapa& _mapa, int posy, int posx);
	int GhostAndPacman(Mapa& _mapa, Player& _player, Ghost& _ghost, int i);
	void Scene2Bounds(Mapa& _mapa, Player& _player, int posY, int posX);
	void ObjCollision(Mapa& _mapa, Player& _player, int posY, int posX);
	void PortalCollision(Mapa& _mapa, Player& _player, int posY, int posX);
//	void PortalCollisionGhost(Mapa& _mapa, GhostManager& _ghostManager);
	void setAll();

	int getJefe()const;
	
};

