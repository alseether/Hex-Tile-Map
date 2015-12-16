#pragma once

#include <SFML/Graphics.hpp>

class Circumference
{
public:
	Circumference(sf::Vector2f center, float radius);
	~Circumference();
private:
	sf::Vector2f center;
	float radius;
public:
	bool isInside(sf::Vector2f point);

	void draw(sf::RenderTarget* target);
};

