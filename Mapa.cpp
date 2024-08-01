#include "Mapa.h"

Mapa::Mapa() {
    initialMap();
}

void Mapa::initialMap()
{
    float valores[25][23] = {
        {0,8,8,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},//0 32
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},//1
        {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},//2
        {0,1,3,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,3,1,0},//3
        {0,1,2,1,1,2,1,1,1,1,2,1,2,1,1,1,1,2,1,1,2,1,0},//4
        {0,1,2,1,1,2,1,1,1,1,2,1,2,1,1,1,1,2,1,1,2,1,0},//5
        {0,1,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,1,0},//6
        {0,1,2,1,2,1,0,1,0,1,2,2,2,1,0,1,0,1,2,1,2,1,0},//7
        {0,1,2,2,2,1,0,1,0,1,1,1,1,1,0,1,0,1,2,2,2,1,0},//8
        {0,1,1,1,2,1,0,1,0,0,0,1,0,0,0,1,0,1,2,1,1,1,0},//9
        {0,0,0,1,2,0,0,1,1,1,0,1,0,1,1,1,0,0,2,1,0,0,0},//10
        {1,1,1,1,2,1,0,1,0,0,0,0,0,0,0,1,0,1,2,1,1,1,1},//11
        {0,0,0,0,2,1,0,0,0,1,1,0,1,1,0,0,0,1,2,0,0,0,0},//12 //Portales
        {1,1,1,1,2,1,0,1,0,1,0,0,0,1,0,1,0,1,2,1,1,1,1},//13
        {0,0,0,1,2,1,0,1,0,1,1,1,1,1,0,1,0,1,2,1,0,0,0},//14
        {0,1,1,1,2,1,0,1,0,0,0,0,0,0,0,1,0,1,2,1,1,1,0},//15 //Pacman spawn
        {0,1,2,2,2,2,0,0,0,1,1,1,1,1,0,0,0,2,2,2,2,1,0},//16
        {0,1,2,1,1,2,1,1,2,2,2,1,2,2,2,1,1,2,1,1,2,1,0},//17
        {0,1,2,2,1,2,2,2,2,1,2,1,2,1,2,2,2,2,1,2,2,1,0},//18
        {0,1,1,2,1,2,2,1,2,1,2,1,2,1,2,1,2,2,1,2,1,1,0},//19
        {0,1,2,2,2,2,1,1,2,1,2,1,2,1,2,1,1,2,2,2,2,1,0},//20
        {0,1,2,1,1,2,1,1,2,1,2,1,2,1,2,1,1,2,1,1,2,1,0},//21
        {0,1,3,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,3,1,0},//22
        {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},//23
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
        //0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18
    };

    for (int i = 0; i < _altura; ++i) {
        for (int j = 0; j < _ancho; ++j) {
            _mapa[i][j] = valores[i][j];

        }
    }
    for (int ii = 0; ii < 100; ii++) {
        for (int jj = 0; jj < 92; jj++) {
            if (_mapa[ii / 4][jj / 4] == 1) {
                logicmap[ii][jj] = 1;
            }
        }
    }
}

void Mapa::Boss()
{
    float escenario[25][23] = {
        {0,0,0,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0,1,1,1,0,0},
        {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {8,8,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };

    for (int y = 0; y < _altura;y++) {
        for (int x = 0; x < _ancho;x++) {
            _mapa[y][x] = escenario[y][x];
        }
    }
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 92; j++) {
            if (_mapa[i / 4][j / 4] == 1) {
                logicmap[i][j] = 1;
            }
        }
    }

}

void Mapa::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    //Sprite = necesarios para dibujar 1= bordes del mapa, 2= los comestibles, 3= los bonificadores
    //Texture = necesario para que Sprite pueda usar la textura que corresponda a cada numero
    sf::Sprite sp;
    sf::Texture  textu;

    textu.loadFromFile("Recursos/images/Map16.png");
    sp.setTexture(textu);

    sf::Sprite s;
    sf::Texture  t;

    t.loadFromFile("Recursos/images/Heart1.png");
    s.setTexture(t);

    sf::Sprite spp;
    sf::Texture  textur;

    textur.loadFromFile("Recursos/images/heart.png");
    spp.setTexture(textur);

    for (int i = 0; i < _ancho; i++) {
        for (int j = 0; j < _altura; j++) {

           if (_mapa[j][i] == 0) {

           }
           if (_mapa[j][i] == 1) {
               int textura = getRetorno(i,j);
               
               sp.setTextureRect(sf::IntRect(32*textura, 0, cell, cell));
             
               sp.setPosition(i * cell, j * cell);
     
               target.draw(sp,states);

            } 
           if (_mapa[j][i] == 2) { 

               sp.setTextureRect(sf::IntRect(0, cell, cell, cell));
          
               sp.setPosition(i* cell, j* cell );
               target.draw(sp, states);
               
            }
           if (_mapa[j][i] == 3) {

               sp.setTextureRect(sf::IntRect(cell,cell,cell,cell));
               sp.setPosition(i * cell, j * cell);
               target.draw(sp, states);
            }
           if (_mapa[j][i] == 8) {
               spp.setTextureRect(sf::IntRect(0, 0, 32, 32));
               spp.setPosition(i * cell, j * cell);
               target.draw(spp, states);
           }
           
           if (_mapa[j][i] == 9) {
               s.setTextureRect(sf::IntRect(0, 0, 32, 32));
              
               s.setPosition(i * cell, j * cell);
               target.draw(s, states);
           }

        }
    }


}

void Mapa::setMapa(int y, int x, float value)
{
    _mapa[y][x] = value;
}

float Mapa::getMapa(int y, int x)
{
    return _mapa[y][x];
}

int Mapa::getRetorno(int i, int j) const
{
    if (_mapa[j][i]==1) {
        if (_mapa[j][i + 1] != 1 && _mapa[j - 1][i] == 1 && _mapa[j][i - 1] != 1 && _mapa[j + 1][i] == 1) {
            return 9;
        }
        if (_mapa[j][i+1] == 1 && _mapa[j-1][i] == 1 && _mapa[j][i-1] != 1 && _mapa[j+1][i] == 1) {
            return 13;
        }
        
        if (_mapa[j][i + 1] == 1 && _mapa[j - 1][i] == 1 && _mapa[j][i - 1] != 1 && _mapa[j + 1][i] != 1) {
            return 12;
        }
        if (_mapa[j][i + 1] == 1 && _mapa[j - 1][i] != 1 && _mapa[j][i - 1] == 1 && _mapa[j + 1][i] != 1) {
            return 6;
        }
        if (_mapa[j][i + 1] == 1 && _mapa[j - 1][i] != 1 && _mapa[j][i - 1] != 1 && _mapa[j + 1][i] == 1) {
            return 5;
        }
        if (_mapa[j][i + 1] == 1 && _mapa[j - 1][i] != 1 && _mapa[j][i - 1] != 1 && _mapa[j + 1][i] != 1) {
            return 4;
        }
        if (_mapa[j][i + 1] != 1 && _mapa[j - 1][i] != 1 && _mapa[j][i - 1] != 1 && _mapa[j + 1][i] == 1) {
            return 1;
        }
        if (_mapa[j][i + 1] != 1 && _mapa[j - 1][i] != 1 && _mapa[j][i - 1] == 1 && _mapa[j + 1][i] != 1) {
            return 2;
        }
        if (_mapa[j][i + 1] != 1 && _mapa[j - 1][i] == 1 && _mapa[j][i - 1] == 1 && _mapa[j + 1][i] != 1) {
            return 10;
        }
        if (_mapa[j][i + 1] != 1 && _mapa[j - 1][i] == 1 && _mapa[j][i - 1] != 1 && _mapa[j + 1][i] != 1) {
            return 8;
        }
        if (_mapa[j][i + 1] == 1 && _mapa[j - 1][i] != 1 && _mapa[j][i - 1] == 1 && _mapa[j + 1][i] == 1) {
            return 7;
        }
        if (_mapa[j][i + 1] != 1 && _mapa[j - 1][i] != 1 && _mapa[j][i - 1] == 1 && _mapa[j + 1][i] == 1) {
            return 3;
        }
        if (_mapa[j][i + 1] == 1 && _mapa[j - 1][i] == 1 && _mapa[j][i - 1] == 1 && _mapa[j + 1][i] != 1) {
            return 14;
        }
        if (_mapa[j][i + 1] != 1 && _mapa[j - 1][i] == 1 && _mapa[j][i - 1] == 1 && _mapa[j + 1][i] == 1) {
            return 11;
        }

        

    }
    return 0;
}


int Mapa::getLogicMap(int y, int x)
{
    return logicmap[y][x];
}

