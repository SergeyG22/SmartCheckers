#pragma once
#include <SFML/Graphics.hpp>
#include "truthvaluefield.h"

class Figure: public sf::Drawable {

protected:
	sf::Sprite sprite;
	sf::Texture texture;
public:
	virtual ~Figure() { }
	virtual sf::Sprite getSprite()const = 0;
	virtual bool move(sf::Event&, TruthValueField&) { return false; };
	virtual void activate() { };
	virtual void deactivate() { };
	virtual bool isActive()const { return false; };
	virtual bool isEnable()const { return false; };
	virtual void disable() { };
};

