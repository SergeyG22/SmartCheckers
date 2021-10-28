#pragma once
#include "figure.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>

class BlackPawn: public Figure {
	sf::Vector2f pos;
	sf::Vector2i end_point;
	bool activity = false;
	bool enable = true;
public:
	BlackPawn(sf::Vector2f);
	virtual void draw(sf::RenderTarget&, sf::RenderStates)const;
	sf::Sprite getSprite()const override;                             //получить спрайт
	void setEndPoint(sf::Vector2i point) { end_point = point; };     //устанавливает для фигуры конечную точку
	sf::Vector2i getEndPoint()const { return end_point; };           //получить конечную точку для заданной фигуры
	bool move(sf::Event& event, TruthValueField& truth_value_field); //двигать
	void activate()override;                                         //активировать фигуру (активировать - состояние которое можно восстановить.Не путать с Disable)
	void deactivate()override;                                       //деактивировать фигуру 
	bool isActive() const override;                                  //проверить активность фигуры
	void disable();                                                  //полностью отключить фигуру
	bool isEnable()const;                                            //проверить состояние фигуры
	bool enteringOpponentSquare(sf::Sprite&);                        //вызывается когда фигура входит в квадрат 3x3 правого нижнего угла шахматной доски
	sf::Vector2i coordinatePrioritySquare(TruthValueField&);         //координаты внутреннего квадрата 2x2 правого нижнего угла шахматной доски
	sf::Vector2i coordinateOuterSquare(TruthValueField&);            //координаты внешнего квадрата правого нижнего угла шахматной доски
};
