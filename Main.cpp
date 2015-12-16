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
	sf::VideoMode videoMode = sf::VideoMode::getFullscreenModes().at(2);
	sf::RenderWindow window(videoMode, "Hexagon Tile Map");
	std::vector<int> candidates;
	std::vector<Hexagon> hexTileMap = generateHexMatrix(SIZEX, SIZEY, SIDE);
	bool debug = false;
	int lastSide = SIDE;
	int sizeX = SIZEX;
	int sizeY = SIZEY;
	sf::Font f;
	f.loadFromFile("arial.ttf");

	/************** Debug Mode Button and Label *****************/
	sf::CheckButton chk(sf::Vector2f(videoMode.width * 0.75, videoMode.height * 0.1), 15);
	sf::Text debugModeLabel("Debug Mode ", f);
	debugModeLabel.setPosition(videoMode.width * 0.77, videoMode.height * 0.0925);
	debugModeLabel.setCharacterSize(25);
	/************************************************************/

	/************** Zoom Scroll and Label *****************/
	std::vector<std::string> elem; 
	elem.push_back("25");	elem.push_back("50");	elem.push_back("75"); 
	elem.push_back("100");	elem.push_back("150");	elem.push_back("200");
	sf::ScrollBar scroll(sf::Vector2f(videoMode.width * 0.75, videoMode.height * 0.2), sf::Vector2f(120, 20), elem, sf::Orientation::HORIZONTAL);
	scroll.setSelectedIndex(1);
	sf::Text ZoomLabel("Zoom", f);
	ZoomLabel.setPosition(videoMode.width * 0.825, videoMode.height * 0.196);
	ZoomLabel.setColor(sf::Color::White);
	ZoomLabel.setCharacterSize(25);
	/******************************************************/
		
	/************** Add/Delete Row Button and Label *****************/
	sf::Text addRowLabel("Row +", f);
	addRowLabel.setPosition(videoMode.width * 0.78, videoMode.height * 0.296);
	addRowLabel.setColor(sf::Color::White);
	addRowLabel.setCharacterSize(25);
	PlainButton addRowButton(sf::Vector2f(videoMode.width * 0.75, videoMode.height * 0.3), sf::Vector2f(25, 25));
	sf::Text deleteRowLabel("Row -", f);
	deleteRowLabel.setPosition(videoMode.width * 0.78, videoMode.height * 0.346);
	deleteRowLabel.setColor(sf::Color::White);
	deleteRowLabel.setCharacterSize(25);
	PlainButton deleteRowButton(sf::Vector2f(videoMode.width * 0.75, videoMode.height * 0.35), sf::Vector2f(25, 25));
	/****************************************************************/

	/************** Add/Delete Column Button and Label *****************/
	sf::Text addColLabel("Col +", f);
	addColLabel.setPosition(videoMode.width * 0.78, videoMode.height * 0.496);
	addColLabel.setColor(sf::Color::White);
	addColLabel.setCharacterSize(25);
	PlainButton addColButton(sf::Vector2f(videoMode.width * 0.75, videoMode.height * 0.5), sf::Vector2f(25, 25));
	sf::Text deleteColLabel("Col -", f);
	deleteColLabel.setPosition(videoMode.width * 0.78, videoMode.height * 0.546);
	deleteColLabel.setColor(sf::Color::White);
	deleteColLabel.setCharacterSize(25);
	PlainButton deleteColButton(sf::Vector2f(videoMode.width * 0.75, videoMode.height * 0.55), sf::Vector2f(25, 25));
	/*******************************************************************/

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
				else if (addRowButton.isPointInside(pointer)){
					sizeY++;
					hexTileMap = generateHexMatrix(sizeX, sizeY, lastSide);
				}
				else if (deleteRowButton.isPointInside(pointer)){
					sizeY--;
					hexTileMap = generateHexMatrix(sizeX, sizeY, lastSide);
				}
				else if (addColButton.isPointInside(pointer)){
					sizeX++;
					hexTileMap = generateHexMatrix(sizeX, sizeY, lastSide);
				}
				else if (deleteColButton.isPointInside(pointer)){
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
		window.draw(debugModeLabel);
		window.draw(ZoomLabel);
		window.draw(addRowLabel);
		window.draw(deleteRowLabel);
		window.draw(addColLabel);
		window.draw(deleteColLabel);
		addRowButton.draw(&window);
		deleteRowButton.draw(&window);
		addColButton.draw(&window);
		deleteColButton.draw(&window);
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