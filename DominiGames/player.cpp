#include "player.h"

std::vector<Figure*> Player::getFigures() {
	return white_pawn;
}

std::vector<sf::Vector2f> Player::getEndCoordinates()const {
	return end_coordinates;
}
