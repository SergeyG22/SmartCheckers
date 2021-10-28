#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class TruthValueField {
	const int WIDTH_CELL = 75;                                 //75 x 75 ������ ������
	const int HEIGHT_CELL = 75;
	bool field[8][8]{                                          //���� ����������� ������ � ����� ����� ��������� �����������
		{ true, true, true, true, true, true, true, true },    //���� true - ����� ��������
		{ true, true, true, true, true, true, true, true },    //���� false - ����� ������
		{ true, true, true, true, true, true, true, true },
		{ true, true, true, true, true, true, true, true },
		{ true, true, true, true, true, true, true, true },
		{ true, true, true, true, true, true, true, true },
		{ true, true, true, true, true, true, true, true },
		{ true, true, true, true, true, true, true, true }
	};
public:
	TruthValueField();
	inline void setFlag(int x, int y, bool value) { field[x / WIDTH_CELL][y / HEIGHT_CELL] = value;} //���������� ���� �� �������� �����������
	inline bool getFlag(int x, int y) const       { return field[x / WIDTH_CELL][y / HEIGHT_CELL]; } //�������� ���� �� ����������� (true ��� false)                              
	inline int getWidthCell()const  { return WIDTH_CELL; }
	inline int getHeightCell()const { return HEIGHT_CELL; }
};

