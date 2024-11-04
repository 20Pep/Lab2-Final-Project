#include "Ghost.h"

Ghost::Ghost(int y, int x, int coloor, int tam)
{
	setPosition(x, y);
	Colour = coloor;
	_head.setRadius(tam);
	_EstadoAnt ;
	isAlive = true;
	Scared = false;
	_homeY = y;
	_homeX = x;
	tickValidMove = 0;

	

	textu.loadFromFile("Recursos/images/Ghost16.png");
	sp.setTexture(textu);
	setColor(Colour);
	sp.setTextureRect(sf::IntRect(4 * 0, 0, 29, 32));

}

Ghost::Ghost(){

}

sf::FloatRect Ghost::getBounds()
{
	return getTransform().transformRect(sp.getGlobalBounds());
}

void Ghost::setColor(int Colour)
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

	sp.setColor(color);
}

void Ghost::setAll(int color)
{
	setPosition(_homeX, _homeY);
	_estado = 0;
	_EstadoAnt = 0;
	isAlive = true;
	Scared = false;
	setColor(color);
	tickValidMove = 0;
	isValidMove = true;
	_vel = { 0, 0 };
}

int Ghost::getHomeY()
{
	return _homeY;
}

int Ghost::getHomeX()
{
	return _homeY;
}

//void Ghost::setColor(int color)
//{
//	Colour = color;
//}

void Ghost::setValidMove(bool valid)
{
	isValidMove = valid;
}

bool Ghost::getValidMove()
{
	return isValidMove;
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
	tickValidMove++;

	if (tickValidMove >= 16) {
		isValidMove = true;
		tickValidMove = 0;
	}
	
	

	switch (_estado)
	{
	case 1:
		_vel = { 0,-2};
		break;
	case 2:
		_vel = { 0,2 };
		break;
	case 3:
		_vel = { -2,0 };
		break;
	case 4:
		_vel = { 2,0 };
		break;
	}

	if (tickValidMove < 16) {
		move(_vel);
	}
	

}

void Ghost::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	
	states.transform *= getTransform();
	target.draw(sp, states);
}
