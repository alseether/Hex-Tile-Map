#include "Hexagon.hpp"
#include "CheckButton.hpp"
#include "ScrollBar.hpp"
#include "PlainButton.hpp"
#include "SFML\Graphics.hpp"
#include <iostream>

#define OFFSET 50
#define SIZEX 8
#define SIZEY 6
#define SIDE 50

std::vector<Hexagon> generateHexMatrix(unsigned int sizeX, unsigned int sizeY, unsigned int side){
	std::vector<Hexagon> hexTileMap;
	float h = sqrt((3 * side*side) / 4);
	for (int i = 0; i < sizeY+2; ++i){
		for (int j = 0; j < sizeX+2; ++j){
			sf::Vector2f center;
			if (j % 2 == 0){
				center = sf::Vector2f(OFFSET + (1.5*side*j), OFFSET + (i * 2 * h));
				hexTileMap.push_back(Hexagon(center, side));
			}
			else{
				center = sf::Vector2f(OFFSET + (1.5 * side*j), OFFSET + h + (i * 2 * h));
				hexTileMap.push_back(Hexagon(center, side));
			}
		}
	}
	return hexTileMap;
}

bool isDrawableHexagon(std::vector<Hexagon>* hexTileMap, int sizeX, int sizeY, int i){
	if (i >= sizeX + 2 && i <= (hexTileMap->size() - (sizeX + 2))){
		if ((i % (sizeX + 2) != 0) && (i % (sizeX + 2) != (sizeX + 1))){
			return true;
		}
	}
	return false;
}

void drawSelectedHexagon(sf::RenderTarget* target, std::vector<Hexagon>* hexTileMap, int sizeX, int sizeY, int i, bool debug){
	if (isDrawableHexagon(hexTileMap, sizeX, sizeY, i)){
		hexTileMap->at(i).draw(target, sf::Color::Yellow, debug);
	}
}

void drawLineBetween(sf::RenderTarget* target, std::vector<Hexagon>* hexTileMap, int sizeX, int sizeY, int i, int j){
	sf::VertexArray line(sf::PrimitiveType::Lines, 2);
	std::vector<sf::Vertex> verticesA;
	std::vector<sf::Vertex> verticesB;
	bool draw = false;
	if (isDrawableHexagon(hexTileMap, sizeX, sizeY,i)){
		draw = true;
	}
	if (isDrawableHexagon(hexTileMap, sizeX, sizeY, j)){
		draw = true;
	}
	if (draw){
		verticesA = hexTileMap->at(i).getVertices();
		verticesB = hexTileMap->at(j).getVertices();
		line.clear();
		for (int i = 0; i < 6; ++i){
			for (int j = 0; j < 6; ++j){
				if (int(verticesA[i].position.x) == int(verticesB[j].position.x) && int(verticesA[i].position.y) == int(verticesB[j].position.y)){
					verticesA[i].color = sf::Color::Yellow;
					line.append(verticesA[i]);
					j = 6;
				}
			}
		}
		target->draw(line);
	}
}

void drawPointBetween(sf::RenderTarget* target, std::vector<Hexagon>* hexTileMap, int sizeX, int sizeY, int i, int j, int k){
	sf::CircleShape dot(4);
	std::vector<sf::Vertex> verticesA;
	std::vector<sf::Vertex> verticesB;
	std::vector<sf::Vertex> verticesC;
	verticesA = hexTileMap->at(i).getVertices();
	verticesB = hexTileMap->at(j).getVertices();
	verticesC = hexTileMap->at(k).getVertices();
	for (int i = 0; i < 6; ++i){
		for (int j = 0; j < 6; ++j){
			for (int k = 0; k < 6; ++k){
				if (int(verticesA[i].position.x) == int(verticesB[j].position.x) && int(verticesA[i].position.y) == int(verticesB[j].position.y)){
					if (int(verticesA[i].position.x) == int(verticesC[k].position.x) && int(verticesA[i].position.y) == int(verticesC[k].position.y)){
						sf::Vector2f pos(verticesA[i].position.x - 4, verticesA[i].position.y - 4);
						dot.setPosition(pos);
						dot.setFillColor(sf::Color::Yellow);
						k = 6;
						j = 6;
						i = 6;
					}
				}
			}
		}
	}
	target->draw(dot);
}

int main(){
	sf::RenderWindow window(sf::VideoMode(1000, 800), "Hexagon Tile Map");
	std::vector<int> candidates;
	std::vector<Hexagon> hexTileMap = generateHexMatrix(SIZEX, SIZEY, SIDE);
	bool debug = false;
	int lastSide = SIDE;
	int sizeX = SIZEX;
	int sizeY = SIZEY;
	CheckButton chk(sf::Vector2f(200, 800-89), 15);
	std::vector<std::string> elem; 
	elem.push_back("25");	elem.push_back("50");	elem.push_back("75"); 
	elem.push_back("100");	elem.push_back("150");	elem.push_back("200");
	ScrollBar scroll(sf::Vector2f(400, 800-95), sf::Vector2f(120,20), elem);
	scroll.setSelectedIndex(1);
	sf::Font f;
	f.loadFromFile("arial.ttf");
	sf::Text t("Debug Mode ", f);
	t.setPosition(40, 800 - 100);
	t.setCharacterSize(25);
	sf::Text t2("Side ", f);
	t2.setPosition(400-60, 800 - 100);
	t2.setColor(sf::Color::White);
	t2.setCharacterSize(25);
	sf::Text t3("Rows ", f);
	t3.setPosition(600, 800 - 100);
	t3.setColor(sf::Color::White);
	t3.setCharacterSize(25);
	sf::Text t4("Cols ", f);
	t4.setPosition(600, 800 - 50);
	t4.setColor(sf::Color::White);
	t4.setCharacterSize(25);
	sf::Text t5(" +", f);
	t5.setPosition(680, 800 - 25);
	t5.setColor(sf::Color::White);
	t5.setCharacterSize(25);
	sf::Text t6(" -", f);
	t6.setPosition(720, 800 - 30);
	t6.setColor(sf::Color::White);
	t6.setCharacterSize(25);
	PlainButton b0(sf::Vector2f(680, 800 - 100), sf::Vector2f(25,25));
	PlainButton b1(sf::Vector2f(720, 800 - 100), sf::Vector2f(25, 25));
	PlainButton b2(sf::Vector2f(680, 800 - 50), sf::Vector2f(25, 25));
	PlainButton b3(sf::Vector2f(720, 800 - 50), sf::Vector2f(25, 25));

	std::vector<std::string> vector;
	for (size_t i = 0; i < 100; ++i){
		vector.push_back(std::to_string(i));
	}

	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			switch (event.type){
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				while(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					sf::Vector2i pointer = sf::Mouse::getPosition(window);
					int index = scroll.getIndexFromPointer(pointer);
					if (index != -1){
						scroll.setSelectedIndex(index);
						scroll.draw(&window);
						window.display();
					}
				}
				break;
			case sf::Event::MouseButtonReleased:
				sf::Vector2i pointer = sf::Mouse::getPosition(window);
				if (chk.isPointInside(pointer)){
					chk.toogleMarked();
					debug = chk.isMarked();
				}
				else if (b0.isPointInside(pointer)){
					sizeY++;
					hexTileMap = generateHexMatrix(sizeX, sizeY, lastSide);
				}
				else if (b1.isPointInside(pointer)){
					sizeY--;
					hexTileMap = generateHexMatrix(sizeX, sizeY, lastSide);
				}
				else if (b2.isPointInside(pointer)){
					sizeX++;
					hexTileMap = generateHexMatrix(sizeX, sizeY, lastSide);
				}
				else if (b3.isPointInside(pointer)){
					sizeX--;
					hexTileMap = generateHexMatrix(sizeX, sizeY, lastSide);
				}
				else {
					int index = scroll.getIndexFromPointer(pointer);
					if (index != -1){
						scroll.setSelectedIndex(index);
					}
				}
				break;
			}
		}
		if (std::to_string(lastSide) != scroll.getSeletedElement()){
			lastSide = std::atoi(scroll.getSeletedElement().c_str());
			hexTileMap = generateHexMatrix(sizeX, sizeY, lastSide);
		}

		window.clear();
		window.draw(t);
		window.draw(t2);
		window.draw(t3);
		window.draw(t4);
		window.draw(t5);
		window.draw(t6);
		b0.draw(&window);
		b1.draw(&window);
		b2.draw(&window);
		b3.draw(&window);
		chk.draw(&window);
		scroll.draw(&window);
		for (int i = 0; i < hexTileMap.size(); ++i){
			if (debug)	hexTileMap[i].draw(&window, sf::Color::Green, debug);
			sf::Vector2i pointerInt(sf::Mouse::getPosition(window));
			if (hexTileMap[i].isInOutterCircle(sf::Vector2f(pointerInt.x, pointerInt.y))){
				candidates.push_back(i);
			}
			if (isDrawableHexagon(&hexTileMap, sizeX, sizeY, i)){
				hexTileMap[i].draw(&window, sf::Color::Blue, debug);
			}
			
		}
		if (candidates.size() == 1){
			drawSelectedHexagon(&window, &hexTileMap, sizeX, sizeY, candidates[0], debug);
		}
		else if (candidates.size() == 2){
			drawLineBetween(&window, &hexTileMap, sizeX, sizeY, candidates[0], candidates[1]);
		}
		else if (candidates.size() == 3){
			drawPointBetween(&window, &hexTileMap, sizeX, sizeY, candidates[0], candidates[1], candidates[2]);
		}
		candidates.clear();
		window.display();
	}

		
	return 0;
}