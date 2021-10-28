#include "al.h"

std::vector<Figure*> Al::getFigures() {
	return black_pawn;
}

Al::Al() {
    setRandomCoordinates();                                      //перед стартом задать случайные координаты конечных точек случайным фигурам al
    random(range); 
}

void Al::setRandomCoordinates() {                                //устанавливает случайные координаты к которым будет стремится al
      std::vector<int>range{ 0,1,2,3,4,5,6,7,8 };
      random(range);
      for (int i = 0; i < black_pawn.size(); ++i) {
          auto it = end_coordinates.begin();
          std::advance(it, range[i]);
          sf::Vector2i end_point;
          end_point.x = (it)->x;
          end_point.y = (it)->y;
          dynamic_cast<BlackPawn*>(black_pawn[i])->setEndPoint(end_point);
      }
}


void Al::setRandomActivity() {                                    //устанавливает случайную активную фигуру в диапазоне (0,8)    
    black_pawn[position]->activate();   
    range.erase(range.begin());
    position++;
    
    if (range.empty()) {                                          //если контейнер пуст
        range = { 0,1,2,3,4,5,6,7,8 };                            //заполняем по новой
        random(range);                                            //генерируем новую последовательность
        position = 0;
    }
}

void Al::random(std::vector<int>&vec) {                           //генератор случайных чисел
    srand(time(0));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::random_shuffle(std::begin(vec), std::end(vec));          //перемешать
}

std::list<sf::Vector2i> Al::getFinalSquareCoordinates() {         //получить координаты квадратов нижнего правого угла (3x3)
    return end_coordinates;
}



















