#include <SFML/Graphics.hpp>
#include "Circumference.hpp"


Circumference::Circumference(sf::Vector2f center, float radius)
{
	this->center = center;
	this->radius = radius;
}


Circumference::~Circumference()
{
}


bool Circumference::isInside(sf::Vector2f point)
{
	if (point.x >= 0 && point.y >= 0){
		float a = (point.x - center.x) * (point.x - center.x);
		float b = (point.y - center.y) * (point.y - center.y);
		return (a + b) < (radius*radius);
	}
	return false;
}

void Circumference::draw(sf::RenderTarget* target)
{
	sf::CircleShape circle(radius);
	circle.setFillColor(sf::Color::Transparent);
	sf::Color color = sf::Color::Color(255, 0, 0, 63);
	circle.setOutlineColor(color);
	circle.setOutlineThickness(1);
	circle.setPosition(center.x-radius, center.y-radius);

	target->draw(circle);

	return;
}
