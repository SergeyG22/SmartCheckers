#include "cursor.h"

Cursor::Cursor() {
	rectangle.setSize(sf::Vector2f(75, 75));
	rectangle.setFillColor(sf::Color(252, 3, 67, 100));
	rectangle.setPosition(525, 525);
}

void Cursor::draw(sf::RenderTarget& target, sf::RenderStates states)const {
	target.draw(rectangle);
}

void Cursor::setPosition(int x, int y) {
	rectangle.setPosition(x,y);
}
