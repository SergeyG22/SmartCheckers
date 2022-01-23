#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <vector>
#include <set>
#include <memory>
#include "../include/truthvaluefield.h"
#include "../include/cursor.h"
#include "../include/player.h"
#include "../include/al.h"
#include "../include/figure.h"
#include "../include/whitepawn.h"
#include "../include/blackpawn.h"
#include "../include/gameboard.h"
#include "../include/cheesboard.h"



void initializingFlags(std::unique_ptr<Player>&player,std::unique_ptr<Al>&al, TruthValueField& truth_value_field) {           //������������� ������������ ���� ���������� true/false

    for (Figure* figure : player->getFigures()) {
        int x = figure->getSprite().getPosition().x;
        int y = figure->getSprite().getPosition().y;
        truth_value_field.setFlag(x, y, false);
    }
    
    for (Figure* figure : al->getFigures()) {
        int x = figure->getSprite().getPosition().x;
        int y = figure->getSprite().getPosition().y;
        truth_value_field.setFlag(x, y, false);
    }
}

void disableAlShapes(int& shape, Figure* figure) {                                                                             //���������������� ���������� ����� Al �� ���� �� ���������� �������� �����
    switch (shape) {
    case 0: {
        if (figure->getSprite().getPosition() == sf::Vector2f(525, 525)) {
            figure->disable();
            shape++;
        }
        break;
    }
    case 1: {
        if (figure->getSprite().getPosition() == sf::Vector2f(450, 525)) {
            figure->disable();
            shape++;
        }
        break;
    }

    case 2: {
        if (figure->getSprite().getPosition() == sf::Vector2f(525, 450)) {
            figure->disable();
            shape++;
        }
        break;
    }
    case 3: {
        if (figure->getSprite().getPosition() == sf::Vector2f(450, 450)) {
            figure->disable();
            shape++;
        }
        break;
    }
    case 4: {
        if (figure->getSprite().getPosition() == sf::Vector2f(375, 525)) {
            figure->disable();
            shape++;
        }
        break;
    }
    case 5: {
        if (figure->getSprite().getPosition() == sf::Vector2f(525, 375)) {
            figure->disable();
            shape++;
        }
        break;
    }

    case 6: {
        if (figure->getSprite().getPosition() == sf::Vector2f(375, 450)) {
            figure->disable();
            shape++;
        }
        break;
    }
    case 7: {
        if (figure->getSprite().getPosition() == sf::Vector2f(450, 375)) {
            figure->disable();
            shape++;
        }
        break;
    }
    case 8: {
        if (figure->getSprite().getPosition() == sf::Vector2f(375, 375)) {
            figure->disable();
            shape++;
        }
        break;
    }

    }

}



bool currentGameState(std::unique_ptr<Player>& player, std::unique_ptr<Al>& al) {        //������� ��������� ���� (���������/���)
    int number_figures = 9;
    int end_for_player = 0;
    int end_for_al = 0;
    for (const Figure* figure : player->getFigures()) {
        sf::Vector2f current_position = figure->getSprite().getPosition();               //������� ���������� ����� ������ ������� ����� �� �������� �����
        for (const sf::Vector2f vec : player->getEndCoordinates()) {
            if (current_position == vec) {
                end_for_player++;
            }
        }
    }

    for (const Figure* figure : al->getFigures()) {
        sf::Vector2f current_position = figure->getSprite().getPosition();               //������� ���������� ����� al ������� ����� �� �������� �����
        for (const sf::Vector2i vec : al->getFinalSquareCoordinates()) {
            if (sf::Vector2i(current_position) == vec) {
                end_for_al++;
            }
        }
    }

    if ((end_for_al == number_figures) || (end_for_player == number_figures)) {          //���� �����-�� �� ������ ������� ��� - ������� false � ��������� ����
        return false;
    }
    return true;
}

//###############################################
//################# [GUIDE]  ####################
//###############################################
//click left mouse button on shape = select current shape to make move
//Keyboard keys:
//w = move 'up'
//s = move 'down'
//a = move 'left'
//d = move 'right'
//###############################################


int main()
{

    sf::RenderWindow window(sf::VideoMode(600, 600), "cheesboard");

    Cursor cursor;
    TruthValueField field_value;

    auto cheesboard = std::unique_ptr<CheesBoard>();
    auto player = std::make_unique<Player>();
    auto al = std::make_unique<Al>();

    initializingFlags(player,al,field_value);
    const int NUMBER_OF_SHAPES = 8;
    int shape = 0;
    bool game_over = false;
    
    while (window.isOpen()) {

        sf::Event event;

        while (window.pollEvent(event)) {

            sf::Vector2i pos = sf::Mouse::getPosition(window);
            sf::Vector2f mouse_pos = window.mapPixelToCoords(pos);

            int x = ((int)mouse_pos.x / field_value.getWidthCell()) * field_value.getWidthCell();
            int y = ((int)mouse_pos.y / field_value.getHeightCell()) * field_value.getHeightCell();
            cursor.setPosition(x, y);

            if (game_over){                                                                     //���� false ���� �����������
                for (Figure* figure : player->getFigures()) {
                    if (figure->isActive()) {                                                   //���� ������ �������� �
                        if (figure->move(event, field_value)) {                                 //���� ������ ����� �������
                            int index = 0;
                            bool repeat = true;                                                 //��������� ��������                                        
                            while (repeat && index < NUMBER_OF_SHAPES) {                        //���� ����������� �� ��� ��� ���� ��� ������ AL ��  ������ ���� �������                    
                                al->setRandomActivity();                                        //������������� ���������� ��� ��������� ������
                                for (Figure* figure : al->getFigures()) {                       //��������� �� ���� �������
                                    if (figure->isEnable()) {                                   //���� ������ ��������   (�� �������� �������� �����)
                                        if (figure->isActive()) {                               //� ���� ������ �������� (�������� ������)
                                            for (Figure* figure : al->getFigures()) {           //��������� �� ���� �������
                                                disableAlShapes(shape, figure);                  //� ���� �������� �� ����������� �� ��� �������� ����� ��������� ������                  
                                            }

                                            if (!figure->move(event, field_value)) {            //���� ������ ������ ��������                                                                    //�� deactivate
                                                repeat = true;                                  //�� ������ ����� ������ ������
                                                break;                                          //����� �� �����
                                            }
                                            else {
                                                repeat = false;                                 //���� �� �����, �� �� ���������
                                            }
                                        }
                                    }
                                }
                                for (Figure* figure : al->getFigures()) {
                                    figure->deactivate();                                      //����� ���������� �������� ������������ ��� ��������� ������ Al
                                }
                                index++;                                                       //��������� ������������ - ���� index == 8, ������ ��������� ����������� ����
                            }


                            if (index == NUMBER_OF_SHAPES) {
                                for (Figure* figure : al->getFigures()) {
                                    for (sf::Vector2i vec : al->getFinalSquareCoordinates()) {                                         //�������� ��� ��������� ���������� ������ ��������� ������� ������� ���� (9x9)
                                        if ((sf::Vector2i)dynamic_cast<BlackPawn*>(figure)->getSprite().getPosition() != vec) {        //���� ������� �� ����� �� ������ ���� �������
                                            for (sf::Vector2i square_coord : al->getFinalSquareCoordinates()) {                        //�� �������� ����� ���������� ������ ���������
                                                if (field_value.getFlag(square_coord.x, square_coord.y)) {                             //��������� ��������� �� ���
                                                    dynamic_cast<BlackPawn*>(figure)->setEndPoint(square_coord);                       //���� ������� ��������� �� ������ ���� ������ �������� �����
                                                    break;
                                                }
                                            }
                                        }

                                    }


                                }

                            }




                        }

                    }
                }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.key.code == sf::Mouse::Left) {
                    for (Figure* figure : player->getFigures()) {
                        if (figure->getSprite().getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) {   //��� ������� ���� ���������� ��������� ������
                            figure->activate();
                            for (Figure* others_figures : player->getFigures()) {
                                if (others_figures != figure) {
                                    others_figures->deactivate();                                         //��� ��������� ������������
                                }
                            }
                        }
                    }
                }
            }
        }

                if (event.type == sf::Event::Closed) {
                    window.close();
                }

            
        }
                                                                                  
        game_over = currentGameState(player,al);                                                         //������ false ���� ���� ��������


        window.clear();
        window.draw(cheesboard->getSprite());

        for (const Figure* figure : player->getFigures()) {
            window.draw(figure->getSprite());
        }
        for (const Figure* figure : al->getFigures()) {
            window.draw(figure->getSprite());
        }

        window.draw(cursor);
        window.display();
        
    }

    return 0;
}



