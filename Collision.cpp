#include "Collision.h"
#include "iostream"


bool Collision::CheckCollision(int state, Mapa& _mapa, int posy, int posx)
{
   
      int CurrentPosY = posy / 8; //calcula por cada celda de 8 de logicMap
      int CurrentPosX = posx / 8;


    switch (state)
    {
    case 1:
        if (_mapa.getLogicMap(CurrentPosY -1, CurrentPosX) != 1) { //los -1 y +4 los deje asi pq asi me funco, habria que verlo mejor
            return true;
        }
        
        break;
    case 2:
        if (_mapa.getLogicMap(CurrentPosY +4, CurrentPosX) != 1) {
           return true;
        }
        
        break;
    case 3:
        if (_mapa.getLogicMap(CurrentPosY, CurrentPosX -1) != 1) {
            return true;
        }
        break;
    case 4:
        if (_mapa.getLogicMap(CurrentPosY, CurrentPosX +4) != 1) {
            return true;
        }
        break;
    }

    return false;

}


int Collision::GhostAndPacman(Mapa& _mapa, int posx, int posy, Player& _player, int posY, int posX, int ghost)
{
    bool hunter = _player.getHunter();
    if (posx == posX && posy == posY && hunter) {
        std::cout << "TE COMI ";
        return ghost;
    }
    else if (posx == posX && posy == posY && !hunter)
    {
        return 0;
    }
    return -1;
}

void Collision::ObjCollision(Mapa& _mapa, Player& _player, int posY, int posX)
{
    int CurrentPosY = posY / cell;
    int CurrentPosX = posX / cell;
    int maxim;
    //bool pass = true;
    

    if (_mapa.getMapa(CurrentPosY, CurrentPosX) == 2) {
        contFood++;//cuenta cuanto se comio el pacman
        maxim = contFood;
        if (maxim >= 14) {
           // pass = false;
            std::cout << "Entre" << std::endl;
            origen = false;
           _mapa.Boss();
        }

        _mapa.setMapa(CurrentPosY, CurrentPosX, 0);
        
       
        if (getJefe() == false) {
             
        std::cout << "CAMBIO" << std::endl;
          }
    }
    tick3++;
    if (_mapa.getMapa(CurrentPosY, CurrentPosX) == 3) {
        _mapa.setMapa(CurrentPosY, CurrentPosX, 0);    
        _player.setHunter(true);
        tick3 = 0;
    }
    else if (tick3 >= 60 * 7) {
        _player.setHunter(false);
    
    }
    
}

void Collision::PortalCollision(Mapa& _mapa, Player& _player, int posY, int posX) {


    if (getJefe() != false) { //si getJefe devuelve true entonces estaran los portales de la escena 1 activos
        if (posX == 0 && posY == 384) {
            _player.setPosition(672, 384);

        }
        else if (posX == 704 && posY == 384) {
            _player.setPosition(32, 384);
        }
    }
    else { //en el caso que sea false se desactivaran los portales de la escena 1 para habilitar los de la escena 2

        if (posX <= 0 && posY == 704) {
            _player.setPosition(714, 704);

        }
        else if (posX >= 714 && posY == 704) {
            _player.setPosition(0, 704);
        }
    }
}

void Collision::setAll()
{
    tick3 = 0;
    contFood = 0;
}

int Collision::getJefe() const
{
    return origen;
}









