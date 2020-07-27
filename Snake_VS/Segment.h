#ifndef SEGMENT_H
#define SEGMENT_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <thread>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Constants.h"



class Segment {
private:
	int x, y, type; //types: 0 - plain, 1 - obstacle, 2 - snake, 3 - fruit
	sf::RectangleShape segment_unit;
public:
	Segment();
	sf::RectangleShape getSegment_unit();
	sf::Color getUnitColor();
	int getXPosition();
	int getYPosition();
	int getType();
	void setType(int type);
	void setSize(int seg_size);
	void setBorderColor(sf::Color color);
	void setUnitColor(sf::Color color);
	void setBorderThick(int thickness);
	void setPosition(int x_val, int y_val);

};

#endif



