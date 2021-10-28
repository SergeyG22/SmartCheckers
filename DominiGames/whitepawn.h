#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "figure.h"
#include "truthvaluefield.h"

class WhitePawn: public Figure {
	sf::Vector2f pos;
	bool activity = false;
public:
	WhitePawn(sf::Vector2f);
	virtual void draw(sf::RenderTarget&, sf::RenderStates)const;
	sf::Sprite getSprite()const override;
	bool move(sf::Event&, TruthValueField&) override;
	void deactivate()override;
	void activate()override;             	
	bool isActive() const override;
};


