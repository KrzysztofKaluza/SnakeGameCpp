#include "Segment.h"

Segment::Segment() {
	segment_unit.setSize(sf::Vector2f(segment_size, segment_size));
	segment_unit.setFillColor(sf::Color::Green);
	this->x = 1;
	this->y = 1;
}

sf::RectangleShape Segment::getSegment_unit() {
	return segment_unit;
}

sf::Color Segment::getUnitColor() {
	return this->segment_unit.getFillColor();
}

int Segment::getXPosition() {
	return x;
}

int Segment::getYPosition() {
	return y;
}

int Segment::getType() {
	return type;
}

void Segment::setType(int type) {
	this->type = type;
}

void Segment::setSize(int seg_size) {
	this->segment_unit.setSize(sf::Vector2f(seg_size, seg_size));
}

void Segment::setBorderColor(sf::Color color) {
	this->segment_unit.setOutlineColor(color);
}

void Segment::setUnitColor(sf::Color color) {
	this->segment_unit.setFillColor(color);
}

void Segment::setBorderThick(int thickness) {
	this->segment_unit.setOutlineThickness(thickness);
}

void Segment::setPosition(int x_val, int y_val) {
	this->x = x_val;
	this->y = y_val;
	this->segment_unit.setPosition(x*segment_size, y*segment_size);
}
