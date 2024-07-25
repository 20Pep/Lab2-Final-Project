#include "Scene.h"
#include "iostream"

//FANTASMAS 1 = ROJO | 2 = ROSA | 3 = AZUL | 4 = NARANJA
Scene::Scene()
{
	_player.setPosition(352, 480);
	_vidas.setVidas(3);
	
	pause = 0;
	//_tickmoveG = 0;
	 nombre = false;
	 isPlaying = true;
	 cont = 0;
}

void Scene::update() 
{	
	if (pause == 0) {
		if (_collision.getJefe() != false) { //Escena 1
			_player.SoloX(_collision.getJefe());

			if (_player.getEstado() != 0) {
				_manager.setPest(_player.getEstado());
			}


			_collision.ObjCollision(_mapa, _player, _player.getPosition().y, _player.getPosition().x);
			_collision.PortalCollision(_mapa, _player, _player.getPosition().y, _player.getPosition().x);

			int IsAlive[4];
			for (int i = 1; i <= 4; i++) {
				IsAlive[i - 1] = _collision.GhostAndPacman(_mapa, _manager.GetPosX(i), _manager.GetPosY(i), _player, _player.getPosition().y, _player.getPosition().x, i);
				if (IsAlive[i - 1] == 0) {
					_vidas.setVidas(_vidas.getVidas() - 1);
					_mapa.setMapa(0, _vidas.getVidas() + 1, 0);
					pause = 3 * 60;
					if (_vidas.getVidas() == 0) isPlaying = false;
					setScene();
					break;
				}
				else if (IsAlive[i - 1] > 0) { // pacman comio 
					_manager.returnHome(i);
				}
			}


			if (_player.getHunter()) {
				_manager.setScared(true);
			}
			else {
				_manager.setScared(false);
			}
			bool canMove;
			if (_player.getValidMove()) {
				int estado = _player.actualState();
				canMove = _collision.CheckCollision(estado, _mapa, _player.getPosition().y, _player.getPosition().x);
			}
			else {
				canMove = true;
			}
			_manager.setPacman(_player.getPosition().y, _player.getPosition().x);
			
			_manager.update();

			if (canMove) {
				_player.update();
				
			}
			else {
				_player.setEstado(0); // Resetea el estado si no puede moverse
			}

		}
		else { // Escena 2

			scene2();
		}
	}
	else {
		pause--;
	}

}

void Scene::scene2()
{
	_player.SoloX(_collision.getJefe());// Si .SoloX(False) entonces se activa el movimiento solo en el eje x
	int estado = _player.actualState();
	bool canMove = _collision.CheckCollision(estado, _mapa, _player.getPosition().y, _player.getPosition().x);
	if (canMove) {
		_player.update();

	}
	else if (nombre == false) { //el bool nombre actua como una bandera para setear la posicion el pacman en la escena 2
		nombre = true;
		_player.setPosition(354, 704);//setea la posicion inicial del pacman para la escena 2
	}
	else if (nombre != false) {

		_player.update();
	}
	else {
		_player.setEstado(0); // Resetea el estado si no puede moverse
	}

	_collision.PortalCollision(_mapa, _player, _player.getPosition().y, _player.getPosition().x); //portal donde el pacman se teletransporta del borde izuiquierdo hacia el borde derecho y viceversa
	
	if (nombre != false) {
		cont--;//contador que permite la movilidad del fantasma
		if (cont > -100) {
			cont = -10;
			//std::cout <<"X: " << _boss.getPosition().x << std::endl;
		}
	}

	if (_player.Shoot()) {
		_balas.bala(_player.getPosition().x, _player.getPosition().y, cont);
	}
	else {
		cont = 0;
	}
	_balas.update();
	_balas.update();
	_boss.update();

	if (_boss.CheckCollision(_balas)) {
		std::cout << "Colisión detectada!" << std::endl; //17
		_boss.setvida(_boss.getvida() - 1);
		_mapa.setMapa(0, _boss.getvida() + 1, 0);
	
		if (_boss.getvida() == 0) isPlaying = false;
		
	
		// Añade aquí la lógica para manejar la colisión
	}

	

}

void Scene::setScene()
{
	_player.setPosition(352, 480);
	_manager.setAll();
	//_player.setTickMove(0);
	//_tickmoveG = 0;
}

void Scene::ResetAll()
{
	_player.setPosition(352, 480);
	//_player.setTickMove(0);
	_vidas.setVidas(3);
	//_tickmoveG = 0;
	nombre = false;
	_manager.setAll();
	_mapa.initialMap();
	_collision.setAll();

}

bool Scene::getIsPlaying()
{
	return isPlaying;
}

void Scene::setIsPlaying()
{
	isPlaying = true;
}


void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (_collision.getJefe() != false) {
		target.draw(_mapa, states);
		target.draw(_player, states);
		target.draw(_manager, states);
	}
	else {
		target.draw(_mapa, states);
		target.draw(_player, states);
		target.draw(_balas, states);
		target.draw(_boss, states);
	}	
	
}






