#include "Boss.h"
#include "iostream"

//Maneja al jefe final

Boss::Boss()
{
	_texture.loadFromFile("Recursos/images/Ghost16.png");
	_sprite.setTexture(_texture);
	_sprite.setTextureRect(sf::IntRect(0, 0, 29, 30));
	_sprite.setColor(sf::Color::Red);
	_sprite.setScale(10, 10);
	_sprite.setPosition(0, 100);
	
	
	estado = 1;
    _tick = 0.0f;
    _sprite.setPosition(position);
    position = sf::Vector2f(0, 100);   
    _vida = 15;

    updateHitbox();
}

void Boss::resetAll()
{
   
	estado = 1;
    _tick = 0.0f;
    _sprite.setPosition(position);
    _sprite.setPosition(0, 100);
    position = sf::Vector2f(0, 100);   
    _vida = 15;

    updateHitbox();
}

void Boss::update()
{
    const float LEFT_BOUNDARY = 0;
    const float RIGHT_BOUNDARY = 452;
    const float SPEED = 18;

    _tick++; // Increment the tick counter

    if (_tick >= 5) { // Update every 5 ticks
        if (estado == 0) { // Move right
            position.x += SPEED;
            if (position.x >= RIGHT_BOUNDARY) {
                estado = 1; // Change direction to left
                position.x = RIGHT_BOUNDARY; // Ensure it doesn't exceed the boundary
            }
        }
        else { // Move left
            position.x -= SPEED;
            if (position.x <= LEFT_BOUNDARY) {
                estado = 0; // Change direction to right
                position.x = LEFT_BOUNDARY; // Ensure it doesn't exceed the boundary
            }
        }
        // Update the sprite's position to match the Boss position
        _sprite.setPosition(position);
        _tick = 0; // Reset the tick counter
    }
    // Update the hitbox
    updateHitbox();
}

bool Boss::CheckCollision(const Balas& bala) //esto deberia estar en collision.cpp
{
	return _hitbox.intersects(bala.getGlobalBounds());
}

void Boss::updateHitbox()
{
	_hitbox = _sprite.getGlobalBounds();
}

void Boss::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	states.transform *= getTransform();
	target.draw(_sprite, states);
}

void Boss::setvida(int vida) //esto posiblemnte deberia estar en vida.cpp
{
    _vida = vida;
}

int Boss::getvida()
{
    return _vida;
}
