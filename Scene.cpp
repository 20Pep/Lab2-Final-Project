#include "Scene.h"
#include "iostream"

//FANTASMAS 1 = ROJO | 2 = ROSA | 3 = AZUL | 4 = NARANJA
Scene::Scene()
{
	_player.setPosition(352, 480);
	_vidas.setVidas(3);
	pause = 0;
	nombre = false;
	isPlaying = true;
	cont = 0;
	banderaScared = false;
	ticktest = 0;
}

void Scene::update() 
{	
	if (pause == 0) {
		ticktest++;
		if (ticktest % 60 == 0) {
			std::cout << ticktest / 60 << "  ";
		}
		if (_collision.getJefe() == true && ticktest > 60) { //Escena 1
		//	_player.SoloX(_collision.getJefe());
			
			int IsAlive[4];
			for (int i = 1; i <= 4; i++) {
				IsAlive[i - 1] = _collision.GhostAndPacman(_mapa, _ghostManager.GetPosX(i), _ghostManager.GetPosY(i), _player, _player.getPosition().y, _player.getPosition().x, i, _ghostManager.getBounds(i));
				if (IsAlive[i - 1] == 0) {
					_vidas.setVidas(_vidas.getVidas() - 1);
					_mapa.setMapa(0, _vidas.getVidas() + 1, 0);
					pause = 3 * 60;
					if (_vidas.getVidas() == 0) isPlaying = false;
					setScene();
					break;
				}
				else if (IsAlive[i - 1] > 0) { // pacman comio 
					_ghostManager.returnHome(i);
				}
			}

			if (_player.getEstado() != 0) {
				_ghostManager.setPest(_player.getEstado());
			}

			_collision.ObjCollision(_mapa, _player, _player.getPosition().y, _player.getPosition().x);
			_collision.PortalCollision(_mapa, _player, _player.getPosition().y, _player.getPosition().x);
			if (_player.getHunter()) { // fantasmas asustados
				if (banderaScared == false) { 
					_ghostManager.setScared(true);
					banderaScared = true;
				}
			}
			else {
				_ghostManager.setScared(false);
				banderaScared = false;
			}

			bool canMove;
            _player.handleInput(_player.getPosition().y, _player.getPosition().x);

            if (_player.getValidMove()) {
            int estado = _player.actualState();
            canMove = _collision.CheckCollision(estado, _mapa, _player.getPosition().y, _player.getPosition().x);
            if (!canMove) {
            _player.setEstado(_player.getAntEstado());
            } }
			else {
				canMove = true;
			}

			_ghostManager.setPacman(_player.getPosition().y, _player.getPosition().x);
			_ghostManager.update();

			if (canMove) {
				_player.update();
				
			}
			//else {
			//	_player.setEstado(0); // Resetea el estado si no puede moverse
			//}
		}
		else if(_collision.getJefe() == false) { // Escena 2
			if (ticktest > 60) {
				scene2();
				//setScene2();
			}
			else if (ticktest == 60) {
				std::cout << "START FINAL FIGHT" << std::endl;
			}
		}
	}
	else if (ticktest == 60) {
		std::cout << "START YOUR ADVENTURE" << std::endl;
	}
	else {
		pause--;
	}
}

void Scene::scene2()
{
	if (!nombre) { 
		nombre = true;
		setScene2();
	}
	//_player.SoloX(true); // Si .SoloX(False) entonces se activa el movimiento solo en el eje x
	//bool canMove;
	_player.handleInput2();
	

	/*if (_player.getValidMove()) {
		
		canMove = _collision.CheckCollision(estado, _mapa, _player.getPosition().y, _player.getPosition().x);
		if (!canMove) {
			_player.setEstado(_player.getAntEstado());
		}
	}
	else {
		canMove = true;
	}*/
	
	//_collision.PortalCollision(_mapa, _player, _player.getPosition().y, _player.getPosition().x); // portal donde el pacman se teletransporta del borde izuiquierdo hacia el borde derecho y viceversa
	_collision.ObjCollision(_mapa, _player, _player.getPosition().y, _player.getPosition().x);
	if (nombre) {
		cont--; // contador que permite la movilidad del fantasma
		if (cont > -100) {
			cont = -10;
		}
	}

    if (_player.Shoot()) {
        _balas.bala(_player.getPosition().x, _player.getPosition().y, cont);
    } else {
        cont = 0;
    } 

    if (_boss.CheckCollision(_balas) && _player.getIsContactShot() == false) { //Collision entre el boss y las balas
		_player.setIsContactShot(true);
		_balas.position();
        _boss.setvida(_boss.getvida() - 1);
        _mapa.setMapa(0, _boss.getvida() + 3, 0);
        if (_boss.getvida() == 0) isPlaying = false;
    }
	_collision.Scene2Bounds(_mapa, _player, _player.getPosition().y, _player.getPosition().x);
	_mapa.updateItem();
	_balas.update();
	_boss.update();
	/*if (canMove) {*/
		_player.update();
	/*}*/
}

void Scene::setScene()
{
	_player.setPosition(352, 480);
	_player.ResetPlayer();
	_ghostManager.setAll();
	ticktest = 0;
}

void Scene::setScene2()
{
	_player.ResetPlayer();
	_player.setPosition(352, 704);
	_boss.resetAll();
	_balas.position();
	ticktest = 0;
}

void Scene::ResetAll()
{
	_player.setPosition(352, 480);
	_player.ResetPlayer();
	_vidas.setVidas(3);
	nombre = false;
	_ghostManager.setAll();
	_mapa.initialMap();
	_collision.setAll();
	banderaScared = false;
	ticktest = 0;
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
		target.draw(_ghostManager, states);
	}
	else {
		target.draw(_mapa, states);
		target.draw(_player, states);
		target.draw(_balas, states);
		target.draw(_boss, states);
	}	
	
}
