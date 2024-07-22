#include "Municion.h"
#include <iostream>

Balas::Balas()
{
	_texture.loadFromFile("Recursos/images/Map16.png");
	_sprite.setTexture(_texture);
	_sprite.setTextureRect(sf::IntRect(96, 32, 32, 32));
	setPosition(354, -20);
}

void Balas::bala(float x, float y, float v)
{
	setPosition(x, y);

	vel = v;
}
void Balas::update()
{
	move(0, vel);
}
sf::FloatRect Balas::getGlobalBounds() const
{
	return getTransform().transformRect(_sprite.getGlobalBounds());
}



void Balas::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	
	states.transform *= getTransform();
	target.draw(_sprite, states);
}

