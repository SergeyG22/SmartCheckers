#include "../../include/blackpawn.h"

BlackPawn::BlackPawn(sf::Vector2f position) :pos{position} {
	if (!texture.loadFromFile("../resource/images/black_pawn.png")) {
		std::cout << "file upload error";
	}
	sprite.setTexture(texture);
	sprite.setPosition(pos);
}

void BlackPawn::draw(sf::RenderTarget& target, sf::RenderStates states)const {
	target.draw(sprite);
}

sf::Sprite BlackPawn::getSprite()const {  //получить спрайт
	return sprite;
}

void BlackPawn::activate() {              //активировать фигуру
    activity = true;
}

void BlackPawn::deactivate() {           //деактивировать фигуру
    activity = false;
}

bool BlackPawn::isActive()const {        //текущее состояние активности
    return activity;
}

void BlackPawn::disable() {              //отключить фигуру
    enable = false;
}

bool BlackPawn::isEnable()const {        //вернуть состояние
    return enable;
}


bool BlackPawn::move(sf::Event& event, TruthValueField& truth_value_field) {
        if (sprite.getPosition().y >= 75) {
            if (truth_value_field.getFlag(sprite.getPosition().x, sprite.getPosition().y - 75)) {    //w (движение вверх)
                              
                if (sprite.getPosition().y > end_point.y) {
                    int x = sprite.getPosition().x;
                    int y = sprite.getPosition().y;
                    truth_value_field.setFlag(x, y - 75, false);
                    truth_value_field.setFlag(x, y, true);
                    sprite.setPosition(x, y - 75);
            
                    if (enteringOpponentSquare(sprite)) {                                         //если фигура вошла в квадрат 3x3 правого нижнего угла
                        if (coordinatePrioritySquare(truth_value_field) != sf::Vector2i(0, 0)) {  //и обнаруживает свободные координаты                                                    //[][][]
                            end_point = coordinatePrioritySquare(truth_value_field);              //найти свободную точку внутреннего квадрата 2x2 правого нижнего угла                    //[] # #
                        }                                                                         //и присвоить ее текущей фигуре                                                          //[] # #
                        else {                         
                            end_point = coordinateOuterSquare(truth_value_field);                 //если ее нету присвоить фигуре свободную точку наружного квадрата правого нижнего угла   // # # #
                        }                                                                                                                                                                   // # [][]             
                    }                                                                                                                                                                       // # [][]
                    return true;
                }             
            }
        }

        if (sprite.getPosition().x > 0) {
            if (truth_value_field.getFlag(sprite.getPosition().x - 75, sprite.getPosition().y)) {    //a (движение влево)
               
                if (sprite.getPosition().x > end_point.x) {                                          //аналогично
                    int x = sprite.getPosition().x;
                    int y = sprite.getPosition().y;
                    truth_value_field.setFlag(x - 75, y, false);
                    truth_value_field.setFlag(x, y, true);
                    sprite.setPosition(x - 75, y);
                    if (enteringOpponentSquare(sprite)) {
                        if (coordinatePrioritySquare(truth_value_field) != sf::Vector2i(0, 0)) {                           
                            end_point = coordinatePrioritySquare(truth_value_field);
                        }
                        else {
                            end_point = coordinateOuterSquare(truth_value_field);
                        }
                    }
                    return true;
                }

            }
        }

        if (sprite.getPosition().x <= 450) {
            if (truth_value_field.getFlag(sprite.getPosition().x + 75, sprite.getPosition().y)) {     //d (движение вправо)
                
                if (sprite.getPosition().x < end_point.x) {                                           //аналогично
                    int x = sprite.getPosition().x;
                    int y = sprite.getPosition().y;
                    truth_value_field.setFlag(x + 75, y, false);
                    truth_value_field.setFlag(x, y, true);
                    sprite.setPosition(x + 75, y);

                    if (enteringOpponentSquare(sprite)) {
                        if (coordinatePrioritySquare(truth_value_field) != sf::Vector2i(0, 0)) {
                            end_point = coordinatePrioritySquare(truth_value_field);
                        }
                        else {
                            end_point = coordinateOuterSquare(truth_value_field);
                        }
                    }
                    return true;
                }

            }
        }

        if (sprite.getPosition().y <= 450) {
            if (truth_value_field.getFlag(sprite.getPosition().x, sprite.getPosition().y + 75)) {      //s (движение вниз)
                              
                if (sprite.getPosition().y < end_point.y) {                                            //аналогично
                    int x = sprite.getPosition().x;
                    int y = sprite.getPosition().y;
                    truth_value_field.setFlag(x, y + 75, false);
                    truth_value_field.setFlag(x, y, true);
                    sprite.setPosition(x, y + 75);
                    if (enteringOpponentSquare(sprite)) {
                        if (coordinatePrioritySquare(truth_value_field) != sf::Vector2i(0, 0)) {
                            end_point = coordinatePrioritySquare(truth_value_field);                           
                        }
                        else {
                            end_point = coordinateOuterSquare(truth_value_field);
                        }
                    }
                    return true;
                }
            }
        }

        return false;
}


bool BlackPawn::enteringOpponentSquare(sf::Sprite& sprite) {                            //функция вызывается когда фигура входит в наружный квадрат
                                                                                        //если это произошло вернет координаты этой точки
    if (sf::Vector2f(375, 375) == sprite.getPosition()) { return true; }
    if (sf::Vector2f(450, 375) == sprite.getPosition()) { return true; }
    if (sf::Vector2f(525, 375) == sprite.getPosition()) { return true; }
    if (sf::Vector2f(375, 450) == sprite.getPosition()) { return true; }
    if (sf::Vector2f(375, 525) == sprite.getPosition()) { return true; }

    return false;
}

sf::Vector2i BlackPawn::coordinatePrioritySquare(TruthValueField& truth_value_field) {  //функция проверяет состояние внутреннего квадрата
                                                                                        //если нет препятствий вернет координаты свободной точки
    if (truth_value_field.getFlag(525, 525)) return sf::Vector2i(525 ,525);  //8   
    if (truth_value_field.getFlag(450, 525)) return sf::Vector2i(450, 525);  //7
    if (truth_value_field.getFlag(525, 450)) return sf::Vector2i(525, 450);  //5
    if (truth_value_field.getFlag(450, 450)) return sf::Vector2i(450, 450);  //4

    return sf::Vector2i(0,0);
}

sf::Vector2i BlackPawn::coordinateOuterSquare(TruthValueField& truth_value_field) {     //функция проверяет состояние наружного квадрата
    if (truth_value_field.getFlag(525, 375)) return sf::Vector2i(525, 375);  //2        //если нет препятствий вернет координаты свободной точки
    if (truth_value_field.getFlag(450, 375)) return sf::Vector2i(450, 375);  //1
    if (truth_value_field.getFlag(375, 375)) return sf::Vector2i(375, 375);  //0          [0][1][2]
    if (truth_value_field.getFlag(375, 450)) return sf::Vector2i(375, 450);  //3          [3][4][5]    //расположение точек квадрата
    if (truth_value_field.getFlag(375, 525)) return sf::Vector2i(375, 525);  //6          [6][7][8]

    return sf::Vector2i(0,0);
}









