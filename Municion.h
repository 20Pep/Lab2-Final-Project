#pragma once
#include "SFML/Graphics.hpp"
#include "Player.h"

class Balas : public sf::Drawable, public sf::Transformable 
{
private:
	
	sf::Sprite _sprite;
	sf::Texture _texture;
	float vel = 0;
	
public:
	Balas();
	void bala(float x, float y ,float v);
	void position();
	void update();	
	sf::FloatRect getGlobalBounds() const; //getGlobalBounds tendria que permitir reconocer los huesos que tiene el sprite de bala, no reconoce
	void draw(sf::RenderTarget& target, sf::RenderStates states)const;
};