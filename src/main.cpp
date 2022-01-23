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



void initializingFlags(std::unique_ptr<Player>&player,std::unique_ptr<Al>&al, TruthValueField& truth_value_field) {           //инициализация абстрактного поля значениями true/false

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

void disableAlShapes(int& shape, Figure* figure) {                                                                             //последовательное отключение фигур Al по мере их достижения заданных точек
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



bool currentGameState(std::unique_ptr<Player>& player, std::unique_ptr<Al>& al) {        //текущее состояние игры (закончена/нет)
    int number_figures = 9;
    int end_for_player = 0;
    int end_for_al = 0;
    for (const Figure* figure : player->getFigures()) {
        sf::Vector2f current_position = figure->getSprite().getPosition();               //считает количество фигур игрока которые дошли до конечной точки
        for (const sf::Vector2f vec : player->getEndCoordinates()) {
            if (current_position == vec) {
                end_for_player++;
            }
        }
    }

    for (const Figure* figure : al->getFigures()) {
        sf::Vector2f current_position = figure->getSprite().getPosition();               //считает количество фигур al которые дошли до конечной точки
        for (const sf::Vector2i vec : al->getFinalSquareCoordinates()) {
            if (sf::Vector2i(current_position) == vec) {
                end_for_al++;
            }
        }
    }

    if ((end_for_al == number_figures) || (end_for_player == number_figures)) {          //если какая-то из сторон собрала ряд - вернуть false и закончить игру
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

            if (game_over){                                                                     //если false игра остановлена
                for (Figure* figure : player->getFigures()) {
                    if (figure->isActive()) {                                                   //если фигура активная и
                        if (figure->move(event, field_value)) {                                 //если фигуру можно двигать
                            int index = 0;
                            bool repeat = true;                                                 //повторить действие                                        
                            while (repeat && index < NUMBER_OF_SHAPES) {                        //цикл выполняется до тех пор пока все фигуры AL не  займут свои позиции                    
                                al->setRandomActivity();                                        //устанавливаем активность для случайной фигуры
                                for (Figure* figure : al->getFigures()) {                       //пробегаем по всем фигурам
                                    if (figure->isEnable()) {                                   //если фигура включена   (не достигла конечной точки)
                                        if (figure->isActive()) {                               //и если фигура активная (выделена мышкой)
                                            for (Figure* figure : al->getFigures()) {           //пробегаем по всем фигурам
                                                disableAlShapes(shape, figure);                  //и если достигла ли какаянибудь из них конечной точки выключаем фигуру                  
                                            }

                                            if (!figure->move(event, field_value)) {            //если фигуру нельзя сдвинуть                                                                    //то deactivate
                                                repeat = true;                                  //то начать поиск другой фигуры
                                                break;                                          //выйти из цикла
                                            }
                                            else {
                                                repeat = false;                                 //если не нашел, то не повторять
                                            }
                                        }
                                    }
                                }
                                for (Figure* figure : al->getFigures()) {
                                    figure->deactivate();                                      //после выполнения движения деактивируем все имеющиеся фигуры Al
                                }
                                index++;                                                       //устраняет зацикливание - если index == 8, значит вариантов перемещений нету
                            }


                            if (index == NUMBER_OF_SHAPES) {
                                for (Figure* figure : al->getFigures()) {
                                    for (sf::Vector2i vec : al->getFinalSquareCoordinates()) {                                         //получить все доступные координаты девяти квадратов правого нижнего угла (9x9)
                                        if ((sf::Vector2i)dynamic_cast<BlackPawn*>(figure)->getSprite().getPosition() != vec) {        //если какаято из фигур не заняла свою позицию
                                            for (sf::Vector2i square_coord : al->getFinalSquareCoordinates()) {                        //то получить новые координаты девяти квадратов
                                                if (field_value.getFlag(square_coord.x, square_coord.y)) {                             //проверить свободные ли они
                                                    dynamic_cast<BlackPawn*>(figure)->setEndPoint(square_coord);                       //если находит свободный то задать этой фигуре конечную точку
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
                        if (figure->getSprite().getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) {   //при нажатии мыши активирует выбранную фигуру
                            figure->activate();
                            for (Figure* others_figures : player->getFigures()) {
                                if (others_figures != figure) {
                                    others_figures->deactivate();                                         //все остальные деактивирует
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
                                                                                  
        game_over = currentGameState(player,al);                                                         //вернет false если игра окончена


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



