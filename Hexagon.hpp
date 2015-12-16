#pragma once

#include <SFML\Graphics.hpp>
#include "Circumference.hpp"

class Hexagon
{
public:
	Hexagon(sf::Vector2f center, float side);
	~Hexagon();
private:
	sf::Vector2f center;
	float h;
	float side;
	std::vector<sf::Vertex> vertices;
	Circumference outter;
public:
	std::vector<sf::Vertex> getVertices();
	bool isInOutterCircle(sf::Vector2f point);
	void draw(sf::RenderTarget* target, sf::Color color, bool debug);
	
};

