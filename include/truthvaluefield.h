#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class TruthValueField {
	const int WIDTH_CELL = 75;                                 //75 x 75 размер клетки
	const int HEIGHT_CELL = 75;
	bool field[8][8]{                                          //поле позволяющее узнать в какой точке находится препятствие
		{ true, true, true, true, true, true, true, true },    //если true - место свободно
		{ true, true, true, true, true, true, true, true },    //если false - место занято
		{ true, true, true, true, true, true, true, true },
		{ true, true, true, true, true, true, true, true },
		{ true, true, true, true, true, true, true, true },
		{ true, true, true, true, true, true, true, true },
		{ true, true, true, true, true, true, true, true },
		{ true, true, true, true, true, true, true, true }
	};
public:
	TruthValueField();
	inline void setFlag(int x, int y, bool value) { field[x / WIDTH_CELL][y / HEIGHT_CELL] = value;} //установить флаг по заданным координатам
	inline bool getFlag(int x, int y) const       { return field[x / WIDTH_CELL][y / HEIGHT_CELL]; } //получить флаг по координатам (true или false)                              
	inline int getWidthCell()const  { return WIDTH_CELL; }
	inline int getHeightCell()const { return HEIGHT_CELL; }
};

