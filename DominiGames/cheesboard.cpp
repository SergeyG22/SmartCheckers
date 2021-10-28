#include "cheesboard.h"

CheesBoard::CheesBoard() {
	if (!texture.loadFromFile("images/chessboard.png")) {
		std::cout << "file upload error";
	}
	sprite.setTexture(texture);
}

void CheesBoard::draw(sf::RenderTarget& target, sf::RenderStates states)const {
	target.draw(sprite);
}

sf::Sprite CheesBoard::getSprite()const {
	return sprite;
}



