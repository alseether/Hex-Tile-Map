#include "PlainButton.hpp"


PlainButton::PlainButton(sf::Vector2f position, sf::Vector2f size) :
position(position),
size(size),
box(size)
{
	box.setPosition(position);
	box.setFillColor(sf::Color(127, 127, 127, 255));
	box.setOutlineColor(sf::Color(63, 63, 63, 255));
	box.setOutlineThickness(3);
}


PlainButton::~PlainButton()
{
}


bool PlainButton::isPointInside(sf::Vector2i pointer)
{
	return (pointer.x > position.x) && (pointer.x < position.x + size.x) && (pointer.y > position.y) && (pointer.y < position.y + size.y);
}


void PlainButton::draw(sf::RenderTarget* target)
{
	target->draw(box);
}


void PlainButton::action(void* data)
{
}
