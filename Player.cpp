#include "Player.h"
#include "iostream"

Player::Player()
{
	_state = 0;
	_tickmove = 0;
	hunter = false;
	_tickTeclaZ = 0;
	validMove = false;
	_antEstado = 0;
	_lastkey = 0;
	Look = 2;
	textu.loadFromFile("Recursos/images/Pacman16.png");
	sp.setTexture(textu);
	sp.setTextureRect(sf::IntRect(32, (32*Look), 32, 32));
}

void Player::ResetPlayer()
{
	Look = 2;
	_state = 0;
	_antEstado = 0;
	_lastkey = 0;
	_tickmove = 0;
	hunter = false;
	_tickTeclaZ = 0;
	_lastkey = 0;
	validMove = false;
	disparo = true;
	canShoot = false;
}

bool Player::checkCollision(int x, int y) //esto deberia estar en collision.cpp
{
	// Assuming each cell is 32x32 pixels
	int cellX = x / 32;
	int cellY = y / 32;

	// Check if the cell is within the map bounds
	if (cellX < 0 || cellX >= 23 || cellY < 0 || cellY >= 25) {
		return true; // Out of bounds, treat as collision
	}

	// Check if the cell is blocked
	return _mapa.getMapa(cellX,cellY)== 1;
}

void Player::handleInput(int posy, int posx)
{
	sf::Vector2f position = getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (!checkCollision(posy - 32, posx)) {
			_lastkey = 1;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (!checkCollision(posy +32, posx)) {
			_lastkey = 2;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (!checkCollision(posy , posx - 32)) {
			_lastkey = 3;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (!checkCollision(posy , posx + 32)) {
			_lastkey = 4;
		}
	}
}

void Player::handleInput2()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		_lastkey = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		_lastkey = 2;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		_lastkey = 3;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		_lastkey = 4;
	}
	actualState();
}

int Player::actualState()
{
	
	if (_state == 0) {
		_tickmove = 0;
		validMove = false;
		if (_lastkey == 1) {
			return _state = 1;
		}
		if (_lastkey == 2) {
			return _state = 2;
		}
		if (_lastkey == 3) {
			return _state = 3;
		}
		if (_lastkey == 4) {
			return _state = 4;
		}
	}
	return _state;
}

void Player::update()
{
	if (_tickmove >= 16){ // ahora le damos utilidad a los tickmove, sirve para que haga un movimiento de una celda de 32, solo q ahora es mas lento
		_state = 0;
		_tickmove = 0;// Corrección: debe ser una asignación, no una comparación
		validMove = true;
		
	}
	_tickmove++;

	//if (SoloX(movX) == true) {
		switch (_state)
		{
		case 0:
			_vel = { 0,0 };
			break;
		case 1:
			_vel = { 0,-2};
			Look = 1;
			break;
		case 2:
			_vel = { 0,2};
			Look = 3;
			break;
		case 3:
			_vel = { -2,0 };
			Look = 2;
			break;
		case 4:
			_vel = { 2,0 };
			Look = 0;
			break;
		default:
			break;
		}
	//}
	//else if (SoloX(movX) == false) {
	//	switch (_state)
	//	{
	//	case 0:
	//		_vel = { 0,0 };
	//		break;
	//	case 3:
	//		_vel = { -2,0 };
	//		break;
	//	case 4:
	//		_vel = { 2,0 }; 
	//		break;
	//	default:
	//		break;
	//	}
	//}

	if (_tickmove <= 16) {
		move(_vel);
	}
	else {
		_vel = { 0, 0 };
		move(_vel);
	}
	textu.loadFromFile("Recursos/images/Pacman16.png");
	sp.setTexture(textu);
	sp.setTextureRect(sf::IntRect(32, (32 * Look), 32, 32));
}

bool Player::Shoot()//si pulsa la tecla z dispara
{
	_tickTeclaZ++;
	if (canShoot == true)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && disparo != true) {
			disparo = true;
			isContactShot = false;
			canShoot = false;
			return true;
		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			if (_tickTeclaZ >= 30) {
				disparo = false;
				_tickTeclaZ = 0;
			}
		}
	}
	return false;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sp, states);
}

sf::FloatRect Player::returnBounds()
{
	return getTransform().transformRect(sp.getGlobalBounds());
}

void Player::setLastkey(int key)
{
	_lastkey = key;
}

int Player::getEstado()
{
	return _state;
}

int Player::getAntEstado()
{
	return _antEstado;
}

bool Player::getCanShoot(){
	return canShoot;
}

void Player::setCanShoot(bool value) {
	canShoot = value;
}

int Player::setEstado(int state)
{
	return _state = state;
}

int Player::getTickMove()
{
	return _tickmove;
}

bool Player::getValidMove()
{
	return validMove;
}

int Player::setTickMove(int tick)
{
	return _tickmove = tick;
}

bool Player::getHunter()
{
	return hunter;
}

void Player::setHunter(bool state)
{
	hunter = state;
}


bool Player::getIsContactShot(){
    return isContactShot;
}

void Player::setIsContactShot(bool value) {
    isContactShot = value;
}
//bool Player::SoloX(bool posx)
//{
//	if (posx == true) {
//		movX = true;
//		return true;
//	}
//	else
//	{
//		movX = false;
//		return false;
//	}
//}

