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

	textu.loadFromFile("Recursos/images/Pacman16.png");
	sp.setTexture(textu);
	sp.setTextureRect(sf::IntRect(32, 0, 32, 32));
}

sf::FloatRect Player::returnBounds()
{	
	
	return getTransform().transformRect(sp.getGlobalBounds());
}

void Player::ResetPlayer()
{
	_state = 0;
	_tickmove = 0;
	hunter = false;
	_tickTeclaZ = 0;
	_lastkey = 0;
	validMove = false;
	
}

void Player::handleInput()
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
}

void Player::setLastkey(int key)
{
	_lastkey = key;
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

	if (SoloX(movX) == true) {
		switch (_state)
		{
		case 0:
			_vel = { 0,0 };
			break;
		case 1:
			_vel = { 0,-2};
			break;
		case 2:
			_vel = { 0,2};
			break;
		case 3:
			_vel = { -2,0 };
			break;
		case 4:
			_vel = { 2,0 };
			break;
		default:
			break;
		}
	}
	else if (SoloX(movX) == false) {
		switch (_state)
		{
		case 0:
			_vel = { 0,0 };
			break;
		case 3:
			_vel = { -2,0 };
			break;
		case 4:
			_vel = { 2,0 }; 
			break;
		default:
			break;
		}
	}

	if (_tickmove <= 16) {
		move(_vel);
	}
	else {
		_vel = { 0, 0 };
		move(_vel);
	}

}



void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sp, states);
}

int Player::getEstado()
{
	return _state;
}

int Player::getAntEstado()
{
	return _antEstado;
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

bool Player::Shoot()//si pulsa la tecla z dispara
{
	_tickTeclaZ++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && disparo != true) {
		std::cout << "Hola" << std::endl;
		disparo = true;
		return true;

	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		if (_tickTeclaZ >= 70) {
			disparo = false;
			_tickTeclaZ = 0;
		}

	}
	return false;

}

bool Player::SoloX(bool posx)
{
	if (posx == true) {
		movX = true;
		return true;
	}
	else
	{
		movX = false;
		return false;
	}

}
