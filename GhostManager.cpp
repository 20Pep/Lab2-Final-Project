#include "GhostManager.h"
#include "iostream"
GhostManager::GhostManager() : _red(352, 352, 1, 16), _pink(416, 352, 2, 16), _blue(416, 320, 3, 16), _orange(416,384, 4, 16) {
	tick = 0;
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void GhostManager::setAll()
{
	_red.setAll(1);
	_pink.setAll(2);
	_blue.setAll(3);
	_orange.setAll(4);
	tick = 0;
	Scared = false;
}

void GhostManager::setTick(int tick)
{
	tick = 0;
}

void GhostManager::setScared(bool is)
{
	Ghost* ghost ;
	int i = 0;
	for (Ghost* ghost : { &_red, &_pink, &_blue, &_orange }) {
		i++;
		ghost->setScared(is);
		if (is) {
			ghost->setColor(5);
			ghost->EstadoActual(0); // Resetear el estado actual
			ghost->setEstAnt(0);    // Resetear el estado anterior
		}
		else {
			ghost->setColor(i);
		}

	}
}

void GhostManager::setPacman(int y, int x)
{
	Py = y / 32, Px = x / 32;
}

void GhostManager::setPest(int estado)
{
	Pest = estado;
}

void GhostManager::setPos(int y, int x, int n)
{
	switch (n)
	{
	case 1:
		_red.setPosition(x, y);
		break;
	case 2:
		_pink.setPosition(x, y);
		break;
	case 3:
		_blue.setPosition(x, y);
		break;
	case 4:
		_orange.setPosition(x, y);
		break;
	}
}

int GhostManager::GetPosY(int n)
{
	switch (n)
	{
	case 1:
		return _red.getPosition().y;
		break;
	case 2:
		return _pink.getPosition().y;
		break;
	case 3:
		return _blue.getPosition().y;
		break;
	case 4:
		return _orange.getPosition().y;
		break;
	}
}

int GhostManager::GetPosX(int n)
{
	switch (n)
	{
	case 1:
		return _red.getPosition().x;
		break;
	case 2:
		return _pink.getPosition().x;
		break;
	case 3:
		return _blue.getPosition().x;
		break;
	case 4:
		return _orange.getPosition().x;
		break;
	}
}

int GhostManager::getCazado()
{
	return cazado;
}

void GhostManager::returnHome(int ghost)
{
	
	switch (ghost)
	{
	case 1: 
		_red.setIsAlive(false);
		break;
	case 2:  
		_pink.setIsAlive(false);
		break;
	case 3: 
		_blue.setIsAlive(false);
		break;
	case 4: 
		_orange.setIsAlive(false);
		break;
	default: return;
	}
}

//bool GhostManager::pathHome(Ghost& _ghost, int Ygoal, int Xgoal)
//{
//	int startY = _ghost.getPosition().y / 32;
//	int startX = _ghost.getPosition().x / 32;
//	_AStar.setStart(startY, startX);
//	_AStar.setGoal(Ygoal, Xgoal);
//
//	int pathLength = 0;
//	int Gestado;
//	_AStar.Algoritmo(pathLength, Gestado);
//
//	// Si ya está en el tile objetivo, prueba las direcciones en orden: 1, 3, 2, 4
//	if (startY == Ygoal && startX == Xgoal) {
//		_ghost.setIsAlive(true);
//		_ghost.setEstAnt(0);
//		return false;
//	}
//
//	int oppositeState = _ghost.getOppositeState(_ghost.getEstAnt());
//	
//		// Lógica existente para moverse hacia el objetivo
//		if (Gestado == oppositeState) {
//			int alternativeStates[] = { 1, 3, 2, 4 };
//			for (int state : alternativeStates) {
//				if (state != oppositeState && _col.CheckCollision(state, _mapa, _ghost.getPosition().y, _ghost.getPosition().x)) {
//					Gestado = state;
//					break;
//				}
//			}
//		}
//	
//	_ghost.EstadoActual(Gestado);
//	bool canMoveGhost = _col.CheckCollision(Gestado, _mapa, _ghost.getPosition().y, _ghost.getPosition().x);
//	_ghost.setEstAnt(Gestado);
//
//	return canMoveGhost;
//}

sf::Vector2i GhostManager::targetPink(int estado, int y, int x)
{
	switch (estado)
	{
	case 1: y -= 2; break; // Arriba
	case 2: y += 2; break; // Abajo
	case 3: x -= 2; break; // Izquierda
	case 4: x += 2; break; // Derecha
	}
	return sf::Vector2i(x, y);
}




bool GhostManager::Scatter (Ghost& _ghost, int Ygoal, int Xgoal)
{
	int startY = _ghost.getPosition().y / 32;
	int startX = _ghost.getPosition().x / 32;
	_AStar.setStart(startY, startX);
	_AStar.setGoal(Ygoal, Xgoal);
	
	int pathLength = 0;
	int Gestado;
	_AStar.Algoritmo(pathLength, Gestado);
	
	int oppositeState = _ghost.getOppositeState(_ghost.getEstAnt());
	int alternativeStates[] = { 1, 3, 2, 4 };
	// Si ya está en el tile objetivo, prueba las direcciones en orden: 1, 3, 2, 4
	if (startY == Ygoal && startX == Xgoal) {
		for (int dir : alternativeStates){
			if (dir != oppositeState && _col.CheckCollision(dir, _mapa, _ghost.getPosition().y, _ghost.getPosition().x)) {
				Gestado = dir;
				break;
			}
		}
	}
	else {
		// Lógica existente para moverse hacia el objetivo
		if (Gestado == oppositeState) {	
			for (int state : alternativeStates) {
				if (state != oppositeState && _col.CheckCollision(state, _mapa, _ghost.getPosition().y, _ghost.getPosition().x)) {
					Gestado = state;
					break;
				}
			}
		}
		if (Gestado == oppositeState) {
			Gestado = _ghost.getEstAnt();
		}
	}

	_ghost.EstadoActual(Gestado);
	bool canMoveGhost = _col.CheckCollision(Gestado, _mapa, _ghost.getPosition().y, _ghost.getPosition().x);
	_ghost.setEstAnt(Gestado);
	
	return canMoveGhost;
}

bool GhostManager::Chase(Ghost& _ghost, int pacmanY, int pacmanX)
{
	int startY = _ghost.getPosition().y / 32;
	int startX = _ghost.getPosition().x / 32;
	_AStar.setStart(startY, startX);
	_AStar.setGoal(pacmanY, pacmanX);

	int pathLength = 0;
	int Gestado;
	_AStar.Algoritmo(pathLength, Gestado);
	
	int oppositeState = _ghost.getOppositeState(_ghost.getEstAnt());
	int alternativeStates[] = { 1, 3, 2, 4 };
	
	// Si ya está en el tile objetivo, elige una dirección que no sea la opuesta
	if (startY == pacmanY && startX == pacmanX) {
		for (int dir : alternativeStates) {
			if (dir != oppositeState && _col.CheckCollision(dir, _mapa, _ghost.getPosition().y, _ghost.getPosition().x)) {
				Gestado = dir;
				break;
			}
		}
	}
	else {
		// Lógica existente para moverse hacia el objetivo
		if (Gestado == oppositeState) {
			for (int state : alternativeStates) {
				if (state != oppositeState && _col.CheckCollision(state, _mapa, _ghost.getPosition().y, _ghost.getPosition().x)) {
					Gestado = state;
					break;
				}
			}
		}
		if (Gestado == oppositeState) {
			Gestado = _ghost.getEstAnt();
		}
	}

	_ghost.EstadoActual(Gestado);
	bool canMoveGhost = _col.CheckCollision(Gestado, _mapa, _ghost.getPosition().y, _ghost.getPosition().x);
	_ghost.setEstAnt(Gestado);
	
	return canMoveGhost;
}

bool GhostManager::Frightened(Ghost& _ghost)
{
	int maxAttempts = 10; // Evitar bucle infinito
	for (int attempt = 0; attempt < maxAttempts; attempt++) {
		int Gestado = rand() % 4 + 1;
		int oppositeState = _ghost.getOppositeState(_ghost.getEstAnt());

		if (_col.CheckCollision(Gestado, _mapa, _ghost.getPosition().y, _ghost.getPosition().x) && Gestado != oppositeState) {
			_ghost.EstadoActual(Gestado);
			_ghost.setEstAnt(Gestado);
			return true;
		}
	}
	// Si no se encontró una dirección válida, mantén la dirección actual
	return false;
}

void GhostManager::update()
{
	tick++;

	// Array de punteros a fantasmas
	Ghost* ghosts[] = { &_red, &_pink, &_blue, &_orange };

	for (int i = 0; i < 4; ++i) {
		Ghost* ghost = ghosts[i];

		if (!ghost->getIsAlive()) {
			// Si el fantasma no está vivo, lo devolvemos a su posición inicial
			ghost->setEstAnt(0);
			ghost->setEstado(0);
			ghost->setPosition(ghost->getHomeX(), ghost->getHomeY());
			ghost->setIsAlive(true);
			ghost->setScared(false);
			continue;
		}

		if (ghost->getScared()) {
			// Comportamiento asustado
			if (Frightened(*ghost)) {
				ghost->update();
			}
		}
		else {
			// Comportamiento normal (Scatter o Chase)
			bool moved = false;

			if (ghost == &_red) {
				if (Scatter(*ghost, 3, 18) && tick <= 60) {
					moved = true;
				}
				else if (Chase(*ghost, Py, Px) && tick > 60) {
					moved = true;
				}
			}
			else if (ghost == &_pink) {
				sf::Vector2i pinkTarget = targetPink(Pest, Py, Px);
				if (tick > 1) {
					if (Scatter(*ghost, 3, 4) && tick <= 60) {
						moved = true;
					}
					else if (Chase(*ghost, pinkTarget.y, pinkTarget.x) && tick > 60) {
						moved = true;
					}
				}
			}
			else if (ghost == &_blue) {
				if (tick > 15 && Scatter(*ghost, 22, 18)) {
					moved = true;
				}
			}
			else if (ghost == &_orange) {
				if (tick > 17 && Scatter(*ghost, 22, 2)) {
					moved = true;
				}
			}

			if (moved) {
				ghost->update();
			}
		}
	}

	// Reiniciar el tick si es necesario
	if (tick > 180) {  // Puedes ajustar este valor según tus necesidades
		tick = 0;
	}
}

	
void GhostManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_red, states);
	target.draw(_pink, states);
	target.draw(_blue, states);
	target.draw(_orange, states);
}
