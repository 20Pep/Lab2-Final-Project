#include "GhostManager.h"
#include "iostream"
GhostManager::GhostManager() {

	_ghosts[0].setHome(352, 352); // Red
	_ghosts[1].setHome(416, 352); // Pink
	_ghosts[2].setHome(416, 320); // Blue
	_ghosts[3].setHome(416, 384); // Orange
	for (int i = 0; i < 4; i++)
	{
		_ghosts[i].setAll(i + 1);
	}
	tick = 0;
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	homeBlue = true;
	homeOrange = true;
	homePink = true;
	Pest = 0;
	scene2 = false;
}

void GhostManager::set2(Mapa& _map)
{
	_ghosts[1].setColor(2);
	_ghosts[1].setPosition(0, 640);
	_ghosts[2].setColor(3);
	_ghosts[2].setPosition(704, 640 );
	_AStar.InitializeNodes(_map);
	scene2 = true;
}

void GhostManager::setAll(Mapa& _map) {
	for (int i = 0; i < 4; ++i) {
		_ghosts[i].setAll(i + 1);
	}
	homeBlue = true;
	homeOrange = true;
	homePink = true;
	tick = 0;
	scene2 = false;
	_AStar.InitializeNodes(_map);
}

void GhostManager::setTick(int t)
{
	tick = t ;
}

void GhostManager::setScared(bool is)
{
	for (int i = 0; i < 4; ++i) {
		Ghost& ghost = _ghosts[i];
		ghost.setScared(is);
		if (is) {
			ghost.setColor(5);
			ghost.EstadoActual(0); // Resetear el estado actual
			ghost.setEstAnt(0);    // Resetear el estado anterior
		}
		else {
			ghost.setColor(i + 1);
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

void GhostManager::exitHome()
{
	
		if (tick >= (60 * 1)) {
			homePink = false;
		}
		if (tick >= (60 * 7)) {
			homeBlue = false;
		}
		if (tick >= (60 * 9)) {
			homeOrange = false;
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

Ghost& GhostManager::getGhost(int index) {
	if (index >= 0 && index < 4) {
		return _ghosts[index];
	}
	else {
		throw std::out_of_range("Index out of range");
	}
}

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
	float startY = _ghost.getPosition().y / 32;
	float startX = _ghost.getPosition().x / 32;
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

void GhostManager::update() {
	tick++;
	exitHome();

	for (int i = 0; i < 4; ++i) {
		Ghost& ghost = _ghosts[i];

		if (!ghost.getIsAlive()) {
			ghost.setAll(i + 1);
			continue;
		}
		if (ghost.getValidMove()) {
			if (ghost.getScared()) {
				if (Frightened(ghost)) {
					ghost.setValidMove(false);
					ghost.update();
				}
			}
			else {
				bool moved = false;
				if (i == 0) { // Red
					if (Scatter(ghost, 3, 18) && tick <= 60 * 12) {
						moved = true;
					}
					else if (Chase(ghost, Py, Px) && tick > 60 * 12) {
						moved = true;
					}
				}
				else if (i == 1) { // Pink
					sf::Vector2i pinkTarget = targetPink(Pest, Py, Px);
					if (!homePink) {
						if (Scatter(ghost, 3, 4) && tick <= 60 * 12) {
							moved = true;
						}
						else if (Chase(ghost, pinkTarget.y, pinkTarget.x) && tick > 60 * 12) {
							moved = true;
						}
					}
				}
				else if (i == 2) { // Blue
					if (!homeBlue && Scatter(ghost, 22, 18)) {
						moved = true;
					}
				}
				else if (i == 3) { // Orange
					if (!homeOrange && Scatter(ghost, 22, 2)) {
						moved = true;
					}
				}

				if (moved) {
					ghost.setValidMove(false);
					ghost.update();
				}
			}
		}
		else {
			ghost.update();
		}
	}

	if (tick > 60 * 34) {
		tick = 0;
	}
}

bool GhostManager::Chase2(Ghost& _ghost, int pacmanY, int pacmanX)
{
	float startY = _ghost.getPosition().y / 32;
	float startX = _ghost.getPosition().x / 32;
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
			if (dir != oppositeState) {
				Gestado = dir;
				break;
			}
		}
	}
	else {
		// Lógica existente para moverse hacia el objetivo
		if (Gestado == oppositeState) {
			for (int state : alternativeStates) {
				if (state != oppositeState) {
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
	_ghost.setEstAnt(Gestado);

	return true;
}

void GhostManager::updateChaseMode()
{
	for (int i = 1; i < 3; ++i) {
		Ghost& ghost = _ghosts[i];

		if (ghost.getValidMove()) {
			bool moved = false;
			if (Chase2(ghost, Py, Px)) {
				moved = true;
			}

			if (moved) {
				ghost.setValidMove(false);
				ghost.update();
			}
		}
		else {
			ghost.update();
		}
	}
}
	
void GhostManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (!scene2) {
		for (int i = 0; i < 4; ++i) {
			target.draw(_ghosts[i], states);
		}
	}
	else {
		target.draw(_ghosts[1], states); // Pink
		target.draw(_ghosts[2], states); // Blue
	}
}
