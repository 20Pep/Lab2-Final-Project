#include "Ghost.h"

Ghost::Ghost(int y, int x, int color, int tam)
{
	setPosition(x, y);
	Colour = color;
	_head.setRadius(tam);
	_EstadoAnt ;
	isAlive = true;
	Scared = false;
	_homeY = y;
	_homeX = x;

}

Ghost::Ghost()
{
}


void Ghost::setAll(int color)
{
	setPosition(_homeX, _homeY);
	_estado = 0;
	_EstadoAnt = 0;
	isAlive = true;
	Scared = false;
	Colour = color;

}

int Ghost::getHomeY()
{
	return _homeY;
}

int Ghost::getHomeX()
{
	return _homeY;
}

void Ghost::setColor(int color)
{
	Colour = color;
}

void Ghost::setIsAlive(bool live)
{
	isAlive = live;
}

bool Ghost::getIsAlive()
{
	return isAlive;
}

void Ghost::setScared(bool is)
{
	Scared = is;
}

bool Ghost::getScared()
{
	return Scared;
}

void Ghost::setEstAnt(int e)
{
	_EstadoAnt = e;
}

void Ghost::setEstado(int e)
{
	_estado = e;
}

int Ghost::getEstAnt()
{
	return _EstadoAnt;
}

int Ghost::getEstado()
{
	return _estado;
}

int Ghost::getOppositeState(int state) {
	switch (state) {
	case 1: return 2;
	case 2: return 1;
	case 3: return 4;
	case 4: return 3;
	default: return 0;
	}
}

int Ghost::EstadoActual(int e)
{
	return _estado = e;
}

void Ghost::update()
{
	
	switch (_estado)
	{
	case 1:
		_vel = { 0,-32 };
		break;
	case 2:
		_vel = { 0,32 };
		break;
	case 3:
		_vel = { -32,0 };
		break;
	case 4:
		_vel = { 32,0 };
		break;
	}

	move(_vel);

}

void Ghost::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Color color;
	switch (Colour)
	{
	case 1:
		color = color.Red;
		break;
	case 2:
		color = color.Magenta;
		break;
	case 3:
		color = color.Cyan;
		break;
	case 4:
		color = color.Yellow;
		break;
	case 5:
		color = color.Blue;
	}

	sf::Sprite sp;
	sf::Texture textu;

	textu.loadFromFile("Recursos/images/Ghost16.png");
	sp.setTexture(textu);
	sp.setColor(color);
	sp.setTextureRect(sf::IntRect(4 * 0, 0, 29, 32));
	states.transform *= getTransform();
	target.draw(sp, states);
}
