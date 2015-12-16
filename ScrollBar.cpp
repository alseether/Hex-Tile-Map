#include "ScrollBar.hpp"


namespace sf{
	ScrollBar::ScrollBar(sf::Vector2f position, sf::Vector2f size, std::vector<std::string> elements, sf::Orientation orientation) :
		position(position),
		size(size),
		elements(elements),
		cursor(sf::Vector2f(CURSOR_WIDTH, size.y + 4)),
		box(size)
	{
		textBox.setFillColor(sf::Color::Black);
		box.setFillColor(sf::Color(63, 63, 63, 255));
		box.setOutlineColor(sf::Color::Black);
		box.setOutlineThickness(4);
		cursor.setPosition(position);
		cursor.setFillColor(sf::Color(127, 127, 127, 255));
		selectedIndex = 0;
		steps = elements.size();
		this->orientation = orientation;
		if (orientation == sf::Orientation::HORIZONTAL){
			textBox.setSize(sf::Vector2f(size.x*1.1, 20));
			box.setPosition(sf::Vector2f(position.x, position.y + 2));
			stepSize = size.x / steps;
			cursor.setSize(sf::Vector2f(stepSize, size.y + 4));
		}
		else{
			textBox.setSize(sf::Vector2f(20, size.y*1.1));
			box.setPosition(sf::Vector2f(position.x + 2, position.y));
			stepSize = size.y / steps;
			cursor.setSize(sf::Vector2f(size.x + 4, stepSize));
		}
		f.loadFromFile("arial.ttf");
	}


	ScrollBar::~ScrollBar()
	{
	}


	std::string ScrollBar::getSeletedElement()
	{
		return elements[selectedIndex];
	}


	int ScrollBar::getSelectedIndex()
	{
		return selectedIndex;
	}


	int ScrollBar::getIndexFromPointer(sf::Vector2i pointer)
	{
		if ((pointer.y > position.y) && (pointer.y < (position.y + size.y)) && (pointer.x > position.x) && (pointer.x < (position.x + size.x))){
			if (orientation == sf::Orientation::HORIZONTAL){
				for (size_t i = 0; i < steps; ++i){
					if (pointer.x > position.x + stepSize*i && pointer.x < position.x + stepSize*(i + 1)){
						return i;
					}
				}
				return -1;
			}
			else{
				for (size_t i = 0; i < steps; ++i){
					if (pointer.y > position.y + stepSize*i && pointer.y < position.y + stepSize*(i + 1)){
						return i;
					}
				}
			}
			return -1;
		}
		return -1;
	}

	void ScrollBar::setSelectedIndex(int index){
		selectedIndex = index;
	}

	void ScrollBar::draw(sf::RenderTarget* target){
		sf::Text t(elements[selectedIndex], f);
		target->draw(box);
		if (orientation == sf::Orientation::HORIZONTAL){
			sf::Vector2f pos(position.x + stepSize*selectedIndex, position.y);
			cursor.setPosition(pos);
			pos.y = pos.y + cursor.getSize().y;
			textBox.setPosition(sf::Vector2f(position.x, pos.y));
			t.setPosition(pos);
		}
		else
		{
			sf::Vector2f pos(position.x, position.y + stepSize*selectedIndex);
			cursor.setPosition(pos);
			pos.x = pos.x + cursor.getSize().x;
			textBox.setPosition(sf::Vector2f(pos.x, position.y));
			t.setPosition(pos);
		}
		t.setCharacterSize(15);
		target->draw(textBox);
		target->draw(cursor);
		target->draw(t);
	}
}
