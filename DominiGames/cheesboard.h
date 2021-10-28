#pragma once
#include "gameboard.h"
#include <iostream>

class CheesBoard: public GameBoard {

public:
	CheesBoard();
	virtual void draw(sf::RenderTarget&, sf::RenderStates)const;
	sf::Sprite getSprite()const override;
};
