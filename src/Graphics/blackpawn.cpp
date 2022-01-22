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

sf::Sprite BlackPawn::getSprite()const {  //�������� ������
	return sprite;
}

void BlackPawn::activate() {              //������������ ������
    activity = true;
}

void BlackPawn::deactivate() {           //�������������� ������
    activity = false;
}

bool BlackPawn::isActive()const {        //������� ��������� ����������
    return activity;
}

void BlackPawn::disable() {              //��������� ������
    enable = false;
}

bool BlackPawn::isEnable()const {        //������� ���������
    return enable;
}


bool BlackPawn::move(sf::Event& event, TruthValueField& truth_value_field) {
        if (sprite.getPosition().y >= 75) {
            if (truth_value_field.getFlag(sprite.getPosition().x, sprite.getPosition().y - 75)) {    //w (�������� �����)
                              
                if (sprite.getPosition().y > end_point.y) {
                    int x = sprite.getPosition().x;
                    int y = sprite.getPosition().y;
                    truth_value_field.setFlag(x, y - 75, false);
                    truth_value_field.setFlag(x, y, true);
                    sprite.setPosition(x, y - 75);
            
                    if (enteringOpponentSquare(sprite)) {                                         //���� ������ ����� � ������� 3x3 ������� ������� ����
                        if (coordinatePrioritySquare(truth_value_field) != sf::Vector2i(0, 0)) {  //� ������������ ��������� ����������                                                    //[][][]
                            end_point = coordinatePrioritySquare(truth_value_field);              //����� ��������� ����� ����������� �������� 2x2 ������� ������� ����                    //[] # #
                        }                                                                         //� ��������� �� ������� ������                                                          //[] # #
                        else {                         
                            end_point = coordinateOuterSquare(truth_value_field);                 //���� �� ���� ��������� ������ ��������� ����� ��������� �������� ������� ������� ����   // # # #
                        }                                                                                                                                                                   // # [][]             
                    }                                                                                                                                                                       // # [][]
                    return true;
                }             
            }
        }

        if (sprite.getPosition().x > 0) {
            if (truth_value_field.getFlag(sprite.getPosition().x - 75, sprite.getPosition().y)) {    //a (�������� �����)
               
                if (sprite.getPosition().x > end_point.x) {                                          //����������
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
            if (truth_value_field.getFlag(sprite.getPosition().x + 75, sprite.getPosition().y)) {     //d (�������� ������)
                
                if (sprite.getPosition().x < end_point.x) {                                           //����������
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
            if (truth_value_field.getFlag(sprite.getPosition().x, sprite.getPosition().y + 75)) {      //s (�������� ����)
                              
                if (sprite.getPosition().y < end_point.y) {                                            //����������
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


bool BlackPawn::enteringOpponentSquare(sf::Sprite& sprite) {                            //������� ���������� ����� ������ ������ � �������� �������
                                                                                        //���� ��� ��������� ������ ���������� ���� �����
    if (sf::Vector2f(375, 375) == sprite.getPosition()) { return true; }
    if (sf::Vector2f(450, 375) == sprite.getPosition()) { return true; }
    if (sf::Vector2f(525, 375) == sprite.getPosition()) { return true; }
    if (sf::Vector2f(375, 450) == sprite.getPosition()) { return true; }
    if (sf::Vector2f(375, 525) == sprite.getPosition()) { return true; }

    return false;
}

sf::Vector2i BlackPawn::coordinatePrioritySquare(TruthValueField& truth_value_field) {  //������� ��������� ��������� ����������� ��������
                                                                                        //���� ��� ����������� ������ ���������� ��������� �����
    if (truth_value_field.getFlag(525, 525)) return sf::Vector2i(525 ,525);  //8   
    if (truth_value_field.getFlag(450, 525)) return sf::Vector2i(450, 525);  //7
    if (truth_value_field.getFlag(525, 450)) return sf::Vector2i(525, 450);  //5
    if (truth_value_field.getFlag(450, 450)) return sf::Vector2i(450, 450);  //4

    return sf::Vector2i(0,0);
}

sf::Vector2i BlackPawn::coordinateOuterSquare(TruthValueField& truth_value_field) {     //������� ��������� ��������� ��������� ��������
    if (truth_value_field.getFlag(525, 375)) return sf::Vector2i(525, 375);  //2        //���� ��� ����������� ������ ���������� ��������� �����
    if (truth_value_field.getFlag(450, 375)) return sf::Vector2i(450, 375);  //1
    if (truth_value_field.getFlag(375, 375)) return sf::Vector2i(375, 375);  //0          [0][1][2]
    if (truth_value_field.getFlag(375, 450)) return sf::Vector2i(375, 450);  //3          [3][4][5]    //������������ ����� ��������
    if (truth_value_field.getFlag(375, 525)) return sf::Vector2i(375, 525);  //6          [6][7][8]

    return sf::Vector2i(0,0);
}









