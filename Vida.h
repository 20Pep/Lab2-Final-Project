#pragma once
#include "Player.h"
#include "Ghost.h"
class Vida
{
private:
	int _vidas;
public:
	int getVidas();
	void setVidas(int vidas);
	void setScene(Player& _player, Ghost& _ghost);
	void closeScene();
};

