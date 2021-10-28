#pragma once
#include <vector>
#include "figure.h"
#include "whitepawn.h"

class Player {
    std::vector<Figure*>white_pawn { new WhitePawn{sf::Vector2f(375.0,375.0)},new WhitePawn{sf::Vector2f(450.0,375.0)},new WhitePawn{sf::Vector2f(525.0,375.0)},   //вектор со всеми фигурами Player
                                     new WhitePawn{sf::Vector2f(375.0,450.0)},new WhitePawn{sf::Vector2f(450.0,450.0)},new WhitePawn{sf::Vector2f(525.0,450.0)},
                                     new WhitePawn{sf::Vector2f(375.0,525.0)},new WhitePawn{sf::Vector2f(450.0,525.0)},new WhitePawn{sf::Vector2f(525.0,525.0)},
    };
    std::vector<sf::Vector2f>end_coordinates { sf::Vector2f(0,0),sf::Vector2f(75,0),sf::Vector2f(150,0),
                                               sf::Vector2f(0,75),sf::Vector2f(75,75),sf::Vector2f(150,75),
                                               sf::Vector2f(0,150),sf::Vector2f(75,150),sf::Vector2f(150,150)
    };
public:
    std::vector<Figure*>getFigures();
    std::vector<sf::Vector2f>getEndCoordinates()const;
};
