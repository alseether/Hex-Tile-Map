#pragma once
#include "SFML\Graphics.hpp">

class PlainButton
{
public:
	PlainButton(sf::Vector2f position, sf::Vector2f size);
	~PlainButton();
private:
	sf::Vector2f position;
	sf::Vector2f size;
	sf::RectangleShape box;
public:
	bool isPointInside(sf::Vector2i pointer);
	void draw(sf::RenderTarget* target);
	void action(void* data);
};

