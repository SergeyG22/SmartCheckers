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
	sf::Sprite getSprite()const override;                             //�������� ������
	void setEndPoint(sf::Vector2i point) { end_point = point; };     //������������� ��� ������ �������� �����
	sf::Vector2i getEndPoint()const { return end_point; };           //�������� �������� ����� ��� �������� ������
	bool move(sf::Event& event, TruthValueField& truth_value_field); //�������
	void activate()override;                                         //������������ ������ (������������ - ��������� ������� ����� ������������.�� ������ � Disable)
	void deactivate()override;                                       //�������������� ������ 
	bool isActive() const override;                                  //��������� ���������� ������
	void disable();                                                  //��������� ��������� ������
	bool isEnable()const;                                            //��������� ��������� ������
	bool enteringOpponentSquare(sf::Sprite&);                        //���������� ����� ������ ������ � ������� 3x3 ������� ������� ���� ��������� �����
	sf::Vector2i coordinatePrioritySquare(TruthValueField&);         //���������� ����������� �������� 2x2 ������� ������� ���� ��������� �����
	sf::Vector2i coordinateOuterSquare(TruthValueField&);            //���������� �������� �������� ������� ������� ���� ��������� �����
};
