#pragma once
#include <SFML/Graphics.hpp>

class Cursor : public sf::Drawable {
	sf::RectangleShape rectangle;
public:
	Cursor();
	void draw(sf::RenderTarget&, sf::RenderStates)const override;
	void setPosition(int,int);
};





