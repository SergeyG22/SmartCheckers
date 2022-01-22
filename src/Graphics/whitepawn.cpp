#include "../../include/whitepawn.h"

WhitePawn::WhitePawn(sf::Vector2f position):pos(position) {
	if (!texture.loadFromFile("../resource/images/white_pawn.png")) {
		std::cout << "file upload error";
	}
	sprite.setTexture(texture);
	sprite.setPosition(pos);
}

void WhitePawn::draw(sf::RenderTarget& target, sf::RenderStates states)const {
	target.draw(sprite);
}

sf::Sprite WhitePawn::getSprite()const {
	return sprite;
}

void WhitePawn::activate() {       //активировать фигуру
	activity = true;
}

void WhitePawn::deactivate() {     //деактивировать фигуру
	activity = false;
}

bool WhitePawn::isActive()const {  //проверить активность
	return activity;
}

bool WhitePawn::move(sf::Event& event, TruthValueField& truth_value_field) {

	if (event.type == sf::Event::KeyPressed) {        
		if (sf::Keyboard::Key::W == event.key.code) {
			if (sprite.getPosition().y >= 75) {                                                              //если не вышла за пределы экрана
				if (truth_value_field.getFlag(sprite.getPosition().x, sprite.getPosition().y - 75)) {        //и нет препятвия в соседней клетке
					truth_value_field.setFlag(sprite.getPosition().x, sprite.getPosition().y - 75, false);   //то в эту клетку устанавливаем false
					truth_value_field.setFlag(sprite.getPosition().x, sprite.getPosition().y, true);         //а в пред идущую true
					sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - 75);                 //перемещаем фигуру
					return true;                                                                             //вернув true сообщаем al, что наш ход закончен
				}
			}
		}
		if (sf::Keyboard::Key::A == event.key.code) {
			if (sprite.getPosition().x > 0) {                                                                //аналогично
				if (truth_value_field.getFlag(sprite.getPosition().x - 75, sprite.getPosition().y)) {
					truth_value_field.setFlag(sprite.getPosition().x - 75, sprite.getPosition().y, false);
					truth_value_field.setFlag(sprite.getPosition().x, sprite.getPosition().y, true);
					sprite.setPosition(sprite.getPosition().x - 75, sprite.getPosition().y);
					return true;
				}
			}
		}
		if (sf::Keyboard::Key::D == event.key.code) {
			if (sprite.getPosition().x <= 450) {															 //аналогично
				if (truth_value_field.getFlag(sprite.getPosition().x + 75, sprite.getPosition().y)) {
					truth_value_field.setFlag(sprite.getPosition().x + 75, sprite.getPosition().y, false);
					truth_value_field.setFlag(sprite.getPosition().x, sprite.getPosition().y, true);
					sprite.setPosition(sprite.getPosition().x + 75, sprite.getPosition().y);
					return true;
				}
			}
		}
		if (sf::Keyboard::Key::S == event.key.code) {
			if (sprite.getPosition().y <= 450) {															//аналогично
				if (truth_value_field.getFlag(sprite.getPosition().x, sprite.getPosition().y + 75)) {
					truth_value_field.setFlag(sprite.getPosition().x, sprite.getPosition().y + 75, false);
					truth_value_field.setFlag(sprite.getPosition().x, sprite.getPosition().y, true);
					sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 75);
					return true;
				}
			}
		}
	}
	return false;
}