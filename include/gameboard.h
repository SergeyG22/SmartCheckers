#pragma once
#include <SFML/Graphics.hpp>

class GameBoard: public sf::Drawable {

protected:
	sf::Sprite sprite;
	sf::Texture texture;
public:
	virtual ~GameBoard();
	virtual sf::Sprite getSprite()const = 0;
};
