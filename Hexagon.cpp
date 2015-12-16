#include "Hexagon.hpp"
#include <math.h>

#define EXTRA(l) 0.2*l	// A 20% will be added in order to set the outter circumference


Hexagon::Hexagon(sf::Vector2f center, float side) :
center(center),
outter(center,side + EXTRA(side))	// (side + side*0.2) is the outter circumference radius
{
	this->side = side;
	h = sqrt((3*side*side)/4);	
	vertices.push_back(sf::Vertex(sf::Vector2f(center.x - side, center.y)));			// left vertex
	vertices.push_back(sf::Vertex(sf::Vector2f(center.x - side / 2, center.y - h)));	// up-left vertex
	vertices.push_back(sf::Vertex(sf::Vector2f(center.x + side / 2, center.y - h)));	// up-right vertex
	vertices.push_back(sf::Vertex(sf::Vector2f(center.x + side, center.y)));			// right vertex
	vertices.push_back(sf::Vertex(sf::Vector2f(center.x + side / 2, center.y + h)));	// down-right vertex
	vertices.push_back(sf::Vertex(sf::Vector2f(center.x - side / 2, center.y + h)));	// down-left vertex
}


Hexagon::~Hexagon()
{
}


bool Hexagon::isInOutterCircle(sf::Vector2f point)
{
	return outter.isInside(point);
}

void Hexagon::draw(sf::RenderTarget* target, sf::Color color, bool debug)
{
	sf::VertexArray temp(sf::PrimitiveType::Lines);

	temp.append(this->vertices[0]);		// up-left border	(/)
	temp.append(this->vertices[1]);

	temp.append(this->vertices[1]);		// upper border	(-)
	temp.append(this->vertices[2]);

	temp.append(this->vertices[2]);		// up-right border (\)
	temp.append(this->vertices[3]);

	temp.append(this->vertices[3]);		// down-right border (/)
	temp.append(this->vertices[4]);

	temp.append(this->vertices[4]);		// down border	(_)
	temp.append(this->vertices[5]);

	temp.append(this->vertices[5]);		// down-left border(\)
	temp.append(this->vertices[0]);

	for (int i = 0; i < temp.getVertexCount(); ++i){
		temp[i].color = color;
	}

	target->draw(temp);
	

	if (debug)	outter.draw(target);
}

std::vector<sf::Vertex> Hexagon::getVertices(){
	return this->vertices;
}