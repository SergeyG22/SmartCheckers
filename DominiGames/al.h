#pragma once
#include <vector>
#include <list>
#include <random>
#include <algorithm>
#include <ctime>
#include "figure.h"
#include "blackpawn.h"

class Al {
    std::vector<Figure*>black_pawn { new BlackPawn{sf::Vector2f(0.0,0.0)},new BlackPawn{sf::Vector2f(75.0,0.0)},new BlackPawn{sf::Vector2f(150.0,0.0)},            //контейнер со всеми фигурами Al
                                     new BlackPawn{sf::Vector2f(0.0,75.0)},new BlackPawn{sf::Vector2f(75.0,75.0)},new BlackPawn{sf::Vector2f(150.0,75.0)},
                                     new BlackPawn{sf::Vector2f(0.0,150.0)},new BlackPawn{sf::Vector2f(75.0,150.0)},new BlackPawn{sf::Vector2f(150.0,150.0)},
    };
    std::list<sf::Vector2i>end_coordinates { sf::Vector2i(375,375),sf::Vector2i(450,375),sf::Vector2i(525,375),                                                   //контейнер с координатами квадрата 3x3 правого нижнего угла
                                             sf::Vector2i(375,450),sf::Vector2i(450,450),sf::Vector2i(525,450),
                                             sf::Vector2i(375,525),sf::Vector2i(450,525),sf::Vector2i(525,525)
    };
    std::vector<int>range{ 0,1,2,3,4,5,6,7,8 };                                                                                                                   //диапазон задающий числом случайную позицию
    int position = 0;
public:
    Al();
	std::vector<Figure*>getFigures();
    std::list<sf::Vector2i>getFinalSquareCoordinates();
    void setRandomCoordinates();
    void setRandomActivity();
    void random(std::vector<int>&);
};

