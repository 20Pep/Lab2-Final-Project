#include "Collision.h"
#include "iostream"

//Manejo de colisiones

bool Collision::CheckCollision(int state, Mapa& _mapa, int posy, int posx)
{   
     int CurrentPosY = posy / 32; //calcula por cada celda de 8 de logicMap
     int CurrentPosX = posx / 32;

    switch (state)
    {
    case 1:
        if (_mapa.getMapa(CurrentPosY -1, CurrentPosX) != 1) { 
            return true;
        }
        
        break;
    case 2:
        if (_mapa.getMapa(CurrentPosY +1, CurrentPosX) != 1) {
           return true;
        }
        
        break;
    case 3:
        if (_mapa.getMapa(CurrentPosY, CurrentPosX -1) != 1) {
            return true;
        }
        break;
    case 4:
        if (_mapa.getMapa(CurrentPosY, CurrentPosX +1) != 1) {
            return true;
        }
        break;
    }
    return false;
}



int Collision::GhostAndPacman(Mapa& _mapa, int posx, int posy, Player& _player, int posY, int posX, int ghost, sf::FloatRect o)
{
    bool hunter = _player.getHunter();
    
    if (_player.returnBounds().intersects(o) && hunter) {
        std::cout << "TE COMI ";
        return ghost;
    }
    else if (_player.returnBounds().intersects(o) && !hunter)
    {
        return 0;
    }
    return -1;
}

void Collision::Scene2Bounds(Mapa& _mapa, Player& _player, int posY, int posX)
{
    if (posX <= 0 ) {
        _player.setPosition(0, posY); // Mantener en el borde izquierdo
    }
    else if (posX >= 704 ) {
        _player.setPosition(704, posY); // Mantener en el borde derecho
    }
    else if (posY >= 768) {
        _player.setPosition(posX, 768); // Mantener en el borde inferior
    }
	else if (posY <= 640) {
		_player.setPosition(posX, 640); // Mantener en el borde superior
	}
}


void Collision::ObjCollision(Mapa& _mapa, Player& _player, int posY, int posX)
{
    int currentPosY = posY / cell;
    int currentPosX = posX / cell;
    int foodGoal;
 
    if (_mapa.getMapa(currentPosY, currentPosX) == 2) {
        contFood++;//cuenta cuanto se comio el pacman
        foodGoal = contFood;
        if (foodGoal >= 1) {//151
            origen = false;
            _mapa.Boss();
            std::cout << "CAMBIO" << std::endl;
        }
        _mapa.setMapa(currentPosY, currentPosX, 0);
    }
    energizerTick++;
    if (_mapa.getMapa(currentPosY, currentPosX) == 3) {
        _mapa.setMapa(currentPosY, currentPosX, 0);    
        _player.setHunter(true);
		if(origen == false)_player.setCanShoot(true);
        energizerTick = 0;
    }
    else if (energizerTick >= (60 * 10)) {
        _player.setHunter(false);
    }
}

void Collision::PortalCollision(Mapa& _mapa, Player& _player, int posY, int posX) {


    /*if (getJefe() != false) {*/ //si getJefe devuelve true entonces estaran los portales de la escena 1 activos
        if (posX == 0 && posY == 384) {
            _player.setPosition(672, 384);

        }
        else if (posX == 704 && posY == 384) {
            _player.setPosition(32, 384);
        }
    //}
    //else { //en el caso que sea false se desactivaran los portales de la escena 1 para habilitar los de la escena 2

    //    if (posX <= 0 && posY == 704) {
    //        _player.setPosition(714, 704);

    //    }
    //    else if (posX >= 714 && posY == 704) {
    //        _player.setPosition(0, 704);
    //    }
    //}
}

void Collision::setAll()
{
    energizerTick = 0;
    contFood = 0;
    origen = true;
}

int Collision::getJefe() const 
{
    return origen;
}










